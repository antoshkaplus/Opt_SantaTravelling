
#include "Improvement.h"

typedef LocalSolutionControl::Edge Edge;

Improvement::Improvement(char* fnamecities, char* fnameapprox, char* fnamenear){
  FILE *file = fopen(fnamecities, "r");
  readCities(file, &ps);
  fclose(file);
  n = (Size)ps.size();
  file = fopen(fnameapprox, "r");
  VSize paths[2];
  readApprox(file, paths);
  fclose(file);
  sc.set(n);
  sc.fill(paths[0], paths[1]);
  file = fopen(fnamenear, "r");
  readNearest(file, &near);
  kLast = (Size)near[0].size();
  fclose(file);
  computeLengths(ps, paths, d);
}

void Improvement::improve(){
  Size u;
  //while((u = twoOpt(n)) > 0) printf("%u\n",u);
  while ((u = threeLocalOpt(n)) > 0) printf("%u\n",u);
}

bool Improvement::oneOptCondition(Size i, Size i1, Size i2, Size j, Size j1, Size j2, char k, double& D){
  char notK = (k == 0) ? 1 : 0;
  bool res = false;
  Size iin, jin;
  if(j1 == i){
    jin = j2;
    iin = (j == i1 ? i2 : i1);
    res = true;
  }else if(j2 == i){
    jin = j1;
    iin = (j == i1 ? i2 : i1);
    res = true;
  }
  /*  Preinstalled in twoOpt
  if (res && sc.notIn(iin, j, notK) && sc.notIn(i, jin, notK) &&
  (D = ps[iin].distance(ps[j])+ps[i].distance(ps[jin])
  -ps[iin].distance(ps[i])-ps[j].distance(ps[jin])) < 0.) {
    assert(!sc.notIn(i, iin, k) && !sc.notIn(i, j, k) && !sc.notIn(j, jin, k));
    sc.exchange(iin,i,j,jin,k);
    return true;
  }
  */
  if(!res){
    if(j1 == i1){
      iin = i2;
      jin = j1;
      res = true;
    }else if(j1 == i2){
      iin = i1;
      jin = j1;
      res = true;
    }else if(j2 == i1){
      iin = i2;
      jin = j2;
      res = true;
    }else if(j2 == i2){
      iin = i1;
      jin = j2;
      res = true;
    }
    /* Preinstalled in twoOpt
    if (res && sc.notIn(iin, jin, notK) && sc.notIn(i, j, notK) &&
    (D = ps[iin].distance(ps[jin])+ps[i].distance(ps[j])
    -ps[iin].distance(ps[i])-ps[jin].distance(ps[j])) < 0.) {
      assert(!sc.notIn(i, iin, k) && !sc.notIn(i, jin, k) && !sc.notIn(j, jin, k));
      sc.exchange(iin,i,jin,j,k);
      return true;
    }
    */
  }
  if(!res){
    if (sc.notIn(i, j1, j, notK) && sc.notIn(i1, i2, notK) &&
    (D = ps[i1].distance(ps[i2])+ps[i].distance(ps[j1])+ps[i].distance(ps[j])
    -ps[i].distance(ps[i1])-ps[i].distance(ps[i2])-ps[j].distance(ps[j1]) < 0.)) {
      sc.rearrange(i,i1,i2,j,j1,k);
      return true;
    }
    if (sc.notIn(i, j2, j, notK) && sc.notIn(i1, i2, notK) &&
    (D = ps[i1].distance(ps[i2])+ps[i].distance(ps[j2])+ps[i].distance(ps[j])
    -ps[i].distance(ps[i1])-ps[i].distance(ps[i2])-ps[j].distance(ps[j2]) < 0.)) {
      sc.rearrange(i,i1,i2,j,j2,k);
      return true;
    }
  }
  return false;
}

Size Improvement::twoOpt(Size maxMoves){
  // compute who begins show
  char b0 = 0, b1 = 1;
  Size goodMoves = 0, moves = 0, a;
  const Size *aa;
  // some usefull variables
  Size i1, i2, j1, j2;
  double D, d12;
  while (moves < maxMoves) {
    if (d[b0] < d[b1]) {
      swap(b0,b1);
    }
    moves += 1;
    i2 = rand()%n;
    aa = sc.get(i2, b0);
    i1 = aa[0];
    Point &p1 = ps[i1];
    Point &p2 = ps[i2];
    d12 = p1.distance(p2);
    j1 = i2;
    j2 = aa[1];
    for(;;) {
      a = j1;
      aa = sc.get(j2, b0);
      j1 = j2;
      j2 = (aa[0] == a ? aa[1] : aa[0]);
      if (j2 == i1) break;
      if (sc.notIn(i1, j1, b1) && sc.notIn(i2, j2, b1) &&
      (D = p1.distance(ps[j1])+p2.distance(ps[j2])
      -d12-ps[j1].distance(ps[j2]) < 0.)) {
        sc.regroup(i1, i2, j1, j2, b0);
        d[b0] += D;
        goodMoves += 1;
        break;
      }
    }
  }
  return goodMoves;
}

Size Improvement::oneOpt(Size maxMoves){
  // compute who begins show
  char b0 = 0, b1 = 1;
  if (d[b0] < d[b1]) {
    swap(b0,b1);
  }
  Size moves = 0, a;
  const Size *aa;
  // some usefull variables
  Size icur, istart, iprev, inext;
  double D;
  char bad = 0;
  bool good;
  while (bad != 2 && moves < maxMoves) {
    good = false;
    istart = icur = rand()%n;
    aa = sc.get(icur, b0);
    iprev = aa[0];
    inext = aa[1];
    do {
      for(VSizeIt it = near[icur].begin(); it != near[icur].end(); ++it){
        a = *it;
        aa = sc.get(a, b0);
        if (oneOptCondition(icur, iprev, inext, a, aa[0], aa[1], b0, D)){
          d[b0] += D;
          moves += 1;
          good = true;
          icur = iprev;
          if(d[b0] < d[b1]){
            swap(b0,b1);
            goto loop;
          }
          break;
        }
      }
      aa = sc.get(inext, b0);
      iprev = icur;
      icur = inext;
      assert(aa[0] == iprev || aa[1] == iprev);
      inext = (aa[0] == iprev ? aa[1] : aa[0]);
    } while (icur != istart);
  loop:
    if(!good){
      swap(b0,b1);
      bad++;
    }else{
      bad = 0;
    }
  }
  return moves;
}

bool Improvement::threeOptSupport(LocalSolutionControl &lsc, VPoint &ps, double d[2], Size center){
  // compute who begins show
  char b0 = 0, b1 = 1;
  if (d[b0] < d[b1]) {
    swap(b0,b1);
  }
  bool good = false;
  char r;
  bool jb, kb;
  Size i1, i2, j1, j2, k1, k2;
  for(char q = 0; q < 2; ++q){
    Edge *e = lsc.get(center, q);
    for(char ei = 0; ei < 2; ++ei){
      if(e->changeable[ei]){
        i1 = center;
        i2 = e->ind[ei];
        // init js
        e = lsc.get(i2, q);
        r = (e->ind[0] == i1 ? 1 : 0);
        j1 = e->ind[r];
        e = lsc.get(j1, q);
        r = (e->ind[0] == i2 ? 1 : 0);
        jb = e->changeable[r];
        j2 = e->ind[r];
        double D;
        while (j2 != k1){
          // init ks
          e = lsc.get(j2, q);
          r = (e->ind[0] == j1 ? 1 : 0);
          k1 = e->ind[r];
          e = lsc.get(k1, q);
          r = (e->ind[0] == j2 ? 1 : 0);
          kb = e->changeable[r];
          k2 = e->ind[r];
          while (k2 != i1) {
            if (jb && kb){
              double Dold = ps[i1].distance(ps[i2])+ps[j1].distance(ps[j2])+ps[k1].distance(ps[k2]);
              if (lsc.notIn(j1, k1, b1) && lsc.notIn(j2, i1, b1) && lsc.notIn(k2, i2, b1) &&
                  (D = ps[j1].distance(ps[k1])+ps[j2].distance(ps[i1])+ps[k2].distance(ps[i2])-Dold) < 0.) {
                // regroup
              }
              if (lsc.notIn(j1, k2, b1) && lsc.notIn(i1, j2, b1) && lsc.notIn(k1, i2, b1) &&
                  (D = ps[j1].distance(ps[k2])+ps[j2].distance(ps[i1])+ps[k1].distance(ps[i2])-Dold) < 0.) {
                // regroup
              }
              if (lsc.notIn(j1, k2, b1) && lsc.notIn(i1, k1, b1) && lsc.notIn(j2, i2, b1) &&
                  (D = ps[j1].distance(ps[k2])+ps[i1].distance(ps[k1])+ps[j2].distance(ps[i2])-Dold) < 0.){
                // regroup
              }
            }
            // iterate ks
            e = lsc.get(k2, q);
            r = (e->ind[0] == k1 ? 1 : 0);
            kb = e->changeable[r];
            k1 = k2;
            k2 = e->ind[r];
          }
          // iterate js
          e = lsc.get(j2, q);
          r = (e->ind[0] == j1 ? 1 : 0);
          jb = e->changeable[r];
          j1 = j2;
          j2 = e->ind[r];
        }
      }
    }
    swap(b0, b1);
  }
  return good;
}

Size Improvement::threeLocalOpt(Size maxMoves){
  Size goodMoves = 0;
  const Size *a;
  Size icur, inext;
  for (Size q = 0; q < maxMoves; ++q) {
    VSize p[2];
    p[0].resize(n);
    p[1].resize(n);
    Size center = rand()%n;
    for(char k = 0; k < 2; ++k){
      VSize &pp = p[k];
      icur = center;
      inext = sc.get(center, k)[1];
      for(Size i = 0; i < n; ++i){
        pp[icur] = i;
        a = sc.get(inext, k);
        if (icur == a[0]) {
          icur = inext;
          inext = a[1];
        }else{
          icur = inext;
          inext = a[0];
        }
      }
    }
    VSize iNear(near[center]);
    iNear.push_back(center);
    Size nNear = (Size)iNear.size();
    VPoint pNear(nNear);
    for (Size i = 0; i < nNear; ++i) {
      pNear[i] = ps[iNear[i]];
    }
    VIndex v[2];
    v[0].resize(nNear); // +1 for the center
    v[1].resize(nNear);
    for(char k = 0; k < 2; ++k){
      VIndex &vv = v[k];
      VSize &pp = p[k];
      Size i = 0;
      for(; i < nNear; ++i){
        vv[i].ind = i;
        vv[i].orderInd = pp[iNear[i]];
      }
      sort(vv.begin(), vv.end(), Index::compByOrderInd);
    }
    LocalSolutionControl lsc(nNear);
    for(char k = 0; k < 2; ++k){
      VIndex &vv = v[k];
      Index *r1, *r2;
      bool changeable;
      Size i = 0;
      for(; i < nNear-1; ++i){
        r1 = &vv[i];
        r2 = &vv[i+1];
        changeable = (r2->orderInd-r1->orderInd > 1 ? false : true);
        lsc.add(r1->ind, r2->ind, changeable, k);
      }
      r1 = &vv[i];
      r2 = &vv[0];
      changeable = (r2->orderInd-r1->orderInd > 1 ? false : true);
      lsc.add(r1->ind, r2->ind, changeable, k);
    }
    if(threeOptSupport(lsc, pNear, d, nNear)) ++goodMoves;
  }
  return goodMoves;
}

void Improvement::output(char* fnamesolution){
  FILE *file = fopen(fnamesolution, "w");
  VSize paths[2];
  sc.fillPaths(paths, paths+1);
  writeSolution(file, paths);
  fclose(file);
}






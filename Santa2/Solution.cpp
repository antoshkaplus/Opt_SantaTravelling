//
//  Solution.cpp
//  Santa2
//
//  Created by Anton Logunov on 1/9/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#include "Solution.h"



double Solution::cost(Size i, Size i1, Size i2){
  return weightedDistance(i,i1)+weightedDistance(i,i2)-weightedDistance(i1,i2);
}

// returns index of array of indexes of points
SSetIt Solution::nearest(Size i1, Size i2, char k){
  char notK = (k == 0 ? 1 : 0);
  SSet &v = left[k];
  SSetIt minQ = v.end();
  double D, minD = DBL_MAX;
  for(SSetIt it = v.begin(); it != v.end(); ++it){
    if((D = cost(*it, i1, i2)) < minD && sc.notIn(*it, i1, i2, notK)){
      minD = D;
      minQ = it;
    }
  }
  return minQ;
}

SSetIt Solution::nearest(Size i, char k){
  char notK = (k == 0 ? 1 : 0);
  SSet &v = left[k];
  SSetIt minQ = v.end();
  double D, minD = DBL_MAX;
  for(SSetIt it = v.begin(); it != v.end(); ++it){
    if((D = ps[*it].distance(ps[i])) < minD && sc.notIn(*it, i, notK)){
      minD = D;
      minQ = it;
    }
  }
  return minQ;
}

void Solution::approximate(){
  Size q, i, i1, i2, i3;
  char k;
  Entry e;
  bool again = false;
  SSetIt it;
  do{
    VEntry heap[2];
    sc.set(n);
    d[0] = 0.;
    d[1] = 0.;
    for(k = 0; k < 2; ++k){
      SSet &v = left[k];
      v.clear();
      for(i = 0; i < n; ++i){
        v.insert(i);
      }
      // making simplexes
      i1 = *(it = v.find(rand()%n));
      v.erase(it);
      i2 = *(it = nearest(i1, k));
      v.erase(it);
      sc.add(i1, i2, k);
      d[k] += ps[i1].distance(ps[i2]);
      i3 = *(it = nearest(i1, i2, k));
      v.erase(it);
      sc.add(i1, i3, k);
      d[k] += ps[i1].distance(ps[i3]);
      sc.add(i2, i3, k);
      d[k] += ps[i2].distance(ps[i3]);
      // adding entries to heap
      VEntry &h = heap[k];
      h.resize(3);
      Size a[3][2] = {{i1,i2},{i2,i3},{i1,i3}};
      for(q = 0; q < 3; ++q){
        it = nearest(i1, i2, k);
        h[q].set(cost(*it, a[q][0], a[q][1]), *it, a[q][0], a[q][1]);
      }
      make_heap(h.begin(), h.end());
    }
    char b0 = 0, b1 = 1;
    for(q = 0; q < n-3; ++q){
      for (k = 0; k < 2; ++k) {
        VEntry &h = heap[b0];
        SSet &v = left[b0];
        while (!h.empty()) {
          pop_heap(h.begin(), h.end());
          e = h[h.size()-1];
          h.pop_back();
          i1 = e.i1;
          i2 = e.i2;
          i = e.i;
          if (v.find(i) == v.end() || !sc.notIn(i, i1, i2, b1)) {
            it = nearest(i1, i2, b0);
            if (it != v.end()) {
              e.cost = cost(*it, i1, i2);
              e.i = *it;
              h.push_back(e);
              push_heap(h.begin(), h.end());
            }
          }else break;
        }
        if(h.empty()){
          again = true;
          goto loop;
        }
        sc.extend(i, i1, i2, b0);
        d[b0] += ps[i].distance(ps[i1])+
                 ps[i].distance(ps[i2])-
                 ps[i1].distance(ps[i2]);
        v.erase(v.find(i));
        it = nearest(i, i1, b0);
        if(it != v.end()){
          e.set(cost(*it, i, i1), *it, i, i1);
          h.push_back(e);
          push_heap(h.begin(), h.end());
        }
        it = nearest(i, i2, b0);
        if(it != v.end()){
          e.set(cost(*it, i, i2), *it, i, i2);
          h.push_back(e);
          push_heap(h.begin(), h.end());
        }
        swap(b0, b1);
      }
      if(d[b0] < d[b1]) swap(b0, b1);
    }
  loop:
    if(again) printf("again...\n");
  }while(again);
}

Size Solution::twoOpt(Size maxMoves){
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

void Solution::update(){
  Index im;
  Size j1, j2;
  VSize p[2];
  sc.fillPaths(&p[0], &p[1]);
  for(char k = 0; k < 2; ++k){
    VSize &pp = p[k];
    for(Size i = 0; i < n-1; ++i){
      j1 = pp[i];
      j2 = pp[i+1];
      if(j1 > j2) swap(j1,j2);
      im = (Index)n*j1+j2;
      if(map.find(im) != map.end()) ++map[im];
      else map[im] = 1;
    }
  }
}








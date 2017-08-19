//
//  Algorithm.cpp
//  Santa
//
//  Created by Anton Logunov on 1/4/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#include "Approximation.h"


typedef Approximation::Entry Entry;
typedef Approximation::SetIt SetIt;

bool operator<(const Entry& e1, const Entry& e2){
  return e1.cost > e2.cost;
}

void Entry::set(double cost, Size i, Size i1, Size i2){
  this->cost = cost;
  this->i = i;
  this->i1 = i1;
  this->i2 = i2;
}

double Approximation::cost(Size i, Size i1, Size i2){
  return ps[i].distance(ps[i1])+ps[i].distance(ps[i2])-ps[i1].distance(ps[i2]);
}

// returns index of array of indexes of points
SetIt Approximation::nearest(Size i1, Size i2, char k){
  char notK = (k == 0 ? 1 : 0);
  Set &v = left[k];
  SetIt minQ = v.end();
  double D, minD = DBL_MAX;
  for(SetIt it = v.begin(); it != v.end(); ++it){
    if((D = cost(*it, i1, i2)) < minD && sc.notIn(*it, i1, i2, notK)){
      minD = D;
      minQ = it;
    }
  }
  return minQ;
}

SetIt Approximation::nearest(Size i, char k){
  char notK = (k == 0 ? 1 : 0);
  Set &v = left[k];
  SetIt minQ = v.end();
  double D, minD = DBL_MAX;
  for(SetIt it = v.begin(); it != v.end(); ++it){
    if((D = ps[*it].distance(ps[i])) < minD && sc.notIn(*it, i, notK)){
      minD = D;
      minQ = it;
    }
  }
  return minQ;
}

void Approximation::solve(){
  Size q, i, i1, i2, i3;
  char k;
  Entry e;
  bool again = false;
  SetIt it;
  do{
    double d[2] = {0., 0.};
    VEntry heap[2];
    sc.set(n);
    d[0] = 0.;
    d[1] = 0.;
    for(k = 0; k < 2; ++k){
      Set &v = left[k];
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
        Set &v = left[b0];
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

void Approximation::output(char *fnameapprox){
  FILE *file = fopen(fnameapprox, "w");
  VSize paths[2];
  sc.fillPaths(paths, paths+1);
  writeApprox(file, paths);
  fclose(file);
}


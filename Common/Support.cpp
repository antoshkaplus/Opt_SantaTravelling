//
//  Support.cpp
//  Santa
//
//  Created by Anton Logunov on 1/5/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#include "Support.h"

const char *root = "/Users/antoshkaplus/Documents/Programming/Contests/Kaggle/SantaProblem/Santa/Results/";


void Point::set(Int x, Int y){
  this->x = x;
  this->y = y;
}

double Point::distance(Point &p){
  return sqrt(double((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y)));
}

int Index::compByOrderInd(Index& i1, Index& i2){
  return i1.orderInd - i2.orderInd;
}

void readCities(FILE* file, VPoint* ps){
  Point p;
  VPoint &psr = *ps;
  Size n;
  fscanf(file, "%u", &n);
  psr.resize(n);
  for(Size i = 0; i < n; ++i){
    fscanf(file, "%d %d", &psr[i].x, &psr[i].y);
  }
}

void readNearest(FILE* file, VVSize* inds){
  VVSize &indsr = *inds;
  Size n, k;
  fscanf(file, "%u %u", &n, &k);
  indsr.resize(n);
  for(Size i = 0; i < n; ++i){
    VSize &v = indsr[i];
    v.resize(k);
    for(Size j = 0; j < k; ++j){
      fscanf(file,"%u",&v[j]);
    }
  }
}

void writeNearest(FILE* file, VVSize& inds){
  Size n = (Size)inds.size(), k = (Size)inds[0].size();
  fprintf(file, "%u %u\n", n, k);
  for(Size i = 0; i < n; ++i){
    VSize &v = inds[i];
    for(Size j = 0; j < k; ++j){
      fprintf(file, "%u ", v[j]);
    }
    fprintf(file, "\n");
  }
}

void readApprox(FILE* file, VSize paths[2]){
  VSize &p1 = paths[0];
  VSize &p2 = paths[1];
  Size n;
  fscanf(file, "%u", &n);
  p1.resize(n);
  p2.resize(n);
  for(Size i = 0; i < n; ++i){
    fscanf(file, "%u,%u", &p1[i], &p2[i]);
  }
}

void writeApprox(FILE *file, VSize paths[2]){
  VSize &p1 = paths[0];
  VSize &p2 = paths[1];
  Size n = (Size)p1.size();
  fprintf(file, "%u\n", n);
  for(Size i = 0; i < n; ++i){
    fprintf(file, "%u,%u\n", p1[i], p2[i]);
  }
}

void writeSolution(FILE *file, VSize paths[2]){
  VSize &p1 = paths[0];
  VSize &p2 = paths[1];
  Size n = (Size)p1.size();
  for(Size i = 0; i < n; ++i){
    fprintf(file, "%u,%u\n", p1[i], p2[i]);
  }
}

void computeLengths(VPoint &ps, VSize paths[2], double d[2]){
  VSize &p1 = paths[0];
  VSize &p2 = paths[1];
  Size n = (Size)p1.size();
  for(Size i = 0; i < n-1; ++i){
    d[0] += ps[p1[i]].distance(ps[p1[i+1]]);
    d[1] += ps[p2[i]].distance(ps[p2[i+1]]);
  }
  d[0] += ps[p1[0]].distance(ps[p1[n-1]]);
  d[1] += ps[p2[0]].distance(ps[p2[n-1]]);
}















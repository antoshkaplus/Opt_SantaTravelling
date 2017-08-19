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

bool operator<(const Entry& e1, const Entry& e2){
  return e1.cost > e2.cost;
}

void Entry::set(double cost, Size i, Size i1, Size i2){
  this->cost = cost;
  this->i = i;
  this->i1 = i1;
  this->i2 = i2;
}

void readCities(FILE* file, VPoint* ps){
  Point p;
  VPoint &psr = *ps;
  Size n;
  fscanf(file, "%u", &n);
  psr.resize(n);
  for(Size i = 0; i < n; ++i){
    fscanf(file, "%lf %lf", &psr[i].x, &psr[i].y);
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















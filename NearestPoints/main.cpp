//
//  main.cpp
//  NearestPoints
//
//  Created by Anton Logunov on 1/3/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#include <iostream>

#include "Support.h"

struct Comp {
  VPoint &ps;
  Size i;
  Comp(VPoint &ps) : ps(ps){}
  void set(Size i){
    this->i = i;
  }
  bool operator()(Size i1, Size i2){
    return ps[i].distance(ps[i1]) < ps[i].distance(ps[i2]);
  }
};


int main(int argc, const char * argv[])
{
  char path[200];
  strcpy(path, root);
  char name[20];
  scanf("%s",name);
  Size k;
  scanf("%u",&k);
  strcat(path, name);
  char in[200];
  strcpy(in, path);
  strcat(in, ".pts");
  FILE *fin = fopen(in, "r");
  VPoint ps;
  readCities(fin, &ps);
  fclose(fin);
  Comp comp(ps);
  VSize a(ps.size());
  for(Size i = 0; i < a.size(); ++i){
    a[i] = i;
  }
  VVSize s(ps.size());
  for(Size i = 0; i < s.size(); ++i){
    comp.set(i);
    partial_sort(a.begin(), a.begin()+1, a.end(), comp);
    s[i].resize(k);
    for(Size j = 1; j < k+1; ++j){
      s[i][j-1] = a[j];
    }
  }
  char out[200];
  strcpy(out, path);
  strcat(out, ".near");
  FILE *fout = fopen(out, "w");
  writeNearest(fout, s);
  fclose(fout);
  return 0;
}


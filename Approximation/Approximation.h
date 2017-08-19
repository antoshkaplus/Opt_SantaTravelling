//
//  AlgoInsertion.h
//  Santa
//
//  Created by Anton Logunov on 1/3/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#ifndef Santa_Algorithm_h
#define Santa_Algorithm_h

#include <cfloat>
#include <set>
#include <cmath>

#include "Support.h"
#include "SolutionControl.h"

using namespace std;

struct Approximation {
  struct Entry{
    double cost;
    Size i, i1, i2;
    friend bool operator<(const Entry &e1, const Entry &e2);
    void set(double cost, Size i, Size i1, Size i2);
  };
  
  typedef vector<Entry> VEntry;
  typedef VSize::iterator VSizeIter;
  typedef set<Size> Set;
  typedef Set::iterator SetIt;
  
  VPoint ps;
  SolutionControl sc;
  Size n;
  Set left[2]; // here for using nearest
  double d[2];
  
  Approximation(char *fnamecit){
    FILE *file = fopen(fnamecit, "r");
    readCities(file, &ps);
    n = (Size)ps.size();
  }
  void output(char *fnameapprox);
  void solve();
  double cost(Size i, Size i1, Size i2);
  SetIt nearest(Size i1, Size i2, char k);
  SetIt nearest(Size i, char k);
};

#endif

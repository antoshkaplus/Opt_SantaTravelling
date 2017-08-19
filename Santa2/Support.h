//
//  Support.h
//  Santa
//
//  Created by Anton Logunov on 1/5/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#ifndef __Santa__Support__
#define __Santa__Support__

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <cfloat>

using namespace std;

extern const char *root;

typedef double Int;
typedef uint32_t Size;
typedef uint64_t Index;


struct Point{
public:
  Int x, y;
  Point(){}
  Point(Int x, Int y) : x(x), y(y){}
  void set(Int x, Int y);
  double distance(Point &p);
};

struct Entry{
  double cost;
  Size i, i1, i2;
  friend bool operator<(const Entry &e1, const Entry &e2);
  void set(double cost, Size i, Size i1, Size i2);
};


typedef vector<Point> VPoint;
typedef vector<Size> VSize;
typedef VSize::iterator VSizeIt;
typedef vector<bool> VBool;
typedef vector<Point>::iterator VPointIt;
typedef unordered_map<Index, Size> Map;
typedef set<Size> SSet;
typedef SSet::iterator SSetIt;
typedef vector<Entry> VEntry;

void readCities(FILE* file, VPoint* ps);
void readApprox(FILE* file, VSize paths[2]);
void writeApprox(FILE *file, VSize path[2]);
void writeSolution(FILE *file, VSize path[2]);
void computeLengths(VPoint &ps, VSize paths[2], double d[2]);


#endif /* defined(__Santa__Support__) */

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

using namespace std;

extern const char *root;

typedef int32_t Int;
typedef uint32_t Size;


struct Point{
public:
  Int x, y;
  Point(){}
  Point(Int x, Int y) : x(x), y(y){}
  void set(Int x, Int y);
  double distance(Point &p);
};

struct Index{
public:
  Size ind, orderInd;
  static int compByOrderInd(Index& i1, Index& i2);
};

typedef vector<Point> VPoint;
typedef vector<Size> VSize;
typedef vector<VSize> VVSize;
typedef VSize::iterator VSizeIt;
typedef vector<bool> VBool;
typedef vector<Point>::iterator VPointIt;
typedef vector<Index> VIndex;
typedef set<Size> SSize;
    
void readCities(FILE* file, VPoint* ps);
void readNearest(FILE* file, VVSize* inds);
void writeNearest(FILE* file, VVSize& inds);
void readApprox(FILE* file, VSize paths[2]);
void writeApprox(FILE *file, VSize path[2]);
void writeSolution(FILE *file, VSize path[2]);
void computeLengths(VPoint &ps, VSize paths[2], double d[2]);


#endif /* defined(__Santa__Support__) */

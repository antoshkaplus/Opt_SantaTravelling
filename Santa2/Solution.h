//
//  Solution.h
//  Santa2
//
//  Created by Anton Logunov on 1/9/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#ifndef __Santa2__Solution__
#define __Santa2__Solution__

#include <iostream>


#include "Support.h"
#include "SolutionControl.h"

struct Solution{  
  char resultPath[200];
  char pointsPath[200];
  VPoint ps;
  Map map;
  Size nRepetitions;
  Size n;
  SolutionControl sc;
  SSet left[2];
  double d[2];
  
  double weightedDistance(Size i1, Size i2){
    if(i1 > i2) swap(i1,i2);
    double factor = 1.;
    Index mi = (Index)n*i1+i2;
    if(map.find(mi) != map.end()){
      factor = max((Size)100 - map[mi],(Size)0)/100.l;
    }
    return factor*ps[i1].distance(ps[i2]);
  }
  
  double simpleDistance(Size i1, Size i2){
    return ps[i1].distance(ps[i2]);
  }
  
  
  Solution(){
    strcat(pointsPath, root);
    strcat(pointsPath, "ireland.pts");
    strcat(resultPath, root);
    strcat(resultPath, "ireland.cvs");
    FILE *file = fopen(pointsPath, "r");
    readCities(file, &ps);
    n = (Size)ps.size();
  }
  
  void solve(){
    for(Size i = 0; i < 100; ++i){
      approximate();
      twoOpt(n);
      update();
      printf("new length: %f\n",max(d[0], d[1]));
    }
    FILE *file = fopen(resultPath, "w");
    VSize p[2];
    sc.fillPaths(&p[0], &p[1]);
    writeSolution(file, p);
  }

  // approximation methods
  void approximate();
  double cost(Size i, Size i1, Size i2);
  SSetIt nearest(Size i1, Size i2, char k);
  SSetIt nearest(Size i, char k);
  Size twoOpt(Size maxMoves);
  void update();
};


#endif /* defined(__Santa2__Solution__) */

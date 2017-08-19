//
//  LocalSolutionControl.h
//  Santa
//
//  Created by Anton Logunov on 1/8/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#ifndef __Santa__LocalSolutionControl__
#define __Santa__LocalSolutionControl__

#include <iostream>

#include "Support.h"

struct LocalSolutionControl {
  struct Edge{
    bool changeable[2];
    Size ind[2];
    char sz;
  };
  
  VPoint ps;
  Edge *edges;
  Size n;
  
  LocalSolutionControl(Size n) : edges(NULL){
    set(n);
  }
  void set(Size n){
    this->n = n;
    if(edges != NULL){
      free(edges);
    }else{
      edges = (Edge*)calloc(2*n, sizeof(Edge));
      memset(edges, 0, 2*n*sizeof(Edge));
    }
  }
  void add(Size i1, Size i2, bool changeable, char owner){
    Size k = owner*n;
    Edge &e1 = edges[i1+k];
    Edge &e2 = edges[i2+k];
    e1.ind[e1.sz++] = i2;
    e2.ind[e2.sz++] = i1;
  }
  Edge* get(Size i, char owner){
    return edges+i+owner*n;
  }
  bool notIn(Size i, Size i1, char owner){
    Edge &e = edges[i+owner*n];
    if(e.ind[0] == i1 || e.ind[1] == i1){
      return false;
    }
    return true;
  }
};


#endif /* defined(__Santa__LocalSolutionControl__) */

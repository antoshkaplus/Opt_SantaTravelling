//
//  SolutionControl.h
//  Santa
//
//  Created by Anton Logunov on 1/3/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#ifndef __Santa__SolutionControl__
#define __Santa__SolutionControl__

#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct SolutionControl{
private:
  struct Edge{
    size_t index;
    char owner;
    void set(size_t index, char owner){
      this->index = index;
      this->owner = owner;
    }
  };
  struct Vertix{
    vector<Edge> edges;
    char quantity[2];
  };
  typedef vector<Edge> VEdge;
  typedef vector<Vertix> VVertix;
  
public:
  VVertix content;
  
  SolutionControl();
  SolutionControl(size_t n);
  bool available(size_t i1, size_t i2);
  bool canAdd(size_t i1, size_t i2, char owner);
  void add(size_t i1, size_t i2, char owner);
  void set(size_t n);
  void writeToFile(FILE *file);
  void extend(size_t i, size_t i1, size_t i2);
  void neighbors(size_t i, char k, size_t in[2]);
  void rearrange(size_t i, size_t i1old, size_t i2old, size_t i1new, size_t i2new);
  void exchange(size_t i, size_t inear, size_t q, size_t qnear);
};


#endif /* defined(__Santa__SolutionControl__) */

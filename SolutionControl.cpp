//
//  SolutionControl.cpp
//  Santa
//
//  Created by Anton Logunov on 1/3/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#include "SolutionControl.h"

SolutionControl::SolutionControl(){}

SolutionControl::SolutionControl(size_t n){
  set(n);
}

bool SolutionControl::available(size_t i1, size_t i2){
  VEdge &vch = content[i1].edges;
  char j = 0;
  for(; j < vch.size(); ++j){
    if(vch[j].index == i2) break;
  }
  return j == vch.size();
}

bool SolutionControl::canAdd(size_t i1, size_t i2, char owner){
  return available(i1,i2) && content[i1].quantity[owner] < 2 &&
  content[i2].quantity[owner] < 2;
}

void SolutionControl::add(size_t i1, size_t i2, char owner){
  Edge e;
  e.set(i2, owner);
  content[i1].edges.push_back(e);
  content[i1].quantity[owner] += 1;
  e.set(i1, owner);
  content[i2].edges.push_back(e);
  content[i2].quantity[owner] += 1;
}

void SolutionControl::set(size_t n){
  content.resize(n);
  for(char i = 0; i < n; ++i){
    content[i].edges.clear();
    memset(content[i].quantity,0,sizeof(char[2]));
  }
}

void SolutionControl::writeToFile(FILE *file){
  size_t n = content.size();
  size_t nextI[2] = {0, 0}, curI[2] = {-1, -1};
  size_t r[2];
  for(size_t q = 0; q < n; ++q){
    for(char k = 0; k < 2; ++k){
      size_t &next = nextI[k],
      &cur = curI[k];
      VEdge &es = content[next].edges;
      size_t j = 0;
      while(es[j].owner != k || es[j].index == cur) ++j;
      cur = next;
      next = es[j].index;
      r[k] = next;
    }
    fprintf(file, "%lu,%lu\n" ,r[0],r[1]);
  }
}

void SolutionControl::extend(size_t i, size_t i1, size_t i2){
  VEdge::iterator it;
  it = content[i1].edges.begin();
  while (it->index != i2) ++it;
  it->index = i;
  it = content[i2].edges.begin();
  while (it->index != i1) ++it;
  it->index = i;
  char k = it->owner;
  Edge e;
  e.set(i1, k);
  content[i].edges.push_back(e);
  e.set(i2, k);
  content[i].edges.push_back(e);
  content[i].quantity[k] += 2;
}

void SolutionControl::neighbors(size_t i, char k, size_t in[2]){
  VEdge &vch = content[i].edges;
  char r = 0;
  for(char j = 0; j < vch.size(); ++j){
    if(vch[j].owner == k){
      in[r++] = vch[j].index;
    }
  }
}

void SolutionControl::rearrange(size_t i, size_t i1old, size_t i2old,
                                          size_t i1new, size_t i2new){
  VEdge::iterator it;
  it = content[i1old].edges.begin();
  while (it->index != i) ++it;
  it->index = i2old;
  it = content[i2old].edges.begin();
  while (it->index != i) ++it;
  it->index = i1old;
  it = content[i1new].edges.begin();
  while (it->index != i2new) ++it;
  it->index = i;
  it = content[i2new].edges.begin();
  while (it->index != i1new) ++it;
  it->index = i;
  it = content[i].edges.begin();
  while (it->index != i1old) ++it;
  it->index = i1new;
  it = content[i].edges.begin();
  while (it->index != i2old) ++it;
  it->index = i2new;
}

void SolutionControl::exchange(size_t i, size_t inear, size_t q, size_t qnear){
  VEdge::iterator it;
  it = content[i].edges.begin();
  while (it->index != inear) ++it;
  it->index = qnear;
  it = content[inear].edges.begin();
  while (it->index != i) ++it;
  it->index = q;
  it = content[q].edges.begin();
  while (it->index != qnear) ++it;
  it->index = inear;
  it = content[qnear].edges.begin();
  while (it->index != q) ++it;
  it->index = i;
}


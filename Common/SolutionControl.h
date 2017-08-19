
#include "Support.h"

struct SolutionControl {
  struct Edge{
    Size ind[2];
    char sz;
  };
  
  /* 1-st loop by indeces of cities
   * 2-nd loop by owners */
  Edge *edges;
  Size n;
  SolutionControl() : edges(NULL){}
  SolutionControl(Size n) : edges(NULL){
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
  void add(Size i1, Size i2, char owner){
    Size k = owner*n;
    Edge &e1 = edges[i1+k];
    Edge &e2 = edges[i2+k];
    e1.ind[e1.sz++] = i2;
    e2.ind[e2.sz++] = i1;
  }
  const Size* get(Size i, char owner){
    return edges[i+owner*n].ind;
  }
  bool notIn(Size i, Size i1, Size i2, char owner){
    Edge &e = edges[i+owner*n];
    if(e.sz >= 1 && (e.ind[0] == i1 || e.ind[0] == i2)){
      return false;
    }
    if(e.sz == 2 && (e.ind[1] == i1 || e.ind[1] == i2)){
      return false;
    }
    return true;
  }
  bool notIn(Size i, Size i1, char owner){
    Edge &e = edges[i+owner*n];
    if(e.sz >= 1 && e.ind[0] == i1){
      return false;
    }
    if(e.sz == 2 && e.ind[1] == i1){
      return false;
    }
    return true;
  }
  void extend(Size i, Size i1, Size i2, char owner){
    Size k = owner*n;
    Edge &e = edges[i+k];
    e.ind[0] = i1;
    e.ind[1] = i2;
    e.sz = 2;
    Size *a;
    a = edges[i1+k].ind;
    if(a[0] == i2) a[0] = i;
    else a[1] = i;
    a = edges[i2+k].ind;
    if(a[0] == i1) a[0] = i;
    else a[1] = i;
  }
  void fill(VSize &p1, VSize &p2){
    for(Size i = 0; i < n-1; ++i){
      add(p1[i], p1[i+1], 0);
      add(p2[i], p2[i+1], 1);
    }
    add(p1[0], p1[n-1], 0);
    add(p2[0], p2[n-1], 1);
  }
  void fillPaths(VSize *pp1, VSize *pp2){
    VSize &p1 = *pp1;
    VSize &p2 = *pp2;
    p1.resize(n);
    p2.resize(n);
    const Size *a;
    a = get(0, 0);
    Size icur1 = 0, inext1 = a[0];
    a = get(0, 1);
    Size icur2 = 0, inext2 = a[0];
    for(Size q = 0; q < n; ++q){
      // for p1
      p1[q] = icur1;
      a = get(inext1,0);
      if(a[0] == icur1){
        icur1 = inext1;
        inext1 = a[1];
      }else{
        icur1 = inext1;
        inext1 = a[0];
      }
      // for p2
      p2[q] = icur2;
      a = get(inext2,1);
      if(a[0] == icur2){
        icur2 = inext2;
        inext2 = a[1];
      }else{
        icur2 = inext2;
        inext2 = a[0];
      }
    }
  }
  void exchange(Size i1, Size i2, Size i3, Size i4, char owner){
    assert(!notIn(i1, i2, owner) && !notIn(i2, i3, owner) && !notIn(i3, i4, owner));
    Size k = owner*n;
    Size *a = edges[i1+k].ind;
    if (a[0] == i2) a[0] = i3;
    else{
      assert(a[1] == i2);
      a[1] = i3;
    }
    a = edges[i2+k].ind;
    if (a[0] == i1) a[0] = i4;
    else{
      assert(a[1] == i1);
      a[1] = i4;
    }
    a = edges[i3+k].ind;
    if (a[0] == i4) a[0] = i1;
    else{
      assert(a[1] == i4);
      a[1] = i1;
    }
    a = edges[i4+k].ind;
    if (a[0] == i3) a[0] = i2;
    else{
      assert(a[1] == i3);
      a[1] = i2;
    }
  }
  void rearrange(Size i, Size i1, Size i2, Size j1, Size j2, char owner){
    assert(!notIn(i, i1, owner) && !notIn(i, i2, owner) && !notIn(j1, j2, owner));
    Size k = owner*n;
    Size *a = edges[i+k].ind;
    a[0] = j1;
    a[1] = j2;
    a = edges[i1+k].ind;
    if (a[0] == i) a[0] = i2;
    else{
      assert(a[1] == i);
      a[1] = i2;
    }
    a = edges[i2+k].ind;
    if (a[0] == i) a[0] = i1;
    else{
      assert(a[1] == i);
      a[1] = i1;
    }
    a = edges[j1+k].ind;
    if (a[0] == j2) a[0] = i;
    else{
      assert(a[1] == j2);
      a[1] = i;
    }
    a = edges[j2+k].ind;
    if (a[0] == j1) a[0] = i;
    else{
      assert(a[1] == j1);
      a[1] = i;
    }
  }
  void regroup(Size i1, Size i2, Size j1, Size j2, char owner){
    Size k = owner*n;
    Size *a = edges[i1+k].ind;
    if(a[0] == i2) a[0] = j1;
    else a[1] = j1;
    a = edges[i2+k].ind;
    if(a[0] == i1) a[0] = j2;
    else a[1] = j2;
    a = edges[j1+k].ind;
    if(a[0] == j2) a[0] = i1;
    else a[1] = i1;
    a = edges[j2+k].ind;
    if(a[0] == j1) a[0] = i2;
    else a[1] = i2;
  }
};








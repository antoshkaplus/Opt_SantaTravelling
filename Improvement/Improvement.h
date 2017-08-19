
#include <vector>
#include <cstdio>

#include "Support.h"
#include "SolutionControl.h"
#include "LocalSolutionControl.h"

using namespace std;

struct Improvement{
  
  VVSize near; // should read nearest points
  VPoint ps;
  SolutionControl sc;
  Size n;
  Size kLast;
  double d[2];
  
  Improvement(char* fnamecities, char* fnameapprox, char* fnamenear);
  void improve();
  bool oneOptCondition(Size i, Size i1, Size i2, Size j, Size j1, Size j2, char notK, double& D);
  Size oneOpt(Size maxMoves);
  Size twoOpt(Size maxMoves);
  static bool threeOptSupport(LocalSolutionControl &lsc, VPoint &ps, double d[2], Size center);
  Size threeLocalOpt(Size maxMoves);
  void output(char* fnamesolution);
};
//
//  main.cpp
//  Santa
//
//  Created by Anton Logunov on 1/5/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#include "Improvement.h"

int main(){
  //srand((Size)time(NULL));
  char path[200];
  strcpy(path, root);
  char name[20];
  scanf("%s",name);
  strcat(path, name);
  char inpts[200], inapx[200], innear[200];
  strcpy(inpts, path);
  strcat(inpts, ".pts");
  strcpy(inapx, path);
  strcat(inapx, ".apx");
  strcpy(innear, path);
  strcat(innear, ".near");
  Improvement i(inpts,inapx,innear);
  i.improve();
  char out[200];
  strcpy(out, path);
  strcat(out, ".cvs");
  i.output(out);
}
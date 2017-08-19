//
//  main.cpp
//  Santa
//
//  Created by Anton Logunov on 1/5/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#include "Approximation.h"

int main(){
  srand((Size)time(NULL));
  char path[200];
  strcpy(path, root);
  char name[20];
  scanf("%s",name);
  strcat(path, name);
  char in[200];
  strcpy(in, path);
  strcat(in, ".pts");
  Approximation a(in);
  a.solve();
  char out[200];
  strcpy(out, path);
  strcat(out, ".apx");
  a.output(out);
}

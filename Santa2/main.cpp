//
//  main.cpp
//  Santa2
//
//  Created by Anton Logunov on 1/9/13.
//  Copyright (c) 2013 Anton Logunov. All rights reserved.
//

#include <iostream>

#include "Solution.h"

int main(int argc, const char * argv[])
{
  srand(time(NULL));
  Solution s;
  s.solve();
  // insert code here...
  std::cout << "Hello, World!\n";
  return 0;
}


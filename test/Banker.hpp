//
//  Banker.hpp
//  test
//
//  Created by Harkaran Brar on 11/25/17.
//  Copyright © 2017 Harkaran Brar. All rights reserved.
//

#ifndef Banker_hpp
#define Banker_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <pthread.h>
#include <sstream>
using namespace std;


#define Customers 5
#define Resources 3


class banker{
    
    
public:
    banker();
    void display_data();
    bool is_it_safe();
    void Update_data();
    
    
private:
    int available[Resources] = {10,5,7};        //Available Resources
    int max[Customers][Resources] = {{7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}};  //Max
    int alloc [Customers][Resources] = {{0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}};  //Alloc
    
    int needed [Customers][Resources];
    
protected:
    
    
    
};

#endif /* Banker_hpp */

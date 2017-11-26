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
using namespace std;

#define NUMBER_OF_RESOURCES 3

class banker{
    
    
public:
    banker();
    void display_data();
    bool is_it_safe();
    
private:
    int available[NUMBER_OF_RESOURCES] = {10,5,7};
    
protected:
    
    
    
};

#endif /* Banker_hpp */

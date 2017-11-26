//
//  Banker.cpp
//  test
//
//  Created by Harkaran Brar on 11/25/17.
//  Copyright © 2017 Harkaran Brar. All rights reserved.
//

#include "Banker.hpp"


banker::banker(){
    
    display_data();
    is_it_safe();

    
    cout<<is_it_safe()<<endl;
    
}

void banker::display_data()
{
    for(int i=0; i<3; i++)
    {
        cout<<available[i]<<endl;
    }
    
}

bool banker::is_it_safe(){
    
    
    return 0;
}

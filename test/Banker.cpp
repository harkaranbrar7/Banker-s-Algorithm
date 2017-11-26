//
//  Banker.cpp
//  test
//
//  Created by Harkaran Brar on 11/25/17.
//  Copyright © 2017 Harkaran Brar. All rights reserved.
//

#include "Banker.hpp"


banker::banker(){
    cout<<"Initial state";
    Update_data();
    display_data();
    is_it_safe();

    
    cout<<is_it_safe()<<endl;
    
}

void banker::Update_data(){
    // Getting the neededed matrix
    
    for(int i=0;i<Customers;i++)
        for(int j=0;j<Resources;j++)
            needed[i][j]=max[i][j]-alloc[i][j];
    
    //Updating the available list
    for(int i=0;i<Resources;i++)
        for(int j=0;j<Customers;j++)
            available[i]=available[i]-alloc[j][i];
    
}


void banker::display_data()
{
    cout<<"\n\n";
    cout<<"------Maximum------";
    for(int i=0;i<Customers;i++)
    {
        cout<<"\n";
        for(int j=0;j<Resources;j++)
            cout<<"   |"<<max[i][j]<<"|";
    }
    
    cout<<"\n\n";
    cout<<"------Allocated------";
    for(int i=0;i<Customers;i++)
    {
        cout<<"\n";
        for(int j=0;j<Resources;j++)
            cout<<"   |"<<alloc[i][j]<<"|";
    }
    
    
    cout<<"\n\n";
    cout<<"------Needed------";
    for(int i=0;i<Customers;i++)
    {
        cout<<"\n";
        for(int j=0;j<Resources;j++)
            cout<<"   |"<<needed[i][j]<<"|";
    }
    
    cout<<"\n\n";
    cout<<"------Available------\n";
    
    for(int i=0;i<Resources;i++)
        cout<<"   |"<<available[i]<<"|";
    
    cout<<"\n\n";

}




bool banker::is_it_safe(){
    
    
    return 0;
}

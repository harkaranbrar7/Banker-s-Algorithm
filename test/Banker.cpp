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
    
    
    // calculating the needed matrix
    // max - alloc = needed
    for(int i=0;i<Customers;i++)
        for(int j=0;j<Resources;j++)
            needed[i][j]=max[i][j]-alloc[i][j];
    
    // available list updating
    // available - sum of alloc
    for(int i=0;i<Resources;i++)
        for(int j=0;j<Customers;j++)
            available[i]=available[i]-alloc[j][i];
    
}


void banker::display_data()
{
    int i,j;
    
    cout<<"\n\n";
    cout<<"------Maximum------";
    for(i=0;i<Customers;i++)
    {
        cout<<"\n";
        for(j=0;j<Resources;j++)
            cout<<"   |"<<max[i][j]<<"|";
    }
    
    cout<<"\n\n";
    cout<<"------Allocated------";
    for(i=0;i<Customers;i++)
    {
        cout<<"\n";
        for(j=0;j<Resources;j++)
            cout<<"   |"<<alloc[i][j]<<"|";
    }
    
    
    cout<<"\n\n";
    cout<<"------Needed------";
    for(i=0;i<Customers;i++)
    {
        cout<<"\n";
        for(j=0;j<Resources;j++)
            cout<<"   |"<<needed[i][j]<<"|";
    }
    
    cout<<"\n\n";
    cout<<"------Available------\n";
    
    for(i=0;i<Resources;i++)
        cout<<"   |"<<available[i]<<"|";
    
    cout<<"\n\n";

}




bool banker::is_it_safe(){
    int myWork[Resources];
    bool finish[Customers];
    string sequence[Customers];
    int num = 0;
    
    stringstream convert;
    
    //flags for if its safe, if need[i] is lesser than available
    bool safe_flag=true;
    bool need_flag=true;
    int loopNumber=0;
    
    //copying available to Mywork
    for(int i=0;i<Resources;i++)
        myWork[i]=available[i];
    
    // Initialise all the finish flag to false
    for(int i=0;i<Customers;i++)
        finish[i]=false;
    
    for(int i=0;i<Customers;i++)
        sequence[i]="No Process";
    
    while (loopNumber<10) {
        
        for(int i=0; i < Resources;i++)
        {
            need_flag=true;
        }
    } //end while
    
    return 0;
}

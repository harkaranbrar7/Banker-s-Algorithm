//
//  Banker.cpp
//  test
//
//  Created by Harkaran Brar on 11/25/17.
//  Copyright © 2017 Harkaran Brar. All rights reserved.
//

#include "Banker.h"



int main(){
  banker mybanker;
    
    
}

banker::banker(){
    cout<<"Initial state";
    Update_data();
    display_data();
    is_it_safe();
    do_the_stuff();
    
    
}

void banker::do_the_stuff()
{
    int random;
    int allot;
    int counter = 0;
    
    
    while(counter<10){
        random =rand()%4;
        {
              set_req_res(random);
            //allot = pthread_create(&mycustomer[random],NULL,)
            
            
        }
        
    }
    
}


void banker::set_req_res(int){
    
    cout<<"WTFFFFFFFF"<<endl;
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
 
   
    bool finish[Customers] = {0};   // Bool set to false for all process
    int safe_sequence[Customers];   // for storing safe sequence
    int work[Resources];            // for coping the available to work
    int count = 0;
    
    
    for (int i = 0; i < Resources ; i++)
    {
        work[i] = available[i];
    }
    
    // While all processes are not finished
    // or system is not in safe state.
    
    while (count < Customers)
    {
        // Find a process which is not finish and
        // whose needs can be satisfied with current
        // work[] resources.
        bool safe = false;
        for (int p = 0; p < Customers; p++)
        {
            // First check if a process is finished,
            // if no, go for next condition
            if (finish[p] == 0)
            {
                // Check if for all resources of
                // current P need is less
                // than work
                int j;
                for (j = 0; j < Resources; j++)
                    if (needed[p][j] > work[j])
                        break;
                
                // If all needs of p were satisfied.
                if (j == Resources)
                {
                    // Add the allocated resources of
                    // current P to the available/work
                    // resources i.e.free the resources
                    for (int k = 0 ; k < Resources ; k++)
                        work[k] += alloc[p][k];
                    
                    // Add this process to safe sequence.
                    safe_sequence[count++] = p;
                    
                    // Mark this p as finished
                    finish[p] = 1;
                    
                    safe = true;
                }
            }
        }
        
        // If we could not find a next process in safe
        // sequence.
        if (safe == false)
        {
            cout << "System is not in safe state";
            return false;
        }
    }
    
    // If system is in safe state then
    // safe sequence will be as below
   // cout << "\033[1;31mSystem is in safe state.\nSafe sequence is: \033[0m\n";
    cout << "System is in safe state.\nSafe sequence is: ";
    for (int i = 0; i < Customers ; i++)
        cout <<"|P"<< safe_sequence[i] << "| ";
    
    
    cout<<"\n\n";
    
    return true;

    
    
    
    
    

    
    
    
    
    
    /*
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
        
        for(int i=0; i < Customers;i++)
        {
            need_flag=true;
            if (finish[i]==false)
            {
                for(int j=0; j<Resources;j++)
                {
                    if(needed[i][j]>myWork[j])
                    {
                        need_flag = false;
                        break;
                    } //end if
                }//end for
                while(need_flag == true && finish[i]==false)
                {
                    for(int j=0; j<Resources; j++)
                    {
                        myWork[j]=myWork[j]+alloc[i][j];
                    } //end for
                    
                    finish[i]=true;
                    convert<<i;
                    sequence[num++]="Process"+ convert.str();
                    convert.str("");
                }//end while
            }//end if
        } //end for
        loopNumber++;
    } //end while
    
    for(int i=0;i<Customers;i++)
        if(finish[i]==false)
            safe_flag=false;
    
    
    if(safe_flag)
    {
        cout<<"The request is safe and is granted";
        cout<<"\nSafety Sequence is ";
        for(int i=0;i<Customers;i++)
            cout<<sequence[i]<<"->";
    }
    else
        cout<<"The request denied\n";
    
    return safe_flag;
   */
   }





void* _resource_request_send(void*)
{
 
    return 0;
}




















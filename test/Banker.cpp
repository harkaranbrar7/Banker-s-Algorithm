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
    
    Update_data();
    display_data();
    is_it_safe();
    do_the_stuff();
    
    
}

void banker::do_the_stuff()
{
    int random;
    int allot;
   // int counter;
    
    for (int counter=0; counter<10;counter++){
    //while(counter<10){
    //cout<<" counter = "<<counter<<endl;
        random = rand()%4;
        {
            set_req_res(random);
            allot = pthread_create(&mycustomer[random],NULL,_resource_request_send,(void *)&res_o[random]);

            set_req_res(random);
            allot = pthread_create(&mycustomer[random],NULL,_release_request_send,(void *)&res_o[random]);

          // counter++;
        }

    }//end for
    
}


void banker::set_req_res(int custom_id){
    
    res_o[custom_id]._id_Customer=custom_id;
    for(int i=0;i<Resources;i++)
    {
        if (needed[custom_id][i]==0) {
            res_o[custom_id]._req[i]=0;
        }
        else {
            res_o[custom_id]._req[i]=rand()%(needed[custom_id][i]+1);
        }
    }
    
}

void banker::set_rel_res(int custom_id){
    
    res_o[custom_id]._id_Customer=custom_id;
    for(int i=0;i<Resources;i++)
    {
        if (alloc[custom_id][i]==0) {
            res_o[custom_id]._rele[i]=0;
        }
        else {
            res_o[custom_id]._rele[i]=rand()%(alloc[custom_id][i]+1);
        }
    }
    
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
    
    cout<<"=-= All the Matrix =-=";
    
    cout<<"\n\n";
    cout<<"=-=-=- Maximum -=-=-=";
    for(i=0;i<Customers;i++)
    {
        cout<<"\n";
        for(j=0;j<Resources;j++)
            cout<<"   |"<<max[i][j]<<"|";
    }
    
    cout<<"\n\n";
    cout<<"=-=-=- Allocated -=-=-=";
    for(i=0;i<Customers;i++)
    {
        cout<<"\n";
        for(j=0;j<Resources;j++)
            cout<<"   |"<<alloc[i][j]<<"|";
    }
    
    
    cout<<"\n\n";
    cout<<"=-=-=- Needed -=-=-=";
    for(i=0;i<Customers;i++)
    {
        cout<<"\n";
        for(j=0;j<Resources;j++)
            cout<<"   |"<<needed[i][j]<<"|";
    }
    
    cout<<"\n\n";
    cout<<"=-=-=- Available -=-=-=\n";
    
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
    
    
    while (count < Customers)
    {
     
        bool safe = false;
        int process = 0;
        while (process < Customers)
        //for (int process = 0; process < Customers; process++)
        {
            

            if (finish[process] == 0)
            {
        
                int jCounter;
                for (jCounter = 0; jCounter < Resources; jCounter++)
                    if (needed[process][jCounter] > work[jCounter])
                        break;
            
                if (jCounter == Resources)
                {
                  
                    for (int k = 0 ; k < Resources ; k++)
                        work[k] += alloc[process][k];
                    
                
                    safe_sequence[count++] = process;
                    

                    finish[process] = 1;
                    
                    safe = true;
                }
            }
            process++;
        }
        

        if (safe == false)
        {
            cout << "System is not in safe state";
            return safe;
        }
    }

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
 
    cout<<" resource requested"<<endl;
    return 0;
}


void* _release_request_send(void*)
{
    
    cout<<" resource released "<<endl;
    return 0;
}














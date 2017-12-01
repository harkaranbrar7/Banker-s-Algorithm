//
//  Banker.cpp
//  test
//
//  Created by Harkaran Brar on 11/25/17.
//  Copyright © 2017 Harkaran Brar. All rights reserved.
//

#include "Banker.h"


//banker mI;

int main(){
  //banker mybanker;
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
    int random_resouces = 4;
    
    for (int counter=0; counter<10;counter++){
        random = rand()%random_resouces;
        {
            set_req_res(random);
            allot = pthread_create(&mycustomer[random],NULL,_resource_request_send,(void *)&res_o[random]);

            set_req_res(random);
            allot = pthread_create(&mycustomer[random],NULL,_release_request_send,(void *)&res_o[random]);

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

   }


int banker::requested(int custom_id, int requested[]){
    
    bool my_Need_check = true;
    bool availab_check = true;
    bool allocate_check = false;
    cout<<"\n\n"<<"Processing request of customer "<<custom_id;
    cout<<"\nCustomer "<<custom_id<<" has requested for "<<res_o[custom_id]._req[0]<<" "<<res_o[custom_id]._req[1]<<" "<<res_o[custom_id]._req[2]<<endl;
    
    int jcounter = 0;
    while(jcounter < Resources)
    {
        switch (requested[jcounter]>needed[custom_id][jcounter]) {
            case 1:
                cerr<<"\nIllegal resources requested";
                my_Need_check=false;
                break;
                
            default:
                break;
        }
        jcounter++;
    }
    
    switch (my_Need_check == true) {
        case 1:
            for (int i =0; i<Resources; i++) {
                switch (requested[i]>available[i]) {
                    case 1:
                        availab_check = false;
                        break;
                        
                    default:
                        break;
                } // inside switch
            }
            break;
            
        default:
            break;
    }
    
    //Pretending to allocate resources when
    
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    for(int i=0;i<Resources;i++)
    {
        //available[i]-=requested[i];
        available[i] = available[i]-requested[i];
        alloc[custom_id][i] = alloc[custom_id][i] + requested[i];
        needed[custom_id][i] = needed[custom_id][i] - requested[i];
    }
    
//    for(int i=0;i<3;i++){
//    cout<<available[i]<<endl;
//
//    }
    
    allocate_check = is_it_safe();
    //cout<<allocate_check<<endl;
    
    switch (!allocate_check) {
        case 1:
            for(int i=0;i<Resources;i++)
        {
            //available[i]-=requested[i];
            available[i] = available[i] + requested[i];
            alloc[custom_id][i] = alloc[custom_id][i] - requested[i];
            needed[custom_id][i] = needed[custom_id][i] + requested[i];
        }
            break;
            
        default:
            break;
    }
    
    return allocate_check;
}

int banker:: released(int custom_id, int released[]){
    
    bool release_check = true;
   cout<<"\n\n"<<" Processing release request of customer "<< custom_id;
    cout<<"\n Customer "<<custom_id<<" has requested to release for "<<released[0]<<" "<<released[1]<<" "<<released[2]<<endl;
    
    for (int i=0;i<Resources;i++)
    {
        switch (released[i]>alloc[custom_id][i]) {
            case 1:
                 release_check=false;
                break;
                
            default:
                break;
        }
           
    }
    
    switch (release_check == false) {
        case 1:
            cerr<<"\nRelease request exceed allocated";
            return release_check;
            break;
            
        default:
            break;
    }

    
    for(int i=0;i<Resources;i++)
    {
        //available[i]-=requested[i];
        available[i] = available[i] + released[i];
        alloc[custom_id][i] = alloc[custom_id][i] - released[i];
        needed[custom_id][i] = needed[custom_id][i] + released[i];
    }
    cout<<"Resources Released! \n";
    //pthread_mutex_unlock( &update );
    return release_check;

}


void* _resource_request_send(void* mythread)
{
    int custom_id;
    bool mybool;
    int req_res[Resources];
    struct request_res *custreq;
    
    pthread_mutex_lock(&My_mutex);  // lock
   
    custreq = (struct request_res*) mythread;
    custom_id = custreq->_id_Customer;
    
    for(int i=0;i<3;i++)
    {
        req_res[i]=custreq->_req[i];
    }
    
    mybool = m.requested(custom_id, req_res);
    pthread_mutex_unlock( &My_mutex );   //unlock
    return NULL;
}


void* _release_request_send(void* mythread)
{
    
    int custom_id;
    bool mybool;
    int req_res[Resources];
    struct request_res *custreq;
    
    pthread_mutex_lock(&My_mutex);  // lock
    custreq = (struct request_res*) mythread;
    custom_id = custreq->_id_Customer;
    
    for(int i=0;i<3;i++)
    {
        req_res[i]=custreq->_rele[i];
    }

    mybool = m.released(custom_id, req_res);
    pthread_mutex_unlock( &My_mutex );   //unlock
    return NULL;
}













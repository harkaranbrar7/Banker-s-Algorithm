//
//  Banker.cpp
//
//
//  Created by Harkaranjeet Singh on 11/22/17.
//  Copyright © 2017 Harkaranjeet Singh. All rights reserved.
//

#include "Banker.h"


banker mybanker;

int main()
{
    
}

banker::banker(){
    
    Update_data();
    //  display_data();
    is_it_safe();
    do_the_stuff();
    
}

void banker::do_the_stuff()
{
    int random;
    int random_resouces = 4;
    bool times = true;
    
    while(times){
        //for (int counter=0; counter<times;counter++){
        
        random = rand()%random_resouces;
        //cout<<"-------------  "<<random<<endl;
        {
            set_req_res(random);
            //  cout<<"-------------  "<<random<<endl;
            pthread_create(&mycustomer[random],NULL,_resource_request_send,(void *)&res_o[random]);
            //cout<<"-------------  "<<random<<endl;
            set_rel_res(random);
            //cout<<"-------------  "<<random<<endl;
            pthread_create(&mycustomer[random],NULL,_release_request_send,(void *)&res_o[random]);
            pthread_join(mycustomer[random], NULL);
            
        }
        //        pthread_mutex_lock(&My_mutex);
        //
        //        display_data();
        //        pthread_mutex_unlock(&My_mutex);
    }//end for
    
    //pthread_exit(NULL);
}


void banker::set_req_res(int custom_id){
    
    res_o[custom_id]._id_Customer = custom_id;
    for(int i=0;i<Resources;i++)
    {
        
        switch (needed[custom_id][i]) {
            case 1:
                res_o[custom_id]._req[i]=0;
                break;
                
            default:
                res_o[custom_id]._req[i]=rand()%(needed[custom_id][i]+1);
                break;
        }
    }
    
}

void banker::set_rel_res(int custom_id){
    
    res_o[custom_id]._id_Customer=custom_id;
    for(int i=0;i<Resources;i++)
    {
        
        switch (alloc[custom_id][i]) {
            case 0:
                res_o[custom_id]._rele[i]=0;
                break;
                
            default:
                res_o[custom_id]._rele[i]=rand()%(alloc[custom_id][i]+1);
                break;
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
    
    cerr<<"\n\n=-= All the Matrix =-=";
    
    cerr<<"\n\n";
    cerr<<"=-=-=- Maximum -=-=-=";
    for(i=0;i<Customers;i++)
    {
        cerr<<"\n";
        for(j=0;j<Resources;j++)
            cerr<<"   |"<<max[i][j]<<"|";
    }
    
    cerr<<"\n\n";
    cerr<<"=-=-=- Allocated -=-=-=";
    for(i=0;i<Customers;i++)
    {
        cerr<<"\n";
        for(j=0;j<Resources;j++)
            cerr<<"   |"<<alloc[i][j]<<"|";
    }
    
    
    cerr<<"\n\n";
    cerr<<"=-=-=- Needed -=-=-=";
    for(i=0;i<Customers;i++)
    {
        cerr<<"\n";
        for(j=0;j<Resources;j++)
            cerr<<"   |"<<needed[i][j]<<"|";
    }
    
    cerr<<"\n\n";
    cerr<<"=-=-=- Available -=-=-=\n";
    
    for(i=0;i<Resources;i++)
        cerr<<"   |"<<available[i]<<"|";
    
    cerr<<"\n\n";
    
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
            cerr << "\033[1;31m Warning: System is not in safe state \033[0m\n";
            return safe;
        }
    }
    cerr << "\033[1;32m System is in safe state.\n Safe sequence is:  \033[0m\n";
    for (int i = 0; i < Customers ; i++)
        cerr <<"|P"<< safe_sequence[i] << "| ";
    
    
    cerr<<"\n";
    
    return true;
    
}


int banker::requested(int custom_id, int requested[]){
    
    bool my_Need_check = true;
    bool availab_check = true;
    bool allocate_check = false;
    //cerr<<"\n\n"<<" Process request ID "<<custom_id<<endl;
    cerr<<" ID "<<custom_id<<" has requested resources|"<<res_o[custom_id]._req[0]<<"| |"<<res_o[custom_id]._req[1]<<"| |"<<res_o[custom_id]._req[2]<<"|"<<endl;
    
    int jcounter = 0;
    while(jcounter < Resources)
    {
        switch (requested[jcounter]>needed[custom_id][jcounter]) {
            case 1:
                cerr << "\033[1;31m Resources request is no appropriate \033[0m\n";
                my_Need_check=false;
                break;
                
            default:
                break;
        }
        jcounter++;
    }
    
    switch (my_Need_check) {
        case true:
            for (int i =0; i<Resources; i++) {
                if (requested[i]>available[i])
                {
                    availab_check = false;
                    break;
                }
            }
            break;
            
        default:
            break;
    }
    
    for(int i=0;i<Resources;i++)
    {
        available[i] = available[i]-requested[i];
        alloc[custom_id][i] = alloc[custom_id][i] + requested[i];
        needed[custom_id][i] = needed[custom_id][i] - requested[i];
    }
    
    allocate_check = is_it_safe();
    
    switch (allocate_check) {
        case 0:
            for(int i=0;i<Resources;i++)
            {
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

int banker:: released(int custom_id, int rel_eased[]){
    
    bool release_check = true;
    // cerr<<" Process release ID "<< custom_id<<endl;
    cerr<<" ID "<<custom_id<<" has requested resources to release|"<<rel_eased[0]<<"| |"<<rel_eased[1]<<"| |"<<rel_eased[2]<<"|"<<endl;
    
    cerr<<"\n\n";
    
    for (int i=0;i<Resources;i++)
    {
        if(rel_eased[i]>alloc[custom_id][i])
        {
            release_check=false;
        }
    }
    
    switch (release_check) {
        case 0: // for false
            cerr << "\033[1;31m Release request exceed allocated \033[0m\n";
            return release_check;
            break;
            
        default:
            break;
    }
    
    
    for(int i=0;i<Resources;i++)
    {
        available[i] = available[i] + rel_eased[i];
        alloc[custom_id][i] = alloc[custom_id][i] - rel_eased[i];
        needed[custom_id][i] = needed[custom_id][i] + rel_eased[i];
    }
    // cerr<<" Resources Released! \n";
    return release_check;
    
}


void* _resource_request_send(void* mythread)
{
    int custom_id;
    int req_res[Resources];
    struct request_res *custreq;
    pthread_mutex_lock(&My_mutex);  // lock
    custreq = (struct request_res*) mythread;
    custom_id = custreq->_id_Customer;
    
    for(int i=0;i<3;i++)
    {
        req_res[i]=custreq->_req[i];
    }
    
    mybanker.requested(custom_id, req_res);
    pthread_mutex_unlock( &My_mutex );   //unlock
    return NULL;
}


void* _release_request_send(void* mythread)
{
    pthread_mutex_lock(&My_mutex);  // lock
    int custom_id;
    int rel_res[Resources];
    struct request_res *custreq;
    custreq = (struct request_res*) mythread;
    custom_id = custreq->_id_Customer;
    
    for(int i=0;i<3;i++)
    {
        rel_res[i]=custreq->_rele[i];
    }
    
    mybanker.released(custom_id, rel_res);
    pthread_mutex_unlock( &My_mutex );   //unlock
    return NULL;
}













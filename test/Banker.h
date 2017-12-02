//
//  Banker.h
//
//
//  Created by Harkaranjeet Singh on 11/22/17.
//  Copyright © 2017 Harkaranjeet Singh. All rights reserved.
//

#ifndef Banker_hpp
#define Banker_hpp

#include <iostream>
#include <pthread.h>
using namespace std;


#define Customers 5
#define Resources 3


pthread_t mycustomer[Customers];
pthread_mutex_t My_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t update_t = PTHREAD_MUTEX_INITIALIZER;

void* _resource_request_send(void*);
void* _release_request_send(void*);


struct request_res{
public:
    int _id_Customer;
    int _req[Resources];  //request
    int _rele[Resources]; // release
    
private:
    
protected:
};

struct request_res res_o[Customers];

class banker{
public:
    banker();
    void display_data();
    bool is_it_safe();
    void Update_data();
    void do_the_stuff();
    int requested(int,int[]); // request resource
    int released(int, int[]);  //released resources
    void set_req_res(int);
    void set_rel_res(int);
    
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





























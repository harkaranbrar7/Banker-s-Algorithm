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


pthread_t mycustomer[Customers];
pthread_mutex_t My_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t update_t = PTHREAD_MUTEX_INITIALIZER;

class banker{
    
    
public:
    banker();
    void display_data();
    bool is_it_safe();
    void Update_data();
    void do_the_stuff();
    int requested(int, int[]); //request resources
    int released(int, int[]);  //released resources
    
    void set_req_res(int);
    void set_rel_res(int);
    int* rel(int);
    

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



struct request_res{
public:
    int _id_Customer;
    int _req[3];  //request
    int _rele[3]; // release
};

struct request_res r[Customers];

void* _resource_request_send(void*);
void* _release_request_send(void*);

#endif /* Banker_hpp */





























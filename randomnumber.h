// to create random number
# include<cstdlib>
# include<iostream>
# include<ctime>
using namespace std;
#ifndef __RANDOMNUMBER__H
#define __RANDOMNUMBER__H

//Define the function random to create the random integer between 0 to x.
int random(int x) {
    return rand()%(x);
}
//Using function  overloaded (重载),to create the double number between a to b.
double random(double a ,double b){
    return  ((double)rand()/RAND_MAX)*(b-a) + a;
}
#endif 



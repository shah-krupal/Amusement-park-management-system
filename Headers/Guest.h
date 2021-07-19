#pragma once
#include <string>

using namespace std;

class Guest{
    private : 
        unsigned long long int uid; 
        string name;
        unsigned short int age;
        char gender;
        int counter ;
        string number ;
        int guest_count ;
        unsigned long long int get_id() ;
        float overall ;
        int previous ;

    public:
        void datafiller(unsigned long long int uid,string name,unsigned short int age,char gender,string number) ;
        void input() ;
        void ratings() ;
        void cumulative_rating(int) ;

        Guest() ;        
        Guest(unsigned long long int uid) ;  

        friend class Ride;
        friend class Admin;
        void loadVars();
        void putVars();
};

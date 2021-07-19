#pragma once
#include <string>
//#include "Extras.cpp"

using namespace std;

/*Helping functions*/

class Ride{
    signed int RideUid, SessionCount;
    string name;
    string description;

    unsigned short int min_age;
    unsigned short int max_age;
    unsigned short int occupancy;

    public: 

    Ride(int);
    void setData(unsigned int uid, string ride_name, string desc, unsigned short int minAge, unsigned short int maxAge, unsigned short int occu);
    void loadData(unsigned short int);

    void StartNewSession();

    string getSessionId(int);
    void putSessionId();

    void getSessionCount();
    bool CheckGuest(unsigned short int a); // to check if a guest can enter the ride
};



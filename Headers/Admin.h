#pragma once
#include "Extras.cpp"
#include "Guest.cpp"
#include <string>

using namespace std;

class Admin{
    string pass;    //password of Admin
    float guestIndex;   //rating 
    unsigned int rideCount;
    unsigned int maxRideCount;

    void loadPass();
    void changePass();

    void loadRideCount();
    void updateRideCount(int);
    
    void loadMaxRideCount();
    void updateMaxRideCount(int);

    void addRide();
    void deleteRide();
    void updateRide();

    void searchGuest(unsigned long long int Gid);

    void seeRating();
    
    public :

    Admin();
    friend int main();
};
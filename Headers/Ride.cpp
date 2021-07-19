#pragma once
#include "Ride.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace std;

//Ride password is parkRide_<ride_uid>

Ride::Ride(int CurrID){
    /*  Constructor to create the Ride object and load data in it 
    */
    this->loadData(CurrID);
    this->getSessionCount();
    cout<<"Ride Instance created successfully!"<<endl;
}

void Ride::loadData(unsigned short int CurrID){
    /* Searches if the given Ride Id is there 
        and load data to object
    */
    string line;
    ifstream file;
     
    file.open("../Files/Rides/Rides.txt");
    
    while(getline(file,line)){
        stringstream ss(line);

        unsigned short int minAge, maxAge, occupancy;
        string ride_name, desc, tmp;

        int tmpId;
        ss>>tmpId;

        if (tmpId==CurrID){
            getline(ss,tmp,',');
            getline(ss,ride_name,',');
            getline(ss,desc,',');
            ss>>minAge;
            getline(ss,tmp,',');
            ss>>maxAge;
            getline(ss,tmp,',');
            ss>>occupancy;
            //cout<<"minage loaded is : "<<minAge<<endl;
            //cout<<"maxage loaded is : "<<maxAge<<endl;
            this->setData(CurrID,ride_name,desc,minAge,maxAge,occupancy);

            break;
        }
    }
}

void Ride::setData(unsigned int uid, string ride_name, string desc, unsigned short int minAge, unsigned short int maxAge, unsigned short int occu){
    /* A stter function
    */
    this->RideUid=uid;
    this->name = ride_name;
    this->description = desc;
    this->min_age = minAge;
    this->max_age = maxAge;
    this->occupancy = occu;
}


string Ride::getSessionId(int Id){
    /*  Generates unique Session Id in the form 
        Date:Ride:Count
        and return its string
    */
    string ans = getDate();
    ans.append(":");
    ans.append(to_string(this->RideUid));
    ans.append(":");

    if (Id<10){
        ans.append("00");
    } else if (Id<100){
        ans.append("0");
    } 
    ans.append( to_string(Id));

    return ans;
}


void Ride::putSessionId(){
    /* Puts the count in file
    */
    string path("../Files/Rides/Ride");
    path.append( to_string(this->RideUid));
    path.append(".txt");

    fstream rideFile;
    rideFile.open(path);

    string date;
    rideFile<<getDate()<<endl;
    rideFile<<this->SessionCount<<endl;
}

void Ride::getSessionCount(){
    /* Loads the session count from file
    */
    string path("../Files/Rides/Ride");
    path.append( to_string(this->RideUid));
    path.append(".txt");

    fstream rideFile;
    rideFile.open(path);

    string date;
    rideFile>>date;

    if (date == getDate()) {
        int ans;
        rideFile>>ans;
        this->SessionCount = ans;

    } else {
        this->SessionCount = 0;
    }

    cout<<"Session Count is "<<this->SessionCount<<endl;
}


void Ride::StartNewSession(){
    /* Calls function to get its unique session Id
        Admit the guest if all constraint are satisfied
        Put the data in Ride File
    */

    string SessionId = this->getSessionId(++this->SessionCount);
    
    string path("../Files/Rides/Ride");
    path.append( to_string(this->RideUid));
    path.append(".txt");

    ofstream file;
    file.open(path,ios::app);

    stringstream guestData,output;
    
    unsigned int c=0;
    unsigned long long int GuestID;

    do {
        cout<<endl<<"Enter Guest Id (0 to end session ): ";
        cin>>GuestID;

        if ( GuestID==0 ){
            break;
        }
        else {
            Guest g(GuestID);

            if (g.uid == 0 ) {
                cout<<"Guest not found"<<endl;
            }
            else{
                if ( !CheckGuest(g.age) ){
                    cout<<"Guest can't enter this ride"<<endl;  
                } 
                else{
                    cout<<"Entry admitted"<<endl;
                    guestData<<GuestID<<",";
                    guestData<<getTime()<<",";
                    guestData<<getDate()<<endl;
                    c++;

                    /*Searching Uid in Guest track and pushing the data*/
                    bool flag=false;
                    fstream file;
                    file.open("../Files/Guest/GuestTrack.txt");
                    ofstream outfile("../Files/Guest/tmp.txt"); //file to store non deleted values


                    string data;
                    if (file.is_open()){

                        while( getline(file,data)){
                            stringstream ss(data);

                            unsigned long long int Id;
                            ss>>Id;

                            if (Id!=GuestID){
                                outfile<<data<<endl;
                            }
                            else {
                                flag = true;
                                stringstream ans;
                                ans<<ss.str()<<","<<SessionId<<endl;
                                outfile<<ans.str();                
                            }
                        }
                    }
                    else{
                        cout<<"Error opening GuestTrack file"<<endl;
                    }

                    file.close();
                    outfile.close();

                    //deleting previous file
                    remove("../Files/Guest/GuestTrack.txt");
                    rename("../Files/Guest/tmp.txt","../Files/Guest/GuestTrack.txt");
                
                    if (flag){
                        cout<<"GuestTrack updated successfully"<<endl;
                    } else{
                        cout<<"GuestTrack not found!"<<endl;
                    }
                }
            }
        }

    } while(GuestID && c<=this->occupancy);

    if (c==this->occupancy){
        cout<<"Ride occupancy reached"<<endl;
    } 

    output<<"Session: "<<SessionId<<"  Date: "<<getDate()<<"  Time: "<<getTime()<<"  Count: "<<c<<endl;
    output<<guestData.str()<<endl;

    file<<output.str()<<endl;
}

bool Ride::CheckGuest(unsigned short int age){
    /* Checks if the Guest is allowed in the Ride
        If not it gives the appropriate error message
    */
    if ( between(age, this->min_age, this->max_age) ){
        return true;
    }
    else if ( age>this->max_age){
        cout<<"Maxmimum age allowed is "<<max_age<<" Guest is "<<age<<endl;
    }
    else if ( this->min_age>age){
        cout<<"Minimum age allowed is "<<min_age<<" Guest is "<<age<<endl;
    }
    return false;
}


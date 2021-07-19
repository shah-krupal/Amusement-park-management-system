#pragma once
#include "Admin.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

Admin::Admin(){
    loadPass();
    loadRideCount();
    loadMaxRideCount();
}

void Admin::loadPass(){
    /*  Function to read the password from file
        and load it in the Class
        
        the password is hashed then stored for security purpose
    */
    string p;

//fstream ifstream ofstream
    ifstream file;
    file.open("../Files/Admin/Password.txt");

    if(file.is_open()){
        file >> p;
        file.close(); 
    } else{
        cout<<"Error opening password" <<endl;
        return;
    }

    this->pass = p;
}


void Admin::changePass(){
    /*  Function to change password, after necessary checks */
    
    string old_pass,pass1,pass2;
    do {
        cout<<"Enter old password : ";
        cin>>old_pass;
    } while( hashFunc(old_pass) != this->pass);
    
    do {
        cout<<"Enter new password : ";
        cin>>pass1;
        cout<<"Confirm password : ";
        cin>>pass2;

        if ( pass1 == pass2 ){
            
            ofstream file;
            file.open("../Files/Admin/Password.txt");
            file.seekp(0);
            file<<hashFunc(pass1);
            file.close();

            this->loadPass();
            break;
        }
        else{
            cout<<"The passwords don't match! Try again! "<<endl;
        }

    } while( true );
}


void Admin::loadRideCount(){
    /*  Function to read the RideCount from file
        and load it in the Class
        
        First number in file is required
    */
    string s; char c;
    int i;

    ifstream file;
    file.open("../Files/Admin/Count.txt");

    if(file.is_open()){
        file >> s; // waste string
        file >> c; // waste char
        file >> i;
        file.close(); 

    } else{
        cout<<"Error opening Count" <<endl;
        return;
    }

    this->rideCount = i;
    cout<<"Current Count is : "<<this->rideCount<<endl;
}


void Admin::updateRideCount(int j){
    /*  Function to update the RideCount from file
        and load it in the Class
        
        First number in file is required
    */
    string s("Ride : ");

    fstream file;
    file.open("../Files/Admin/Count.txt");

    if(file.is_open()){
        file<< s<< j<<endl;
        file.close(); 
        
    } else{
        cout<<"Error opening Count" <<endl;
        return;
    }

    cout<<"Current Count is : "<<j<<endl;
    this->rideCount = j ;
}


void Admin::loadMaxRideCount(){
    /*  Function to read the RideCount from file
        and load it in the Class
        
        First number of file is required
    */
    string s; char c;
    int i;

    ifstream file;
    file.open("../Files/Admin/Count.txt");
    
    file>>s>>c>>i;

    if(file.is_open()){
        file>>s>>c>>i;
        file.close(); 

    } else{
        cout<<"Error opening Count" <<endl;
        return;
    }

    this->maxRideCount = i;
    cout<<"Current Count is : "<<this->maxRideCount<<endl;
}


void Admin::updateMaxRideCount(int j){
    /*  Function to update the RideCount from file
        and load it in the Class
        
        First number in file is required
    */
    string s("MaxRide : "),tmp;
    char c; int i;

    fstream file;

    file.open("../Files/Admin/Count.txt");
    file>>tmp>>c>>i;
    if(file.is_open()){
        file<<s<<j<<endl;
        file.close(); 
        
    } else{
        cout<<"Error opening Count" <<endl;
        return;
    }
    
    cout<<"Current max Count is : "<<j<<endl;
    this->maxRideCount = j ;
}

void Admin::addRide(){
    /* Function to create a new Ride,
        and also create its necessary files 
    */

    unsigned int uid = this->maxRideCount + 1;
    unsigned short int minAge, maxAge, occupancy;
    string ride_name,desc;

    cout<<"Enter ride name : ";
    cin.ignore();
    cin>>ride_name;

    cout<<"Enter ride description (don't use any commas{,} ) : ";
    cin.ignore();
    getline(cin,desc);

    cout<<"Enter minimum age : ";
    cin>>minAge;

    cout<<"Enter maximum age : ";
    cin>>maxAge;

    cout<<"Enter maximum occupancy : ";
    cin>>occupancy;

    stringstream ss;
    ss<<uid<<",";
    ss<<ride_name<<",";
    ss<<desc<<",";
    ss<<minAge<<",";
    ss<<maxAge<<",";
    ss<<occupancy<<'\n';

    fstream file;
    file.open("../Files/Rides/Rides.txt");

    if (file.is_open()){
        string s;
        for (int i=0; i<this->rideCount; i++){
            getline(file,s);
        }
        file<<ss.str();

        this->rideCount++;
        this->updateRideCount(this->rideCount);
        this->maxRideCount++;
        this->updateMaxRideCount(this->maxRideCount);

        //creating the ride file
        string path("../Files/Rides/Ride");
        path.append( to_string(uid));
        path.append(".txt");
        cout<<"path to create file is "<<path<<endl;

        ofstream newFile(path);
        newFile<<getDate()<<endl;
        newFile<<0<<endl;
        newFile<<endl;
        newFile.close();

        cout<<"Ride Added Successfully!"<<endl;
    } 
    else{
        cout<<"Problem opening Rides file!"<<endl;  
    }
}

void Admin::deleteRide(){
    /* Function to delete the new Ride,
        and also delete its necessary files,
        it also decrements the ridecount 
    */

    int id;
    cout<<"Enter ride Id to delete : ";
    cin>>id;

    if ( id>this->maxRideCount || id<1 ){
        cout<<"Invalid Id to delete!"<<endl;
    } else{
        bool flag=false;
        string line;
    
        ifstream file;
        file.open("../Files/Rides/Rides.txt");
        ofstream outfile("../Files/Rides/tmp.txt"); //file to store non deleted values

        while(getline(file,line)){
            stringstream ss(line);
            int tmpId;
            ss>>tmpId;
            if (tmpId!=id){
                outfile<<line<<endl;
            } else if (tmpId==id) {
                flag=true;
            }
        }

        outfile.close();
        file.close();

        //deleting previous file
        remove("../Files/Rides/Rides.txt");
        rename("../Files/Rides/tmp.txt","../Files/Rides/Rides.txt");
    
        if (flag){
            this->rideCount--;
            this->updateRideCount(this->rideCount);

            string path("../Files/Rides/Ride");
            path.append( to_string(id));
            path.append(".txt");

            remove(path.c_str());

            cout<<"Ride deleted successfully"<<endl;
        } else{
            cout<<"Ride not found!"<<endl;
        }
    }
}

void Admin::updateRide(){
    /* Function to update the ride details
    */
    int id;
    cout<<"Enter ride Id to update : ";
    cin>>id;

    if ( id>this->maxRideCount || id<1 ){
        cout<<"Invalid Id to update!"<<endl;
    } else{
        bool flag=false;
        string line;
    
        ifstream file;
        file.open("../Files/Rides/Rides.txt");
        ofstream outfile("../Files/Rides/tmp.txt"); //file to store non deleted values

        while(getline(file,line)){
            stringstream ss(line);
            int tmpId;
            ss>>tmpId;
            if (tmpId!=id){
                outfile<<line<<endl;
            } else if (tmpId==id) {
                unsigned short int minAge, maxAge;
                string ride_name,desc, occupancy;
                //Ride found anf now asking for new details
                cout<<"Enter ride name : ";
                cin.ignore();
                cin>>ride_name;

                cout<<"Enter ride description (don't use any commas{,} ) : ";
                cin.ignore();
                getline(cin,desc);

                cout<<"Enter minimum age : ";
                cin>>minAge;

                cout<<"Enter maximum age : ";
                cin>>maxAge;

                cout<<"Enter maximum occupancy : ";
                cin>>occupancy;

                stringstream ss;
                ss<<id<<",";
                ss<<ride_name<<",";
                ss<<desc<<",";
                ss<<minAge<<",";
                ss<<maxAge<<",";
                ss<<occupancy<<'\n';
                outfile<<ss.str();
                //end
                flag=true;
            }
        }

        outfile.close();
        file.close();

        //deleting previous file
        remove("../Files/Rides/Rides.txt");
        rename("../Files/Rides/tmp.txt","../Files/Rides/Rides.txt");
    
        if (flag){
            cout<<"Ride updated successfully"<<endl;
        } else{
            cout<<"Ride not found!"<<endl;
        }
    }
}


void Admin::searchGuest(unsigned long long int GuestID){
    /*  Check if guest is valid
        And display the details of its last ride
    */
    Guest g(GuestID);

    if (g.uid == 0 ) {
        cout<<"Guest not found"<<endl;
        return;
    }
    else{
        cout<<endl<<"Guest Information loaded successfully"<<endl;
        cout<<"Id : "<<g.uid<<endl;
        cout<<"Name : "<<g.name<<endl;
        cout<<"Age : "<<g.age<<endl;
        cout<<"Gender : "<<g.gender<<endl;
        cout<<"Number : "<<g.number<<endl;
    }


    string path("../Files/Guest/GuestTrack.txt"), data, tmp;
    ifstream file;
    file.open(path);
    
    if (file.is_open()){

        while (getline(file,data)){
            stringstream ss(data);        //making stringstream out of string

            unsigned long long int tmpId;
            ss>>tmpId;

            if (tmpId==GuestID){
                string session,tmp;
                stringstream tt(ss.str());

                while (getline(tt,session,','));
                cout<<"Last Session Id : "<<session<<endl;

                //to extract 
                stringstream temp(session);
                getline(temp,tmp,':');
                getline(temp,tmp,':');
                int rideNo = stoi(tmp);

                //Opening Ride File to get session info
                string path("../Files/Rides/Ride");
                path.append( to_string(rideNo));
                path.append(".txt");

                ifstream file;
                file.open(path);
                string line;
                if (file.is_open()){
                    
                    while (getline(file,line)){
                        stringstream tt(line);
                        string sessionId;

                        tt>>tmp;
                        tt>>sessionId;

                        if (sessionId == session){
                            string date,time;

                            tt>>tmp;
                            tt>>date;
                            tt>>tmp;
                            tt>>time;
                            
                            cout<<"Date : "<<date<<endl;
                            cout<<"Time : "<<time<<endl;
                        }
                    }
                }   
                else{
                    cout<<"Error opening Ride file"<<endl;
                } 
                break;
            }
        }
    }
    else{
        cout<<"Error opening Guestdata file"<<endl;
    }
    file.close();
}


void Admin::seeRating(){

    ifstream file;
    file.open("../Files/Admin/Guest.txt");
    string line,tmp;
    float rating;

    for (int i=0; i<3; i++){
        getline(file,line);
    }

    stringstream ss(line);
    ss>>tmp;
    ss>>rating;
    cout<<"Cummulative so far : "<<(rating)<<endl;
}
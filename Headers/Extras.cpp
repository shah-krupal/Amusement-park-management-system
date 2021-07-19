#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

string getDate(){
    /*  Function to return Date string
    */

    time_t now = time(0) ;
    tm* date_time = localtime(&now) ;

    int day = date_time->tm_mday;
    int month = date_time->tm_mon+1 ;
    int year = date_time->tm_year+1900 ;

    stringstream time ;
    time<<year;

    if (month < 10)
        time<<"0" ;
    time<<month;

    if (day < 10)
        time<<"0";
    time<<day;

    return time.str();
}


string hashFunc(string password){ 
    /*  A Hashfunction to return the hash string of password
        Always the Hashes are compared not the actual string
    */
    stringstream local ;
    
    int len = password.length() ;
    int array[len] ;
    
    for (int i = 0 ; i < len ; i++){

        array[i] = password[i] ;
        if (array[i] < 100)
            local<<"0" ;
        local<<array[i] ;
    }
    string pass = local.str() ;
    
    for (int i=0 ; i<4 ; i++)    // shift cipher
    {
        string tmp = pass.substr(0,3) ;
        pass.erase(0,3) ;
        pass.append(tmp) ;
    }
      
    return pass;
}

template <class T>
bool between(T a, T min, T max){
    // check if a is between min and max
    if ( a>=min && max>=a){
        return true;
    }
    
    return false;
}

string getTime(){
    /* Function to return string of time
    */
    time_t now = time(0);
    tm *ltm = localtime(&now);
    // India is +5:30 frot GMT
    int sec = ltm->tm_sec;
    int min = ltm->tm_min ;
    int hr  = ltm->tm_hour;
    
    string ans("(");

    ans.append(to_string(hr));
    ans.append(":");
    ans.append(to_string(min));
    ans.append(":");
    ans.append(to_string(sec));
    ans.append(")");

    return ans;
}

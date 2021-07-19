#include "Guest.h"
#include"sstream"
#include"fstream"
#include<iostream>
#include<ctime>
using namespace std ;

Guest::Guest(){
    /* Default Constructor to create Guest Object and load essetial vars
    */
    loadVars();
}

Guest::Guest(unsigned long long int Id){
    /* Parametrised constructor 
        Seraches Data for Guest with given Id
        Loads All information
        Returns Object with Id=0 if no record is found
    */
    string path("../Files/Guest/Guestdata.txt"), data, tmp;

    ifstream file;
    file.open(path);
    
    if (file.is_open()){

        bool flag=false;
        while (getline(file,data)){
            stringstream ss(data);        //making stringstream out of string

            unsigned long long int tmpId;
            ss>>tmpId;

            if (tmpId==Id){
                flag = true;

                unsigned long int Uid; 
                string Name;
                unsigned short int Age;
                char Gender;
                string Number ;

                getline(ss,tmp,',');
                getline(ss,Name,',');
                ss>>Age;
                getline(ss,tmp,',');
                ss>>Gender;
                getline(ss,tmp,',');
                getline(ss,Number,',');
                
                this->uid = Id;
                this->age = Age;
                this->name = Name;
                this->number = Number;
                this->gender = Gender;

                this->loadVars();
                break;
            }
        }

        if (!flag){
            this->uid = 0;
        }
    }
    else{
        cout<<"Error opening Guestdata file"<<endl;
    }
    file.close();
}



void Guest::loadVars(){
    /* Loads all four essential vars to Guest Object
    */
    string path("../Files/Admin/Guest.txt"), tmp;
    
    ifstream file;
    file.open(path);

    if (file.is_open()){
        file>>tmp;
        file>>this->counter;
        file>>tmp;
        file>>this->guest_count;
        file>>tmp;
        file>>this->overall;
        file>>tmp;
        file>>this->previous;
        //cout<<"Loaded vars : counter"<<counter<<" guest_count"<<guest_count<<" overall"<<overall<<" previous"<<previous<<endl;
    }
    else{
        cout<<"Problem opening Admin Guest file"<<endl;
    }
    file.close();
}

void Guest::putVars(){
    /* Puts all four essential vars to Guest Object to file
        so they can be used later
     */
    string path("../Files/Admin/Guest.txt"), tmp;
    
    ofstream file;
    file.open(path);
    if (file.is_open()){
        file<<"counter= "<<this->counter<<endl; 
        file<<"guest_count= "<<this->guest_count<<endl; 
        file<<"overall= "<<this->overall<<endl; 
        file<<"previous= "<<this->previous<<endl; 
        //cout<<"Putted vars : counter"<<counter<<" guest_count"<<guest_count<<" overall"<<overall<<" previous"<<previous<<endl;
    }
    else{
        cout<<"Error opening Admin Guest file for puts"<<endl;
    }
    file.close();
}

void Guest::datafiller(unsigned long long int uid,string name,unsigned short int age,char gender,string number){
    /* A setter function
    */
    this->uid = uid ;
    this->name = name ;
    this->age = age ;
    this->gender = gender ;
    this->number = number ;
    stringstream data ;
    data<<uid<<"," ;
    data<<name<<"," ;
    data<<age<<"," ;
    data<<gender<<"," ;
    data<<number<<endl;

    fstream file;
    file.open("../Files/Guest/Guestdata.txt",ios::app);
    
    if (file.is_open())
        file<<data.str();
    else    
        cout<<"Error opening GuestData file";
    file.close();

    file.open("../Files/Guest/GuestTrack.txt",ios::app);
    if ( file.is_open()){
        file<<uid<<" : "<<endl;
    }
    else{
        cout<<"Error opening GuestTrack file";
    }
    file.close();
}

void Guest::input(){
    /*  Function to take input from console and call setter function
    */
    string tmpnumber ;
    string tmpname ;
    unsigned int tmpuid; 
    unsigned short int tmpage;
    char tmpgender;
    cout<<endl<<"Please Provide the details mentioned\n" ;
    cout<<"Name : " ;
    cin>>tmpname ;
    cout<<"Age : " ;
    cin>>tmpage ;
    cout<<"Gender : " ;
    cin>>tmpgender ;
    cout<<"Mobile number : " ;
    cin>>tmpnumber ;

    unsigned long long int id_number = get_id() ;    

    // to input data to the file
    datafiller(id_number,tmpname,tmpage,tmpgender,tmpnumber) ;
}

unsigned long long int Guest::get_id(){
    /* Function to generate Unique ID using Date and previous Data
    */

    time_t now = time(0) ;       // to get time date info from system
    tm* date_time = localtime(&now) ;
    int month = date_time->tm_mon+1 ;
    int year = date_time->tm_year+1900 ;
    int day = date_time->tm_mday ;

    if (previous != day)  // to set zero on new day
        guest_count = 0 ;
    previous = day ;

    stringstream time ;
    time<<year ;
    if (month < 10)
        time<<"0" ;
    time<<month ;

    if (day < 10)
        time<<"0" ;
    time<<day ;
    guest_count++ ;

    if (guest_count<10)
        time<<"00" ;
    else if (guest_count<100)
        time<<"0" ;
    time<<guest_count ;

    return (  stoll(time.str()) ) ;
}

void Guest::ratings(){
    /* Take rating from User and call   cumulative_rating function
    */
    int rating ;
    cout<<"Rate us and your experience \nOut of 10 : " ;
    cin>>rating ;
    cout<<"\nThanks for rating" ;
    cumulative_rating(rating) ;
    cout<<"\nOUR CUMULATIVE RATING IS : "<<overall<<endl ;
}

void Guest::cumulative_rating(int rate){
    /* Function to compute cumulative rating
    */
    float tmp = overall*counter ;
    tmp = tmp + rate ;
    counter++ ;
    overall = tmp/counter ;
}
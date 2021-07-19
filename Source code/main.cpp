#include "../Headers/Admin.cpp"
#include "../Headers/Ride.cpp"
// #include "../Headers/Guest.cpp"  #included in Ride.cpp
#include <iostream>

using namespace std;

bool FoundRide(unsigned short int CurrID);

int main(){
    int ch;

    do {
        cout<<endl<<endl<<"WELOCOME TO AMUSEMENT PARK"<<endl;
        cout<<"1. Admin Login"<<endl;
        cout<<"2. Rides Login"<<endl;
        cout<<"3. Guest Login"<<endl;
        cout<<"4. Exit "<<endl;

        cout<<"Enter your choice : ";
        cin>>ch;

        switch(ch){
            case 1:{
                Admin Ad;

                string pass;
                do {
                    cout<<"Enter password (0 to exit) : ";
                    cin>>pass;

                    if (pass == "0"){
                        break;
                    }

                } while( hashFunc(pass)!=Ad.pass);

                if (pass == "0" ){
                    break;
                }

                if( hashFunc(pass) == Ad.pass ){
                    int a_ch;
                    do {
                        cout<<endl<<"1. Search a Guest  "<<endl;
                        cout<<"2. Add a new Ride  "<<endl;
                        cout<<"3. Update a Ride  "<<endl;
                        cout<<"4. Delete a ride  "<<endl;
                        cout<<"5. Change password  "<<endl;
                        cout<<"6. See Rating "<<endl;
                        cout<<"7. Exit  "<<endl;

                        cout<<"Enter your choice : ";
                        cin>>a_ch;

                        switch(a_ch){
                            case 1: {
                                unsigned long long int Id;
                                cout<<"Enter Guest Id to search : ";
                                cin>>Id;

                                Ad.searchGuest(Id);
                                break;
                            }
                            case 2: {
                                Ad.addRide();
                                break;
                            }
                            case 3: {
                                Ad.updateRide();
                                break;
                            }
                            case 4: {
                                Ad.deleteRide();
                                break;
                            }
                            case 5: {
                                Ad.changePass();
                                break;
                            }
                            case 6:{
                                Ad.seeRating();
                            }
                            case 7: {
                                a_ch=0;
                                break;
                            }
                            default :{
                                cout<<"Invalid choice ! "<<endl;
                                break;
                            }
                        }
                    } while(a_ch);
                }
                break;
            }

            case 2:{
                unsigned short int RideId;
                
                do {
                    cout<<"Enter Ride Id to operate (0 to exit ): ";
                    cin>>RideId;

                    if (RideId==0){
                        break;
                    }
                } while ( !FoundRide(RideId));

                if (RideId==0){
                    break;
                }

                string pass("parkRide"), user_pass;
                pass.append(to_string(RideId));

                do {
                    cout<<"Enter password : ";
                    cin>>user_pass;

                } while(user_pass != pass);

                int ch;
                Ride CurrRide(RideId); // Creating the ride instance

                do {
                    cout<<endl<<"MENU for Ride No "<<RideId<<endl;
                    cout<<"1. Start a new session "<<endl;
                    cout<<"2. Exit "<<endl;

                    cout<<"Enter your choice : ";
                    cin>>ch;

                    switch(ch){
                        case 1:{
                            CurrRide.StartNewSession();
                            break;
                        }
                        case 2:{
                            CurrRide.putSessionId();
                            ch=0;
                            break;
                        }
                        default :{
                            cout<<"Invalid choice !"<<endl;
                            break;
                        }
                    }

                } while (ch);

                break;
            }

            case 3:{
                int select ;
                do {
                    Guest guestobj;
                    cout<<endl<<"GUEST PAGE"<<endl;
                    cout<<"1. For guest entry"<<endl;
                    cout<<"2. For Reviewing us"<<endl;
                    cout<<"3. Exit"<<endl;

                    cout<<"Enter your choice : ";
                    cin>>select;

                    switch(select){
                        case 1:{
                            guestobj.input() ;
                            guestobj.putVars();
                            break;
                        }
                        case 2:{
                            guestobj.ratings() ;
                            guestobj.putVars();
                            break;
                        }
                        case 3:{
                            select=0;
                            break;
                        }
                        default:{
                            cout<<"Invalid Choice!"<<endl;
                            break;
                        }
                    }
                } while(select);

                break;
            }

            case 4:{
                cout<<"Unsaved data was lost"<<endl;
                cout<<endl<<"THANKS FOR USING"<<endl;
                cout<<endl<<"Made with Love"<<endl;
                cout<<"By :- Krupal Shah(202001057)"<<endl;
                cout<<"      Dakshveer Singh(202001048)"<<endl;
                ch=0;
                break;
            }

            default:{
                cout<<"Invalid Choice"<<endl;
                break;
            }
        }
    } while(ch);

    return 0;
}


bool FoundRide(unsigned short int CurrID){
    /*
        Function to check if a ride is found
    */
    bool flag = false;
    string line;
    ifstream file;
     
    file.open("../Files/Rides/Rides.txt");
    
    while(getline(file,line)){
        stringstream ss(line);
        int tmpId;
        ss>>tmpId;
        if (tmpId==CurrID){
            flag=true;
            break;
        }
    }
    return flag;
}

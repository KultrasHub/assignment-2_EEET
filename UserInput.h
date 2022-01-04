
#include "Checker.h"
#include <string>
using namespace std;
//ask for id
string AskForItemID()
{
    string id;
    cout<<"Please enter id for this item:"<<endl;
    cin>>id;
    //check for valid
    if(isIdValid(id))
    {
        return id;
    }
    else{
        cout<<"ID is not in correct format!(Ixxx-yyy)"<<endl;
        cout<<"xxx is an unique code"<<endl;
        cout<<"yyyyy is publish year"<<endl;
        cout<<"Please re-enter the id!"<<endl;
        cout<<"---"<<endl;
        return AskForItemID();
    }
}
//ask for name
string AskForItemName()
{
    string name;
    //there are no condition for name
    cout<<"Please enter title for this product:"<<endl;
    cin.ignore();
    getline(cin,name);
    if(isItemNameValid(name))
    {
        return name;
    }
    else{
        cout<<"Title should represent the item"<<endl;
        cout<<"Please re-enter the title"<<endl;
        cout<<"---"<<endl;
        return AskForItemName();
    }
}
//ask for rental Type
string AskForRentType()
{
    string type;
    cout<<"Please enter an option for rent type"<<endl;
    cout<<"1 .Record"<<endl;
    cout<<"2 .DVD"<<endl;
    cout<<"3 .Game"<<endl;
    cin>>type;
    if(type=="1")
    {
        return "Record";
    }
    else if( type=="2")
    {
        return "DVD";
    }
    else if(type=="3")
    {
        return "Game";
    }
    else{
        cout<<"Invalid Option!"<<endl;
        cout<<"You should only enter either 1 or 2 or 3! no space or special characters"<<endl;
        cout<<"Please re-select your option"<<endl;
        cout<<"---"<<endl;
        return AskForRentType();
    }
}
//ask for loan type
string AskForLoanName()
{
    string type;
    cout<<"Please enter an option for loan type"<<endl;
    cout<<"1 .2-day"<<endl;
    cout<<"2 .1-week"<<endl;
    cin>>type;
    if(type=="1")
    {
        return "2-day";
    }
    else if( type=="2")
    {
        return "1-weel";
    }
    else{
        cout<<"Invalid Option!"<<endl;
        cout<<"You should only enter either 1 or 2! no space or special characters"<<endl;
        cout<<"Please re-select your option"<<endl;
        cout<<"---"<<endl;
        return AskForLoanName();
    }
}
//ask for copies Amount
int AskForCopiesAmount()
{
    string amount;
    cout<<"Please enter amount of copies"<<endl;
    cin>>amount;
    if(isCopiesValid(amount))
    {
        return stoi(amount);
    }
    else{
         cout<<"Invalid Input"<<endl;
         cout<<"amount of copies must be a positive integer!, +1 or 1.0 are also considered invalid instead try 1"<<endl;
         cout<<"Please re-enter the copies amount"<<endl;
         cout<<"---"<<endl;
         return AskForCopiesAmount();
    }
}
// ask for fee
float AskForFee()
{
    string fee;
    cout<<"Please enter the rent fee of this item"<<endl;
    cin>>fee;
    if(isFeeValid(fee))
    {
        return stof(fee);
    }
    else{
        cout<<"Invalid Input"<<endl;
        cout<<"Fee must be a numeric value!"<<endl;
        cout<<"Please re-enter the rental fee"<<endl;
        cout<<"--"<<endl;
        return AskForFee();
    }
}
//ask for genre
string AskForGenre()
{
    string type;
    cout<<"Please enter an option for DVD Genre"<<endl;
    cout<<"1 .Action"<<endl;
    cout<<"2 .Horror"<<endl;
    cout<<"3 .Drama"<<endl;
    cout<<"4 .Comedy"<<endl;
    cin>>type;
    if(type=="1")
    {
        return "Action";
    }
    else if( type=="2")
    {
        return "Horror";
    }
    else if(type=="3")
    {
        return "Drama";
    }
    else if(type=="4")
    {
        return "Comedy";
    }
    else{
        cout<<"Invalid Option!"<<endl;
        cout<<"You should only enter either 1 or 2 or 3 or 4! no space or special characters"<<endl;
        cout<<"Please re-select your option"<<endl;
        cout<<"---"<<endl;
        return AskForGenre();
    }
}
//ask for item Selection 
int AskForSelection(int maxSize)
{
    string userInput;
    cin>>userInput;
    if(isCopiesValid(userInput))
    {
        //check stoi
        int option=stoi(userInput);
        if(option<maxSize)
        {
            return option;
        }
        else{
            //wrong input
            cout<<"Your option is out of order!"<<endl;
            cout<<"Please Re-enter your option!"<<endl;
            return AskForSelection(maxSize);
        }
    }
    else{
        //wronng input
        cout<<"Your option is not valid!"<<endl;
        cout<<"Please Re-enter your option!"<<endl;
        return AskForSelection(maxSize);
    }
}
//ask for item attribute
int AskForAttribute(int max)
{
    string input;
    cin>>input;
    //check
    if(isCopiesValid(input))
    {
        //check size
        int option=stoi(input);
        if(option<=max)//max for return to menu
        {
            return option;
        }
        else{
            cout<<"Invalid Option!"<<endl;
            cout<<"Try again with the given option"<<endl;
            return AskForAttribute(max);
        }
    }
    else{
        cout<<"Invalid Option!"<<endl;
        cout<<"Try again with the given option"<<endl;
        return AskForAttribute(max);
    }
}
//Customer Service------------------------------------
string AskForCustomerID()
{
    string id;
    cout<<"Please enter id for this Customer:"<<endl;
    cin>>id;
    //check for valid
    if(isCustomerIdValid(id))
    {
        return id;
    }
    else{
        cout<<"ID is not in correct format!(Cxxx)"<<endl;
        cout<<"xxx is an unique code"<<endl;
        cout<<"Please re-enter the id!"<<endl;
        cout<<"---"<<endl;
        return AskForCustomerID();
    }
}
//customer name
string AskForCustomerName()
{
    string name;
    //there are no condition for name
    cout<<"Please enter name for this Customer:"<<endl;
     cin.ignore();
    getline(cin,name);
    if(isNameValid(name))
    {
        return name;
    }
    else{
        cout<<"Invalid Name"<<endl;
        cout<<"Please re-enter the customer Name"<<endl;
        cout<<"---"<<endl;
        return AskForCustomerName();
    }
}
//address
string AskForAddress()
{
    string address;
    //there are no condition for address
    cout<<"Please enter address for this Customer:"<<endl;
    cin.ignore();
    getline(cin,address);
    return address;
}
//string phone 
string AskForPhoneNumber()
{
    string phone;
    cout<<"Please enter phone number of this Customer:"<<endl;
        cin>>phone;
    if(isPhoneValid(phone))
    {
        return phone;
    }
    else{
        cout<<"Invalid Phone Number"<<endl;
        cout<<"Please re-enter the customer Phone"<<endl;
        cout<<"---"<<endl;
        return AskForPhoneNumber();
    }
}
//ask for rank
string AskForRank()
{
    string rank;
    cout<<"Please Select a rank Option"<<endl;
    cout<<"1 .Guest Member"<<endl;
    cout<<"2 .Regular Member"<<endl;
    cout<<"3 .VIP Member"<<endl;
    cin>>rank;
    if(rank=="1")
    {
        return "Guest";
    }
    else if(rank =="2")
    {
        return "Regular";
    }
    else if(rank=="3")
    {
        return "VIP";
    }
    else{
        cout<<"Invalid Option"<<endl;
        cout<<"Please Re-enter your option"<<endl;
        cout<<"---"<<endl;
        return AskForRank();
    }
}

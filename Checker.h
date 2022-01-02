#include <string>
#include <iostream>
#include <vector>
using namespace std;
//Checking Item-----------------------------------------------------------------
bool isCopiesValid(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!isdigit(s[i]))
        {
            cout<<"corrupted amount of copies in Stock: "<<s<<" is not a positive integer"<<endl;
            return false;
        }
    }
    return true;
}
//check fee
bool isFeeValid(string str)
{
    int dot = 1;//allow one dot
    //not allow + or -
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
        {
            if (str[0] == ' ')//only first char are allowed to be space
            {
                continue;
            }
            else if (str[i] == '.' && dot == 1)
            {
                dot--;
                continue;
            }
            else
            {         
                // if(str[i]=='\r'&&i == (str.length() -1))//in csv file line contain \r at the end 
                // {
                //     //cout<<"special key found";
                //     cout<<"does here is fine"<<endl;
                //     return true;
                // }  
                cout<<"corrupted item fee "<<str<<" is not a valid fee number"<<endl;
                return false;
            }
        }
        else
        {
            if (i == (str.length() -1))//last key 
            {
                return true;
                break;
            }
            else
            {
                continue;
            }
        }
    }
    
    return false;
}
//check rental Type
bool isRentalValid(string s)
{
    if(s=="Game"||s=="DVD"||s=="Record")
    {
        return true;
    }
    else{
        cerr<<"invalid Rental Type"<< s<<endl;
        return false;
    }
}
//check loan Type
bool isLoanTypeValid(string s)
{
    if(s=="1-week"||s=="2-day")
    {
        return true;
    }
    else{
        cerr<<"invalid Loan Type"<<s<<endl;
        return false;
    }
}
//check id
bool isIdValid(string s)
{
    return true;
}
//check item name
bool isItemNameValid(const string s)
{
    if(s.length()<3)
    {
        cout<<"title too short, at least 3 characters long"<<endl;;
        return false;
    }
    int count=0;
    //check if all space
    for(int i=0;i<s.length();i++)
    {
        if(s[i]==' ')
        {
            count++;
        }
    }
    if(count==s.length())
    {
        cout<<"you cannot leave empty space"<<endl;
        return false;
    }
    return true;
}
//check DVD genre
bool isDVDGenreValid(string s)
{
    if(s=="Action"||s=="Drama"||s=="Horror"||s=="Comedy")
    {
        return true;
    }
    return false;
}
//Checking Customer-----------------------------------------------------------------
bool isCustomerIdValid(string s)
{
    //cout<<"id work"<<endl;
    return true;
}
//check phone number
bool isPhoneValid(string s)
{
    //check length
    if(s.length()>12||s.length()<9)
    {
        cout<<"phone number has 9 to 12 digits"<<endl;
        return false;
    }

    //check for digits
    for(int i=0;i<s.length();i++)
    {
        if(!isdigit(s[i]))
        {
            cout<<"invalid Phone Number"<<endl;
            return false;
        }
    }
    return true;
}
//check rentAmount
bool isRentAmountValie(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!isdigit(s[i]))
        {
            cout<<"corrupted rental Amount "<<s<<" is not a positive integer"<<endl;
            return false;
        }
    }
    return true;
}
//check if rank is valid
bool isRankValid(string s)
{
    if(s=="VIP"||s=="Guest"||s=="Regular")
    {
        return true;
    }
    return false;
}
//check name valid
bool isNameValid(string s)
{
    if(s.length()<5)
    {
        cout<<"name too short, at least 5 characters long"<<endl;;
        return false;
    }
    int count=0;
    //check if all space
    for(int i=0;i<s.length();i++)
    {
        if(s[i]==' ')
        {
            count++;
        }
    }
    if(count==s.length())
    {
        cout<<"you cannot leave empty space"<<endl;
        return false;
    }
    return true;
}
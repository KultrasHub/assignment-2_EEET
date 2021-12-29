#include <iostream>
#include <string>
using namespace std;
class Item{
    private:
        string id;
        string title;
        string rent;
        string loan;
        int copies;
        float rentalFee;
        bool rentalStatus;
    // method
    public:
    //require copies In stock
        Item(string newId,string newTitle,string rType,string lType,int copiesInStock,float fee)
        {
            id=newId;
            title=newTitle;
            rent=rType;
            loan=lType;
            this->copies =copiesInStock;
            this->rentalFee=fee;
            if(copies>0)
            {
                rentalStatus=true;
            }
            else{
                rentalStatus=false;
            }
        }
    //dont require copies In Stock
        Item(string newId,string newTitle,string rType,string lType,float fee)
        {
            id=newId;
            title=newTitle;
            rent=rType;
            loan=lType;
            this->copies =0;
            this->rentalFee=fee;
            rentalStatus=false;
        }
    //Set 
        void SetID(string newID)
        {
            id=newID;
        }
        void SetTitle(string newTitle)
        {
            title=newTitle;
        }
        void SetRetalType(string rType)
        {
            rent=rType;
        }
        void SetLoanType(string lType)
        {
            loan=lType;
        }
        void SetCopiesInStock(int amount)
        {
            copies=amount;
        }
        void SetRentFee(float value)
        {
            rentalFee=value;
        }
    //Get
        string GetID()
        {
            return id;
        }
        string GetTitle()
        {
            return title;
        }
        string GetRentalType()
        {
            return rent;
        }
        string GetLoanType()
        {
            return loan;
        }
        int GetCopieInStock()
        {
            return copies;
        }
        float GetRentFee()
        {
            return rentalFee;
        }
        bool GetStatus()//use to check if an item is "actionable"
        {
            return rentalStatus;
        }
    //Other Method
    private:
    ///Check there are still copies in stock and set rental status accordingly
        void CheckCopiesInStock()
        {
            if(copies<=0)
            {
                if(!rentalStatus)
                {
                    return;
                }
                //there are no copy left
                rentalStatus=false;
            }
            else{
                if(rentalStatus)
                {
                    return;
                }
                //there are still copies
                rentalStatus=true;
            }
        }
    public:
    //add default of one
        void AddCopies()
        {
            copies++;
            CheckCopiesInStock();
        }
    //add with amount
        void AddCopies(int amount){
            copies+=amount;
             CheckCopiesInStock();
        }
    //return Item
        void SetReturn()
        {
            copies++;
            CheckCopiesInStock();
        }
        void SetReturn(int amount){
            copies+=amount;
            CheckCopiesInStock();
        }
    //borrow Item
        bool CheckBorrow(){
            //check
            if(copies>=1)
            {
            //reduce
            copies--;
            //recheck stock
            CheckCopiesInStock();
            return true;
            }
            else{
                return false;
            }
        }
        bool CheckBorrow(int amount){
             //check
            if(copies>=amount)
            {
            //reduce
            copies-=amount;
            //recheck stock
            CheckCopiesInStock();
            return true;
            }
            else{
                return false;
            }
        }
    //Display
        virtual void Display(){
            cout<<"--"<<endl;
            cout<<"Item: "<<title<<" - "<<id<<endl<<" rent type: "<<GetRentalType()<<endl<<" loan type: "<<GetLoanType()<<endl<<" copies: "<<copies<<endl<<" fee: "<<rentalFee<<endl<<" status: "<<rentalStatus<<endl;
        }
    
};
class DVDItem:public Item{
    private:
        string genre;
    //method
    public: 
    //with copies amount
    DVDItem(string id,string title,string rType,string lType,int copiesInStock,float fee,string genre):Item::Item(id,title,rType,lType,copiesInStock,fee){
        this->genre=genre;
    }
    //without copies amount 
    DVDItem(string id,string title,string rType,string lType,float fee,string genre):Item::Item(id,title,rType,lType,fee){
        this->genre=genre;
    }
    //Set
    void SetGenre(string g){
        genre=g;
    }
    //Get
    string GetGenre()
    {
        return genre;
    }
    //overriding
    void Display(){
        cout<<"Item: "<<GetTitle()<<" - "<<GetID()<<endl<<" rent type: "<<GetRentalType()<<endl<<" loan type: "<<GetLoanType()<<endl<<" DVD Genre: "<<GetGenre()<<endl<<" copies: "<<GetCopieInStock()<<endl<<" fee: "<<GetRentFee()<<endl<<" status: "<<GetStatus()<<endl;
    }
};
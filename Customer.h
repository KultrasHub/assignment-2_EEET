#include <string>
#include <iostream>
#include <vector>
#include "Item.h"


using namespace std;
class Customer {
private:
	string name;
	string id;
	string address;
	string phone;
protected:
	vector<Item*> itemList;
	string rankName;
	//promotion
	int rentCount;
public:
    //constructor
	Customer(){
        name = "NA";
	    id = "NA";
	    address = "NA";
	    phone = "NA";
    }
    //with full detail
	Customer(string name, string id, string address, string phone){
        this->name = name;
	    this->id = id;
	    this->address = address;
	    this->phone = phone;
    }
	virtual ~Customer()
	{
		//clan the item List
		//delete all pointer in List
        // for(int i=0;i<itemList.size();i++)
        // {
        //     Item* pItem=itemList.at(i);
        //     delete pItem;
        // }
        itemList.clear();
	}
    //display
	virtual void displayAllInformation(){
		cout<<"--"<<endl;
        cout << "Name: " << this->name << endl;
	    cout << "Id: " << this->id << endl;
	    cout << "Address: " << this->address << endl;
	    cout << "Phone: " << this->phone << endl;
    }
	void DisplaySelection(int index)
	{
		cout<<index<<" ."<<name<<" -id: "<<id<<endl;
	}
	int DisplayAttribute()
	{
		cout<<"0 .Id: "<<id<<endl;
		cout<<"1 .Name: "<<name<<endl;
		cout<<"2 .Address: "<<address<<endl;
		cout<<"3 .Phone: "<<phone<<endl;
		return 4;
	}
    //setter, getter
	//setter
	void setName(string name){
        this->name = name;
    }
	void setId(string id)
    {
        this->id=id;
    }
	void setAddress(string address)
	{
		this->address=address;
	}
	void setPhone(string phone)
	{
		this->phone=phone;
	}
	void setRentCount(int count)
	{
		rentCount=count;
	}
	//getter
	string getId(){
        return id;
    }
	string getName(){
        return name;
    }
	string getAddress()
	{
		return address;
	}
	string getPhone()
	{
		return phone;
	}
	bool compareRank(string name)
	{
		if(name==rankName)
		{
			return true;
		}
		else{
			return false;
		}
	}
	virtual string getRank()
	{
		return rankName;
	}
	//construct an osstream store informationn for saving
	//savign innfomation
	ostream& getSavingInfomation(ostream& os)
	{
		//action with os
		string c=",";
		os<<getId()<<c<<getName()<<c<<getAddress()<<c<<getPhone()<<c<<rentCount<<c<<rankName<<endl;
		//item
		for(int i=0;i<itemList.size();i++)
		{
			os<<itemList.at(i)->GetID()<<endl;
		}
		return os;
	}
	//pass pointer
	friend ostream& operator<<(ostream& os,Customer* c)
	{
		//cout<<"does this get call"<<endl;
		return c->getSavingInfomation(os);
	}
	//pass address
	friend ostream& operator<<(ostream& os,Customer& c)
	{
		//cout<<"does this get call"<<endl;
		return c.getSavingInfomation(os);
	}
	//function
	//Display all item borroww
	void DisplayAllItem()
	{
		cout<<"--"<<endl;
		cout<<rankName<<" member-id: "<<getId()<<" currently borrows:"<<endl;
		for(int i=0;i<itemList.size();i++)
		{
			cout<<i<<". "<<itemList.at(i);
		}
	}
	//display promotion
	void DisplayPromotion(int index)
	{
		cout<<index<<" ."<<getName()<<" -id: "<<getId()<<"has rented "<<rentCount<<"/3 times ";
		if(CanPromote())
		{
			cout<<" :ABLE to be promoted"<<endl;
		}
		else{
			cout<<" :UNABLE to be promoted"<<endl;
		}
	}
	//add an item to borrow list
	virtual void AddBorrowItem(Item* item)=0;
	virtual void AddBorrowItemWithNoUpdate(Item* item)
	{
		itemList.push_back(item);
		item->EmptyBorrow();
	}
	//return an item at the index
	virtual void ReturnAnItem(int atIndex)
	{
		//check if index is within list range
		if(atIndex>=itemList.size())
		{
			return;
		}
		//return Item
		itemList.at(atIndex)->SetReturn();
		//remove item from list
		itemList.erase(itemList.begin()+atIndex);
		//increase return count
		rentCount++;
	}
	//return an item by id
	//not use this for now
	//virtual void ReturnAnItem(string id);
	//check if this account can be promoted
	virtual bool CanPromote() 
	{
		if(rentCount>=3)
		{
			return true;
		}
		//cout<<"This account need "<<3-rentCount<<" rents "<<" to be able to get promoted!"<<endl;
		return false;
	}
	
};

//GuestAccount
class GuestAccount:public Customer{
	static const int maxBorrowAllowed=2;
	//constructor
	public:
	GuestAccount(string name, string id, string address, string phone):Customer(name,id,address,phone){
		rankName="Guest";
	};
	//overriding
	//check current borrow List
	void AddBorrowItem(Item* item)
	{
		//check if there are still copies in 
		if(!item->CheckBorrow())
		{
			//there are no in store to borrow
			cout<<"There are no available copies in store for item"<<item->GetID()<<endl;
			return;
		}
		//check if this customer still abkle to borrow item
		if(itemList.size()>=maxBorrowAllowed)
		{
			//at max borrow amount
			cout<<"Guest Member can onnly borrow at max 2 items"<<endl;
			return;
		}
		//check if item is borrowable
		if(item->is2DayVideo())
		{
			//guest cannot borrow 2day dvd or record
			cout<<"Guest Account can not borrow 2-day video(records and DVD)"<<endl;
			return;
		}
		cout<<rankName<<" id: "<<getId()<<" has successfully borrowed "<<item->GetID()<<endl;
		//guest can borrow
		itemList.push_back(item);
		//call borrow in item//reduce copies
		item->Borrow();
	}
	//display 	
	void displayAllInformation(){
    	Customer::displayAllInformation();
		//add rank
		cout<<"Rank: "<<rankName<<endl;
    }

};
//
class RegularAccount:public Customer{
	public:
	//constructor
	RegularAccount(string name,string id,string address,string phone):Customer(name,id,address,phone){
		rankName="Regular";
		rentCount=0;
	};
	//copy constructor from guess account for promotion
	RegularAccount(Customer* guest):Customer(guest->getName(),guest->getId(),guest->getAddress(),guest->getPhone()){
		rankName="RegularAccount";
		rentCount=0;
		cout<<"Guest Account:"<<guest->getId()<<" has been promoted to "<<"Regular Account"<<endl;
	};
	//overriding
	//function 
	//
	void AddBorrowItem(Item* item)
	{
		//check if there are stilll item in store
		if(!item->CheckBorrow())
		{
			//there are no in store to borrow
			cout<<"There are no available copies in store"<<endl;
			return;
		}
		//other wise this item has been borrowed succesfully
		cout<<rankName<<" id: "<<getId()<<" has successfully borrowed "<<item->GetID()<<endl;
		//guest can borrow
		itemList.push_back(item);
		//call borrow in item//reduce copies
		item->Borrow();
	}
	//display 	
	void displayAllInformation(){
    	Customer::displayAllInformation();
		//add rank
		cout<<"Rank: "<<rankName<<endl;
    }
};

//VIP Account
class VIPAccount:public Customer{
	int rewardPoint;
	public:
	//Constructor
	VIPAccount(string name,string id,string address,string phone):Customer(name,id,address,phone){
		rankName="VIP";
		rentCount=0;
	};
	//copy constructor for promotion
	VIPAccount(Customer* regularAccount):Customer(regularAccount->getName(),regularAccount->getId(),regularAccount->getAddress(),regularAccount->getPhone()){
		rankName="VIP";
		rentCount=0;
		cout<<"Regular Account:"<<regularAccount->getId()<<" has been promoted to"<<" VIP Account"<<endl;
	};
	//overriding
	//function 
	void AddBorrowItem(Item* item)
	{
		//check if there are stilll item in store
		if(!item->CheckBorrow())
		{
			//there are no in store to borrow
			cout<<"There are no available copies in store"<<endl;
			return;
		}
		//other wise this item has been borrowed succesfully
		cout<<rankName<<" member-id: "<<getId()<<" has successfully borrowed "<<item->GetID()<<endl;
		//guest can borrow
		itemList.push_back(item);
		//call borrow in item//reduce copies
		item->Borrow();
		//add reward Point
		cout<<rankName<<" member-id:"<<getId()<<"receive 10 reward points"<<endl;
		rewardPoint+=10;
		//check for free rennt
		if(rewardPoint>=100)
		{
			cout<<rankName<<" member-id:"<<getId()<<"can rent an item for free"<<endl;
		}
	}
	//display 	
	void displayAllInformation(){
    	Customer::displayAllInformation();
		//add rank
		cout<<"Rank: "<<rankName<<endl;
		cout<<"Reward Point:"<<rewardPoint<<endl;
    }
	void SetRewardPoint(int point)
	{
		rewardPoint=point;
	}
	//promote
	bool CanPromote()
	{
		cout<<"- Highest Rank";
		return false;
	}
};
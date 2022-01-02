#include "Customer.h"
#include "UserInput.h"
#include <fstream>
#include <sstream>
using namespace std;

class ItemManager{
    vector<Item*> itemList;
    //vector<int> changeIndex;
    //
    string fileLocation;
    //Method
    private: 
    //openn and assign item to list
        void OpenFile()
        {
            cout<<"Extracting Item File"<<endl;
            //Initualize
            string line;
            string word;
            vector<string> row;
            //open file 
            ifstream inFile(fileLocation,ios::in);
            //check if file has open successfully
            if(!inFile)
            {
                cerr<<"Fail to open file for reading"<<endl;
                return;//is a empty list
            }
            //track
            int count=1;
            string delimiter=",";            
            while(getline(inFile,line))
            {
                count++;
                //reset row
                row.clear();
                //get line by line
                //get individual section
                stringstream str(line);
                while(getline(str,word,','))
                {
                    row.push_back(word);
                }
                if(row.size()<6)
                {
                    cout<<"Missing column can cause crash in line!:"<<count<<endl;
                    cout<<"item Line: "<<count<<" is ignored and discarded in the next saving"<<endl;
                    continue;
                }
                if(!isIdValid(row.at(0)))
                {
                    cout<<"Invalid Item id in line: "<<count<<endl;
                }
                if(!isRentalValid(row.at(2)))
                {
                    cout<<"Invalid Rent Type in line:"<<count<<endl;
                }
                if(!isLoanTypeValid(row.at(3)))
                {
                    cout<<"Invalid Loan Type in line:"<<count<<endl;
                }
                if(!isCopiesValid(row.at(4)))
                {
                    cout<<"Invalid Copies Amount in line: "<<count<<","<<row.at(4)<<" will be converted to "<<stoi(row.at(4))<<endl;
                }
                if(!isFeeValid(row.at(5)))
                {
                    cout<<"Invalid Fee in line: "<<count<<","<<row.at(5)<<" will be converted to "<<stof(row.at(5));
                }
                //conversion
                int copiesAmount=stoi(row.at(4));
                float fee=stof(row.at(5));
                //build Item
                //check if word is valid
                if(row.at(2)!="DVD")
                {
                    Item* obj=new Item(row.at(0),row.at(1),row.at(2),row.at(3),copiesAmount,fee);
                    itemList.push_back(obj);
                    continue;
                }
                else if(row.size()==7&&isDVDGenreValid(row.at(6))){
                    //cout<<"any DVD"<<row.at(0)<<endl;
                    Item* obj=new DVDItem(row.at(0),row.at(1),row.at(2),row.at(3),copiesAmount,fee,row.at(6));
                    itemList.push_back(obj);
                    continue;
                }
                else{
                   //dvd genre
                    cerr<<"Error has occured due to invalid DVD Genre"<<endl;
                    cerr<<"it is recommended that you check DVD genre of datafile at line"<<count<<endl;
                    Item* obj=new DVDItem(row.at(0),row.at(1),row.at(2),row.at(3),copiesAmount,fee,row.at(6));
                    itemList.push_back(obj);
                }
            }
            //close file
            inFile.close();
            cout<<"Extracting Item Completed"<<endl;
        }
    public:
    //constructor
        ItemManager(string location)
        {
            fileLocation=location;
            OpenFile();
        }
    //deconstructor 
        ~ItemManager()
        {
            cout<<"Clean process to dellocatie all pointers!"<<endl;
            //delete all pointer in List
            for(int i=0;i<itemList.size();i++)
            {
                Item* pItem=itemList.at(i);
                delete pItem;
            }
            itemList.clear();
        }
    //set file location for futher
    //write items to File
        void WriteToFile()
        {
            cout<<"Start Saving"<<endl;
            //open file 
            ofstream fout(fileLocation,ios::out);
            //check if file has open successfully
            if(!fout)
            {
                cerr<<"File failed to open"<<endl;
                return;
            }
            // write to file
            for(int i=0;i<itemList.size();i++)
            {
                cout<<"item at index: "<<i<<"- "<<itemList.at(i);
                fout<<itemList.at(i);
            }
            fout.close();
            cout<<"Saving Complete"<<endl;
        }
    //get size
        int Size()
        {
            return itemList.size();
        }
    //add item To list
        void AddItem(Item* item)
        {
            itemList.push_back(item);
        }
        void AddItem()
        {
            //input to create an Item 
            cout<<"----"<<endl;
            //id
            string id=AskForItemID();
            //name
            string name=AskForItemName();
            //rennt
            string rent=AskForRentType();
            //loan
            string loan=AskForLoanName();
            //copies
            int copies=AskForCopiesAmount();
            //fee
            float fee=AskForFee();
            //build Item
            if(rent=="DVD")
            {
                //genre
                string genre=AskForGenre();
                Item* item=new DVDItem(id,name,rent,loan,copies,fee,genre);
                //add to list
                AddItem(item);
            }
            else{
                Item* item =new Item(id,name,rent,loan,copies,fee);
                AddItem(item);
            }
       }
    //remove item from List
        void RemoveItem(int index)
        {
            //must check that it is not borrowed
            if(itemList.at(index)->GetBorrowCount()>0)
            {
                cout<<"cannot delete item that is currently borrowed"<<endl;
                return;
            }
            else{
                //dealocate
                delete itemList.at(index);
                //delete pointer before erase from lsit
                itemList.erase(itemList.begin()+index);
                cout<<"Item has been deleted"<<endl;
            }
        }
    //get item from List
        Item*& GetItem(int index)
        {
            return itemList.at(index);
        } 
    //find item by id
        Item* GetItem(string id)
        {
            for(int i=0;i<itemList.size();i++)
            {
                if(itemList.at(i)->GetID()==id)
                {
                    //this is the item need to find
                    return itemList.at(i);
                }
            }
            return NULL;
        }
    //display
        void DisplayAllItem()
        {
            cout<<"------------------------------------------------"<<endl;
            cout<<"Items in shop"<<endl;
            for(int i=0;i<itemList.size();i++)
            {
                itemList.at(i)->Display();
            }
        }
    //display with order
        void DisplayAllItem(bool usingId,bool AZ)
        {
            if(AZ)
            {   cout<<"------------------------------------------------"<<endl;
                cout<<"Display in A-Z order"<<endl;
                SortListAZ(usingId);
            }
            else{
                cout<<"------------------------------------------------"<<endl;
                cout<<"Display in Z-A order"<<endl;
                SortListZA(usingId);
            }
            cout<<"Items in shop:"<<endl;
            for(int i=0;i<itemList.size();i++)
            {
                itemList.at(i)->Display();
            }
        }
    //display NoStock
        void DisplayNoStockItem()
        {
            cout<<"Item with no copies:"<<endl;
            for(int i=0;i<itemList.size();i++)
            {
                if(itemList.at(i)->GetCopieInStock()==0)
                {
                    itemList.at(i)->Display();
                }
            }
        }
    //display Selection
        void DisplaySelection()
        { 
            for(int i=0;i<itemList.size();i++)
            {
                itemList.at(i)->Display(i);
            }
        }
    //display item at index
        void DisplayItem(int index)
        {
            itemList.at(index)->Display();
        }
    //search
    //by id
        void SearchByID(string id)
        {
            for(int i=0;i<itemList.size();i++)
            {
                if(itemList.at(i)->GetID()==id)
                {
                    itemList.at(i)->Display();
                    return;
                }
            }
        }
    //by title
        void SearchByTitle(string title)
        {
            for(int i=0;i<itemList.size();i++)
            {
                if(itemList.at(i)->GetTitle()==title)
                {
                    itemList.at(i)->Display();
                    return;
                }
            }
        }
    //search only need title and id
    //by rentType
        Item* SearchByRentType(string rent)
        {
            for(int i=0;i<itemList.size();i++)
            {
                if(itemList.at(i)->GetRentalType()==rent)
                {
                    return itemList.at(i);
                }
            }
            return NULL;
        }
    //by loanTYpe
        Item* SearchByLoanType(string loan)
        {
            for(int i=0;i<itemList.size();i++)
            {
                if(itemList.at(i)->GetLoanType()==loan)
                {
                    return itemList.at(i);
                }
            }
            return NULL;
        }
    //by copies
        Item* SearchByCopies(int copies)
        {
            for(int i=0;i<itemList.size();i++)
            {
                if(itemList.at(i)->GetCopieInStock()==copies)
                {
                    return itemList.at(i);
                }
            }
            return NULL;
        }
    //by rentalFee
        Item* SearchByRentalFee(float fee)
        {
            for(int i=0;i<itemList.size();i++)
            {
                if(itemList.at(i)->GetRentFee()==fee)
                {
                    return itemList.at(i);
                }
            }
            return NULL;
        }
    //by DVD Genre
        Item* SearchByGenre(string Genre)
        {
            for(int i=0;i<itemList.size();i++)
            {
                if(itemList.at(i)->CompareGenre(Genre))
                {
                    return itemList.at(i);
                }
            }
            return NULL;
        }
//Action function-----------------------------------------------------------------
    //sort by id or title
    void swapItem(Item* &i1,Item* &i2)
    {
        Item* temp=i1;
        i1=i2;
        i2=temp;
    }
    private:
    //sort item list base on key( 0 for id, 1 for title) in alphabetical order
    void SortListAZ(bool usingId=true)
    {
        for(int i=0;i<itemList.size();i++)//outer
        {
            for(int j=i+1;j<itemList.size();j++)//inner
            {
                if(usingId)//using id to sort
                {
                    if(itemList.at(i)->GetID()>itemList.at(j)->GetID())//a-z
                    {
                        swapItem(itemList.at(i),itemList.at(j));
                    }
                }
                else{//using title
                    if(itemList.at(i)->GetTitle()>itemList.at(j)->GetTitle())//a-z
                    {
                        swapItem(itemList.at(i),itemList.at(j));
                    }
                }
            }
        }
    }
    //sortin list from z- a
    void SortListZA(bool usingId=true)
    {
        for(int i=0;i<itemList.size();i++)//outer
        {
            for(int j=i+1;j<itemList.size();j++)//inner
            {
                if(usingId)//using id to sort
                {
                    if(itemList.at(i)->GetID()<itemList.at(j)->GetID())//a-z
                    {
                        swapItem(itemList.at(i),itemList.at(j));
                    }
                }
                else{//using title
                    if(itemList.at(i)->GetTitle()<itemList.at(j)->GetTitle())//a-z
                    {
                        swapItem(itemList.at(i),itemList.at(j));
                    }
                }
            }
        }
    }

};
class CustomerManager{
    vector<Customer*> customer;
    string fileLocation;
    public:
        void ExtractFile( ItemManager &iList)
        {
            cout<<"Extracting Customer File"<<endl;
            string guestRank="Guest";
            string regularRank="Regular";
            string vipRank="VIP";
            string inValidInfo="NA";
            //Initualize
            string line;
            string word;
            vector<string> row;
            //open file 
            ifstream inFile(fileLocation,ios::in);
            //check if file has open successfully
            if(!inFile)
            {
                cerr<<"Fail to open file for reading"<<endl;
                return;//is a empty list
            }
            //track
            int count=1;//linne count
            int customerCount=0;//count on customer
            string delimiter=",";            
            while(getline(inFile,line))
            {
                count++;
                //get line by line
                //get individual section
                    //reset row
                    row.clear();
                    stringstream str(line);
                    while(getline(str,word,','))
                    {
                        row.push_back(word);
                    }
                    if(row.size()>1)
                    {
                        //check id
                        if(!isCustomerIdValid(row.at(0)))
                        {
                            cout<<"Invalid Customer ID in line:"<<count<<endl;
                        }
                        if(!isPhoneValid(row.at(3)))
                        {
                            cout<<"Invalid Customer Phone in line:"<<count<<endl;
                        }
                        if(!isRentAmountValie(row.at(4)))
                        {
                            cout<<"Invalid RentAmount in line: "<<count<<" any wrong character will be removed"<<endl;
                        }
                        int rentAmount=stoi(row.at(4));
                        //check rank
                        //Customer is guess rank
                        if(row.at(5)==guestRank)
                        {
                            Customer* guest=new GuestAccount(row.at(1),row.at(0),row.at(2),row.at(3));
                            //add to list
                            AddCustomer(guest);
                            guest->setRentCount(rentAmount);
                        }
                        //build Regular
                        else if(row.at(5)==regularRank)
                        {
                            Customer* regular=new RegularAccount(row.at(1),row.at(0),row.at(2),row.at(3));
                            //add to list
                            AddCustomer(regular);
                            regular->setRentCount(rentAmount);
                        }
                        //build VIP
                        else if(row.at(5)==vipRank)
                        {
                            Customer* vip=new VIPAccount(row.at(1),row.at(0),row.at(2),row.at(3));
                            AddCustomer(vip);
                            vip->setRentCount(rentAmount);
                        }
                        else{
                            cout<<"This rank is not defined, customer at line: "<< count<<" will be considered as guest"<<endl;
                            Customer* guest=new GuestAccount(row.at(1),row.at(0),row.at(2),row.at(3));
                            //add to list
                            AddCustomer(guest);
                            guest->setRentCount(rentAmount);
                        }
                }
                else{
                    //consider line as items
                    //get Item from itemManager
                    Item* i=iList.GetItem(line);
                    if(i!=NULL)
                    {
                        //cout<<"item adding at line:"<<count<<endl;
                        //set the customer to borrow the item with no update on item
                        customer.back()->AddBorrowItemWithNoUpdate(i);
                    }
                    else{
                        cout<<"Cannot find default Item"<<endl;
                    }
                }
            }
            //close file
            inFile.close();
            cout<<"Extracting Customers Completed"<<endl;
        }
        //constructor
        CustomerManager(string fileLocation)
        {
            this->fileLocation=fileLocation;
            //Open file and assign
        }
        //deconstructor
        ~CustomerManager()
        {
            cout<<"Clean process to dellocatie all pointers!"<<endl;
            //delete all pointer in List
            for(int i=0;i<customer.size();i++)
            {
                Customer* pItem=customer.at(i);
                delete pItem;
            }
            customer.clear();
        }
        //set file Location
        void SetFileLocation(string location)
        {
            fileLocation=location;
        }
        //getter 
        int Size()
        {
            return customer.size();
        }
        //Write to file
        void WriteToFile()
        {
            cout<<"Start Saving"<<endl;
            //open file 
            ofstream fout(fileLocation,ios::trunc);
            //check if file has open successfully
            if(!fout)
            {
                cerr<<"File failed to open"<<endl;
                return;
            }
            // write to file
            for(int i=0;i<customer.size();i++)
            {
                fout<<customer.at(i);
            }
            fout.close();
            cout<<"Saving Complete"<<endl;
        }
        //Add Customer to list
        void AddCustomer(Customer* c)
        {
            customer.push_back(c);
        }
        //Create and add Customer
        void AddCustomer()
        {
            //input to create an Item 
            cout<<"----"<<endl;
            //id
            string id=AskForCustomerID();
            //name
            string name=AskForCustomerName();
            //address
            string address=AskForAddress();
            //phone
            string phone=AskForPhoneNumber();
            //copies
            string rank=AskForRank();
            //create customer
            if(rank=="Guest")
            {
                //Guest
                Customer* cus=new GuestAccount(name,id,address,phone);
                //add to list
                AddCustomer(cus);
                cout<<"Customer has been added"<<endl;
            }
            else if(rank =="Regular")
            {
                //Regular
                Customer* cus=new RegularAccount(name,id,address,phone);
                //add to list
                AddCustomer(cus);
                cout<<"Customer has been added"<<endl;
            }
            else if(rank=="VIP")
            {
                //VIP
                Customer* cus=new VIPAccount(name,id,address,phone);
                //add to List
                AddCustomer(cus);
                cout<<"Customer has been added"<<endl;
            }
            else{
                //unlikely to run
                // invalid rank
                cout<<"Invalid Rank Error!"<<endl;
                cout<<"Failed to build customer"<<endl;
            }
        }
        //remove customer from List
        void RemoveCustomer(int index)
        {
            customer.erase(customer.begin()+index);
        }
        //Display
        void DisplayAll(bool displayItem=false)
        {
            cout<<"------------------------------------------------"<<endl;
            cout<<"Customers assigned"<<endl;
            for(int i=0;i<customer.size();i++)
            {
                customer.at(i)->displayAllInformation();
                if(displayItem)
                {
                    customer.at(i)->DisplayAllItem();
                }
            }
        }
        //display in order
        void DisplayAll(bool usingId,bool AZ)
        {
            if(AZ)
            {   cout<<"------------------------------------------------"<<endl;
                cout<<"Display in A-Z order"<<endl;
                SortListAZ(usingId);
            }
            else{
                cout<<"------------------------------------------------"<<endl;
                cout<<"Display in Z-A order"<<endl;
                SortListZA(usingId);
            }
            cout<<"customer in shop:"<<endl;
            for(int i=0;i<customer.size();i++)
            {
                customer.at(i)->displayAllInformation();
            }
        }
        //display on rank
        void DisplayOnRank(int rankIndex)
        {
            cout<<"------------------------------------------------"<<endl;
            string rankName="NA";
            if(rankIndex==0)
            {
                rankName="Guest";
            }
            else if(rankIndex==1)
            {
                rankName="Regular";
            }
            else if(rankIndex==2)
            {
                rankName="VIP";
            }
            else{
                cout<<"Your input rank is not found in our system"<<endl;
                return;
            }
            cout<<"Display "<<rankName<<" account"<<endl;
            for(int i=0;i<customer.size();i++)
            {
                if(customer.at(i)->compareRank(rankName))
                {
                customer.at(i)->displayAllInformation();
                }
            }
        }
        //display selection
        void DisplaySelection()
        {
            for(int i=0;i<customer.size();i++)
            {
                customer.at(i)->DisplaySelection(i);
            } 
        }
        //display protmotion
        void DisplayPromotion()
        {
            for(int i=0;i<customer.size();i++)
            {
                customer.at(i)->DisplayPromotion(i);
            } 
        }
        //get customer by index
        Customer* GetCustomer(int id)
        {
            return customer.at(id);
        }
        //get customer by id
        void SearchById(string id)
        {
            for(int i=0;i<customer.size();i++)
            {
                if(customer.at(i)->getId()==id)
                {
                    customer.at(i)->displayAllInformation();
                    return; 
                }
            }
        }
        //search Customer by name
        void SearchByName(string name)
        {
            for(int i=0;i<customer.size();i++)
            {
                if(customer.at(i)->getName()==name)
                {
                    customer.at(i)->displayAllInformation();
                    return;
                }
            }
        }
        //promote
        void Promote(int index)
        {
            if(customer.at(index)->CanPromote())
            {
                //promotable
                //check rank
                if(customer.at(index)->getRank()=="Guest")
                {
                    //guest to regular
                    Customer* temp=new RegularAccount(customer.at(index));
                    //swap with the current in member
                    swap(temp,customer.at(index));
                    //delete
                    delete temp;
                }
                else if(customer.at(index)->getRank()=="Regular")
                {
                    //regular to VIP
                    Customer* temp=new VIPAccount(customer.at(index));
                    //swap with current in member
                    swap(temp,customer.at(index));
                    //delete
                    delete temp;
                }
                else{
                    //SHOULD NOT RUN
                    cout<<"Cannot promote VIP MEMBERs!"<<endl;
                    return;
                }
            }
            else{
                cout<<"This customer is not qualified for promotion"<<endl;
            }
        }
    //Action function-----------------------------------------------------------------
    //sort by id or title
    void swapItem(Customer* &i1,Customer* &i2)
    {
        Customer* temp=i1;
        i1=i2;
        i2=temp;
    }
    private:
    //sort item list base on key( 0 for id, 1 for title) in alphabetical order
    void SortListAZ(bool usingId=true)
    {
        for(int i=0;i<customer.size();i++)//outer
        {
            for(int j=i+1;j<customer.size();j++)//inner
            {
                if(usingId)//using id to sort
                {
                    if(customer.at(i)->getId()>customer.at(j)->getId())//a-z
                    {
                        swapItem(customer.at(i),customer.at(j));
                    }
                }
                else{//using title
                    if(customer.at(i)->getName()>customer.at(j)->getName())//a-z
                    {
                        swapItem(customer.at(i),customer.at(j));
                    }
                }
            }
        }
    }
    //sortin list from z- a
    void SortListZA(bool usingId=true)
    {
        for(int i=0;i<customer.size();i++)//outer
        {
            for(int j=i+1;j<customer.size();j++)//inner
            {
                if(usingId)//using id to sort
                {
                    if(customer.at(i)->getId()<customer.at(j)->getId())//a-z
                    {
                        swapItem(customer.at(i),customer.at(j));
                    }
                }
                else{//using title
                    if(customer.at(i)->getName()<customer.at(j)->getName())//a-z
                    {
                        swapItem(customer.at(i),customer.at(j));
                    }
                }
            }
        }
    }

};
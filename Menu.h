#include "ManagementSource.h"
//declare
void ItemAction(ItemManager &iList,CustomerManager &cList);
void CustomerAction(ItemManager &iList,CustomerManager &cList);
void DisplayMainMenu(ItemManager &iList,CustomerManager &cList);
void Promotion(ItemManager &iList,CustomerManager &cList);
void RentItem(ItemManager &iList,CustomerManager &cList);
void ReturnItem(ItemManager &iList,CustomerManager &cList);
void DisplayItem(ItemManager &iList,CustomerManager &cList);
void DisplayNoStock(ItemManager &iList,CustomerManager &cList);
void DisplayCustomer(ItemManager &iList,CustomerManager &cList);
void DisplayCustomerOnRank(ItemManager &iList,CustomerManager &cList);
void Search(ItemManager &iList,CustomerManager &cList);
//Add,Update,DeleteAn Item
void ItemAction(ItemManager &iList,CustomerManager &cList)
{
    //submenu
    cout<<"------"<<endl;
    string userInput;
    cout<<"Enter an option:"<<endl;
    cout<<"1. Add An Item"<<endl;
    cout<<"2. Update An Item"<<endl;
    cout<<"3. Delete An Item"<<endl;
    cout<<"4. Back to Menu"<<endl;
    cin>>userInput;
    //check condition
    if(userInput=="1")
    {
        iList.AddItem();
        cout<<"Item has been added"<<endl;
    }
    else if(userInput=="2")
    {
        //update
        cout<<"----"<<endl;
        cout<<"Select Item you want to update:"<<endl;
        //display a list
        iList.DisplaySelection();
        //ask for input
        int option=AskForSelection(iList.Size());
        //display item
        cout<<"---"<<endl;
        Item* current=iList.GetItem(option);
        //ask for attribute
        cout<<"Select Attribute you want to update:"<<endl;
        //display list of attribute
        int attributeAmount=current->DisplayAttribute();
        //return to main menu option
        cout<<attributeAmount<<" .Return to menu"<<endl;
        int att=AskForAttribute(attributeAmount);
        cout<<"--"<<endl;
        //condition 
        if(att==0)
        {
            //id
            string id=AskForItemID();
            current->SetID(id);
        }
        else if(att==1){
            //title
            string title=AskForItemName();
            current->SetTitle(title);
        }
        else if(att==2)
        {
            //rent type
            string preRent=current->GetRentalType();
            string rent=AskForRentType();
            current->SetRetalType(rent);
            //change pointer
            if(preRent=="DVD"&&rent!="DVD")
            {
                //downgrade DVD to Item
                Item* temp=new Item(current);
                iList.swapItem(temp,iList.GetItem(option));
                //deallocate pointer
                delete temp;
            }
            else if(preRent!="DVD"&&rent=="DVD")
            {
                //upgrade item to DVD
                //ask for DVD Genre
                cout<<"You just update an non-DVD to DVD item! We need genre for this DVD item"<<endl;
                string genre=AskForGenre();
                Item* temp=new DVDItem(current,genre);
                iList.swapItem(temp,iList.GetItem(option));
                //deallocate pointer
                delete temp;
                
            }
        }
        else if(att==3)
        {
            //loan type
            string loan=AskForLoanName();
            current->SetLoanType(loan);
        }
        else if(att==4)
        {
            int copies=AskForCopiesAmount();
            current->SetCopiesInStock(copies);
        }
        else if(att==5)
        {
            float fee=AskForFee();
            current->SetRentFee(fee);
        }
        //DVD checking or exit
        else if(att==6&&attributeAmount==6)
        {
            cout<<"Go Back to main menu"<<endl;
            cout<<"-------------------------------"<<endl;
            //this is exit
            return DisplayMainMenu(iList,cList);
        }
        else if(att==6&&attributeAmount!=6)
        {
            //Update DVD
            string genre=AskForGenre();
            current->SetGenre(genre);
        }
        else if(att==7&&attributeAmount==7)
        {
            cout<<"Go Back to main menu"<<endl;
            cout<<"-------------------------------"<<endl;
            //this is exit
            return DisplayMainMenu(iList,cList);
        }
        else{
            cout<<"Invalid Option!"<<endl;
            cout<<"back to main menu"<<endl;
            cout<<"-------------------------------"<<endl;
            //this is exit
            return DisplayMainMenu(iList,cList);
        }
        cout<<"item has been updated"<<endl;
    }
    else if(userInput=="3"){
        //delete
        cout<<"----"<<endl;
        cout<<"Select Item you want to delete:"<<endl;
        //display a list
        iList.DisplaySelection();
        //ask for input
        int option=AskForSelection(iList.Size());
        iList.RemoveItem(option);
    }
    else if(userInput=="4")
    {
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    else{
        //error;
        cout<<"Unexpected value of input"<<endl;
        cout<<"Please Re-enter your option:"<<endl;
        return ItemAction(iList,cList);
    }
    cout<<"Press any key to continue..."<<endl;
    cin.ignore();
    getchar();
    cout<<"back to main menu"<<endl;
    cout<<"-------------------------------"<<endl;
    return DisplayMainMenu(iList,cList);
}
//Customer Action
void CustomerAction(ItemManager &iList,CustomerManager &cList)
{
    //submenu
    cout<<"------"<<endl;
    string userInput;
    cout<<"Enter an option:"<<endl;
    cout<<"1. Add A Customer"<<endl;
    cout<<"2. Update A Customer"<<endl;
    cout<<"3 .Back to Menu"<<endl;
    cin>>userInput;
    if(userInput=="1")
    {
        cList.AddCustomer();
    }
    else if(userInput=="2")
    {
        //Update Customer
        cout<<"----"<<endl;
        cout<<"Select Customer you want to update:"<<endl;
        cList.DisplaySelection();
        //ask for user input
        int option=AskForSelection(cList.Size());
        //get customer
        Customer* cus=cList.GetCustomer(option);
        //display attribute
        cout<<"Select attribute you want to update"<<endl;
        int attAmount=cus->DisplayAttribute();
        //return to menu option
        cout<<attAmount<<" .Return to menu"<<endl;
        //check condition
        cout<<"--"<<endl;
        int att=AskForAttribute(attAmount);
        if(att==0)
        {
            //id
            string id=AskForCustomerID();
            cus->setId(id);
        }
        else if(att==1)
        {
            //name
            string name=AskForCustomerName();
            cus->setName(name);
        }
        else if(att==2)
        {
            //address
            string address=AskForAddress();
            cus->setAddress(address);
        }
        else if(att==3)
        {
            //phone
            string phone =AskForPhoneNumber();
            cus->setPhone(phone);
        }
        else if(att==4&&attAmount==4)
        {
            //exit
            cout<<"back to main menu"<<endl;
            cout<<"-------------------------------"<<endl;
            //this is exit
            return DisplayMainMenu(iList,cList);
        }
        else{
            //unlikely
            cout<<"Invalid Option!"<<endl;
            cout<<"back to main menu"<<endl;
            cout<<"-------------------------------"<<endl;
            //this is exit
            return DisplayMainMenu(iList,cList);
        }
        cout<<"Customer has been updated"<<endl;
    }
    else if(userInput=="3")
    {
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    else{
       cout<<"Invalid Option!"<<endl;
        cout<<"Please Re-enter your Option!"<<endl;
    }
    cout<<"Press any key to continue..."<<endl;
    cin.ignore();
    getchar();
    cout<<"back to main menu"<<endl;
    cout<<"-------------------------------"<<endl;
    return DisplayMainMenu(iList,cList);

}
//Promotion  
void Promotion(ItemManager &iList,CustomerManager &cList)
{
    cout<<"------"<<endl;
    cout<<"Please Select a Customer to be promoted:"<<endl;
    //display list of promotion 
    cList.DisplayPromotion();
    cout<<cList.Size()<<" .Return To Main Menu"<<endl;
    //ask for input
    int option=AskForSelection(cList.Size()+1);
    //promote
    if(option<cList.Size())
    {
        cList.Promote(option);
    }
    else{
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    //return to main menu
    cout<<"Press any key to continue..."<<endl;
    cin.ignore();
    getchar();
    cout<<"back to main menu"<<endl;
    cout<<"-------------------------------"<<endl;
    return DisplayMainMenu(iList,cList);
}
//Rent Item
void RentItem(ItemManager &iList,CustomerManager &cList)
{
    //select customer 
    cout<<"------"<<endl;
    cout<<"Please Select a Customer"<<endl;
    //display list
    cList.DisplaySelection();
    cout<<cList.Size()<<" .Return To Main Menu"<<endl;
    //ask for input
    int option=AskForSelection(cList.Size()+1);
    //check if user want to return
    if(option==cList.Size())
    {
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    //select item
    cout<<"-----"<<endl;
    cout<<"Please Select an Customer"<<endl;
    //display
    iList.DisplaySelection();
    cout<<iList.Size()<<" .Return to Main Menu"<<endl;
    int opt2=AskForSelection(cList.Size()+1);
    //check if user want to returnn
    if(opt2==iList.Size())
    {
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    //then start renting here
    cList.GetCustomer(option)->AddBorrowItem(iList.GetItem(opt2));
    //all done
    //back to menu
    cout<<"Press any key to continue..."<<endl;
    cin.ignore();
    getchar();
    cout<<"back to main menu"<<endl;
    cout<<"-------------------------------"<<endl;
    return DisplayMainMenu(iList,cList);
}
//Return Item
void ReturnItem(ItemManager &iList,CustomerManager &cList){
    //select customer 
    cout<<"------"<<endl;
    cout<<"Please Select a Customer"<<endl;
    //display list
    cList.DisplaySelection();
    cout<<cList.Size()<<" .Return To Main Menu"<<endl;
    //ask for input
    int option=AskForSelection(cList.Size()+1);
    //check if user want to return
    if(option==cList.Size())
    {
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    //display list of tiem
    cout<<"-----"<<endl;
    cout<<"select Item to return!"<<endl;
    Customer* cus=cList.GetCustomer(option);
    if(cus->getItemSize()==0)
    {
        cout<<"This customer has no item in borrow!"<<endl;
        cout<<"Press any key to return to main menu."<<endl;
        cin.ignore();
        getchar();
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    cus->DisplayAllItem();
    //select Item
    int opt2=AskForSelection(cus->getItemSize()+1);
    if(opt2==cus->getItemSize())
    {
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    //return item
    cus->ReturnAnItem(opt2);
    //all done
    //back to menu
    cout<<"Item has been returned successfully"<<endl;
    cout<<"Press any key to continue..."<<endl;
    cin.ignore();
    getchar();
    cout<<"back to main menu"<<endl;
    cout<<"-------------------------------"<<endl;
    return DisplayMainMenu(iList,cList);
}
//Display Item
void DisplayItem(ItemManager &iList,CustomerManager &cList)
{
    //display option
    cout<<"------"<<endl;
    cout<<"Select a sortinngdisplay option:"<<endl;
    cout<<"0 .Sort by ID in alphabetical order(A-z)"<<endl;
    cout<<"1 .Sort by ID in reverse alphabetical order(Z-A)"<<endl;
    cout<<"2 .Sort by Title in alphabetical order(A-Z)"<<endl;
    cout<<"3 .Sort by Title in reverse alphabetical order(Z-A)"<<endl;
    cout<<"4 .Return to main menu"<<endl;
    int option=AskForSelection(5);
    if(option==0)
    {
        //id a-z
        iList.DisplayAllItem(true,true);
    }
    else if(option==1)
    {
        iList.DisplayAllItem(true,false);
    }
    else if(option==2)
    {
        iList.DisplayAllItem(false,true);
    }
    else if(option==3)
    {
        iList.DisplayAllItem(false,false);
    }
    else if(option==4)
    {
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    //back to mainn menu
    cout<<"Press any key to continue..."<<endl;
    cin.ignore();
    getchar();
    cout<<"back to main menu"<<endl;
    cout<<"-------------------------------"<<endl;
    return DisplayMainMenu(iList,cList);
}
//Display no stock
void DisplayNoStock(ItemManager &iList,CustomerManager &cList)
{
    cout<<"------"<<endl;
    iList.DisplayNoStockItem();
    cout<<"Press any key to continue..."<<endl;
    cin.ignore();
    getchar();
    cout<<"back to main menu"<<endl;
    cout<<"-------------------------------"<<endl;
    return DisplayMainMenu(iList,cList);
}
//Display Customer
void DisplayCustomer(ItemManager &iList,CustomerManager &cList)
{
    //display option
    cout<<"------"<<endl;
    cout<<"Select a sortinngdisplay option:"<<endl;
    cout<<"0 .Sort by ID in alphabetical order(A-z)"<<endl;
    cout<<"1 .Sort by ID in reverse alphabetical order(Z-A)"<<endl;
    cout<<"2 .Sort by Name in alphabetical order(A-Z)"<<endl;
    cout<<"3 .Sort by Name in reverse alphabetical order(Z-A)"<<endl;
    cout<<"4 .Return to main menu"<<endl;
    int option=AskForSelection(5);

    if(option==0)
    {
        //id a-z
        cList.DisplayAll(true,true);
    }
    else if(option==1)
    {
        cList.DisplayAll(true,false);
    }
    else if(option==2)
    {
        cList.DisplayAll(false,true);
    }
    else if(option==3)
    {
        cList.DisplayAll(false, false);
    }
    else if(option==4)
    {
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
        //back to mainn menu
    cout<<"Press any key to continue..."<<endl;
    cin.ignore();
    getchar();
    cout<<"back to main menu"<<endl;
    cout<<"-------------------------------"<<endl;
    return DisplayMainMenu(iList,cList);
}
//display depend onn rankn
void DisplayCustomerOnRank(ItemManager &iList,CustomerManager &cList){
    //display option
    cout<<"------"<<endl;
    cout<<"Select a rank option:"<<endl;
    cout<<"0 .Guest"<<endl;
    cout<<"1 .Regular"<<endl;
    cout<<"2 .VIP"<<endl;
    cout<<"3 .Return to main menu"<<endl;
    int option=AskForSelection(4);

    if(option==0||option==1||option==2)
    {
        //id a-z
        cList.DisplayOnRank(option);
    }
    else if(option==3)
    {
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    //back to mainn menu
    cout<<"Press any key to continue..."<<endl;
    cin.ignore();
    getchar();
    cout<<"back to main menu"<<endl;
    cout<<"-------------------------------"<<endl;
    return DisplayMainMenu(iList,cList);
}
//search
void Search(ItemManager &iList,CustomerManager &cList)
{
     //display option
    cout<<"------"<<endl;
    cout<<"Select a search option:"<<endl;
    cout<<"0 .Customer"<<endl;
    cout<<"1 .Item"<<endl;
    cout<<"2 .Return to mainn menu"<<endl;
    int option=AskForSelection(3);
    //ask for any innput
    string input;
    cout<<"-----"<<endl;
    cout<<"Please Input Key word (id, customer name or item title) you want to search for"<<endl;
    cin.ignore();
    getline(cin,input);
    if(option==0)
    {
        //customer
        //check id
	//ask for any innput
        string input;
        cout<<"-----"<<endl;
        cout<<"Please Input Key word (id, customer name or item title) you want to search for"<<endl;
        cin.ignore();
        getline(cin,input);
        if(cList.SearchById(input))
        {
            cout<<"FOUND!!!"<<endl;
        }
        else{
            if(cList.SearchByName(input))
            {
                cout<<"FOUND!!!"<<endl;
            }
            else{
                cout<<"no customer found"<<endl;
            }
        }
    }
    else if(option==1)
    {
        //search item
	//ask for any innput
        string input;
        cout<<"-----"<<endl;
        cout<<"Please Input Key word (id, customer name or item title) you want to search for"<<endl;
        cin.ignore();
        getline(cin,input);
        if(iList.SearchByID(input))
        {
            cout<<"FOUND"<<endl;
        }
        else {
            if(iList.SearchByTitle(input))
            {
                cout<<"FOUND"<<endl;
            }
            else{
                cout<<"No item found"<<endl;
            }
        }
    }
    else if(option==2)
    {
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    else{
        cout<<"Invalid Input!"<<endl;
        cout<<"back to main menu"<<endl;
        cout<<"-------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
    //back to mainn menu
    cout<<"Press any key to continue..."<<endl;
    getchar();
    cout<<"back to main menu"<<endl;
    cout<<"-------------------------------"<<endl;
    return DisplayMainMenu(iList,cList);
}
//main menu
void DisplayMainMenu(ItemManager &iList,CustomerManager &cList)
{
    string userInp;
    //display information
    cout << "Welcome to Genie’s video store\n";
		cout << "Enter an option below.\n";
		cout << "1. Add a new item, update or delete an existing item\n";
		cout << "2. Add new customer or update an existing customer \n";
		cout << "3. Promote an existing customer\n";
		cout << "4. Rent an item\n";
		cout << "5. Return an item\n";
		cout << "6. Display all items\n";
		cout << "7. Display out-of-stock items\n";
		cout << "8. Display all customers\n";
		cout << "9. Display group of customers\n";
		cout << "10. Search items or customers\n";
        cout<<"EXIT"<<endl;
		cout << endl;
		cout << "Choose any option: ";
		cin >> userInp;
    //check for relative action
    if(userInp=="1")
    {
        //add,update, delete an item
        return ItemAction(iList,cList);
    }
    else if(userInp=="2")
    {
        //add,update, delete a customer
        return CustomerAction(iList,cList);
    }
    else if( userInp=="3")
    {
        //promote
        return Promotion(iList,cList);
    }
    else if(userInp=="4"){
        //rent an item
        RentItem(iList,cList);
    }
    else if(userInp=="5")
    {
        //return an item
        ReturnItem(iList,cList);
    }
    else if(userInp=="6"){
        //display items
        DisplayItem(iList,cList);
    }
    else if(userInp=="7")
    {
        //display no stock items
        DisplayNoStock(iList,cList);
    }
    else if(userInp=="8")
    {
        //display customers
        DisplayCustomer(iList,cList);
    }
    else if(userInp=="9")
    {
        //display group of customer on their ranking
        DisplayCustomerOnRank(iList,cList);
    }
    else if( userInp=="10")
    {
        //search
        Search(iList,cList);
    }
    else if(userInp=="Exit"||userInp=="EXIT"||userInp=="exit")
    {
        cout<<"--"<<endl;
        //save and exit
        iList.WriteToFile();
        cList.WriteToFile();
        cout<<"--"<<endl;
        //display team member
        cout<<"ASSIGNMENT 1 Group 20"<<endl;
        cout<<"s3836412"<<" ,"<<"s3836412@rmit.edu.vn"<<" ,"<<"Nguyen Ngoc Minh Quang"<<endl;
        cout<<"s3801492"<<" ,"<<"s3801492@rmit.edu.vn"<<" ,"<<"Nghiem The Minh"<<endl;
        cout<<"s3863956"<<" ,"<<"s3863956@rmit.edu.vn"<<" ,"<<"Tran Nguyen Anh Khoa"<<endl;
        cout<<"s3777235"<<" ,"<<"s3777235@rmit.edu.vn"<<" ,"<<"Hua Ha Bao Long"<<endl;
        cout<<"--"<<endl;
        cout<<"PROGRAM EXIT"<<endl;
    }
    else{
        //input invalid
        cout<<"Invalid Input!!"<<endl;
        cout<<"Restarting Program"<<endl;
        cout<<"---------------------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
}

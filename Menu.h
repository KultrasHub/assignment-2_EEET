#include "ManagementSource.h"
//declare
void ItemAction(ItemManager &iList,CustomerManager &cList);
void CustomerAction(ItemManager &iList,CustomerManager &cList);
void DisplayMainMenu(ItemManager &iList,CustomerManager &cList);
void Promotion(ItemManager &iList,CustomerManager &cList);
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
        DisplayMainMenu(iList,cList);
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
    DisplayMainMenu(iList,cList);

}
//Promotion  
void Promotion(ItemManager &iList,CustomerManager &cList)
{
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
        DisplayMainMenu(iList,cList);
    }
    //return to main menu
    cout<<"Press any key to continue..."<<endl;
    cin.ignore();
    getchar();
    cout<<"back to main menu"<<endl;
    cout<<"-------------------------------"<<endl;
    DisplayMainMenu(iList,cList);
}
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
		cout << "Choose any option";
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
    }
    else if(userInp=="5")
    {
        //return an item
    }
    else if(userInp=="6"){
        //display items
    }
    else if(userInp=="7")
    {
        //display no stock items
    }
    else if(userInp=="8")
    {
        //display customers
    }
    else if(userInp=="9")
    {
        //display group of customer on their ranking
    }
    else if( userInp=="10")
    {
        //search
    }
    else{
        //input invalid
        cout<<"Invalid Input!!"<<endl;
        cout<<"Restarting Program"<<endl;
        cout<<"---------------------------------------------"<<endl;
        return DisplayMainMenu(iList,cList);
    }
}
#include "Menu.h"
#include <vector>
#include <sstream>

//using namespace std;
//Read file-----------------------------------------------------------------------
//
int main(int argc, char const *argv[])
{
    //sample text file
    string itemLocation="items.txt";
    ItemManager iList(itemLocation);
    string fileLocation="customers.txt";
    CustomerManager cList(fileLocation);
    cList.ExtractFile(iList);
    //item
    DisplayMainMenu(iList,cList);
    // // iList.DisplayAllItem();
    // string fileLocation="customers.txt";
    // CustomerManager cList(fileLocation);
    // cList.ExtractFile(iList);
    // cList.GetCustomer(0)->AddBorrowItem(iList.GetItem(0));
    // cList.GetCustomer(0)->AddBorrowItem(iList.GetItem(2));
    // cList.GetCustomer(0)->AddBorrowItem(iList.GetItem(3));
    // cList.DisplayAll(true);
    // cList.WriteToFile();
    // //--
    // cout<<"--"<<endl;
    // iList.DisplayAllItem();
    iList.WriteToFile();
    //cList.WriteToFile();
    return 0;
}

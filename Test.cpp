#include <iostream>
#include <vector>
#include <string>
using namespace std;
class base{
    public:
    int id;
    
    public: 
    base(int id)
    {
        this->id=id;
    }
    virtual void Display()
    {
        cout<<"haha base"<<endl;
    }
};
class child:public base{
    public:
    child(int i):base(i){};
    void Display()
    {
        cout<<"hi hi child"<<endl;
    }
};
int main(int argc, char const *argv[])
{
    base* b=new base(0);
    base* a=new base(1);
    base* c=new base(4);
    base* d= new child(5);
    vector<base*> baseList;
    baseList.push_back(b);
    baseList.push_back(a);
    baseList.push_back(c);
    baseList.push_back(d);
    cout<<"Before"<<endl;
    //display
    for(int i=0;i<baseList.size();i++)
    {
        cout<<baseList.at(i)->id;
    }
    cout<<endl;
    vector<base*> enderList;
    enderList.push_back(b);
    enderList.push_back(a);
    enderList.push_back(c);
    enderList.push_back(d);
    //update 
    b->id=2;
    a->id=4;
    //check if vector does destroy object
    enderList.erase(enderList.begin()+1);
     //display
     cout<<"After"<<endl;
     baseList.at(1)->id=10;
     baseList.at(2)->id=9;
    for(int i=0;i<baseList.size();i++)
    {
        cout<<baseList.at(i)->id;
    }
    cout<<endl;
    for(int i=0;i<enderList.size();i++)
    {
        cout<<enderList.at(i)->id;
    }
    cout<<endl;
    d->Display();
    baseList.at(3)->Display();
    delete a;
    delete b;
    delete c;
    delete d;
    }

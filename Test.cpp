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
    cout<<"Please enter somethingn:"<<endl;
    string a;
    getline(cin,a);
    cout<<"a is:"<<a<<endl;
    
}

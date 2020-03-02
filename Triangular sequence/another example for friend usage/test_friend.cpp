#include <iostream>   
using namespace std; 
class Internet; 
 
class Country 
{ 
public: 
Country() 
    { 
        strcpy(cname,"中国"); 
    } 
	void Printname() {cout<< cname;}
    friend class Internet;//友类的声明 
protected: 
    char cname[30]; 
}; 
class Internet 
{ 
public:   
    Internet(char *name,char *address)   
    {   
        strcpy(Internet::name,name);   
        strcpy(Internet::address,address);  
    } 
    void Editcname(Country &temp); 
protected:   
    char name[20]; 
    char address[20]; 
}; 
void Internet::Editcname(Country &temp) 
{ 
    strcpy(temp.cname,"中华人民共和国");  
} 
void main() 
{ 
    Internet a("中国软件开发实验室","www.cndev-lab.com"); 
    Country b; 
    a.Editcname(b);
	b.Printname();
    cin.get(); 
}
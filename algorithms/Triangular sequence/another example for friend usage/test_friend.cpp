#include <iostream>   
using namespace std; 
class Internet; 
 
class Country 
{ 
public: 
Country() 
    { 
        strcpy(cname,"�й�"); 
    } 
	void Printname() {cout<< cname;}
    friend class Internet;//��������� 
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
    strcpy(temp.cname,"�л����񹲺͹�");  
} 
void main() 
{ 
    Internet a("�й��������ʵ����","www.cndev-lab.com"); 
    Country b; 
    a.Editcname(b);
	b.Printname();
    cin.get(); 
}
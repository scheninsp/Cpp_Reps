//word counter
#include<map>
#include<string>
#include<iostream>
using namespace std;

int main()
{
	const string end_word="end";
	map<string,int> words;
	map<string,int>::iterator sentinal=words.begin();
	string tword;
	while(cin >> tword){
		words[tword]++;  //key=tword, value++
		if (!tword.compare(end_word))
			break;
	}

	map<string,int>::iterator iter=words.begin();
	for(;iter!=words.end();++iter)
	cout<< "key:" <<iter->first<<"\t"<<"value:"<<iter->second<<endl;

	string blank;
	cin>>blank;

}
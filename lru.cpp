//LRU(least recently used) Cache

#include<list>
#include<unordered_map>
#include<iostream>

using namespace std;

class LRUCache {
private:
	int capacity;
	list<pair<int, int>> counts;  //pair<key, val>, back is the least recently used
	unordered_map<int, list<pair<int, int>>::iterator> elems;

public:
	LRUCache(int len) : capacity(len) {}

	void put(int key, int val) {
		if (elems.find(key) != elems.end())
			counts.erase(elems[key]);
		else if(elems.size()>=capacity){
			elems.erase(counts.back().first);
			counts.pop_back();
		}
		counts.push_front({ key, val });
		elems[key] = counts.begin();
	}

	int get(int key) {
		if (elems.find(key) != elems.end()) {
			put(key, elems[key]->second);
			return elems[key]->second;
		}
		return -1; //not found, can create new page and put
	}

};

int main() {
	LRUCache lru = LRUCache(3);
	lru.put(1, 1);
	lru.put(2, 2);
	lru.put(3, 3);
	lru.put(4, 4);
	cout << "get 2: " << lru.get(2) << endl; 

	getchar();

}
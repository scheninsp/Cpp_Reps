//LRU(least recently used) Cache

#include<list>
#include<unordered_map>
#include<iostream>

using namespace std;

class LRUCache {
private:
	int capacity;
	list<pair<int, int>> queue;  //pair<key, val>, back is the least recently used
	unordered_map<int, list<pair<int, int>>::iterator> elems;  //save key's positions in queue

public:
	LRUCache(int len) : capacity(len) {}

	void put(int key, int val) {
		if (elems.find(key) != elems.end())
			queue.erase(elems[key]);
		else if(elems.size()>=capacity){
			elems.erase(queue.back().first);
			queue.pop_back();
		}
		queue.push_front({ key, val });
		elems[key] = queue.begin();
	}

	int get(int key) {
		if (elems.find(key) != elems.end()) {
			put(key, elems[key]->second);
			return elems[key]->second;
		}
		return -1; //not found, can create new page and put
	}

	int getMostRecent() {
		return queue.front().second;
	}
};

int main() {
	LRUCache lru = LRUCache(3);
	lru.put(1, 1);
	lru.put(2, 2);
	lru.put(3, 3);
	lru.put(4, 4);
	cout << "get 2: " << lru.get(2) << endl; 
	cout << "most recently visited: " << lru.getMostRecent() << endl;
	cout << "get 4: " << lru.get(4) << endl;
	cout << "most recently visited: " << lru.getMostRecent() << endl;

	getchar();

}
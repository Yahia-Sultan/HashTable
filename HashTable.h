#include <iostream>
#include "Record.h"

#define MAXHASH 1000
using namespace std;

template <class T> class HashTable {

private:
	int numItems;
	Record<T>** records;
	
	int hash(int k) {
		return h1(k); // Select hashing function
	}

	int probe(int k, int i) {
		return p1(k, i); // Select probing function
	}

	int h1(int k){
		return k % MAXHASH;
	}

	int p1(int k, int i) {
		return i;
	}

	int h2(int k) {
		return  (int) (((sqrt(k) - .3) / 2) * (1000 * k));
	}

	int p2(int k, int i) {
		int total;
		int list[16] = {1, 2, 3, 5, 7, 9, 10, 13, 15, 16, 19, 20, 22, 24, 26, 30 };
		int rng = 16;
		if (i > 16) {
			total = k + list[15] + i;
		}
		else {
			total = k + list[i-1];
		}
		return total;
	}

public:
	HashTable() {
		numItems = 0;
		records = new Record<T>*[MAXHASH];
		for (int i = 0; i < MAXHASH; i++) {
			records[i] = new Record<T>();
		}
	}

	HashTable(const HashTable& other) {
		other.numItems = MAXHASH;
		for (int i = 0; i < MAXHASH; i++) {
			other.records[i] = this->records[i];
		}
	}

	HashTable& operator=(const HashTable& other) {
		other.numItems = MAXHASH;
		for (int i = 0; i < MAXHASH; i++) {
			other.records[i] = this->records[i];
		}
		return *this;
	}
	~HashTable() {
		delete records;
		numItems = 0;
	}

	bool insert(int key, T value, int& collisions) {
		T item;
		if (find(key, item) || numItems == (MAXHASH - 1))
			return false;
			

		Record<T>* item2 = new Record<T>(key, value);
		int pos = hash(key) % MAXHASH;
		int offset = 0;
		Record<T> r = *records[pos];
		int turns = 0;
		while (r.getKey() > -1) {
			offset++;
			pos = probe(key, offset) % MAXHASH;
			r = *records[pos];
			turns++;
			if (r.getKey() < 0) {
				turns--;
			}
		}
		collisions += turns;
		records[pos] = item2;
		numItems++;
		return true;
	}

	bool remove(int key, T& value) {
		T item;
		if (!find(key, item)) {
			return false;
		}
		else {
			Record<T> r = *records[hash(key) % MAXHASH];
			r.setValue(value);
			numItems--;
			records[hash(key) % MAXHASH] = new Record<T>(-2);
			return true;
		}
	}

	bool find(int key, T& value) {
		Record<T> r = *records[(hash(key) % MAXHASH)];
		if (r.getKey() == -1) {
			return false;
		}
		else {
			int offset = 0;
			int pos = hash(key) % MAXHASH;
			while (r.getKey() != key) {
				if (r.getKey() == -1){
					return false;
				}
				offset++;
				pos = probe(key, offset) % MAXHASH;
				if (offset == MAXHASH) {
					return false;
				}
				r = *records[pos];
			}
			value = r.getValue();
			return true;
		}
	}

	float alpha() {
		return numItems / (float)MAXHASH;
	}


	template <class U>
	friend ostream& operator<<(ostream& os, const HashTable<U>& ht);
};

template <class U>
ostream& operator<<(ostream& os, const HashTable<U>& ht) {
	cout << "Table\tKey\tValue" << endl;
	for (int i = 0; i < MAXHASH; i++) {
		Record<U> r = *ht.records[i];
		if (r.getKey() != -1) {
			cout << i << "\t" <<  r.getKey() << "\t"
				<< r.getValue() << endl;
		}
	}


	return os;
	
}

#include <iostream>
#include <string>

#include "HashTable.h"

using namespace std;

int main() {
	cout << "USING H1 AND P1" << endl;
	HashTable<int> ht;

	int collisions = 0;
	int lel = 0;
	
	
	ht.insert(1, 2, collisions);
	cout << collisions << endl;
	ht.insert(11, 1, collisions);
	cout << collisions << endl;
//	ht.remove(1, lel);
	ht.insert(1, 1, collisions);
	ht.insert(21, 1, collisions);
	ht.insert(31, 1, collisions);


	cout << ht << endl << endl;

	cout << "Collisions: " << collisions << endl;
	cout << "Alpha: " << ht.alpha() << endl <<endl << endl;

}

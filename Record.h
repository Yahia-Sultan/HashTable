
#include <iostream>

template <class T> class Record
{

private:
	int key;
	T value;
public:
	Record() {
		key = -1;
	}
	Record(int key) {
		this->key = key;
	}
	Record(int key, T value) {
		this->key = key;
		this->value = value;
	}

	int getKey() {
		return key;
	}

	T getValue() {
		return value;
	}

	void setValue(T value) {
		this->value = value;
	}

	void setKey(int key) {
		this->key = key;
	}
};

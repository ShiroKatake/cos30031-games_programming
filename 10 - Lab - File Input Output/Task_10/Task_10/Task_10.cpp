#include <iostream>
#include <fstream>
using namespace std;

class MyClass {
public:
	MyClass(char charInput, int intInput, float floatInput) {
		myChar = charInput;
		myInt = intInput;
		myFloat = floatInput;
	}
public:
	char myChar;
	int myInt;
	float myFloat;
};

int main() {

	MyClass* myClass = new MyClass('asdf', 10, 3.2f);

	char myChar = 'ads';
	int myInt = 20;
	float myFloat = 2.3f;

	ofstream testFile1("testFile1.bin", ios::binary);
	testFile1.write(&myChar, sizeof(myChar));
	testFile1.write(reinterpret_cast<const char*>(&myInt), sizeof(myInt));
	testFile1.write(reinterpret_cast<const char*>(&myFloat), sizeof(myFloat));
	testFile1.close();
	
	return 0;
}
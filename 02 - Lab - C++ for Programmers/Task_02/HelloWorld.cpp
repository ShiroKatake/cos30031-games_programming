#include <iostream>
using namespace std;

int main() {
	//Attempting to do pointers
	int a = rand() % 100 + 1;
	int* ptr = &a;

	//How I learn to do string concatenation
	cout << "Hello World! Have a random number! " << *ptr << endl;
	cout << "The numnber's memory address: " << ptr << endl;
	cin.get();
}
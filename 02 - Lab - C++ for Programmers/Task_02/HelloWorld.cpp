#include <iostream>
#include <string>
using namespace std;

class Person {
	private:string name;
	public: int age;

	public: void SetInfo(string* nameToSet, int* ageToSet) {
		name = *nameToSet;
		age = *ageToSet;
		cout << "Person initialized." << endl;
		cout << "Name has been set to: " << *nameToSet << endl;
		cout << "Age has been set to: " << *ageToSet << endl;
	}
};

int ChangeToOne(int* number) {
	*number = 1;
	return *number;
}

void PrintAllOdds(int const& start, int const& end) {
	cout << "All odd numbers from " << start << " to " << end << ":" << endl;

	for (int i = start; i < end; i++)
	{
		if (i % 2 == 1) {
			cout << i;
			if (i + 1 == end) {
				cout << "\n";
			}
			else {
				cout << ", ";
			}
		}
	}
}

void PrintRandomArray() {
	int intArray[5] = { rand() % 101, rand() % 101, rand() % 101, rand() % 101, rand() % 101 };
	int intArrayLength = sizeof(intArray) / sizeof(*intArray);
	cout << "Random array: [";
	
	for (int i = 0; i < intArrayLength; i++)
	{
		cout << intArray[i];
		if (i + 1 == intArrayLength) {
			cout << "]" << endl << endl;
		}
		else {
			cout << ", ";
		}
	}
}

void PrintWordsFromSentence(string* sentence) {
	string word = "";
	string* wordPtr = &word; //3rd requirement

	for (auto i : *sentence)
	{
		if (i == ' ') {
			cout << *wordPtr << endl;
			*wordPtr = "";
		}
		else {
			*wordPtr += i;
		}
	}

	cout << *wordPtr << endl;
}

int main() {
	Person* person = new Person();
	string name = "Jake";
	int age = 20139;
	string sentence = "This is a string broken down into words";

	cout << "Hello World!" << endl;
	person->SetInfo(&name, &age);
	cout << "Maybe not . . . Age reset to: " << ChangeToOne(&person->age) << endl << endl;
	PrintAllOdds(1, 20);
	PrintRandomArray();
	PrintWordsFromSentence(&sentence);

	cin.get();
}
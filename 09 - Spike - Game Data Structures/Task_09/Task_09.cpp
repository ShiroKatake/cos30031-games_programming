//code learned from https://stackoverflow.com/questions/3815647/using-map-for-inventory-system

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Item {
private:
	string name;
	string description;
public:
	Item(string itemName, string itemDescription) {
		name = itemName;
		description = itemDescription;
	}
	string getName() {
		return name;
	}
	string getDescription() {
		return description;
	}
};

class ItemManager {
private:
	map<string, int> inventory;
public:
	void AddItem(Item* item, int itemCount) {
		inventory.insert(pair<string, int>(item->getName(), itemCount));
	}

	int GetItemCount(string itemName) {
		return inventory[itemName];
	}
};

int main() {
	Item* test_item = new Item("Item A", "This is an item.");
	Item* test_item2 = new Item("Item B", "This is another item.");
	ItemManager* inventory = new ItemManager();
	
	inventory->AddItem(test_item, 5);
	inventory->AddItem(test_item2, 3);

	cout << "I have " << inventory->GetItemCount(test_item->getName())
		<< " " << test_item->getName() << " and "
		<< inventory->GetItemCount(test_item2->getName())
		<< " " << test_item2->getName() << std::endl;
}
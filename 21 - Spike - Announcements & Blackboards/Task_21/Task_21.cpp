// Code learned from https://seanballais.github.io/blog/implementing-a-simple-message-bus-in-cpp/ 
#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <string>

using namespace std;

class Message {
private:
	std::string messageEvent;
	int receiverId;

public:
	Message(const std::string event, const int receiverId)
	{
		messageEvent = event;
		this->receiverId = receiverId;
	}

	std::string GetMessage()
	{
		return messageEvent;
	}

	bool IsMessageForReceiver(int id) {
		return receiverId == id;
	}
};

class Receiver;

class Mailbox {
private:
	vector<Message> messages;
	vector<Receiver*> receivers;

public:
	void AddReceiver(Receiver* receiver) {
		receivers.push_back(receiver);
	}
	void StoreMessage(Message message);
	void Deliver();
};

class Receiver {
private:
	string name;
	int uid;
	Mailbox* mailbox;
public:
	Receiver(string name, int uid, Mailbox* mailbox) {
		this->name = name;
		this->uid = uid;
		this->mailbox = mailbox;
		mailbox->AddReceiver(this);
	}

	void CreateMessage(string event, int id) {
		Message message(event, id);
		mailbox->StoreMessage(message);
	}

	void ReceiveMessage(Message message) {
		if (message.IsMessageForReceiver(uid)) {
			cout << name << " received: " << message.GetMessage() << endl;
		}
	}
};

inline void Mailbox::StoreMessage(Message message) {
	messages.push_back(message);
}

inline void Mailbox::Deliver() {
	for (Receiver* receiver : receivers) {
		for (Message message : messages) {
			receiver->ReceiveMessage(message);
		}
	}
}

int main() {
	Mailbox mailbox;
	Receiver compA("component A", 1, &mailbox);
	Receiver compB("component B", 2, &mailbox);

	compB.CreateMessage("Hi!", 1);
	mailbox.Deliver();
	std::cin.get();

	return 0;
}
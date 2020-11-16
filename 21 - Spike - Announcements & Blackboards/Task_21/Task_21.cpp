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

	std::string GetEvent()
	{
		return messageEvent;
	}

	bool IsMessageForReceiver(int id) {
		return receiverId == id;
	}
};

class MessageBus {
private:
	std::vector<std::function<void(Message)>> receivers;
	std::queue<Message> messages;

public:
	MessageBus() {};
	~MessageBus() {};

	void AddReceiver(std::function<void(Message)> messageReceiver)
	{
		receivers.push_back(messageReceiver);
	}

	void SendMessage(Message message)
	{
		messages.push(message);
	}

	void Notify()
	{
		while (!messages.empty()) {
			for (std::size_t i = 0; i < receivers.size(); ++i) {
				if (messages.front().IsMessageForReceiver(i)) {
					messages.front();
				}
			}

			/*for (auto iter = receivers.begin(); iter != receivers.end(); iter++) {
				(*iter)(messages.front());
			}*/

			messages.pop();
		}
	}
};

class BusNode {
protected:
	MessageBus *messageBus;

	std::function<void(Message)> getNotifyFunc()
	{
		auto messageListener = [=](Message message) -> void {
			this->onNotify(message);
		};
		return messageListener;
	}

	void Send(Message message)
	{
		messageBus->SendMessage(message);
	}

	virtual void onNotify(Message message)
	{
		// Do something here. Your choice. But you could do this.
		// std::cout << "Siopao! Siopao! Siopao! (Someone forgot to implement onNotify().)" << std::endl;
	}

public:
	BusNode(MessageBus *messageBus)
	{
		this->messageBus = messageBus;
		this->messageBus->AddReceiver(this->getNotifyFunc());
	}

	virtual void Update() {}
};

// This class will receive a message from ComponentB.
class ComponentA : public BusNode {
public:
	ComponentA(MessageBus* messageBus) : BusNode(messageBus) {}

private:
	void onNotify(Message message)
	{
		std::cout << "Component A received: " << message.GetEvent() << std::endl;
	}
};

// This class will send a message to ComponentA.
class ComponentB : public BusNode {
public:
	ComponentB(MessageBus* messageBus) : BusNode(messageBus) {}

	void update()
	{
		Message greeting("Hi!", 0);
		Send(greeting);
	}

private:
	void onNotify(Message message)
	{
		std::cout << "Component B received: " << message.GetEvent() << std::endl;
	}
};

//class Message2 {
//private:
//	std::string messageEvent;
//	int receiverId;
//
//public:
//	Message2(const std::string event, const int receiverId)
//	{
//		messageEvent = event;
//		this->receiverId = receiverId;
//	}
//
//	std::string GetMessage()
//	{
//		return messageEvent;
//	}
//
//	bool IsMessageForReceiver(int id) {
//		return receiverId == id;
//	}
//};
//
//class Mailbox {
//private:
//	vector<Message2> messages;
//	vector<std::function<void(Message)>> receivers;
//public:
//	void AddReceiver(Receipient receipient) {
//		receivers.push_back(receipient);
//	}
//	void CreateMessage(Message2 message) {
//		messages.push_back(message);
//	}
//
//	void Deliver() {
//		for (std::size_t i = 0; i < receivers.size(); ++i) {
//			for (Message2 m : messages) {
//				if (m.IsMessageForReceiver(i))
//					receivers[i].ReceiveMessage(m);
//			}
//		}
//	}
//};
//
//class Receipient {
//public:
//	int uid;
//
//	Receipient(int uid, Mailbox* mailbox) {
//		this->uid = uid;
//		mailbox->AddReceiver(*this);
//	}
//
//	void CreateMessage(string event, int id, Mailbox* mailbox) {
//		Message2 message(event, id);
//		mailbox->CreateMessage(message);
//	}
//
//	void ReceiveMessage(Message2 message) {
//		cout << "Component " << this << "received: " << message.GetMessage() << endl;
//	}
//};

int main() {
	//Mailbox mailbox;
	//Receipient compA(1, &mailbox);
	//Receipient compB(2, &mailbox);
	//
	//compB.CreateMessage("Hi!", 1, &mailbox);
	//mailbox.Deliver();

	MessageBus messageBus;

	//Creating ComponentA first will put it at the id of 0
	ComponentA compA(&messageBus);
	ComponentB compB(&messageBus);

	// This is supposed to act like a game loop.
	for (int ctr = 0; ctr < 2; ctr++) {
		compA.Update();
		compB.update();
		messageBus.Notify();
	}

	std::cin.get();

	return 0;
}
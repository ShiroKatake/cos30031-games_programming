#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <string>

using namespace std;

class Message {
private:
	std::string messageEvent;

public:
	Message(const std::string event)
	{
		messageEvent = event;
	}

	std::string GetEvent()
	{
		return messageEvent;
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
			for (auto iter = receivers.begin(); iter != receivers.end(); iter++) {
				cout << "message received" << endl;
				(*iter)(messages.front());
			}
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
		Message greeting("Hi!");
		Send(greeting);
	}

private:
	void onNotify(Message message)
	{
		std::cout << "Component B received: " << message.GetEvent() << std::endl;
	}
};



class Message2 {
private:
	std::string messageEvent;
	std::string receiverId;

public:
	Message2(const std::string event, const int receiverId)
	{
		messageEvent = event;
		this->receiverId = receiverId;
	}

	std::string GetEvent()
	{
		return messageEvent;
	}
};

class ComponentC {
	int uid;
public:
	ComponentC(int uid) {
		this->uid = uid;
	}
};

class Receipient {
public:
	int uid;
	Receipient(int uid) {
		this->uid = uid;
	}
};

int main() {
	MessageBus messageBus;
	ComponentA compA(&messageBus);
	ComponentB compB(&messageBus);
	vector<Receipient> everybody;
	// This is supposed to act like a game loop.
	for (int ctr = 0; ctr < 2; ctr++) {
		compA.Update();
		compB.update();
		messageBus.Notify();
	}

	std::cin.get();

	/*for (Receipient r : everybody) {
		if (r.uid == message.receipientUID)
			r.receiveMessage(message)
	}*/

	return 0;
}
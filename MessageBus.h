#ifndef MESSAGEBUS_H
#define MESSAGEBUS_H

#include <vector>
#include <queue>
#include <memory>

#include "Message.h"
#include "BusNode.h"


class MessageBus
{
public:
	MessageBus() {}
	~MessageBus() {}

	void AddReceiver(std::shared_ptr<BusNode> busNode);

	void SendMessage(std::shared_ptr<Message> msg);
	void SendImmediate(std::shared_ptr<Message> msg);
	void DispatchMessages();

private:
	std::queue<std::shared_ptr<Message>> m_MessageQueue;
	std::vector<std::shared_ptr<BusNode>> m_Receivers;
};

#endif // MESSAGEBUS_H

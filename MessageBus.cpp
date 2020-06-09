#include "MessageBus.h"
#include <iostream>
void MessageBus::AddReceiver(std::shared_ptr<BusNode> busNode)
{
	std::cout << "AddReceiver: " << typeid(*busNode).name() << std::endl;
	m_Receivers.push_back(busNode);
}

void MessageBus::SendMessage(std::shared_ptr<Message> msg)
{
	std::cout << "Received Message: " << (int)msg->m_Type << std::endl;
	m_MessageQueue.push(msg);
}

void MessageBus::SendImmediate(std::shared_ptr<Message> msg)
{
	for (auto iter = m_Receivers.begin(); iter != m_Receivers.end(); iter++)
	{
		(*iter)->HandleMessage(msg);
	}
}

void MessageBus::DispatchMessages()
{
	//std::cout << "MessageBus: I have " << m_Receivers.size() << " Receivers!" << std::endl;
	while (!m_MessageQueue.empty())
	{
		std::cout << "=== MessageBus: Dispatching " << m_MessageQueue.size() << " Messages! ===" << std::endl;
		for (auto iter = m_Receivers.begin(); iter != m_Receivers.end(); iter++)
		{
			//std::cout << "Node: " << typeid(*iter).name() << std::endl;
			std::shared_ptr<BusNode> node = (*iter); 
			//std::cout << "Node: " << typeid(*node).name() << std::endl;
			node->HandleMessage(m_MessageQueue.front());
		}

		m_MessageQueue.pop();
	}
}
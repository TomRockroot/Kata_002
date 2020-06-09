#include "InputComponent.h"
#include <iostream>

void InputComponent::Update(double deltaTime)
{
	while (!m_Workqueue.empty())
	{
		std::cout << "== InputComponent(" << m_EntityID << ") working on " << m_Workqueue.size() << " KeyCalls! ==" << std::endl;
		std::shared_ptr<KeyCall> keyCall = m_Workqueue.front();

		switch (keyCall->key)
		{
		case GLFW_KEY_F:
			if (keyCall->action == GLFW_PRESS)
			{
				std::cout << "InputComponent("<< m_EntityID << ") Pressed " << glfwGetKeyName(GLFW_KEY_F, 0) << " (" << GLFW_KEY_F << ") - payed respects." << std::endl;
			}
			break;

		case GLFW_KEY_W:
			if (keyCall->action == GLFW_REPEAT || keyCall->action == GLFW_PRESS)
			{
				std::shared_ptr<Message> msg = std::make_shared<Message>();
				msg->m_Type = MessageType::MT_MOVE;
				msg->move.id = m_EntityID;
				msg->move.direction.x = 0.0f;
				msg->move.direction.y = 0.0f;
				msg->move.direction.z = 0.1f;

				SystemLocator::GetMessageBus()->SendMessage(msg);
			}
			break;

		case GLFW_KEY_S:
			if (keyCall->action == GLFW_REPEAT || keyCall->action == GLFW_PRESS)
			{
				std::shared_ptr<Message> msg = std::make_shared<Message>();
				msg->m_Type = MessageType::MT_MOVE;
				msg->move.id = m_EntityID;
				msg->move.direction.x = 0.0f;
				msg->move.direction.y = 0.0f;
				msg->move.direction.z = -0.1f;

				SystemLocator::GetMessageBus()->SendMessage(msg);
			}
			break;
		
		case GLFW_KEY_A:
			if (keyCall->action == GLFW_REPEAT || keyCall->action == GLFW_PRESS)
			{
				std::shared_ptr<Message> msg = std::make_shared<Message>();
				msg->m_Type = MessageType::MT_MOVE;
				msg->move.id = m_EntityID;
				msg->move.direction.x = -0.1f;
				msg->move.direction.y = 0.0f;
				msg->move.direction.z = 0.0f;

				SystemLocator::GetMessageBus()->SendMessage(msg);
			}
			break;
		
		case GLFW_KEY_D:
			if (keyCall->action == GLFW_REPEAT || keyCall->action == GLFW_PRESS)
			{
				std::shared_ptr<Message> msg = std::make_shared<Message>();
				msg->m_Type = MessageType::MT_MOVE;
				msg->move.id = m_EntityID;
				msg->move.direction.x = 0.1f;
				msg->move.direction.y = 0.0f;
				msg->move.direction.z = 0.0f;

				SystemLocator::GetMessageBus()->SendMessage(msg);
			}
			break;

		default:
			break;
		}

		m_Workqueue.pop();
	}
}

void InputComponent::AddToWorkqueue(std::shared_ptr<KeyCall> keyCall)
{
	m_Workqueue.push(keyCall);
}

void InputComponent::HandleMessage(std::shared_ptr<Message> msg)
{
	// std::cout << "InputComponent(" << m_EntityID << ") incoming Message ..." << std::endl;
	
	switch (msg->m_Type)
	{
	case MessageType::MT_MOVE:
		break;
	}
}
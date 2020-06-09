#include "Input.h"
#include "EngineConfig.h"

#include <iostream>
#include <cassert>

Input::Input(GLFWwindow* window)
{
	glfwSetKeyCallback(window, key_callback);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::vector< std::shared_ptr<InputComponent>>* components = SystemLocator::GetInput()->GetComponents();
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		std::cout << "ESCAPE" << std::endl;
		glfwSetWindowShouldClose(window, true);
		break;

	case GLFW_KEY_F9:
		if (action == GLFW_PRESS)
		{
			std::cout << "F9" << std::endl;
			Message msg;
			msg.m_Type = MessageType::MT_CONFIG_SWITCH;
			msg.config_switch.attribute = ConfigAttribute::CA_WIREFRAME;
			std::shared_ptr<Message> msg_ptr = std::make_shared<Message>(msg);
			SystemLocator::GetMessageBus()->SendMessage(msg_ptr);
		}
		break;

	case GLFW_KEY_F5:
		if (action == GLFW_PRESS)
		{
			std::cout << "F5" << std::endl;
			Message msg;
			msg.m_Type = MessageType::MT_CONFIG_SWITCH;
			msg.config_switch.attribute = ConfigAttribute::CA_SIMPAUSE;
			std::shared_ptr<Message> msg_ptr = std::make_shared<Message>(msg);
			SystemLocator::GetMessageBus()->SendMessage(msg_ptr);
		}
		break;

	case GLFW_KEY_F6:
		if (action == GLFW_PRESS)
		{
			std::cout << "F6" << std::endl;
			Message msg;
			msg.m_Type = MessageType::MT_CONFIG_SWITCH;
			msg.config_switch.attribute = ConfigAttribute::CA_RENDERPAUSE;
			std::shared_ptr<Message> msg_ptr = std::make_shared<Message>(msg);
			SystemLocator::GetMessageBus()->SendMessage(msg_ptr);
		}
		break;
	
	default:
		if (SystemLocator::GetEngineConfig()->IsSimulationRunning())
		{
			KeyCall keyCall;
			keyCall.key = key;
			keyCall.scancode = scancode;
			keyCall.action = action;
			keyCall.mods = mods;
			std::shared_ptr<KeyCall> call_ptr = std::make_shared<KeyCall>(keyCall);

			for (auto iter = components->begin(); iter != components->end(); iter++)
			{
				(*iter)->AddToWorkqueue(call_ptr);
			}
		}
	}
}


void Input::ProvideComponent(EntityID entityID, MessageBus* msgBus)
{
	std::shared_ptr<InputComponent> comp = std::make_shared<InputComponent> (entityID);
	msgBus->AddReceiver(comp);
	p_Components.push_back(comp);
}

void Input::Update(double deltaTime)
{
	for (auto iter = p_Components.begin(); iter != p_Components.end(); iter++)
	{
		(*iter)->Update(deltaTime);
	}
}
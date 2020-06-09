#include "PhysicsComponent.h"
#include <iostream>

void PhysicsComponent::Update(double deltaTime)
{

}

void PhysicsComponent::HandleMessage(std::shared_ptr<Message> msg)
{
	switch (msg->m_Type)
	{
	case MessageType::MT_MOVE:
		// std::cout << "PhysicsComponent(" << m_EntityID << ") incoming Move Message" << std::endl;
		break;
	}
}
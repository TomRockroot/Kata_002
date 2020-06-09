#include "Physics.h"

void Physics::ProvideComponent(EntityID entityID, MessageBus* msgBus)
{
	std::shared_ptr<PhysicsComponent> physicsComp = std::make_shared<PhysicsComponent>(entityID);
	msgBus->AddReceiver(physicsComp);
	p_Components.push_back(physicsComp);
}

void Physics::Update(double deltaTime)
{

}
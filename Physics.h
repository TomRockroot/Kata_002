#ifndef PHYSICS_H
#define PHYSICS_H

#include "PhysicsComponent.h"
#include "MessageBus.h"

class Physics
{
public:
	Physics() {};
	~Physics() {};

	void ProvideComponent(EntityID entityID, MessageBus* msgBus);
	void Update(double deltaTime);
protected:
	std::vector< std::shared_ptr<PhysicsComponent>> p_Components;
};

#endif // PHYSICS_H


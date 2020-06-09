#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(EntityID entityID) : Component(entityID) {};

	void Update(double deltaTime);
	void HandleMessage(std::shared_ptr<Message> msg) override;

private:

	Transform transform;
};

#endif // PHYSICSCOMPONENT_H
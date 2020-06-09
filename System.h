#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <memory>

#include "Common.h"
#include "Component.h"
#include "MessageBus.h"
#include "SystemLocator.h"

class System
{
public:
	virtual void ProvideComponent(EntityID entityID, MessageBus* msgBus) = 0;
	virtual void Update(double deltaTime) = 0;

protected:
	// std::vector<Component*> p_Components; // This does not work like in C# due to "Downcasting"
};

#endif // SYSTEM_H
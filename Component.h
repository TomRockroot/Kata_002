#ifndef COMPONENT_H
#define COMPONENT_H

#include "Common.h"
#include "MessageBus.h"

class Component : public BusNode
{
public:
	Component(EntityID entityID) 
		: m_EntityID{ entityID } {};

	void Update(double deltaTime);

	bool IsActive() { return b_Active; }
	EntityID GetID() { return m_EntityID; }

protected:
	EntityID m_EntityID;
	bool b_Active = false;
};

#endif // COMPONENT_H
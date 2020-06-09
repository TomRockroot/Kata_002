#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <vector>
#include <queue>
#include <memory>

#include <GLFW/glfw3.h>

#include "Common.h"
#include "Component.h"
#include "Context.h"

#include "MessageBus.h"
#include "SystemLocator.h"

struct KeyCall
{
	int key, scancode, action, mods;
};

class InputComponent : public Component
{
public:
	InputComponent(EntityID entityID) : Component(entityID) {};
	
	void Update(double deltaTime);
	void HandleMessage(std::shared_ptr<Message> msg) override;
	void AddToWorkqueue(std::shared_ptr<KeyCall> keyCall);

private:
	std::queue<std::shared_ptr<KeyCall>> m_Workqueue;
};

#endif // INPUTCOMPONENT_H
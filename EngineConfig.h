#ifndef ENGINECONFIG_H
#define ENGINECONFIG_H

#include <memory>

#include "MessageBus.h"


class EngineConfig : public BusNode
{
public:
	EngineConfig() {};

	bool IsSimulationRunning() { return b_SimulationRunning; }
	bool IsRenderRunning() { return b_RenderRunning; }
	void HandleMessage(std::shared_ptr<Message> msg) override;
private:
	bool b_OpenGLWireframe = false;
	bool b_SimulationRunning = true;
	bool b_RenderRunning = true;
};

#endif // ENGINECONFIG_H


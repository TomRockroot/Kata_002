#include "EngineConfig.h"

#include <iostream>
#include <GL\glew.h>

void EngineConfig::HandleMessage(std::shared_ptr<Message> msg)
{
	switch (msg->m_Type)
	{
	// === Switch ===
	case MessageType::MT_CONFIG_SWITCH:
		switch (msg->config_bool.attribute)
		{
		// = Draw Wireframe =
		case ConfigAttribute::CA_WIREFRAME:
			b_OpenGLWireframe = !b_OpenGLWireframe;
			b_OpenGLWireframe ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE): glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;

		case ConfigAttribute::CA_SIMPAUSE:
			b_SimulationRunning = !b_SimulationRunning;
			std::cout << (b_SimulationRunning ? "Sim UNPAUSED" : "Sim PAUSED") << std::endl;
			break;

		case ConfigAttribute::CA_RENDERPAUSE:
			b_RenderRunning = !b_RenderRunning;
			std::cout << (b_RenderRunning ? "Render UNPAUSED" : "Render PAUSED") << std::endl;
			break;
		}
		break;

	// === Set Bool ===
	case MessageType::MT_CONFIG_SETBOOL:
		break;

	// === Set Float ===
	case MessageType::MT_CONFIG_SETFLOAT:
		break;
	}
}
#ifndef RENDERER_H 
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "RenderComponent.h"
#include "LightComponent.h"
#include "MessageBus.h"
#include "SystemLocator.h"

class Renderer
{
public:
	Renderer(GLFWwindow* window) : m_Window{ window } 
	{
		glEnable(GL_DEPTH_TEST);
	};
	~Renderer() {};
	
	void ProvideComponent(EntityID entityID, MessageBus* msgBus);
	void CreateLightSource(EntityID entityID, MessageBus* msgBus);

	void Update(double deltaTime, float screenRatio);

	std::shared_ptr<RenderComponent> GetComponent(EntityID entityID);
	std::vector<std::shared_ptr<LightComponent>>* GetLights()
	{
		return &p_Lights;
	};

private:
	void DrawGrid(int halfGridSize);

	std::vector<std::shared_ptr<RenderComponent>> p_Components;
	std::vector<std::shared_ptr<LightComponent>> p_Lights;

	GLFWwindow* m_Window;
};

#endif // RENDERER_H
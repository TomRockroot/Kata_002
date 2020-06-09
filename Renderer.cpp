#include "Renderer.h"
#include <iostream>

void Renderer::ProvideComponent(EntityID entityID, MessageBus* msgBus)
{
	std::shared_ptr<RenderComponent> renderComp = std::make_shared<RenderComponent>(entityID);
	msgBus->AddReceiver(renderComp);
	p_Components.push_back(renderComp);
}

void Renderer::CreateLightSource(EntityID entityID, MessageBus* msgBus)
{
	std::shared_ptr<LightComponent> lightComp = std::make_shared<LightComponent>(entityID);
	msgBus->AddReceiver(lightComp);
	p_Lights.push_back(lightComp);
}

std::shared_ptr<RenderComponent> Renderer::GetComponent(EntityID entityID)
{
	auto iter = p_Components.begin();
	auto end = p_Components.end();

	for (; iter != end; iter++)
	{
		if ((*iter)->GetID() == entityID)
		{
			return (*iter);
		}
	}
	assert(false);
	return nullptr;
}

void Renderer::DrawGrid(int halfGridSize)
{
	glBegin(GL_LINES);
	glColor3f(0.7f, 0.7f, 0.7f);
	glLineWidth(5.0);
	for (int i = -halfGridSize; i <= halfGridSize; i++)
	{
		glVertex3f( (float)i, 0, (float)-halfGridSize );
		glVertex3f( (float)i, 0, (float) halfGridSize );

		glVertex3f( (float)-halfGridSize, 0, (float)i );
		glVertex3f( (float)halfGridSize,  0, (float)i );
	}
	glEnd();
}

void Renderer::Update(double deltaTime, float screenRatio)
{
	glClearColor(0.8f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawGrid(100); // ToDo: Does not appear ... why?

	// Update all lights first
	auto iterLight = p_Lights.begin();
	auto endLight = p_Lights.end();

	for (; iterLight != endLight; iterLight++)
	{
		(*iterLight)->Update(deltaTime, screenRatio);
	}

	// Then update all RenderComponents
	auto iter = p_Components.begin();
	auto end  = p_Components.end();
	
	for (; iter != end; iter++)
	{
		(*iter)->Update(deltaTime, screenRatio);
	}
	
	glfwSwapBuffers(m_Window);
}
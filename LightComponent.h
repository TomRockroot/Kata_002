#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

#include "Component.h"
#include "GLShader.h"

#include "Camera.h"
#include "SystemLocator.h"

class LightComponent : public Component
{
public:
	LightComponent(EntityID entityID) : Component(entityID)
	{
		LoadLightSymbol();
	};

	void Update(double deltaTime, float screenRatio);
	void HandleMessage(std::shared_ptr<Message> msg) override;

private:
	double tempTime = 0;

	Float3 m_renderPos;

	GLuint m_VertexArrayObject;
	GLuint m_ShaderProgram;

	void LoadLightSymbol();
};

#endif // LIGHTCOMPONENT_H

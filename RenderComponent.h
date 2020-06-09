#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include <GL\glew.h>

#include "Component.h"
#include "GLShader.h"

#include "Camera.h"
#include "SystemLocator.h"

#include "Model.h"

class RenderComponent : public Component
{
public:
	RenderComponent(EntityID entityID) : Component(entityID) 
	{
		m_renderPos.x = 0.0f;
		m_renderPos.y = 0.0f;
		m_renderPos.z = 0.0f;

		m_renderRota.x = 0.0f;
		m_renderRota.y = 0.0f;
		m_renderRota.z = 0.0f;

		m_renderScale.x = 0.2f;
		m_renderScale.y = 0.2f;
		m_renderScale.z = 0.2f;

		m_ShaderProgram = LoadShader("phong.vert", "phong.frag");
	};

	~RenderComponent()
	{
		delete m_Model;
		
	}

	void Update(double deltaTime, float screenRatio);
	void HandleMessage(std::shared_ptr<Message> msg) override;

	Float3 GetPosition() { return m_renderPos; }

private:
	Model* m_Model = nullptr;

	double tempTime = 0;
	Float3 m_renderPos;
	Float3 m_renderRota;
	Float3 m_renderScale;

	GLuint m_VertexArrayObject = 0;
	GLuint m_ShaderProgram = 0;
	
	void SetShaderInfo(GLuint shader, float screenRatio);

};

#endif // RENDERCOMPONENT_H
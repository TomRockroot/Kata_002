#include "RenderComponent.h"
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "ModelLoader.h"

void RenderComponent::Update(double deltaTime, float screenRatio)
{
	if (m_Model)
	{
		SetShaderInfo(m_ShaderProgram, screenRatio);
		m_Model->Draw(m_ShaderProgram);
	}
}


void RenderComponent::SetShaderInfo(GLuint shader, float screenRatio)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(m_renderPos.x, m_renderPos.y, m_renderPos.z));
	model = glm::rotate(model, glm::radians(m_renderRota.x), glm::vec3(1.0, 0.0, 0.0));
	model = glm::rotate(model, glm::radians(m_renderRota.y), glm::vec3(0.0, 1.0, 0.0));
	model = glm::rotate(model, glm::radians(m_renderRota.z), glm::vec3(0.0, 0.0, 1.0));
	model = glm::scale(model, glm::vec3(m_renderScale.x, m_renderScale.y, m_renderScale.z));

	Camera* cam = SystemLocator::GetCamera();
	glm::mat4 view = cam->GetView();

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), screenRatio, 0.1f, 100.0f);

	glm::mat4 normalMat = glm::transpose( glm::inverse(model) );
	glm::mat4 mvp = projection * view * model;

	glUseProgram(m_ShaderProgram);
	
	// Vertex
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, "normalMat"), 1, GL_FALSE, glm::value_ptr(normalMat));
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	
	// Fragment
		// Material

		// Light
	glm::vec3 lightPos(0.0f, 2.0f, 0.0f);
	glm::vec3 lightColor(1.0f, 1.0f, 0.6f);
	glm::vec3 lightAmbient(0.05f, 0.05f, 0.05f);

	glm::vec3 camPos = cam->GetPosition();
	glm::vec3 camDir = cam->GetDirection();
	
			// Ambient Light
	glUniform3f(glGetUniformLocation(m_ShaderProgram, "ambientLight"), lightAmbient.x, lightAmbient.y, lightAmbient.z);

			// Directional Light
	glUniform3f(glGetUniformLocation(m_ShaderProgram, "dirLight.direction"), 0.5f, -1.0f, 0.0f);
	glUniform3f(glGetUniformLocation(m_ShaderProgram, "dirLight.color"), 0.1f, 0.05f, 0.25f);
	
			// Point Lights
	for (int i = 0; i < 4; i++)
	{
		std::string number = std::to_string(i);
		glUniform3f(glGetUniformLocation(m_ShaderProgram, ("pointLights[" + number + "].position").c_str() ), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(m_ShaderProgram, ("pointLights[" + number + "].color").c_str() ), lightColor.x, lightColor.y, lightColor.z);

		glUniform1f(glGetUniformLocation(m_ShaderProgram, ("pointLights[" + number + "].constant").c_str() ), 1.0f);
		glUniform1f(glGetUniformLocation(m_ShaderProgram, ("pointLights[" + number + "].linear").c_str() ), 0.09f);
		glUniform1f(glGetUniformLocation(m_ShaderProgram, ("pointLights[" + number + "].quadratic").c_str() ), 0.032f);
	}
		// Camera
	glm::vec3 viewPos = cam->GetPosition();
	glUniform3f(glGetUniformLocation(m_ShaderProgram, "viewPos"), viewPos.x, viewPos.y, viewPos.z);
	glUniform1i(glGetUniformLocation(m_ShaderProgram, "material.shininess"), 64);
}


void RenderComponent::HandleMessage(std::shared_ptr<Message> msg)
{
	// std::cout << "RenderComponent(" << m_EntityID << ") incoming Message ..." << std::endl;

	switch (msg->m_Type)
	{
	case MessageType::MT_MOVE:
		if (msg->move.id == m_EntityID)
		{
			m_renderPos.x += msg->move.direction.x;
			m_renderPos.y += msg->move.direction.y;
			m_renderPos.z += msg->move.direction.z;

			std::cout << "== MT_MOVE RenderComp: " << m_EntityID << " ( " << m_renderPos.x << " | " << m_renderPos.y << " | " << m_renderPos.z << " ) " << std::endl;
		}
		break;
	
	case MessageType::MT_LOAD_MODEL:
		if (msg->load_model.id == m_EntityID)
		{
			std::cout << "Loading Model at " << msg->load_model.path << std::endl;
			m_Model = new Model(msg->load_model.path);
		}
		break;
	}

}
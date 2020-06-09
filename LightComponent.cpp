#include "LightComponent.h"

#include <iostream>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "ModelLoader.h"

void LightComponent::LoadLightSymbol()
{
	std::cout << "LET THERE BE LIGHT" << std::endl;
	m_ShaderProgram = LoadShader("light.vert", "light.frag");

	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	unsigned int dataSize;
	const GLfloat* vertex_buffer_data = ModelLoader::LoadShape(ShapeType::ST_CUBE, dataSize);
	glBufferData(GL_ARRAY_BUFFER, dataSize, vertex_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	std::cout << "AND THERE WAS LIGHT" << std::endl;
}

void LightComponent::Update(double deltaTime, float screenRatio)
{
	tempTime += deltaTime;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(m_renderPos.x, m_renderPos.y, m_renderPos.z));
//	model = glm::rotate(model, glm::radians(tempTime * 0.01f), glm::normalize(glm::vec3(1.0, 1.0, 1.0)) );
	model = glm::scale(model, glm::vec3(0.2f));

	glm::mat4 view = SystemLocator::GetCamera()->GetView();

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), screenRatio, 0.1f, 100.0f);

	glm::mat4 mvp = projection * view * model;

	glUseProgram(m_ShaderProgram);


	glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

	glUniform3f(glGetUniformLocation(m_ShaderProgram, "objectColor"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(m_ShaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f);

	glBindVertexArray(m_VertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LightComponent::HandleMessage(std::shared_ptr<Message> msg)
{
	switch (msg->m_Type)
	{
	case MessageType::MT_MOVE:
		if (msg->move.id == m_EntityID)
		{
			Float3 dir = msg->move.direction;
			m_renderPos.x = dir.x;
			m_renderPos.y = dir.y;
			m_renderPos.z = dir.z;
		}
		break;
	}
}
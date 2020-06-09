#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>

#include <memory>

#include "MessageBus.h"
#include "SystemLocator.h"

class Camera : public BusNode
{
public:
	void Update(double deltaTime);

	glm::mat4 GetView() { return m_View; }
	glm::vec3 GetPosition() { return m_CameraPos; }
	glm::vec3 GetDirection() { return m_CameraDirection; }

	void HandleMessage(std::shared_ptr<Message> msg) override;

private:
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 20.0f);
	glm::vec3 m_CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_CameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);	// glm::normalize(m_CameraPos - m_CameraTarget);
	glm::vec3 m_CameraRight = glm::vec3(1.0f, 0.0f, 0.0f);		// glm::normalize(glm::cross(up, m_CameraDirection));
	glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);			//  glm::cross(m_CameraDirection, m_CameraRight);

	EntityID m_TargetID;

	glm::mat4 m_View = glm::mat4(1.0f);

	void SetPosition(float x, float y, float z) { m_CameraPos = glm::vec3(x, y, z); }
	void SetTargetPos(float x, float y, float z){ m_CameraTarget = glm::vec3(x, y, z); }
	void MoveTargetPos(float x, float y, float z) { m_CameraTarget += glm::vec3(x, y, z); }
};
#endif

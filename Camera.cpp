#include "Camera.h"

#include <iostream>

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


void Camera::Update(double deltaTime)
{


	m_CameraDirection	= glm::normalize(m_CameraPos - m_CameraTarget);
	m_CameraRight		= glm::normalize(glm::cross(up, m_CameraDirection));
	m_CameraUp			= glm::cross(m_CameraDirection, m_CameraRight);

	m_View = glm::lookAt(m_CameraPos, m_CameraTarget, m_CameraUp);
}


void Camera::HandleMessage(std::shared_ptr<Message> msg)
{
	std::cout << "Camera: Incoming Message ..." << std::endl;
	switch (msg->m_Type)
	{
	case MessageType::MT_CAM_POSITION:
		Float3 posCamera = msg->cam_position.position;
		SetPosition(posCamera.x, posCamera.y, posCamera.z);

		std::cout << "MT_CAM_POSITION: " << posCamera.x << " | " << posCamera.y << " | " << posCamera.z << std::endl;
		break;

	case MessageType::MT_CAM_TARGET:
		m_TargetID = msg->cam_target.id;
		Float3 posTarget = msg->cam_target.position;
		m_CameraTarget = glm::vec3(posTarget.x, posTarget.y, posTarget.z);

		break;

	case MessageType::MT_MOVE:
		if (msg->move.id == m_TargetID)
		{
			Float3 dir = msg->move.direction;
			MoveTargetPos(dir.x, dir.y, dir.z);
		}
		break;
	}
}
#include <iostream>
#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Input.h"
#include "Physics.h"
#include "Renderer.h"
#include "EngineConfig.h"
#include "Camera.h"

#include "SystemLocator.h"

#include "Common.h"

using namespace std::chrono;
typedef high_resolution_clock::time_point TIME;

static void error_callback(int error, const char* description)
{
	std::cout << "Glew Error: " << error << " " << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	// GLFW SetUp
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		std::cout << "GLFW: Failed to init!" << std::endl;
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Unicorn Invasion of Dundee", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "GLFW: Window could not be created!" << std::endl;

		glfwTerminate();
		return EXIT_FAILURE;
	}

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwMakeContextCurrent(window); // <- mui importante
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLEW SetUP
	glewExperimental = GL_TRUE;

	const GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		std::cout << "GLEW: Failed to init!\n" << glewGetErrorString(err) << std::endl;

		glfwTerminate();
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	// Game Components
	MessageBus msgBus;
	SystemLocator::Provide(&msgBus);

		// ToDo: this seems very odd / unsymmetric ... re-think this!
	std::shared_ptr<EngineConfig> config = std::make_shared<EngineConfig>();
	SystemLocator::Provide(config.get());
	msgBus.AddReceiver(config);

	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	SystemLocator::Provide(camera.get());
	msgBus.AddReceiver(camera);

	Renderer renderer(window);
	SystemLocator::Provide(&renderer);

	Input input(window);
	SystemLocator::Provide(&input);

	Physics physics;
	SystemLocator::Provide(&physics);

	

	// Entity Test
	// ToDo: Entity-Factory
	// Entity ntitty = EntityFactory::LoadEntity(Path);
	// EntityFactory::CreateEntity(ntitty);
	SystemLocator::GetInput()->ProvideComponent(1, &msgBus);
	SystemLocator::GetRenderer()->ProvideComponent(1, &msgBus);
	SystemLocator::GetRenderer()->ProvideComponent(2, &msgBus);
	SystemLocator::GetRenderer()->ProvideComponent(3, &msgBus);
	SystemLocator::GetRenderer()->CreateLightSource(4, &msgBus);
	SystemLocator::GetPhysics()->ProvideComponent(1, &msgBus);

	{
		std::shared_ptr<Message> msg = std::make_shared<Message>();
		msg->m_Type = MessageType::MT_CAM_POSITION;
		msg->cam_position.position.x = 0.0f;
		msg->cam_position.position.y = 10.0f;
		msg->cam_position.position.z = -4.0f;
		SystemLocator::GetMessageBus()->SendMessage(msg);
	}

	{
		Float3 pos = SystemLocator::GetRenderer()->GetComponent(1)->GetPosition();
		std::shared_ptr<Message> msg = std::make_shared<Message>();
		msg->m_Type = MessageType::MT_CAM_TARGET;
		msg->cam_target.id = 1;
		msg->cam_target.position.x = pos.x;
		msg->cam_target.position.y = pos.y;
		msg->cam_target.position.z = pos.z;
		SystemLocator::GetMessageBus()->SendMessage(msg);
	}

	for( int m = 1; m < 4; m++)
	{
		{
			std::shared_ptr<Message> msg = std::make_shared<Message>();
			msg->m_Type = MessageType::MT_MOVE;
			msg->move.id = m + 1;
			msg->move.direction.x = 0.0f + m;
			msg->move.direction.y = 1.1f;
			msg->move.direction.z = 2.0f + m;
			SystemLocator::GetMessageBus()->SendMessage(msg);
		}

		{
			std::shared_ptr<Message> msg = std::make_shared<Message>();
			msg->m_Type = MessageType::MT_LOAD_MODEL;
			msg->load_model.id = m + 1;
			msg->load_model.path = "resources/objects/nanosuit/nanosuit.obj";
			SystemLocator::GetMessageBus()->SendMessage(msg);
		}
	}



	{
		std::shared_ptr<Message> msg = std::make_shared<Message>();
		msg->m_Type = MessageType::MT_LOAD_MODEL;
		msg->load_model.id = 1;
		msg->load_model.path = "resources/objects/nanosuit/nanosuit.obj";
		SystemLocator::GetMessageBus()->SendMessage(msg);
	}

	{
		std::shared_ptr<Message> msg = std::make_shared<Message>();
		msg->m_Type = MessageType::MT_MOVE;
		msg->move.id = 2;
		msg->move.direction.x = -1.5f;
		msg->move.direction.y = 0.1f;
		msg->move.direction.z = -1.0f;
		SystemLocator::GetMessageBus()->SendMessage(msg);
	}

	{
		std::shared_ptr<Message> msg = std::make_shared<Message>();
		msg->m_Type = MessageType::MT_MOVE;
		msg->move.id = 3;
		msg->move.direction.x = 1.5f;
		msg->move.direction.y = 0.1f;
		msg->move.direction.z = 0.4f;
		SystemLocator::GetMessageBus()->SendMessage(msg);
	}

	// Light
	{
		std::shared_ptr<Message> msg = std::make_shared<Message>();
		msg->m_Type = MessageType::MT_MOVE;
		msg->move.id = 4;
		msg->move.direction.x = 0.0f;
		msg->move.direction.y = 2.0f;
		msg->move.direction.z = 0.0f;
		SystemLocator::GetMessageBus()->SendMessage(msg);
	}

	// GameLoop
	TIME lastTime = high_resolution_clock::now();
	while (!glfwWindowShouldClose(window))
	{
		TIME currentTime = high_resolution_clock::now();
		auto millisec = duration_cast<milliseconds>(currentTime - lastTime);
		double deltaTime = (double) millisec.count();

		SystemLocator::GetMessageBus()->DispatchMessages();

		if (SystemLocator::GetEngineConfig()->IsSimulationRunning())
		{
			// INPUT
			SystemLocator::GetInput()->Update(deltaTime);
			// UPDATE
			SystemLocator::GetPhysics()->Update(deltaTime);
		}

		if (SystemLocator::GetEngineConfig()->IsRenderRunning())
		{
			// CAMERA
			SystemLocator::GetCamera()->Update(deltaTime);
			// RENDER
			SystemLocator::GetRenderer()->Update(deltaTime, (float) screenWidth / (float) screenHeight);
		}

		glfwPollEvents();
		lastTime = currentTime;
	}

	glfwTerminate();

	return 0;
}
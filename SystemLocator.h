#ifndef SYSTEMLOCATOR_H
#define SYSTEMLOCATOR_H

// Forward declarations
class Input;
class Renderer;
class Physics;
class MessageBus;
class EngineConfig;
class Camera;

class SystemLocator
{
public:
	static MessageBus* GetMessageBus() { return m_MessageBus; }
	static void Provide(MessageBus* msgBus) { m_MessageBus = msgBus; }

	static Input* GetInput() { return m_Input; }
	static void Provide(Input* input) { m_Input = input; }

	static Renderer* GetRenderer() { return m_Renderer; }
	static void Provide(Renderer* renderer) { m_Renderer = renderer; }

	static Physics* GetPhysics() { return m_Physics; }
	static void Provide(Physics* physics) { m_Physics = physics; }

	static EngineConfig* GetEngineConfig() { return m_EngineConfig; }
	static void Provide(EngineConfig* config) { m_EngineConfig = config; }

	static Camera* GetCamera() { return m_Camera; }
	static void Provide(Camera* camera) { m_Camera = camera; }

private:
	static MessageBus* m_MessageBus;
	static EngineConfig* m_EngineConfig;
	static Input* m_Input;
	static Renderer* m_Renderer;
	static Physics* m_Physics;
	static Camera* m_Camera;
};
#endif SYSTEMLOCATOR_H
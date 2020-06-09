#ifndef INPUT_H
#define INPUT_H



#include "InputComponent.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Input
{
public:
	Input(GLFWwindow* window);
	~Input() {};

	void ProvideComponent(EntityID entityID, MessageBus* msgBus);
	void Update(double deltaTime);

	// important for key_callback(GLFWwindow*, [...] )
	std::vector< std::shared_ptr<InputComponent>>* GetComponents() { return &p_Components;  }
private:
	std::vector< std::shared_ptr<InputComponent>> p_Components;
	std::vector<Context> m_Contexts;
};
#endif // INPUT_H

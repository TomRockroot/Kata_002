#ifndef CONTEXT_H
#define CONTEXT_H

#include <map>

// Forward declarations
class InputAction {};
class InputState {};
class InputRange {};

class Context
{
public:
	Context(int priority, const char* filePath) : m_Priority{ priority } {};
	~Context() {};

	bool ProcessInput(int key);
	bool ProcessInput(int key, bool state);
	bool ProcessInput(int key, double range);

	bool operator() (int lhs, int rhs) const { return lhs < rhs; }

private:
	int m_Priority;
	std::map<int, InputAction> m_Actions;
	std::map<int, InputState> m_States;
	std::map<int, InputRange> m_Ranges;

	void LoadContext(const char* filePath);
};
#endif // CONTEXT_H

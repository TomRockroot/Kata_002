#include "SystemLocator.h"

MessageBus* SystemLocator::m_MessageBus = nullptr;
Input* SystemLocator::m_Input		= nullptr;
Renderer* SystemLocator::m_Renderer = nullptr;
Physics* SystemLocator::m_Physics	= nullptr;
EngineConfig* SystemLocator::m_EngineConfig = nullptr;
Camera* SystemLocator::m_Camera		= nullptr;
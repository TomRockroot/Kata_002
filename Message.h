#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

#include "Common.h"

enum class MessageType
{
	MT_MOVE,
	MT_COLLISION,

	MT_CAM_TARGET,
	MT_CAM_POSITION,

	MT_LOAD_MODEL,

	MT_CONFIG_SWITCH,
	MT_CONFIG_SETBOOL,
	MT_CONFIG_SETFLOAT
};

enum class ConfigAttribute
{
	CA_WIREFRAME,
	CA_GAMESPEED,
	CA_SIMPAUSE,
	CA_RENDERPAUSE
};

struct Float3
{
	float x, y, z;
};

struct Message
{
	MessageType m_Type;
	
	union
	{
		struct
		{
			EntityID id;
			Float3 direction;
		} move;

		struct
		{
			EntityID id1;
			EntityID id2;
			Float3 direction1;
			Float3 direction2;
		} collision;

		struct
		{
			EntityID id;
			Float3 position;
		} cam_target;

		struct
		{
			Float3 position;
		} cam_position;

		struct
		{
			EntityID id;
			const char* path;
		} load_model;

		struct
		{
			ConfigAttribute attribute;
		} config_switch;

		struct
		{
			ConfigAttribute attribute;
			bool value;
		} config_bool;

		struct
		{
			ConfigAttribute attribute;
			float value;
		} config_float;
	};
};

#endif // MESSAGE_H


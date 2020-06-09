#ifndef COMMON_H
#define COMMON_H

typedef unsigned int EntityID;

static const int MAX_NUM_ENTITIES = 16;
static const int WIDTH = 800, HEIGHT = 600;

struct Transform
{
	struct position
	{
		float x, y, z;
	};
	struct rotation
	{
		float pitch, yaw, roll;
	};
	struct scale
	{
		float scaleX, scaleY, scaleZ = 1;
	};
};

struct Velocity
{
	float x, y, z;
};

#endif // COMMON_H
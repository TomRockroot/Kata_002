#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <GL\glew.h>
#include <glm.hpp>

enum class ShapeType
{
	ST_TRI,
	ST_QUAD,
	ST_CUBE
};

class ModelLoader
{
public:
	static const GLfloat* LoadShape(ShapeType shape, unsigned int &size);
	static const GLfloat* LoadModel(const char* modelPath);

private:
	//const char* modelPath;
	//GLfloat m_cached_model[];

	static const GLfloat g_tri[];
	static const GLfloat g_quad[];
	static const GLfloat g_cube[];
};

#endif // MODELLOADER

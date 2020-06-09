#include "ModelLoader.h"

#include <string>
#include <iostream>
#include <fstream>


const GLfloat ModelLoader::g_tri[] =
{
	// vertices				// normals				// tex coords
	-1.0f, -1.0f, 0.0f,		0.0f,  0.0f, 1.0f,		-1.0f, -1.0f,		// bottom left  
	 1.0f, -1.0f, 0.0f,		0.0f,  0.0f, 1.0f,		1.0f, -1.0f,		// bottom right
	 0.0f,  1.0f, 0.0f,		0.0f,  0.0f, 1.0f,		0.0f,	1.0f		// top
};

const GLfloat ModelLoader::g_quad[] =
{
	// positions			// normals				// tex coords
	 0.8f, 0.8f, 0.0f,		0.0f,  0.0f, 1.0f,		1.0f, 1.0f,	// top right
	-0.8f, 0.8f, 0.0f,		0.0f,  0.0f, 1.0f,		0.0f, 1.0f	// top left
	-0.8f,-0.8f, 0.0f,		0.0f,  0.0f, 1.0f,		0.0f, 0.0f,	// bottom left

	 0.8f, 0.8f, 0.0f,		0.0f,  0.0f, 1.0f,		1.0f, 1.0f,	// top right
	-0.8f,-0.8f, 0.0f,		0.0f,  0.0f, 1.0f,		0.0f, 0.0f,	// bottom left
	 0.8f,-0.8f, 0.0f,		0.0f,  0.0f, 1.0f,		1.0f, 0.0f,	// bottom right
};

const GLfloat ModelLoader::g_cube[] =
{
	// positions			// normals				// tex coords
	-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,	1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	1.0f,  0.0f,  0.0f,		0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 0.0f
};

const GLfloat* ModelLoader::LoadModel(const char* modelPath)
{
	unsigned int dataSize;
	return LoadShape(ShapeType::ST_CUBE, dataSize);
}

const GLfloat* ModelLoader::LoadShape(ShapeType shape, unsigned int& size)
{
	switch (shape)
	{
	case ShapeType::ST_CUBE:
		size = sizeof(g_cube);
		return g_cube;

	case ShapeType::ST_QUAD:
		size = sizeof(g_quad);
		return g_quad;

	case ShapeType::ST_TRI:
		size = sizeof(g_tri);
		return g_tri;
	}
}
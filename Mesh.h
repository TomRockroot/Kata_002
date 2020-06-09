#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm.hpp>
#include <string>
#include <vector>

enum class TexType
{
	TT_None,
	TT_Diffuse,
	TT_Specular
};

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};

struct Texture
{
	unsigned int id = 0;
	TexType type = TexType::TT_None;
	std::string path = "";
};

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices,const std::vector<unsigned int>& indices,const std::vector<Texture>& textures) :
		m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
	{
		setupMesh();
	}

	void Draw(GLuint shader);

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif // MESH_H


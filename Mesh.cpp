#include "Mesh.h"

#include <iostream>

void Mesh::Draw(GLuint shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string uniformName;
		TexType type = m_Textures[i].type;
		if (type == TexType::TT_Diffuse)
		{
			uniformName = "material.diffuse" + std::to_string(diffuseNr);
			diffuseNr++;
		}
		else if (type == TexType::TT_Specular)
		{
			uniformName = "material.specular" + std::to_string(specularNr);
			specularNr++;
		}
		glUniform1i(glGetUniformLocation(shader, uniformName.c_str()), i);
		glBindTexture(GL_TEXTURE_2D, m_Textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	std::cout << "Setup Mesh\n Vertices: " << m_Vertices.size() << "\n Indices: " << m_Indices.size() << "\n Textures: " << m_Textures.size() << std::endl;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER,
		m_Vertices.size() * sizeof(Vertex),
		m_Vertices.data(),
		GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		m_Indices.size() * sizeof(unsigned int),
		m_Indices.data(),
		GL_STATIC_DRAW);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
		sizeof(Vertex), (void*)0);
	// normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// tex coord
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FLOAT,
		sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));

	glBindVertexArray(0);
}
#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model
{
public:
	Model(const char* path)
	{
		LoadModel(path);
	}

	void Draw(GLuint shader);

private:
	std::vector<Mesh> m_Meshes;
	std::string m_Directory;

	std::vector<Texture> m_TexturesLoaded;

	void LoadModel(std::string path);

	
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat,
		aiTextureType type, TexType texType);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

#endif // MODEL_H

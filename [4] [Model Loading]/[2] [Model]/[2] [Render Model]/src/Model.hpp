#pragma once

#include "Mesh.hpp"
#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory);

class Model {
public:

	Model(const char* path)
	{
		this->loadModel(path);
	}

	void Draw(Shader& shader)
	{
		for (auto mesh : meshes)
			mesh.Draw(shader);
	}

private:

	// Model Data
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;

	void loadModel(const string& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
			return;
		}

		directory = path.substr(0, path.find_last_of('/'));

		processNode(scene->mRootNode, scene);

	}
	void processNode(aiNode* node, const aiScene* scene)
	{
		// process all the node's meshes (if any)
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}

		// Then do the same for each of its children
		for (int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		// Data
		vector<Vertex> vertices;
		vector<unsigned int> indecies;
		vector<Texture> textures;

		// Vertex
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			// Position
			Vertex vertex;
			glm::vec3 vector3;

			vector3.x = mesh->mVertices[i].x;
			vector3.y = mesh->mVertices[i].y;
			vector3.z = mesh->mVertices[i].z;

			vertex.Position = vector3;

			// Normals 
			if (mesh->HasNormals())
			{
				vector3.x = mesh->mNormals[i].x;
				vector3.y = mesh->mNormals[i].y;
				vector3.z = mesh->mNormals[i].z;

				vertex.Normal = vector3;
			}

			// Texture Coordinate
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vector2;

				vector2.x = mesh->mTextureCoords[0][i].x;
				vector2.y = mesh->mTextureCoords[0][i].y;

				vertex.TexCoords = vector2;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f);

			vertices.push_back(vertex);
		}

		// Indices
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++)
				indecies.push_back(face.mIndices[j]);
		}

		// Texture
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// Diffuse Map
		vector<Texture> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		// Specular Map
		vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		return Mesh(vertices, indecies, textures);
	}

	vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;

		for (int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (int j = 0; j < textures_loaded.size(); j++)
			{
				if (strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}

			if (!skip)
			{
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), directory);
				texture.path = str.C_Str();
				texture.type = typeName;
				textures.push_back(texture);
				textures_loaded.push_back(texture);
			}
		}

		return textures;
	}

};

unsigned int TextureFromFile(const char* path, const string& directory)
{
	string fileName = string(path);
	fileName = directory + '/' + fileName;

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	/* Filter Options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return textureID;
}

#ifndef MORPHEUSRESOURCEMANAGER_H
#define MORPHEUSRESOURCEMANAGER_H

#include "MorpheusModel.h"
#include "MorpheusShader.h"
#include "MorpheusTexture.h"
#include <unordered_map>
#include <string>
#include <vector>

namespace morpheus {
	class ResourceManager {
	private:
		std::vector<std::string> shaderNames;
		std::vector<std::string> modelNames;
		std::vector<std::string> textureNames;
		std::string globalPrefix;
		std::string shaderPrefix;
		std::string modelPrefix;
		std::string texturePrefix;
		std::string shaderSuffix;
		std::string modelSuffix;
		std::string textureSuffix;
		std::string vertSuffix;
		std::string fragSuffix;
		std::unordered_map<std::string, morpheus::Model*> models;
		std::unordered_map<std::string, morpheus::Shader*> shaders;
		std::unordered_map<std::string, morpheus::Texture*> textures;
		int toInt(std::string s);
		unsigned int toUInt(std::string s);
		float toFloat(std::string s);
		double toDouble(std::string s);
		int indexOf(std::string str1, std::string f);
		void loadShaderManifest(std::string fileName);
		void loadModelManifest(std::string fileName);
		void loadTextureManifest(std::string fileName);
		void loadResourceManifest(std::string fileName);
		void loadManifests(std::string fileName);
		int addVert(std::vector<unsigned int>& vertData, unsigned int v, unsigned int n, unsigned int uv);
		void removeModel(std::string fileName);
		void removeShader(std::string fileName);
		void removeTexture(std::string fileName);
		void loadModel(std::string fileName);
		void loadShader(std::string fileName);
		void loadTexture(std::string fileName);
	public:
		ResourceManager(std::string mfName);
		~ResourceManager();
		Model* getModel(std::string fileName);
		Shader* getShader(std::string fileName);
		Texture* getTexture(std::string fileName);
		void convertObjModel(std::string filename);
	};
}

#endif // MORPHEUSRESOURCEMANAGER_H
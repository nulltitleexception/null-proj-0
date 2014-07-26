#ifndef NTERESOURCEMANAGER_H
#define NTERESOURCEMANAGER_H

#include "nteModel.h"
#include "nteShader.h"
#include "nteTexture.h"
#include <unordered_map>
#include <string>
#include <vector>

namespace nte {
	class ResourceManager {
	private:
		std::string version;
		std::string readme;
		std::vector<std::string> shaderNames;
		std::vector<std::string> modelNames;
		std::vector<std::string> textureNames;
		std::string globalPrefix;
		std::string metaPrefix;
		std::string shaderPrefix;
		std::string modelPrefix;
		std::string texturePrefix;
		std::string shaderSuffix;
		std::string modelSuffix;
		std::string textureSuffix;
		std::string vertSuffix;
		std::string fragSuffix;
		std::unordered_map<std::string, nte::Model*> models;
		std::unordered_map<std::string, nte::Shader*> shaders;
		std::unordered_map<std::string, nte::Texture*> textures;
		int toInt(std::string s);
		unsigned int toUInt(std::string s);
		float toFloat(std::string s);
		double toDouble(std::string s);
		int indexOf(std::string str1, std::string f);
		void loadReadme(std::string fileName);
		void loadVersion(std::string versionFileName, std::string buildFileName);
		void loadMetaManifest(std::string fileName);
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
		std::string getVersion();
		Model* getModel(std::string fileName);
		Shader* getShader(std::string fileName);
		Texture* getTexture(std::string fileName);
		void convertObjModel(std::string filename);
	};
}

#endif // NTERESOURCEMANAGER_H
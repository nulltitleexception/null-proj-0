#ifndef NTERESOURCEMANAGER_H
#define NTERESOURCEMANAGER_H

#include "nteModel.h"
#include "nteShader.h"
#include "nteTexture.h"
#include "nteFont.h"
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
		std::vector<std::string> fontNames;
		std::string globalPrefix;
		std::string metaPrefix;
		std::string shaderPrefix;
		std::string modelPrefix;
		std::string texturePrefix;
		std::string fontPrefix;
		std::string shaderSuffix;
		std::string modelSuffix;
		std::string textureSuffix;
		std::string fontSuffix;
		std::string vertSuffix;
		std::string fragSuffix;
		std::unordered_map<std::string, nte::Model*> models;
		std::unordered_map<std::string, nte::Shader*> shaders;
		std::unordered_map<std::string, nte::Texture*> textures;
		std::unordered_map<std::string, nte::Font*> fonts;
		int toInt(std::string);
		unsigned int toUInt(std::string);
		float toFloat(std::string);
		double toDouble(std::string);
		int indexOf(std::string, std::string);
		void loadReadme(std::string);
		void loadVersion(std::string, std::string);
		void loadMetaManifest(std::string);
		void loadShaderManifest(std::string );
		void loadModelManifest(std::string);
		void loadTextureManifest(std::string);
		void loadFontManifest(std::string);
		void loadResourceManifest(std::string);
		void loadManifests(std::string);
		int addVert(std::vector<unsigned int>&, unsigned int, unsigned int, unsigned int);
		void removeModel(std::string);
		void removeShader(std::string);
		void removeTexture(std::string);
		void removeFont(std::string);
		void loadModel(std::string);
		void loadShader(std::string);
		void loadTexture(std::string);
		void loadFont(std::string);
	public:
		ResourceManager(std::string);
		~ResourceManager();
		std::string getVersion();
		Model* getModel(std::string);
		Shader* getShader(std::string);
		Texture* getTexture(std::string);
		Font* getFont(std::string);
		void convertObjModel(std::string);
		void createFont(std::string);
	};
}

#endif // NTERESOURCEMANAGER_H
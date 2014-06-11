#define _CRT_SECURE_NO_DEPRECATE
#include "nteResourceManager.h"
#include "nteError.h"
#include "lodepng.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace nte {
	ResourceManager::ResourceManager(std::string mfName){
		loadManifests(mfName);
	}
	ResourceManager::~ResourceManager(){
		for (int i = 0; i < shaderNames.size(); i++){
			delete shaders[shaderNames.at(i)];
		}
		for (int i = 0; i < modelNames.size(); i++){
			delete models[modelNames.at(i)];
		}
		for (int i = 0; i < textureNames.size(); i++){
			delete textures[textureNames.at(i)];
		}
	}
	int ResourceManager::toInt(std::string s){
		std::stringstream convert(s);
		int i = 0;
		if (!(convert >> i)){
			i = 0;
		}
		return i;
	}
	unsigned int ResourceManager::toUInt(std::string s){
		std::stringstream convert(s);
		unsigned int i = 0;
		if (!(convert >> i)){
			i = 0;
		}
		return i;
	}
	float ResourceManager::toFloat(std::string s){
		std::stringstream convert(s);
		float f = 0;
		if (!(convert >> f)){
			f = 0;
		}
		return f;
	}
	double ResourceManager::toDouble(std::string s){
		std::stringstream convert(s);
		double d = 0;
		if (!(convert >> d)){
			d = 0;
		}
		return d;
	}
	int ResourceManager::indexOf(std::string str1, std::string f){
		std::string::size_type loc = str1.find(f, 0);
		if (loc != std::string::npos) {
			return loc;
		}
		else {
			return -1;
		}
	}
	void ResourceManager::loadShaderManifest(std::string fileName){
		std::string line;
		std::ifstream file(globalPrefix + shaderPrefix + fileName);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (line.length() > 0){
					loadShader(line);
				}
			}
			file.close();
		}
		else {
			std::cout << "Unable to open manifest file";
			handleError(Error::LOAD_FILE, true);
		}
	}
	void ResourceManager::loadModelManifest(std::string fileName){
		std::string line;
		std::ifstream file(globalPrefix + modelPrefix + fileName);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (line.length() > 0){
					loadModel(line);
				}
			}
			file.close();
		}
		else {
			std::cout << "Unable to open manifest file";
			handleError(Error::LOAD_FILE, true);
		}
	}
	void ResourceManager::loadTextureManifest(std::string fileName){
		std::string line;
		std::ifstream file(globalPrefix + texturePrefix + fileName);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (line.length() > 0){
					loadTexture(line);
				}
			}
			file.close();
		}
		else {
			std::cout << "Unable to open manifest file";
			handleError(Error::LOAD_FILE, true);
		}
	}
	void ResourceManager::loadResourceManifest(std::string fileName){
		std::string shadermf;
		std::string modelmf;
		std::string texturemf;
		std::string line;
		std::ifstream file(globalPrefix + fileName);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (indexOf(line, "shaderprefix") == 0){
					shaderPrefix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
				else if (indexOf(line, "modelprefix") == 0){
					modelPrefix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
				else if (indexOf(line, "textureprefix") == 0){
					texturePrefix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
				else if (indexOf(line, "shadermanifest") == 0){
					shadermf = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
				else if (indexOf(line, "modelmanifest") == 0){
					modelmf = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
				else if (indexOf(line, "texturemanifest") == 0){
					texturemf = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
				else if (indexOf(line, "shadersuffix") == 0){
					shaderSuffix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
				else if (indexOf(line, "modelsuffix") == 0){
					modelSuffix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
				else if (indexOf(line, "texturesuffix") == 0){
					textureSuffix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
				else if (indexOf(line, "shadervertexsuffix") == 0){
					vertSuffix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
				else if (indexOf(line, "shaderfragmentsuffix") == 0){
					fragSuffix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
			}
			file.close();
			loadShaderManifest(shadermf);
			loadModelManifest(modelmf);
			loadTextureManifest(texturemf);
		}
		else {
			std::cout << "Unable to open manifest file";
			handleError(Error::LOAD_FILE, true);
		}
	}
	void ResourceManager::loadManifests(std::string fileName){
		std::string resourcemf;
		std::string line;
		std::ifstream file(fileName);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (indexOf(line, "resourceprefix") == 0){
					globalPrefix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
				else if (indexOf(line, "resourcemanifest") == 0){
					resourcemf = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
			}
			file.close();
		}
		else {
			std::cout << "Unable to open resource manifest file";
			handleError(Error::LOAD_FILE, true);
		}
		loadResourceManifest(resourcemf);
	}
	Model* ResourceManager::getModel(std::string fileName){
		return models[fileName];
	}
	Shader* ResourceManager::getShader(std::string fileName){
		return shaders[fileName];
	}
	Texture* ResourceManager::getTexture(std::string fileName){
		return textures[fileName];
	}
	void ResourceManager::removeModel(std::string fileName){
		delete models[fileName];
	}
	void ResourceManager::removeShader(std::string fileName){
		delete shaders[fileName];
	}
	void ResourceManager::removeTexture(std::string fileName){
		delete textures[fileName];
	}
	int ResourceManager::addVert(std::vector<unsigned int>& vertData, unsigned int v, unsigned int n, unsigned int uv){
		for (int i = 0; i < vertData.size(); i += 3){
			if (vertData.at(i) == v && vertData.at(i + 1) == n && vertData.at(i + 2) == uv){
				return i / 3;
			}
		}
		vertData.push_back(v);
		vertData.push_back(n);
		vertData.push_back(uv);
		return (vertData.size() / 3) - 1;
	}
	void ResourceManager::convertObjModel(std::string fileName){
		std::cout << "Converting model file: " << fileName << " (" << (globalPrefix + modelPrefix + fileName + ".obj") << ")..." << std::endl;
		std::string line;
		std::ifstream myfile(globalPrefix + modelPrefix + fileName + ".obj");
		if (myfile.is_open())
		{
			std::vector<float> rawverts;
			std::vector<float> rawnormals;
			std::vector<float> rawUVs;
			std::vector<unsigned int> rawfaces;
			int stage = -1;
			while (getline(myfile, line)) {
				if (line.substr(0, 2) == "vn"){
					if (stage != 2){
						std::cout << rawUVs.size() / 2 << " UVs loaded." << std::endl;
						std::cout << "\tLoading normals...\t";
					}
					stage = 2;
					for (int i = 0; i < 3; i++){
						line = line.substr(indexOf(line, " ") + 1, std::string::npos);
						rawnormals.push_back(toFloat(line.substr(0, indexOf(line, " "))));
					}
					rawnormals.push_back(0);
				}
				else if (line.substr(0, 2) == "vt"){
					if (stage != 1){
						std::cout << rawverts.size() / 4 << " vertices loaded." << std::endl;
						std::cout << "\tLoading UV coords...\t";
					}
					stage = 1;
					for (int i = 0; i < 2; i++){
						line = line.substr(indexOf(line, " ") + 1, std::string::npos);
						rawUVs.push_back(toFloat(line.substr(0, indexOf(line, " "))));
					}
				}
				else if (line.substr(0, 1) == "v"){
					if (stage != 0){
						std::cout << "\tLoading vertices...\t";
					}
					stage = 0;
					for (int i = 0; i < 3; i++){
						line = line.substr(indexOf(line, " ") + 1, std::string::npos);
						rawverts.push_back(toFloat(line.substr(0, indexOf(line, " "))));
					}
					rawverts.push_back(1);
				}
				else if (line.substr(0, 1) == "f"){
					if (stage != 3){
						std::cout << rawnormals.size() / 4 << " normals loaded." << std::endl;
						std::cout << "\tLoading polygons...\t";
					}
					stage = 3;
					while (indexOf(line, " ") != -1){
						line = line.substr(indexOf(line, " ") + 1, std::string::npos);
						unsigned int vertIndex = toUInt(line.substr(0, indexOf(line, "/"))) - 1;
						line = line.substr(indexOf(line, "/") + 1, std::string::npos);
						unsigned int UVIndex = toUInt(line.substr(0, indexOf(line, "/"))) - 1;
						unsigned int normIndex = toUInt(line.substr(indexOf(line, "/") + 1, indexOf(line, " "))) - 1;
						rawfaces.push_back(vertIndex);
						rawfaces.push_back(normIndex);
						rawfaces.push_back(UVIndex);
					}
				}
			}
			std::cout << rawfaces.size() / 9 << " polygons loaded." << std::endl;
			std::cout << "\tProcessing indices...\t";
			std::vector<unsigned int> rawVertexData;
			std::vector<unsigned int> faces;
			std::vector<float> vertexData;
			for (int i = 0; i < rawfaces.size(); i += 3){
				faces.push_back(addVert(rawVertexData, rawfaces.at(i), rawfaces.at(i+1), rawfaces.at(i+2)));
			}
			for (int i = 0; i < rawVertexData.size(); i += 3){
				vertexData.push_back(rawverts.at((rawVertexData.at(i) * 4)));
				vertexData.push_back(rawverts.at((rawVertexData.at(i) * 4) + 1));
				vertexData.push_back(rawverts.at((rawVertexData.at(i) * 4) + 2));
				vertexData.push_back(rawverts.at((rawVertexData.at(i) * 4) + 3));
				vertexData.push_back(rawnormals.at((rawVertexData.at(i + 1) * 4)));
				vertexData.push_back(rawnormals.at((rawVertexData.at(i + 1) * 4) + 1));
				vertexData.push_back(rawnormals.at((rawVertexData.at(i + 1) * 4) + 2));
				vertexData.push_back(rawnormals.at((rawVertexData.at(i + 1) * 4) + 3));
				vertexData.push_back(rawUVs.at((rawVertexData.at(i + 2) * 2)));
				vertexData.push_back(rawUVs.at((rawVertexData.at(i + 2) * 2) + 1));
			}
			std::cout << "Done." << std::endl;
			std::cout << "Done." << std::endl;
			myfile.close();

			FILE *fp = fopen((globalPrefix + modelPrefix + fileName + modelSuffix).c_str(), "wb");

			unsigned int vertslen = vertexData.size();
			fwrite(&vertslen, sizeof(unsigned int), 1, fp);
			fwrite(&vertexData[0], sizeof(float), vertexData.size(), fp);

			unsigned int faceslen = faces.size();
			fwrite(&faceslen, sizeof(unsigned int), 1, fp);
			fwrite(&faces[0], sizeof(unsigned int), faces.size(), fp);

			fclose(fp);
		}
		else {
			std::cout << "Unable to open model file";
			handleError(Error::LOAD_FILE, true);
		}
	}
	void ResourceManager::loadShader(std::string fileName){
		std::cout << "Loading shader: " << fileName << "..." << std::endl;
		std::string line;
		std::string vertString;
		std::ifstream vertFile(globalPrefix + shaderPrefix + fileName + vertSuffix + shaderSuffix);
		std::cout << "\tLoading vertex shader...\t";
		if (vertFile.is_open())
		{
			while (getline(vertFile, line))
			{
				vertString.append(line);
				vertString.append("\n");
			}
			vertFile.close();
			std::cout << "Done." << std::endl;
		}
		else {
			std::cout << "Unable to open vert file";
			handleError(Error::LOAD_FILE, true);
		}
		std::string fragString;
		std::ifstream fragFile(globalPrefix + shaderPrefix + fileName + fragSuffix + shaderSuffix);
		std::cout << "\tLoading fragment shader...\t";
		if (fragFile.is_open())
		{
			while (getline(fragFile, line))
			{
				fragString.append(line);
				fragString.append("\n");
			}
			fragFile.close();
			std::cout << "Done." << std::endl;
		}
		else {
			std::cout << "Unable to open frag file";
			handleError(Error::LOAD_FILE, true);
		}
		std::cout << "Done." << std::endl;
		shaders[fileName] = new Shader(vertString.c_str(), fragString.c_str());
		shaderNames.push_back(fileName);
	}
	void ResourceManager::loadModel(std::string fileName){
		std::cout << "Loading model file: " << fileName << " (" << (globalPrefix + modelPrefix + fileName + modelSuffix) << ")..." << std::endl;
		FILE *fp = fopen((globalPrefix + modelPrefix + fileName + modelSuffix).c_str(), "rb");

		std::cout << "\tLoading vertices...\t";
		unsigned int vertnum;
		fread(&vertnum, sizeof(unsigned int), 1, fp);
		float* verts = new float[vertnum];
		fread(verts, sizeof(float), vertnum, fp);
		std::cout << vertnum / 4 << " vertices loaded." << std::endl;

		std::cout << "\tLoading polygons...\t";
		unsigned int facenum;
		fread(&facenum, sizeof(unsigned int), 1, fp);
		unsigned int* faces = new unsigned int[facenum];
		fread(faces, sizeof(float), facenum, fp);
		std::cout << facenum / 3 << " polygons loaded." << std::endl;

		fclose(fp);
		std::cout << "Done." << std::endl;

		models[fileName] = new Model(verts, vertnum * sizeof(float), 0, 4 * sizeof(float), 8 * sizeof(float), 10 * sizeof(float), faces, facenum * sizeof(unsigned int), facenum);
		modelNames.push_back(fileName);

		delete[] verts;
		delete[] faces;
	}
	void ResourceManager::loadTexture(std::string fileName){
		std::cout << "Loading texture file: " << fileName << " (" << (globalPrefix + texturePrefix + fileName + textureSuffix) << ")..." << std::endl;
		std::cout << "\tLoading pixels...\t";
		std::string fullFileName = (globalPrefix + texturePrefix + fileName + textureSuffix);
			std::vector<unsigned char> image;
			unsigned int width, height;
			unsigned int error = lodepng::decode(image, width, height, &fullFileName[0]);
			if (error)
			{
				std::cout << "error: " << error << ": " << lodepng_error_text(error) << std::endl;
			}
			std::cout << (width * height) << " pixels loaded." << std::endl;
			textures[fileName] = new Texture(&image[0], width, height);
			textureNames.push_back(fileName);
			std::cout << "Done." << std::endl;
	}
}
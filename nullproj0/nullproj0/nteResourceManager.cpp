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
		for (int i = 0; i < fontNames.size(); i++){
			delete textures[fontNames.at(i)];
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
		} else {
			return -1;
		}
	}
	void ResourceManager::loadReadme(std::string fileName){
		std::string line;
		std::ifstream file(globalPrefix + metaPrefix + fileName);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				readme.append(line);
			}
			file.close();
		} else {
			std::cout << "Unable to open readme file";
			handleError(Error::LOAD_FILE, true);
		}
	}
	void ResourceManager::loadVersion(std::string versionFileName, std::string buildFileName){
		std::string prefix;
		int major = -1;
		int minor = -1;
		std::string line;
		std::ifstream vFile(globalPrefix + metaPrefix + versionFileName);
		if (vFile.is_open())
		{
			while (getline(vFile, line))
			{
				if (indexOf(line, "prefix") == 0){
					prefix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "major") == 0){
					major = toInt(line.substr(indexOf(line, "|") + 1, std::string::npos));
				} else if (indexOf(line, "minor") == 0){
					minor = toInt(line.substr(indexOf(line, "|") + 1, std::string::npos));
				}
			}
			vFile.close();
		} else {
			std::cout << "Unable to open version file";
			handleError(Error::LOAD_FILE, true);
		}
		FILE *rfp = fopen((globalPrefix + metaPrefix + buildFileName).c_str(), "rb");
		int bMaj;
		int bMin;
		int build;
		fread(&bMaj, sizeof(int), 1, rfp);
		fread(&bMin, sizeof(int), 1, rfp);
		fread(&build, sizeof(int), 1, rfp);
		fclose(rfp);
		if (bMin != minor || bMaj != major){
			build = 0;
		} else{
			build++;
		}
		FILE *wfp = fopen((globalPrefix + metaPrefix + buildFileName).c_str(), "wb");
		fwrite(&major, sizeof(int), 1, wfp);
		fwrite(&minor, sizeof(int), 1, wfp);
		fwrite(&build, sizeof(int), 1, wfp);
		fclose(wfp);
		std::stringstream versionStream;
		versionStream << prefix << "." << major << "." << minor << "." << build;
		version = versionStream.str();
	}
	void ResourceManager::loadMetaManifest(std::string fileName){
		std::string versionFile;
		std::string readmeFile;
		std::string buildFile;
		std::string line;
		std::ifstream file(globalPrefix + metaPrefix + fileName);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (indexOf(line, "version") == 0){
					versionFile = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "readme") == 0){
					readmeFile = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "build") == 0){
					buildFile = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
			}
			file.close();
			loadReadme(readmeFile);
			loadVersion(versionFile, buildFile);
		} else {
			std::cout << "Unable to open meta manifest file";
			handleError(Error::LOAD_FILE, true);
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
		} else {
			std::cout << "Unable to open shader manifest file";
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
		} else {
			std::cout << "Unable to open model manifest file";
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
		} else {
			std::cout << "Unable to open texture manifest file";
			handleError(Error::LOAD_FILE, true);
		}
	}
	void ResourceManager::loadFontManifest(std::string fileName){
		std::string line;
		std::ifstream file(globalPrefix + fontPrefix + fileName);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (line.length() > 0){
					loadFont(line);
				}
			}
			file.close();
		} else {
			std::cout << "Unable to open font manifest file";
			handleError(Error::LOAD_FILE, true);
		}
	}
	void ResourceManager::loadResourceManifest(std::string fileName){
		std::string metamf;
		std::string shadermf;
		std::string modelmf;
		std::string texturemf;
		std::string fontmf;
		std::string line;
		std::ifstream file(globalPrefix + fileName);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (indexOf(line, "metaprefix") == 0){
					metaPrefix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "shaderprefix") == 0){
					shaderPrefix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "modelprefix") == 0){
					modelPrefix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "textureprefix") == 0){
					texturePrefix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "fontprefix") == 0){
					fontPrefix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "metamanifest") == 0){
					metamf = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "shadermanifest") == 0){
					shadermf = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "modelmanifest") == 0){
					modelmf = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "texturemanifest") == 0){
					texturemf = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "fontmanifest") == 0){
					fontmf = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "shadersuffix") == 0){
					shaderSuffix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "modelsuffix") == 0){
					modelSuffix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "texturesuffix") == 0){
					textureSuffix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "fontsuffix") == 0){
					fontSuffix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "shadervertexsuffix") == 0){
					vertSuffix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				} else if (indexOf(line, "shaderfragmentsuffix") == 0){
					fragSuffix = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
			}
			file.close();
			loadMetaManifest(metamf);
			loadShaderManifest(shadermf);
			loadModelManifest(modelmf);
			loadTextureManifest(texturemf);
			loadFontManifest(fontmf);
		} else {
			std::cout << "Unable to open resource manifest file";
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
				} else if (indexOf(line, "resourcemanifest") == 0){
					resourcemf = line.substr(indexOf(line, "|") + 1, std::string::npos);
				}
			}
			file.close();
		} else {
			std::cout << "Unable to open manifest file";
			handleError(Error::LOAD_FILE, true);
		}
		loadResourceManifest(resourcemf);
	}
	std::string ResourceManager::getVersion(){
		return version;
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
	Font* ResourceManager::getFont(std::string fileName){
		return fonts[fileName];
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
	void ResourceManager::removeFont(std::string fileName){
		delete fonts[fileName];
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
				} else if (line.substr(0, 2) == "vt"){
					if (stage != 1){
						std::cout << rawverts.size() / 4 << " vertices loaded." << std::endl;
						std::cout << "\tLoading UV coords...\t";
					}
					stage = 1;
					for (int i = 0; i < 2; i++){
						line = line.substr(indexOf(line, " ") + 1, std::string::npos);
						rawUVs.push_back(toFloat(line.substr(0, indexOf(line, " "))));
					}
				} else if (line.substr(0, 1) == "v"){
					if (stage != 0){
						std::cout << "\tLoading vertices...\t";
					}
					stage = 0;
					for (int i = 0; i < 3; i++){
						line = line.substr(indexOf(line, " ") + 1, std::string::npos);
						rawverts.push_back(toFloat(line.substr(0, indexOf(line, " "))));
					}
					rawverts.push_back(1);
				} else if (line.substr(0, 1) == "f"){
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
				faces.push_back(addVert(rawVertexData, rawfaces.at(i), rawfaces.at(i + 1), rawfaces.at(i + 2)));
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
		} else {
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
		} else {
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
		} else {
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
	/*
	Font file format:
		initial 4 byte preheader which is the length in bytes of the rest of the file
		divided into sections:
			each section is composed of 4 bytes of the length of the rest of the section
			this int is then followed by data of the specified length
		first section contains general data:
			kerning, space between lines vs characters, etc.  size of the space, tab character, etc.
				first byte is int (used loosely, ints are usually 4 bytes, however this is interpreted into an int during startup) for space between chars horizontally
				second byte is vertical space between lines.
				third is space width in pixels.
				fourth is tab width in pixels
		next section is character order.  this is just a string of all displayable characters in an (arbitrary) order:
			non-displayable character other than tab are displayed as spaces.  tab is displayed as the number of pixels wide as specified above
				EDIT: also newlines are (while not "displayed") used to advance one line and do not display as a space.
		third section is list of positions, widths and heights:
			for each character there is a pos (x and y) in pixels within the "image" as two 4-byte ints
			after the position is two more ints for width then height
		final section is "image":
			first 4 bytes (after the length/header/whatever the hell thing) are width, second 4 are height, remaining are a string of VALUES
			VALUES: these are each one byte and represent a grayscale image/transparency map.
				color is provided by shaders at runtime, this is simply for shape and/or (precalculated) antialiasing
	*/
	void ResourceManager::loadFont(std::string fileName){
		std::cout << "Loading font file: " << fileName << " (" << (globalPrefix + modelPrefix + fileName + modelSuffix) << ")..." << std::endl;
		FILE *fp = fopen((globalPrefix + fontPrefix + fileName + fontSuffix).c_str(), "rb");

		std::cout << "\tLoading header...\t";
		//load stuff...
		std::cout << " done." << std::endl;

		fclose(fp);
		std::cout << "Done." << std::endl;

		fonts[fileName] = new Font();
		fontNames.push_back(fileName);

		//delete stuff
	}
	//default character order:
	//with spaces:
	//		a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 1 2 3 4 5 6 7 8 9 0 ` - = [ ] \ ; ' , . / ~ ! @ # $ % ^ & * ( ) _ + { } | : " < > ?
	//without:
	//		abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`-=[]\;',./~!@#$%^&*()_+{}|:"<>?
	void ResourceManager::createFont(std::string fileName){
		//primary font vars
		int spaceLen = 0;
		int tabLen = 0;
		int kernLen = 0;
		int vertSpace = 0;
		std::vector<unsigned char> glyphOrder;
		//size in number of seperate symbols horizontally
		std::vector<int> glyphSize;

		std::string line;
		std::ifstream myfile(globalPrefix + fontPrefix + fileName + ".txt");
		if (myfile.is_open()) {
			getline(myfile, line);
			spaceLen = toInt(line);
			getline(myfile, line);
			tabLen = toInt(line);
			getline(myfile, line);
			kernLen = toInt(line);
			getline(myfile, line);
			vertSpace = toInt(line);
			getline(myfile, line);
			for (int i = 0; i < line.length(); i++){
				glyphOrder.push_back(line.at(i));
				glyphSize.push_back(1);
			}
			while (getline(myfile, line)){
				glyphSize.at(toInt(line.substr(0, indexOf(line, "|")))) = toInt(line.substr(indexOf(line, "|") + 1, std::string::npos));
			}
		} else {
			std::cout << "error opening font file: " + fileName << std::endl;
		}

		std::string fullTexName = (globalPrefix + fontPrefix + fileName + ".png");
		std::vector<unsigned char> image;
		unsigned int width, height;
		unsigned int error = lodepng::decode(image, width, height, &fullTexName[0]);
		if (error) {
			std::cout << "error: " << error << ": " << lodepng_error_text(error) << std::endl;
		}

		std::vector<unsigned char> grayscale;
		grayscale.resize(image.size() / 4);
		int top = height;
		int bottom = 0;
		int nonEmptyColumns = 0;
		for (int i = 0; i < grayscale.size(); i++){
			grayscale.at(i) = image.at((i * 4) + 3);
		}
		std::vector<bool> isColumnEmpty;
		for (int a = 0; a < width; a++){
			bool empty = true;
			for (int b = 0; b < height; b++){
				unsigned char val = grayscale.at(a + (b * width));
				if (empty && val != 0){
					empty = false;
					nonEmptyColumns++;
				}
				if (b < top && val != 0) {
					top = b;
				}
				if (b > bottom && val != 0) {
					bottom = b;
				}
			}
			isColumnEmpty.push_back(empty);
		}
		char* glyphMap = new char[((bottom + 1) - top) *nonEmptyColumns];
		std::vector<float> glyphs;
		for (int i = 0; i < width; i++){

		}

		/*
		FILE *fp = fopen((globalPrefix + fontPrefix + fileName + ".txt").c_str(), "wb");

		unsigned int vertslen = vertexData.size();
		fwrite(&vertslen, sizeof(unsigned int), 1, fp);
		fwrite(&vertexData[0], sizeof(float), vertexData.size(), fp);

		unsigned int faceslen = faces.size();
		fwrite(&faceslen, sizeof(unsigned int), 1, fp);
		fwrite(&faces[0], sizeof(unsigned int), faces.size(), fp);

		fclose(fp);
		*/
	}
}
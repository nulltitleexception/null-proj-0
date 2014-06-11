#ifndef MORPHEUSGAMEOBJECT_H
#define MORPHEUSGAMEOBJECT_H

#include "MorpheusModel.h"
#include "MorpheusTexture.h"
#include "MorpheusTransform.h"
#include "MorpheusShader.h"

namespace morpheus {
	class GameObject {
	private:
		bool hasModel;
		bool hasTexture;
		bool hasTransform;
		bool modelOnHeap;
		bool textureOnHeap;
		bool transformOnHeap;
		Model* model;
		Texture* texture;
		Transform* transform;
	public:
		GameObject();
		~GameObject();
		void addUniqueModel(Model*);
		void addUniqueTexture(Texture*);
		void addUniqueTransform(Transform*);
		void addModelByReference(Model*);
		void addTextureByReference(Texture*);
		void addTransformByReference(Transform*);
		void removeModel();
		void removeTransform();
		void removeTexture();
		void draw(Shader* s);
		Transform* getTransform(){ return transform; }
	};
}

#endif // MORPHEUSGAMEOBJECT_H
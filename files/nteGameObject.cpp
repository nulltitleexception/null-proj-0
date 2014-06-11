#include "nteGameObject.h"

namespace nte {
	GameObject::GameObject(){
		hasModel = false;
		modelOnHeap = false;
		model = nullptr;
		hasTransform = false;
		transformOnHeap = false;
		transform = nullptr;
		hasTexture = false;
		textureOnHeap = false;
		texture = nullptr;
	}
	GameObject::~GameObject(){
		removeModel();
		removeTransform();
		removeTexture();
		hasModel = false;
		hasTransform = false;
		hasTexture = false;
	}
	void GameObject::addUniqueModel(Model* m){
		removeModel();
		hasModel = true;
		modelOnHeap = true;
		model = m;
	}
	void GameObject::addUniqueTexture(Texture* t){
		removeTexture();
		hasTexture = true;
		textureOnHeap = true;
		texture = t;
	}
	void GameObject::addUniqueTransform(Transform* t){
		removeTransform();
		hasTransform = true;
		transformOnHeap = true;
		transform = t;
	}
	void GameObject::addModelByReference(Model* m){
		removeModel();
		hasModel = true;
		modelOnHeap = false;
		model = m;
	}
	void GameObject::addTextureByReference(Texture* t){
		removeTexture();
		hasTexture = true;
		textureOnHeap = false;
		texture = t;
	}
	void GameObject::addTransformByReference(Transform* t){
		removeTransform();
		hasTransform = true;
		transformOnHeap = false;
		transform = t;
	}
	void GameObject::removeModel(){
		if (hasModel && modelOnHeap){
			delete model;
			modelOnHeap = false;
		}
		hasModel = false;
	}
	void GameObject::removeTexture(){
		if (hasTexture && textureOnHeap){
			delete texture;
			textureOnHeap = false;
		}
		hasTexture = false;
	}
	void GameObject::removeTransform(){
		if (hasTransform && transformOnHeap){
			delete transform;
			transformOnHeap = false;
		}
		hasTransform = false;
  	} 
	 
	void GameObject::draw(Shader* s){
		if (hasModel){
			if (hasTexture){
				texture->bind();
			}
			int modMatPos = glGetUniformLocation(s->getID(), "modelMatrix");
			glUniformMatrix4fv(modMatPos, 1, GL_FALSE, &(transform->getAsMatrix()[0][0]));
			model->draw();
		}
	}
}
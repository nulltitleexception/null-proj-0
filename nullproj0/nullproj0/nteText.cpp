#include "nteText.h"

namespace nte {
	Text::Text(std::string t){
		setText(t);
		setPos(0, 0);
	}
	Text::Text(std::string t, float nX, float nY){
		setText(t);
		setPos(nX, nY);
	}
	Text::~Text(){
		delete model;
	}
	void Text::setText(std::string t){
		modelGenerated = false;
		text = t;
	}
	void Text::setPos(float nX, float nY){
		setX(nX);
		setY(nY);
	}
	void Text::setX(float nX){
		x = nX;
	}
	void Text::setY(float nY){
		y = nY;
	}
	void Text::draw(){
	}
	void Text::generateModel(){
		modelGenerated = true;
	}
}
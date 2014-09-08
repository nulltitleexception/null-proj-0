#ifndef NTETEXT_H
#define NTETEXT_H

#include "nteModel.h"
#include <string>

namespace nte {
	class Text {
	private:
		bool modelGenerated;
		Model* model;
		std::string text;
		float x, y;
	public:
		Text(std::string);
		Text(std::string, float, float);
		~Text();
		void setText(std::string);
		void setPos(float, float);
		void setX(float);
		void setY(float);
		void draw();
		void generateModel();
	};
}

#endif // NTETEXT_H
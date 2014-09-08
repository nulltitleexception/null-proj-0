#ifndef NTEFONT_H
#define NTEFONT_H

#include <string>

namespace nte {
	class Font {
	private:
		int x;
	public:
		Font();
		~Font();
		void draw(std::string, float, float);
	};
}

#endif // NTEFONT_H
#ifndef NTECONFIGURATION_H
#define NTECONFIGURATION_H

namespace nte {
	class Configuration {
	private:
		int width;
		int height;
	public:
		void create(int, int);
	};
}

#endif // NTECONFIGURATION_H
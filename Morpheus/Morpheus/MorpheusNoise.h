#ifndef MORPHEUSNOISE_H
#define MORPHEUSNOISE_H

namespace morpheus {
	namespace noise{
		double smoothCubicNoise(double x, double y, double z, int seed);
		double cubicNoise(double x, double y, double z, int seed);
		double lerpNoise(double x, double y, double z, int seed);
		double scaledNoise(int x, int y, int z, int seed);
		int rawNoise(int x, int y, int z, int seed);
	}
}

#endif // MORPHEUSNOISE_H
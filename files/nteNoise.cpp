#include "nteNoise.h"
#include <iostream>

namespace nte {
	namespace noise{
		int ceil(double n){
			return (int)(n+1);
		}
		int floor(double n){
			return (int)n;
		}
		double lerp(double a, double b, double d){ 
			return a + ((b - a) * d);
		}
		double cubicInterpolate(double v0, double v1, double v2, double v3, double x){
			double P = (v3 - v2) - (v0 - v1);
			double Q = (v0 - v1) - P;
			double R = v2 - v0;
			double S = v1;
			return (P*x*x*x) + (Q*x*x) + (R*x) + S;
		}
		double smoothCubicNoise(double x, double y, double z, int seed){
			double corners = (cubicNoise(x + 1, y + 1, z + 1, seed) + cubicNoise(x - 1, y + 1, z + 1, seed) + cubicNoise(x + 1, y - 1, z + 1, seed) + cubicNoise(x - 1, y - 1, z + 1, seed) + cubicNoise(x + 1, y + 1, z - 1, seed) + cubicNoise(x - 1, y + 1, z - 1, seed) + cubicNoise(x + 1, y - 1, z - 1, seed) + cubicNoise(x - 1, y - 1, z - 1, seed)) / 32;
			double adjacent = (cubicNoise(x + 1, y, z, seed) + cubicNoise(x, y + 1, z, seed) + cubicNoise(x, y, z + 1, seed) + cubicNoise(x - 1, y, z, seed) + cubicNoise(x, y - 1, z, seed) + cubicNoise(x, y, z - 1, seed)) / 24;
			double center = cubicNoise(x, y, z, seed) / 2;
			return corners + adjacent + center;  
		}
		double cubicNoise(double x, double y, double z, int seed){
			double vals[4][4][4];
			for (int a = 0; a < 4; a++){
				for (int b = 0; b < 4; b++){
					for (int c = 0; c < 4; c++){
						vals[a][b][c] = scaledNoise(a + (floor(x) - 1), b + (floor(y) - 1), c + (floor(z) - 1), seed);
					}
				}
			}
			double XYvals[4][4];
			for (int a = 0; a < 4; a++){
				for (int b = 0; b < 4; b++){
					XYvals[a][b] = cubicInterpolate(vals[a][b][0], vals[a][b][1], vals[a][b][2], vals[a][b][3], z - floor(z));
				}
			}
			double Xvals[4];
			for (int a = 0; a < 4; a++){
				Xvals[a] = cubicInterpolate(XYvals[a][0], XYvals[a][1], XYvals[a][2], XYvals[a][3], y - floor(y));
			}
			double val = cubicInterpolate(Xvals[0], Xvals[1], Xvals[2], Xvals[3], x - floor(x));
			return val / 1.4;
		}
		double lerpNoise(double x, double y, double z, int seed){
			return lerp(lerp(lerp(scaledNoise(floor(x), floor(y), floor(z), seed), scaledNoise(floor(x), floor(y), ceil(z), seed), z - floor(z)), lerp(scaledNoise(ceil(x), floor(y), floor(z), seed), scaledNoise(ceil(x), floor(y), ceil(z), seed), z - floor(z)), x - floor(x)), lerp(lerp(scaledNoise(floor(x), ceil(y), floor(z), seed), scaledNoise(floor(x), ceil(y), ceil(z), seed), z - floor(z)), lerp(scaledNoise(ceil(x), ceil(y), floor(z), seed), scaledNoise(ceil(x), ceil(y), ceil(z), seed), z - floor(z)), x - floor(x)), y - floor(y));
		}
		double scaledNoise(int x, int y, int z, int seed){
			return 1.0 - ((double)rawNoise(x, y, z, seed) / 1073741824.0);
		}
		int rawNoise(int x, int y, int z, int seed)
		{
			int n = (1619 * x + 31337 * y + 6971 * z + 1013 * seed) & 0x7fffffff;
			n = (n >> 13) ^ n;
			return (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
		}
	}
}
#ifndef NTEVOXELMAP_H
#define NTEVOXELMAP_H

#include "nteModel.h"
#include <GL/glew.h>

namespace nte {
	struct Voxel {
		int ID;
		float color;
	};
	class VoxelMap {
	private:
		Model* model;
		Voxel* map;
		int* heightmap;
		int xLen, yLen, zLen;
		int pos(int x, int y, int z);
		double lerp(double v1, double v2, double a);
	public:
		VoxelMap(int xl, int yl, int zl);
		~VoxelMap();
		double getHeightAt(double x, double z);
		void generateTerrain();
		void generateHeightmap();
		Voxel* getVoxel(int x, int y, int z); 
		int getWidth();
		int getHeight();
		int getDepth();
		void generateModel();
		void deleteModel();
		void draw();
	};
}

#endif // NTEVOXELMAP_H
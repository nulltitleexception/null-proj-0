#ifndef NTEVOXELMAP_H
#define NTEVOXELMAP_H

#include <GL/glew.h>

namespace nte {
	struct Voxel {
		int ID;
		float color;
	};
	class VoxelMap {
	private:
		GLuint VAO, VBO, IBO;//vertex array, vertex buffer, normal buffer, texture buffer, and index buffer objects
		int drawSize;
		Voxel* map;
		int* heightmap;
		int xLen, yLen, zLen;
		int pos(int x, int y, int z);
	public:
		VoxelMap(int xl, int yl, int zl);
		~VoxelMap();
		void generateTerrain();
		Voxel* getVoxel(int x, int y, int z); 
		int getWidth();
		int getHeight();
		int getDepth();
		void generateBuffers();
		void deleteBuffers();
		void draw();
	};
}

#endif // NTEVOXELMAP_H
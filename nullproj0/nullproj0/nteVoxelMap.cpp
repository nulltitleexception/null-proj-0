#include "nteVoxelMap.h"
#include "nteNoise.h"
#include "nteError.h"
#include <vector>
#include <iostream>

#define SEA_LEVEL (yLen / 2)
#define GROUND_VARIATION (yLen / 4)

namespace nte {
	VoxelMap::VoxelMap(int xl, int yl, int zl){
		xLen = xl;
		yLen = yl;
		zLen = zl;
		map = new Voxel[xLen * yLen * zLen];
		heightmap = new int[xLen * zLen];
	}
	VoxelMap::~VoxelMap(){
		delete[] map;
		delete[] heightmap;
		deleteModel();
	}
	int VoxelMap::pos(int x, int y, int z){
		return x + (y * xLen) + (z * xLen * yLen);
	}
	void VoxelMap::generateTerrain(){
		int seed = 125;
		for (int a = 0; a < xLen; a++){
			for (int c = 0; c < zLen; c++){
				int h = (nte::noise::cubicNoise(a / 30.0, c / 30.0, 0, seed) * GROUND_VARIATION) + SEA_LEVEL;
				for (int b = 0; b < yLen; b++){
					if (b <= h){
						map[pos(a, b, c)].ID = 1;
					} else{
						map[pos(a, b, c)].ID = 0;
					}
				}
			}
		}
	}
	void VoxelMap::generateHeightmap(){
		for (int a = 0; a < xLen; a++){
			for (int c = 0; c < zLen; c++){
				for (int b = 0; b < yLen; b++){
					if (map[pos(a, b, c)].ID != 0) {
						heightmap[pos(a, c, 0)] = b;
						//heightmap[pos(a, c, 0)] = SEA_LEVEL;
					}
				}
			}
		}
	}
	Voxel* VoxelMap::getVoxel(int x, int y, int z){
		return &map[pos(x, y, z)];
	}
	int VoxelMap::getWidth(){
		return xLen;
	}
	int VoxelMap::getHeight(){
		return yLen;
	}
	int VoxelMap::getDepth(){
		return zLen;
	}
	void VoxelMap::generateModel(){
		std::vector<float> verts;
		for (int a = 0; a < xLen; a++){
			for (int b = 0; b < zLen; b++){
				verts.push_back((((float)a) / xLen) - 0.5);
				verts.push_back((((float)heightmap[pos(a, b, 0)]) / yLen) - 0.5);
				verts.push_back((((float)b) / zLen) - 0.5);
				verts.push_back(1);
			}
		}
		std::vector<unsigned int> indices;
		for (int a = 0; a < xLen - 1; a++){
			for (int b = 0; b < zLen - 1; b++){
				indices.push_back(pos(a, b + 1, 0));
				indices.push_back(pos(a, b, 0));
				indices.push_back(pos(a + 1, b, 0));
				indices.push_back(pos(a, b + 1, 0));
				indices.push_back(pos(a + 1, b, 0));
				indices.push_back(pos(a + 1, b + 1, 0));
			}
		}
		model = new Model(&verts[0], verts.size() * sizeof(float), 0, 0, 0, 4 * sizeof(float), &indices[0], indices.size() * sizeof(unsigned int), indices.size());
	}
	void VoxelMap::deleteModel(){
		delete model;
	}
	void VoxelMap::draw(){
		model->draw();
	}
}
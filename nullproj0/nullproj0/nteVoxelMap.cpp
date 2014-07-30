#include "nteVoxelMap.h"
#include "nteNoise.h"
#include "nteError.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#define SEA_LEVEL (yLen / 2)
#define GROUND_VARIATION (yLen / 40)

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
	double VoxelMap::lerp(double v1, double v2, double a){
		return v1 + (a * (v2 - v1));
	}
	double VoxelMap::getHeightAt(double x, double z){
		double hX1 = lerp(heightmap[pos((int)x, (int)z, 0)], heightmap[pos(((int)x) + 1, (int)z, 0)], x - ((int)x));
		double hX2 = lerp(heightmap[pos((int)x, ((int)z) + 1, 0)], heightmap[pos(((int)x) + 1, ((int)z) + 1, 0)], x - ((int)x));
		double hY = lerp(hX1, hX2, z - ((int)z));
		return hY;
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
		float* verts = new float[xLen * zLen * 10];
		for (int a = 0; a < xLen; a++){
			for (int b = 0; b < zLen; b++){
				verts[pos(a, b, 0) * 10] = a - (xLen / 2);
				verts[(pos(a, b, 0) * 10) + 1] = heightmap[pos(a, b, 0)] - SEA_LEVEL;
				verts[(pos(a, b, 0) * 10) + 2] = b - (zLen / 2);
				verts[(pos(a, b, 0) * 10) + 3] = 1;
			}
		}
		for (int a = 0; a < xLen; a++){
			for (int b = 0; b < zLen; b++){
				//if (a == 0 && b == 0){
				if (a < xLen - 1 && b < zLen - 1){
					glm::vec3 v1 = glm::vec3(0, 0, 0);
					v1.x = verts[(pos(a, b, 0) * 10)] - verts[pos(a + 1, b, 0) * 10];
					v1.y = verts[(pos(a, b, 0) * 10) + 1] - verts[(pos(a + 1, b, 0) * 10) + 1];
					v1.z = verts[(pos(a, b, 0) * 10) + 2] - verts[(pos(a + 1, b, 0) * 10) + 2];
					glm::vec3 v2 = glm::vec3(0, 0, 0);
					v2.x = verts[pos(a, b + 1, 0) * 10] - verts[pos(a, b, 0) * 10];
					v2.y = verts[(pos(a, b + 1, 0) * 10) + 1] - verts[(pos(a, b, 0) * 10) + 1];
					v2.z = verts[(pos(a, b + 1, 0) * 10) + 2] - verts[(pos(a, b, 0) * 10) + 2];
					glm::vec3 cross = glm::cross(v1,v2);
					cross = glm::normalize(cross);
					verts[(pos(a, b, 0) * 10) + 4] = cross.x;
					verts[(pos(a, b, 0) * 10) + 5] = cross.y;
					verts[(pos(a, b, 0) * 10) + 6] = cross.z;
					verts[(pos(a, b, 0) * 10) + 7] = 1;
					//std::cout << cross.x << ", " << cross.y << ", " << cross.z << ", " << std::endl;
				}
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
		model = new Model(verts, xLen * zLen * 10 * sizeof(float), 0, 0 * sizeof(float), 0 * sizeof(float), 10 * sizeof(float), &indices[0], indices.size() * sizeof(unsigned int), indices.size());
	}
	void VoxelMap::deleteModel(){
		delete model;
	}
	void VoxelMap::draw(){
		model->draw();
	}
}
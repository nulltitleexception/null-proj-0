#include "nteVoxelMap.h"
#include "nteError.h"

namespace nte {
	int VoxelMap::pos(int x, int y, int z){
		return x + (y * xLen) + (z * xLen * yLen);
	}
	VoxelMap::VoxelMap(int xl, int yl, int zl){
		map = new Voxel[xl * yl * zl];
	}
	VoxelMap::~VoxelMap(){
		delete[] map;
		deleteBuffers();
	}
	void VoxelMap::generateTerrain(){
		for (int a = 0; a < xLen; a++){
			for (int b = 0; b < yLen; b++){
				for (int c = 0; c < zLen; c++){
					map[pos(a, b, c)].ID = 0;
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
	void VoxelMap::generateBuffers(){
		/*drawSize = size;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertlen, verts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)vertOffset);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)normOffset);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)UVOffset);
		glEnableVertexAttribArray(2);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indlen, indices, GL_STATIC_DRAW);

		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		nte::handleError(nte::Error::GL_CREATE_VBO, true);*/
	}
	void VoxelMap::deleteBuffers(){
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &VBO);

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &IBO);

		nte::handleError(nte::Error::GL_DESTROY_VBO, true);
	}
	void VoxelMap::draw(){
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);
		//glEnableVertexAttribArray(2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, drawSize, GL_UNSIGNED_INT, 0);
		//glDisableVertexAttribArray(2);
		//glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

	}
}
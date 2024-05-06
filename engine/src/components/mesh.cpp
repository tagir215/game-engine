#include "engine/components/mesh.h"


void StaticMesh::setColor(float r, float g, float b, float w){
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = w;
}

void StaticMesh::initVertexArrays()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &positionsVbo);
	glGenBuffers(1, &textureVbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, positionsVbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices[0])*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords[0])*texCoords.size(), texCoords.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void StaticMesh::updateTextureBuffer(std::vector<float> coords){
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(coords[0])*coords.size(), coords.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


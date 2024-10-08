#pragma once

class Cube
{
private:
	float vertexPositions[24] = {
			-1.0f,  1.0f, -1.0f, // 0: Front-top-left
			-1.0f, -1.0f, -1.0f, // 1: Front-bottom-left
			 1.0f, -1.0f, -1.0f, // 2: Front-bottom-right
			 1.0f,  1.0f, -1.0f, // 3: Front-top-right
			-1.0f,  1.0f,  1.0f, // 4: Back-top-left
			-1.0f, -1.0f,  1.0f, // 5: Back-bottom-left
			 1.0f, -1.0f,  1.0f, // 6: Back-bottom-right
			 1.0f,  1.0f,  1.0f
	};

	float indices[36] = {
		// Front face
		0, 1, 2, 0, 2, 3,
		// Back face
		4, 5, 6, 4, 6, 7,
		// Left face
		4, 5, 1, 4, 1, 0,
		// Right face
		3, 2, 6, 3, 6, 7,
		// Top face
		4, 0, 3, 4, 3, 7,
		// Bottom face
		1, 5, 6, 1, 6, 2
	};

	float pyramidPositions[54] = { 
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,    //front
		1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,    //right
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  //back
		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  //left
		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, //LF
		1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f  //RR
	};
public:
	const float* GetCubeVertices() const { return vertexPositions; };
	const float* GetCubeIndices() const { return indices; };

	const float* GetPyramidData() const { return pyramidPositions; };
};
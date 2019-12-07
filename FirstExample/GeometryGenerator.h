#pragma once
#include "glm\glm.hpp"
#include "vgl.h"
#include <iostream>
#include <vector>
using namespace std;

enum ShapeType
{
	Cube = 0,
	Plane,
	Wedge,
	Pyrmaind,
	Pentagon,
	Hexagon,
	Diamond,
	Disc,
	Cone,
	Cylinder
};

//struct Shape
//{
//	Shape() {}
//	Shape(GLuint vao, int numIndicices, int numVertices)
//	{
//		this->vao = vao;
//		this->numIndicies = numIndicices;
//		this->numVertices = numVertices;
//	}
//	
//	GLuint vao;
//	int numIndicies, numVertices;
//};

//class GeometryGenerator
//{
//public:
//	GeometryGenerator() {}
//
//	~GeometryGenerator() {}
//
//	Shape& MakeShape(ShapeType type, glm::vec3 colour)
//	{
//		// Create the info based off what shape needs to be made
//		switch (type)
//		{
//		case Cube:
//			numIndicies = 36;
//			numVertices = 24;
//
//			indices = new GLshort[numIndicies]
//			{
//				// Front Face.
//				1, 0, 3,
//				3, 2, 1,
//				// Left Face.
//				6, 5, 4,
//				4, 7, 6,
//				// Bottom Face.
//				8, 9, 10,
//				10, 11, 8,
//				// Right Face.
//				15, 12, 13,
//				13, 14, 15,
//				// Back Face.
//				16, 17, 18,
//				18, 19, 16,
//				// Top Face.
//				20, 21, 22,
//				22, 23, 20
//			};
//			vertices = new GLfloat[numVertices * 3]
//			{
//				// Front Face
//				-0.65f, -0.65f,  0.65f,		// 0(0).
//				 0.65f, -0.65f,  0.65f,		// 1(1).
//				 0.65f,  0.65f,  0.65f,		// 2(2).
//				-0.65f,  0.65f,  0.65f,		// 3(3).
//
//				// Left Face				  
//				-0.65f, -0.65f,  0.65f,		// 4
//				-0.65f,  0.65f,  0.65f,		// 5
//				-0.65f,  0.65f, -0.65f,		// 6
//				-0.65f, -0.65f, -0.65f,		// 7
//
//				// Bottom Face				   
//				-0.65f, -0.65f, -0.65f,		// 8
//				-0.65f, -0.65f,  0.65f,		// 9
//				 0.65f, -0.65f,  0.65f,		// 10
//				 0.65f, -0.65f, -0.65f,		// 11
//
//				// Right Face				 
//				0.65f, -0.65f, -0.65f,		// 12
//				0.65f, -0.65f,  0.65f,		// 13
//				0.65f,  0.65f,  0.65f,		// 14
//				0.65f,  0.65f, -0.65f,		// 15
//
//				// Back Face				   
//				-0.65f, -0.65f, -0.65f, 	// 16(4).
//				 0.65f, -0.65f, -0.65f,		// 17(5).
//				 0.65f,  0.65f, -0.65f,		// 18(6).
//				-0.65f,  0.65f, -0.65f,		// 19(7).
//
//				// Top Face
//				-0.65f,  0.65f, -0.65f,		// 20
//				 0.65f,  0.65f, -0.65f,		// 21
//				 0.65f,  0.65f,  0.65f,		// 22
//				-0.65f,  0.65f,  0.65f,		// 23
//			};
//			uvs = new GLfloat[numVertices * 2]
//			{
//				// Front Face
//				0.0f, 1.0f,
//				0.0f, 0.0f,
//				1.0f, 0.0f,
//				1.0f, 1.0f,
//				
//				// Left Face
//				0.0f, 1.0f,
//				0.0f, 0.0f,
//				1.0f, 0.0f,
//				1.0f, 1.0f,
//				
//				// Bottom Face
//				0.0f, 1.0f,
//				0.0f, 0.0f,
//				1.0f, 0.0f,
//				1.0f, 1.0f,
//				
//				// Right Face
//				0.0f, 1.0f,
//				0.0f, 0.0f,
//				1.0f, 0.0f,
//				1.0f, 1.0f,
//				
//				// Back Face
//				0.0f, 1.0f,
//				0.0f, 0.0f,
//				1.0f, 0.0f,
//				1.0f, 1.0f,
//				
//				// Top Face
//				0.0f, 1.0f,
//				0.0f, 0.0f,
//				1.0f, 0.0f,
//				1.0f, 1.0f,
//			};
//			normals = new GLfloat[numVertices * 3];
//			break;
//		case Wedge:
//			break;
//		case Pyrmaind:
//			break;
//		default:
//			break;
//		}
//
//		// Do the colours
//		colours = new GLfloat[numVertices * 3];
//		for (int i = 0; i < numVertices * 3; i += 3)
//		{
//			colours[i] = colour.x;
//			colours[i + 1] = colour.y;
//			colours[i + 2] = colour.z;
//		}
//
//		// Get the normals
//		calcAverageNormals(indices, numIndicies, vertices,
//			numVertices, 3, normals);
//		
//		vao = 0;
//		glGenVertexArrays(1, &vao);
//		glBindVertexArray(vao);
//
//		// Setting up the index array
//		glGenBuffers(1, &ibo);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//		// Setting up the vertex points
//		points_vbo = 0;
//		glGenBuffers(1, &points_vbo);
//		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//		glEnableVertexAttribArray(0);
//
//		// Then we do the colours
//		colours_vbo = 0;
//		glGenBuffers(1, &colours_vbo);
//		glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//		glEnableVertexAttribArray(1);
//
//		// Now for the UV/ST values.
//		tex_vbo = 0;
//		glGenBuffers(1, &tex_vbo);
//		glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(2);
//
//		// Now for the normal values.
//		normal_vbo = 0;
//		glGenBuffers(1, &normal_vbo);
//		glBindBuffer(GL_ARRAY_BUFFER, normal_vbo);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
//		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(3);
//
//		glBindBuffer(GL_ARRAY_BUFFER, 0); // Can optionally unbind the buffer to avoid modification.
//
//
//		glBindVertexArray(0); // Can optionally unbind the vertex array to avoid modification.
//
//		// Now erase the leftover data
//		delete[] vertices, colours, uvs, normals, indices;
//		vertices = colours = uvs = normals = NULL;
//		indices = NULL;
//
//		// Create and return the new shape
//		return Shape(vao, numIndicies, numVertices);
//	}
//
//private:
//	GLuint vao, ibo, points_vbo, colours_vbo, tex_vbo, normal_vbo;
//	GLfloat* vertices, * colours, * uvs, * normals;
//	GLshort* indices;
//	int numIndicies, numVertices;
//
//	void calcAverageNormals(GLshort* indices, unsigned int indiceCount, GLfloat* vertices,
//		unsigned int verticeCount, unsigned int vLength, GLfloat* normals)
//	{
//		for (unsigned int i = 0; i < indiceCount; i += 3)
//		{
//			// Calculate the normals of each triangle first
//			unsigned int in0 = indices[i] * vLength;
//			unsigned int in1 = indices[i + 1] * vLength;
//			unsigned int in2 = indices[i + 2] * vLength;
//			glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
//			glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
//			glm::vec3 normal = glm::cross(v2, v1);
//			normal = glm::normalize(normal);
//
//			// Then store the normal values inside the normal array
//			normals[in0] += normal.x; normals[in0 + 1] += normal.y; normals[in0 + 2] += normal.z;
//			normals[in1] += normal.x; normals[in1 + 1] += normal.y; normals[in1 + 2] += normal.z;
//			normals[in2] += normal.x; normals[in2 + 1] += normal.y; normals[in2 + 2] += normal.z;
//		}
//
//		// Normalize each of the new normal vectors.
//		for (unsigned int i = 0; i < verticeCount / vLength; i++)
//		{
//			unsigned int nOffset = i * vLength;
//			glm::vec3 vec(normals[nOffset], normals[nOffset + 1], normals[nOffset + 2]);
//			vec = glm::normalize(vec);
//			normals[nOffset] = vec.x; normals[nOffset + 1] = vec.y; normals[nOffset + 2] = vec.z;
//		}
//	}
//
//};

class Shape
{
private:
	int arraySize, numIndices;
	GLuint vao, ibo, points_vbo, colours_vbo, uv_vbo, normals_vbo;
	vector<GLshort> indices;
	vector<GLfloat> vertices, colours, uvs, normals;
	glm::vec3 vertColour;

public:
	Shape(int size = 0, int indices = 0, glm::vec3& col = glm::vec3(0, 0, 0)) 
		: arraySize(size), numIndices(indices), vertColour(col)
	{
		setColours();
	}
	~Shape()
	{
		indices.clear();
		vertices.clear();
		normals.clear();
		colours.clear();
	}
	void setColours()
	{
		for (int i = 0; i < arraySize; i++)
		{
			colours.reserve(arraySize);
			colours.push_back(vertColour.x);
			colours.push_back(vertColour.y);
			colours.push_back(vertColour.z);
		}
	}
	void bindShape()
	{
		vao = 0;
				glGenVertexArrays(1, &vao);
				glBindVertexArray(vao);
		
				// Setting up the index array
				glGenBuffers(1, &ibo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numIndices, &indices.front(), GL_STATIC_DRAW);
		
				// Setting up the vertex points
				points_vbo = 0;
				glGenBuffers(1, &points_vbo);
				glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * arraySize, &vertices.front(), GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(0);
		
				// Then we do the colours
				colours_vbo = 0;
				glGenBuffers(1, &colours_vbo);
				glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
				glBufferData(GL_ARRAY_BUFFER, sizeof(colours[0]) * arraySize, &colours.front(), GL_STATIC_DRAW);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(1);
		
				// Now for the UV/ST values.
				uv_vbo = 0;
				glGenBuffers(1, &uv_vbo);
				glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
				glBufferData(GL_ARRAY_BUFFER, sizeof(uvs[0]) * (uvs.size()), &uvs.front(), GL_STATIC_DRAW);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(2);
		
				// Now for the normal values.
				normals_vbo = 0;
				glGenBuffers(1, &normals_vbo);
				glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
				glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * arraySize, &normals.front(), GL_STATIC_DRAW);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(3);
		
				glBindBuffer(GL_ARRAY_BUFFER, 0); // Can optionally unbind the buffer to avoid modification.
				glBindVertexArray(0); // Can optionally unbind the vertex array to avoid modification.
	}

	GLuint& getVao() { return vao; }
	int& getIndices() { return numIndices; }
	friend class GeometryGenrator;
};

class GeometryGenrator
{
private:
	vector<Shape> shapes;

	void calcAverageNormals(vector<GLshort>& indices, unsigned int indiceCount, vector<GLfloat>& vertices,
				unsigned int verticeCount, unsigned int vLength, vector<GLfloat>& normals)
	{
				for (unsigned int i = 0; i < indiceCount; i += 3)
				{
					// Calculate the normals of each triangle first
					unsigned int in0 = indices[i] * vLength;
					unsigned int in1 = indices[i + 1] * vLength;
					unsigned int in2 = indices[i + 2] * vLength;
					glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
					glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
					glm::vec3 normal = glm::cross(v1, v2);
					normal = glm::normalize(normal);
		
					// Then store the normal values inside the normal array
					normals[in0] += normal.x; normals[in0 + 1] += normal.y; normals[in0 + 2] += normal.z;
					normals[in1] += normal.x; normals[in1 + 1] += normal.y; normals[in1 + 2] += normal.z;
					normals[in2] += normal.x; normals[in2 + 1] += normal.y; normals[in2 + 2] += normal.z;
				}
		
				// Normalize each of the new normal vectors.
				for (unsigned int i = 0; i < verticeCount / vLength; i++)
				{
					unsigned int nOffset = i * vLength;
					glm::vec3 vec(normals[nOffset], normals[nOffset + 1], normals[nOffset + 2]);
					vec = glm::normalize(vec);
					normals[nOffset] = vec.x; normals[nOffset + 1] = vec.y; normals[nOffset + 2] = vec.z;
				}
	}
public:
	GeometryGenrator() {}
	~GeometryGenrator()
	{
		shapes.clear();
	}
	void GenrateShape(ShapeType type, glm::vec3 col)
	{
		int arraySize = 0;
		int numVertices = 0;
		int indices = 0;
		switch (type)
		{
		case Cube:
			arraySize = 72;
			numVertices = 24;
			indices = 36;
			shapes.push_back(Shape(arraySize, indices, col));
			// Adding in the long code
			shapes.back().vertices = {
				// Front Face
				-0.65f, -0.65f,  0.65f,		// 0(0).
				 0.65f, -0.65f,  0.65f,		// 1(1).
				 0.65f,  0.65f,  0.65f,		// 2(2).
				-0.65f,  0.65f,  0.65f,		// 3(3).

				// Left Face				  
				-0.65f, -0.65f,  0.65f,		// 4
				-0.65f,  0.65f,  0.65f,		// 5
				-0.65f,  0.65f, -0.65f,		// 6
				-0.65f, -0.65f, -0.65f,		// 7

				// Bottom Face				   
				-0.65f, -0.65f, -0.65f,		// 8
				-0.65f, -0.65f,  0.65f,		// 9
				 0.65f, -0.65f,  0.65f,		// 10
				 0.65f, -0.65f, -0.65f,		// 11

				// Right Face				 
				0.65f, -0.65f, -0.65f,		// 12
				0.65f, -0.65f,  0.65f,		// 13
				0.65f,  0.65f,  0.65f,		// 14
				0.65f,  0.65f, -0.65f,		// 15

				// Back Face				   
				-0.65f, -0.65f, -0.65f, 	// 16(4).
				 0.65f, -0.65f, -0.65f,		// 17(5).
				 0.65f,  0.65f, -0.65f,		// 18(6).
				-0.65f,  0.65f, -0.65f,		// 19(7).

				// Top Face
				-0.65f,  0.65f, -0.65f,		// 20
				 0.65f,  0.65f, -0.65f,		// 21
				 0.65f,  0.65f,  0.65f,		// 22
				-0.65f,  0.65f,  0.65f,		// 23
			};
			shapes.back().indices = {
				// Front Face.
				1, 0, 3,
				3, 2, 1,
				// Left Face.
				6, 5, 4,
				4, 7, 6,
				// Bottom Face.
				8, 9, 10,
				10, 11, 8,
				// Right Face.
				15, 12, 13,
				13, 14, 15,
				// Back Face.
				16, 17, 18,
				18, 19, 16,
				// Top Face.
				20, 21, 22,
				22, 23, 20
			};
			shapes.back().uvs = {
				// Front Face
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				
				// Left Face
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				
				// Bottom Face
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				
				// Right Face
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				
				// Back Face
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				
				// Top Face
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
			};
			break;
		case Plane:
			arraySize = 12;
			numVertices = 4;
			indices = 6;
			shapes.push_back(Shape(arraySize, indices, col));
			shapes.back().vertices = {
				0.5f, 0.0f,  0.5f, // 0
			   -0.5f, 0.0f,  0.5f, // 1
			   -0.5f, 0.0f, -0.5f, // 2
			    0.5f, 0.0f, -0.5f, // 3
			};
			shapes.back().indices = {
				0, 1, 2,
				2, 3, 0,
			};
			shapes.back().uvs = {
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
			};
			break;
		case Wedge:
			arraySize = 18;
			numVertices = 6;
			indices = 24;
			shapes.push_back(Shape(arraySize, indices, col));
			shapes.back().vertices = {
				// Front
				0.5f, 0.5f, 0.5f,	// 0
				0.5f, -0.5f, 0.5f,	// 1
				-0.5f, -0.5f, 0.5f, // 2

				// Back
				0.5f, 0.5f, -0.5f,   // 3
				0.5f, -0.5f, -0.5f,  // 4
				-0.5f, -0.5f, -0.5f, // 5
			};
			shapes.back().indices = {
				// Front
				0, 1, 2,

				// Faces
				0, 3, 4,
				4, 1, 0,

				1, 4, 5,
				5, 2, 1,

				0, 2, 5,
				5, 3, 0,

				// Back
				3, 5, 4,
			};
			shapes.back().uvs = {
				// Front
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 0.0f,

				// Back
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 0.0f,
			};
			break;
		case Pyrmaind:
			arraySize = 15;
			numVertices = 5;
			indices = 18;
			shapes.push_back(Shape(arraySize, indices, col));
			shapes.back().vertices = {
				0.5f, -0.5f,  0.5f, // 0
			   -0.5f, -0.5f,  0.5f, // 1
			   -0.5f, -0.5f, -0.5f, // 2
				0.5f, -0.5f, -0.5f, // 3
				0.0f,  0.5f,  0.0f, // 4
			};
			shapes.back().indices = {
				// Bottom
				2, 1, 0,
				0, 3, 2,
				// Sides
				0, 1, 4,
				1, 2, 4, 
				2, 3, 4,
				3, 0, 4,
			};
			shapes.back().uvs = {
				0.0f, 0.5f,
				0.0f, 0.0f,
				0.5f, 0.0f,
				0.5f, 0.5f,
				1.0f, 1.0f,
			};
			break;
		case Pentagon:
			arraySize = 36;
			numVertices = 12;
			indices = 60;
			shapes.push_back(Shape(arraySize, indices, col));
			shapes.back().vertices = {
				 0.0f, 0.0f, 0.5f,    // 0

				 0.95f, 0.31f, 0.5f,  // 1
				 0.0f, 1.0f, 0.5f,    // 2
				-0.95f, 0.31f, 0.5f,  // 3
				-0.59f, -0.81f, 0.5f, // 4
				 0.59f, -0.81f, 0.5f, // 5

				 0.0f, 0.0f, -0.5f,   // 6

				 0.75f, 0.31f, -0.5f, // 7
				 0.0f, 1.0f, -0.5f,   // 8
				-0.95f, 0.31f, -0.5f, // 9
				-0.59f, -0.81f, -0.5f, // 10
				0.59f, -0.81f, -0.5f,  // 11
			};
			shapes.back().indices = {
				// Top
				2, 1, 0,
				2, 0, 3,
				3, 0, 4,
				4, 0, 5,
				5, 0, 1,

				// Sides
				8, 7, 1,
				8, 1, 2,

				9, 8, 2,
				9, 2, 3,

				10, 9, 3,
				10, 3, 4,

				11, 10, 4,
				11, 4, 5,

				5, 1, 11,
				11, 1, 7,

				// Bottom
				8, 6, 7,
				9, 6, 8,
				10, 6, 9,
				11, 6, 10,
				7, 6, 11,
			};
			shapes.back().uvs = {
				0.5f, 0.5f,

				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,

				0.5f, 0.5f,

				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
			};
			break;
		case Hexagon:
			arraySize = 42;
			numVertices = 14;
			indices = 72;
			shapes.push_back(Shape(arraySize, indices, col));
			shapes.back().vertices = {
				// Front
				 0.0f, 0.0f, 0.5f,		  // 0

				 1.0f, 0.0f, 0.5f,		  // 1
				 0.5f, 0.86f, 0.5f,	      // 2
				-0.5f, 0.86f, 0.5f,	      // 3
				-1.0f, 0.0f, 0.5f,		  // 4
				-0.5f, -0.86f, 0.5f,	  // 5
				 0.5f, -0.86f, 0.5f,	  // 6

				// Back
				 0.0f, 0.0f, -0.5f,		  // 7

				 1.0f, 0.0f, -0.5f,      // 8
				 0.5f, 0.86f, -0.5f,	  // 9
				-0.5f, 0.86f, -0.5f,	  // 10
				-1.0f, 0.0f, -0.5f,	  // 11
				-0.5f, -0.86f, -0.5f,	  // 12
				 0.5f, -0.86f, -0.5f	  // 13
			};
			shapes.back().indices = {
				// Front triangles
				2, 1, 0,
				2, 0, 3,
				3, 0, 4,
				4, 0, 5,
				5, 0, 6,
				6, 0, 1,

				// Sides triangles
				2, 8, 1,
				9, 8, 2,

				9, 2, 3,
				10, 9, 3,

				10, 3, 4,
				11, 10, 4,

				11, 4, 5,
				12, 11, 5,

				12, 5, 6,
				13, 12, 6,

				13, 6, 1,
				8, 13, 1,

				// Back Triangles
				9, 7, 8,
				10, 7, 9,
				11, 7, 10,
				12, 7, 11,
				13, 7, 12,
				8, 7, 13
			};
			shapes.back().uvs = {
				0.5f, 0.5f,

				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,

				0.5f, 0.5f,

				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
			};
			break;
		case Diamond:
			arraySize = 24;
			numVertices = 8;
			indices = 36;
			shapes.push_back(Shape(arraySize, indices, col));
			shapes.back().vertices = {
			1.0f, 0.0f,  0.0f,	// 0
			0.5f, 0.0f, -0.866f, // 1
		   -0.5f, 0.0f, -0.866f, // 2
		   -1.0f, 0.0f,  0.0f,  // 3
		   -0.5f, 0.0f,  0.866f, // 4
			0.5f, 0.0f,  0.866f, // 5

			// Top Point
			0.0f, 1.0f, 0.0f,  // 6
			// Bottom Point
			0.0f, -1.0f, 0.0f // 7
			};
			shapes.back().indices = {
				// Top triangles
				0, 6, 1,
				1, 6, 2,
				2, 6, 3,
				3, 6, 4,
				4, 6, 5,
				5, 6, 0,

				// Bottom triangles
				1, 7, 0,
				2, 7, 1,
				3, 7, 2,
				4, 7, 3,
				5, 7, 4,
				0, 7, 5,
			};
			shapes.back().uvs = {
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,
				0.25f, 0.25f,

				0.75f, 0.75f,
				0.75f, 0.75f,

			};
			break;
		case Disc:
			arraySize = 75;
			numVertices = 25;
			indices = 72;
			shapes.push_back(Shape(arraySize, indices, col));
			shapes.back().vertices = {
				
				// Center
				0.0f, 0.0f, 0.0f, // 0
				// Quad 1
				1.0f, 0.0f, 0.0f, // 1
				0.97f, 0.0f, -0.26f, // 2
				0.87f, 0.0f, -0.5f, // 3
				0.71f, 0.0f,  -0.71f, // 4
				0.5f, 0.0f, -0.87f, // 5
				0.26f, 0.0f, -0.97f, // 6

				// Quad 2
				0.0f, 0.0f, -1.0f, // 7
				-0.26f, 0.0f, -0.97f, // 8
				-0.5f, 0.0f, -0.87f, // 9
				-0.71f, 0.0f,  -0.71f, // 10
				-0.87f, 0.0f, -0.5f, // 11
				-0.97f, 0.0f, -0.26f, // 12

				// Quad 3
				-1.0f, 0.0f, 0.0f, // 13
				-0.97f, 0.0f, 0.26f, // 14
				-0.87f, 0.0f, 0.5f, // 15
				-0.71f, 0.0f,  0.71f, // 16
				-0.5f, 0.0f, 0.87f, // 17
				-0.26f, 0.0f, 0.97f, // 18

				// Quad 4
				0.0f, 0.0f, 1.0f, // 19
				0.26f, 0.0f, 0.97f, // 20
				0.5f, 0.0f,  0.87f, // 21
				0.71f, 0.0f, 0.71f, // 22
				0.87f, 0.0f, 0.5f, // 23
				0.97f, 0.0f, 0.26f, // 24
			};
			shapes.back().indices = {

				// Quad 1
				1, 0, 2,
				2, 0, 3,
				3, 0, 4,
				4, 0, 5,
				5, 0, 6,
				6, 0, 7,

				// Quad 2
				7, 0, 8,
				8, 0, 9,
				9, 0, 10,
				10, 0, 11,
				11, 0, 12,
				12, 0, 13,

				// Quad 3
				13, 0, 14,
				14, 0, 15,
				15, 0, 16,
				16, 0, 17,
				17, 0, 18,
				18, 0, 19,

				// Quad 4
				19, 0, 20,
				20, 0, 21,
				21, 0, 22,
				22, 0, 23,
				23, 0, 24,
				24, 0, 1,

			};
			shapes.back().uvs = {
				0.5f, 0.5f,

				// Quad 1
				1.0f,  0.0f, 
				0.97f, 0.26f,
				0.87f, 0.5f,
				0.71f, 0.71,
				0.5f,  0.87f,
				0.26f, 0.97f,

				// Quad 2
				0.0f,  1.0f, 
			    0.26f, 0.97,
				0.5f,  0.87f,
			    0.71f, 0.7,
				0.87f, 0.5f,
				0.97f, 0.26f,

				// Quad 3
			    1.0f,  0.0f,
			    0.97f, 0.26f,
			    0.87f, 0.5f,
			    0.71f, 0.71,
			    0.5f,  0.87f,
			    0.26f, 0.97f,

				// Quad 4
				0.0f,  1.0f, 
				0.26f, 0.97f,
				0.5f,  0.87f,
				0.71f, 0.71f,
				0.87f, 0.5f,
				0.97f, 0.26f,
			};
			break;
		case Cone:
			arraySize = 78;
			numVertices = 26;
			indices = 144;
			shapes.push_back(Shape(arraySize, indices, col));
			shapes.back().vertices = {

				// Center
				0.0f, 0.0f, 0.0f, // 0
				// Quad 1
				1.0f, 0.0f, 0.0f, // 1
				0.97f, 0.0f, -0.26f, // 2
				0.87f, 0.0f, -0.5f, // 3
				0.71f, 0.0f,  -0.71f, // 4
				0.5f, 0.0f, -0.87f, // 5
				0.26f, 0.0f, -0.97f, // 6

				// Quad 2
				0.0f, 0.0f, -1.0f, // 7
				-0.26f, 0.0f, -0.97f, // 8
				-0.5f, 0.0f, -0.87f, // 9
				-0.71f, 0.0f,  -0.71f, // 10
				-0.87f, 0.0f, -0.5f, // 11
				-0.97f, 0.0f, -0.26f, // 12

				// Quad 3
				-1.0f, 0.0f, 0.0f, // 13
				-0.97f, 0.0f, 0.26f, // 14
				-0.87f, 0.0f, 0.5f, // 15
				-0.71f, 0.0f,  0.71f, // 16
				-0.5f, 0.0f, 0.87f, // 17
				-0.26f, 0.0f, 0.97f, // 18

				// Quad 4
				0.0f, 0.0f, 1.0f, // 19
				0.26f, 0.0f, 0.97f, // 20
				0.5f, 0.0f,  0.87f, // 21
				0.71f, 0.0f, 0.71f, // 22
				0.87f, 0.0f, 0.5f, // 23
				0.97f, 0.0f, 0.26f, // 24

				// Top
				0.0f, 1.0f, 0.0f, // 25
			};
			shapes.back().indices = {

				// Bottom part
				// Quad 1
				2, 0, 1,
				3, 0, 2,
				4, 0, 3,
				5, 0, 4,
				6, 0, 5,
				7, 0, 6,

				// Quad 2
				8, 0, 7,
				9, 0, 8,
				10, 0, 9,
				11, 0, 10,
				12, 0, 11,
				13, 0, 12,

				// Quad 3
				14, 0, 13,
				15, 0, 14,
				16, 0, 15,
				17, 0, 16,
				18, 0, 17,
				19, 0, 18,

				// Quad 4
				20, 0, 19,
				21, 0, 20,
				22, 0, 21,
				23, 0, 22,
				24, 0, 23,
				1, 0, 24,

				// Upper part
				// Quad 1
				1, 25, 2,
				2, 25, 3,
				3, 25, 4,
				4, 25, 5,
				5, 25, 6,
				6, 25, 7,

				// Quad 2
				7, 25, 8,
				8, 25, 9,
				9, 25, 10,
				10, 25, 11,
				11, 25, 12,
				12, 25, 13,

				// Quad 3
				13, 25, 14,
				14, 25, 15,
				15, 25, 16,
				16, 25, 17,
				17, 25, 18,
				18, 25, 19,

				// Quad 4
				19, 25, 20,
				20, 25, 21,
				21, 25, 22,
				22, 25, 23,
				23, 25, 24,
				24, 25, 1,

			};
			shapes.back().uvs = {
				0.5f, 0.5f,

				// Quad 1
				1.0f,  0.0f,
				0.97f, 0.26f,
				0.87f, 0.5f,
				0.71f, 0.71,
				0.5f,  0.87f,
				0.26f, 0.97f,

				// Quad 2
				0.0f,  1.0f,
				0.26f, 0.97,
				0.5f,  0.87f,
				0.71f, 0.7,
				0.87f, 0.5f,
				0.97f, 0.26f,

				// Quad 3
				1.0f,  0.0f,
				0.97f, 0.26f,
				0.87f, 0.5f,
				0.71f, 0.71,
				0.5f,  0.87f,
				0.26f, 0.97f,

				// Quad 4
				0.0f,  1.0f,
				0.26f, 0.97f,
				0.5f,  0.87f,
				0.71f, 0.71f,
				0.87f, 0.5f,
				0.97f, 0.26f,

				// Top
				1.0f, 1.0f,
			};
			break;
		case Cylinder:
			arraySize = 150;
			numVertices = 50;
			indices = 288;
			shapes.push_back(Shape(arraySize, indices, col));
			shapes.back().vertices = {

				// Center
				0.0f, -2.0f, 0.0f, // 0
				// Quad 1
				1.0f, -2.0f, 0.0f, // 1
				0.97f,-2.0f, -0.26f, // 2
				0.87f,-2.0f, -0.5f, // 3
				0.71f, -2.0f,  -0.71f, // 4
				0.5f, -2.0f, -0.87f, // 5
				0.26f, -2.0f, -0.97f, // 6

				// Quad 2
				0.0f, -2.0f, -1.0f, // 7
				-0.26f, -2.0f, -0.97f, // 8
				-0.5f, -2.0f, -0.87f, // 9
				-0.71f, -2.0f,  -0.71f, // 10
				-0.87f, -2.0f, -0.5f, // 11
				-0.97f, -2.0f, -0.26f, // 12

				// Quad 3
				-1.0f, -2.0f, 0.0f, // 13
				-0.97f, -2.0f, 0.26f, // 14
				-0.87f, -2.0f, 0.5f, // 15
				-0.71f, -2.0f,  0.71f, // 16
				-0.5f,  -2.0f, 0.87f, // 17
				-0.26f, -2.0f, 0.97f, // 18

				// Quad 4
				0.0f, -2.0f, 1.0f, // 19
				0.26f, -2.0f, 0.97f, // 20
				0.5f, -2.0f,  0.87f, // 21
				0.71f, -2.0f, 0.71f, // 22
				0.87f, -2.0f, 0.5f, // 23
				0.97f, -2.0f, 0.26f, // 24

				// Top
				0.0f, 2.0f, 0.0f, // 25
				// Quad 1
				1.0f, 2.0f, 0.0f, // 26
				0.97f, 2.0f, -0.26f, // 27
				0.87f, 2.0f, -0.5f, // 28
				0.71f, 2.0f,  -0.71f, // 29
				0.5f, 2.0f, -0.87f, // 30
				0.26f, 2.0f, -0.97f, // 31

				// Quad 2
				0.0f, 2.0f, -1.0f, // 32
				-0.26f, 2.0f, -0.97f, // 33
				-0.5f, 2.0f, -0.87f, // 34
				-0.71f, 2.0f,  -0.71f, // 35
				-0.87f, 2.0f, -0.5f, // 36
				-0.97f, 2.0f, -0.26f, // 37

				// Quad 3
				-1.0f, 2.0f, 0.0f, // 38
				-0.97f, 2.0f, 0.26f, // 39
				-0.87f, 2.0f, 0.5f, // 40
				-0.71f, 2.0f,  0.71f, // 41
				-0.5f, 2.0f, 0.87f, // 42
				-0.26f, 2.0f, 0.97f, // 43

				// Quad 4
				0.0f, 2.0f, 1.0f, // 44
				0.26f, 2.0f, 0.97f, // 45
				0.5f, 2.0f,  0.87f, // 46
				0.71f, 2.0f, 0.71f, // 47
				0.87f, 2.0f, 0.5f, // 48
				0.97f, 2.0f, 0.26f, // 49
			};
			shapes.back().indices = {

				// Bottom part
				// Quad 1
				2, 0, 1,
				3, 0, 2,
				4, 0, 3,
				5, 0, 4,
				6, 0, 5,
				7, 0, 6,

				// Quad 2
				8, 0, 7,
				9, 0, 8,
				10, 0, 9,
				11, 0, 10,
				12, 0, 11,
				13, 0, 12,

				// Quad 3
				14, 0, 13,
				15, 0, 14,
				16, 0, 15,
				17, 0, 16,
				18, 0, 17,
				19, 0, 18,

				// Quad 4
				20, 0, 19,
				21, 0, 20,
				22, 0, 21,
				23, 0, 22,
				24, 0, 23,
				1, 0, 24,

				// Sides
				1, 26, 27,
				27, 2, 1,

				2, 27, 28,
				28, 3, 2,

				3, 28, 29,
				29, 4, 3,

				4, 29, 30,
				30, 5, 4,

				5, 30, 31,
				31, 6, 5,

				6, 31, 32,
				32, 7, 6,

				7, 32, 33,
				33, 8, 7,

				8, 33, 34,
				34, 9, 8,

				9, 34, 35,
				35, 10, 9,

				10, 35, 36,
				36, 11, 10,

				11, 36, 37,
				37, 12, 11,

				12, 37, 38,
				38, 13, 12,

				13, 38, 39,
				39, 14, 13,

				14, 39, 40,
				40, 15, 14,

				15, 40, 41,
				41, 16, 15,

				16, 41, 42,
				42, 17, 16,

				17, 42, 43,
				43, 18, 17,

				18, 43, 44,
				44, 19, 18,

				19, 44, 45,
				45, 20, 19,

				20, 45, 46,
				46, 21, 20,

				21, 46, 47,
				47, 22, 21,

				22, 47, 48,
				48, 23, 22,

				23, 48, 49,
				49, 24, 23,

				24, 49, 26,
				26, 1, 24,

				// Upper part
				// Quad 1
				26, 25, 27,
				27, 25, 28,
				28, 25, 29,
				29, 25, 30,
				30, 25, 31,
				31, 25, 32,

				// Quad 2
				32, 25, 33,
				33, 25, 34,
				34, 25, 35,
				35, 25, 36,
				36, 25, 37,
				37, 25, 38,

				// Quad 3
				38, 25, 39,
				39, 25, 40,
				40, 25, 41,
				41, 25, 42,
				42, 25, 43,
				43, 25, 44,

				// Quad 4
				44, 25, 45,
				45, 25, 46,
				46, 25, 47,
				47, 25, 48,
				48, 25, 49,
				49, 25, 26,

			};
			shapes.back().uvs = {
				0.5f, 0.5f,

				// Quad 1
				1.0f,  0.0f,
				0.97f, 0.26f,
				0.87f, 0.5f,
				0.71f, 0.71,
				0.5f,  0.87f,
				0.26f, 0.97f,

				// Quad 2
				0.0f,  1.0f,
				0.26f, 0.97,
				0.5f,  0.87f,
				0.71f, 0.7,
				0.87f, 0.5f,
				0.97f, 0.26f,

				// Quad 3
				1.0f,  0.0f,
				0.97f, 0.26f,
				0.87f, 0.5f,
				0.71f, 0.71,
				0.5f,  0.87f,
				0.26f, 0.97f,

				// Quad 4
				0.0f,  1.0f,
				0.26f, 0.97f,
				0.5f,  0.87f,
				0.71f, 0.71f,
				0.87f, 0.5f,
				0.97f, 0.26f,

				// Top
				1.0f, 1.0f,

				// Quad 1
				1.0f,  0.0f,
				0.97f, 0.26f,
				0.87f, 0.5f,
				0.71f, 0.71,
				0.5f,  0.87f,
				0.26f, 0.97f,

				// Quad 2
				0.0f,  1.0f,
				0.26f, 0.97,
				0.5f,  0.87f,
				0.71f, 0.7,
				0.87f, 0.5f,
				0.97f, 0.26f,

				// Quad 3
				1.0f,  0.0f,
				0.97f, 0.26f,
				0.87f, 0.5f,
				0.71f, 0.71,
				0.5f,  0.87f,
				0.26f, 0.97f,

				// Quad 4
				0.0f,  1.0f,
				0.26f, 0.97f,
				0.5f,  0.87f,
				0.71f, 0.71f,
				0.87f, 0.5f,
				0.97f, 0.26f,
			};
			break;
		}

		// Doing the normals is done at the end
		for (int i = 0; i < arraySize; i++)
		{
			shapes.back().normals.push_back(0);
		}
		calcAverageNormals(shapes.back().indices, indices, shapes.back().vertices, numVertices, 3, shapes.back().normals);
		// Then we finally bind the shape
		shapes.back().bindShape();
	}

	Shape& GetShape(int index) { return shapes[index]; }
};
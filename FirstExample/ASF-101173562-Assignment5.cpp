//*************************************************************************** 
// ASF-101173562-Assignment5.cpp by Flavio Jorge Araujo Silva (C) 2018 All Rights Reserved. 
// 
// Assignment 5 submission. 
// 
// Description: 
//   Click run to see the results. 
//***************************************************************************** 

using namespace std;

#include <iostream>
#include "stdlib.h"
#include "time.h"
#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "SoilLib/SOIL.h"
#include "GeometryGenerator.h"

#define X_AXIS glm::vec3(1,0,0)
#define Y_AXIS glm::vec3(0,1,0)
#define Z_AXIS glm::vec3(0,0,1)
#define XY_AXIS glm::vec3(1,1,0)
#define YZ_AXIS glm::vec3(0,1,1)
#define XZ_AXIS glm::vec3(1,0,1)

// Lighting Strucs

// Light variables
struct Light
{
	glm::vec3 ambientColour;
	GLfloat ambientStrength;
	glm::vec3 diffuseColour;
	GLfloat diffuseStrength;
	Light(glm::vec3 aCol, GLfloat aStr, glm::vec3 dCol, GLfloat dStr)
	{
		ambientColour = aCol;
		ambientStrength = aStr;
		diffuseColour = dCol;
		diffuseStrength = dStr;
	}
};

struct DirectionalLight : public Light
{
	glm::vec3 direction;
	DirectionalLight(glm::vec3 dir, glm::vec3 aCol, GLfloat aStr, glm::vec3 dCol, GLfloat dStr)
		: Light(aCol, aStr, dCol, dStr)
	{
		direction = dir;
	}
};

struct PointLight : public Light
{
	glm::vec3 position;
	GLfloat falloffStart, falloffEnd;
	PointLight(glm::vec3 pos, GLfloat fallS, GLfloat fallE,
		glm::vec3 aCol, GLfloat aStr, glm::vec3 dCol, GLfloat dStr)
		: Light(aCol, aStr, dCol, dStr)
	{
		position = pos;
		falloffStart = fallS;
		falloffEnd = fallE;
	}
};

struct Material
{
	GLfloat speculatStrength;
	GLfloat shininess;
};

// IDs
GLuint program, vao, ibo, points_vbo, colours_vbo, tex_vbo, normal_vbo, modelID, projID, viewID;

float xpos = 0.0f, ypos = 0.0f, zpos = 10.0f, scrollSpd = 1.0f;

// Camera and transform variables.
glm::vec3 position, frontVec, worldUp, upVec, rightVec; // Set by function.
GLfloat pitch, yaw,
moveSpeed = 0.1f,
turnSpeed = 1.0f,
rotAngle = 0.0f, 
rotAngle2 = 0.0f;

// Mouse variables.
bool mouseFirst = true, mouseClicked = false;
int lastX, lastY;

 // Light variables.
PointLight pLight(glm::vec3(1.0f, 1.0f, 1.0f),			   // Position 
						1.0f, 10.0f,				       // Falloff start and end range
						glm::vec3(1.0f, 1.0f, 1.0f),	   // Ambient colour
						0.2f,							   // Ambient strength
						glm::vec3(1.0f, 1.0f, 1.0f),	   // Diffuse colour
						1.0f);							   // Diffuse strength

Material mat = { 5.0f, 32 }; // Alternate way to construct an object
// Matrices.
glm::mat4 model, view, projection;

// Testing v3
GeometryGenrator g;
//---------------------------------------------------------------------
//
// resetView
//
void resetView()
{
	position = glm::vec3(0.0f, 1.0f, 4.0f);
	frontVec = glm::vec3(0.0f, 0.0f, -1.0f);
	worldUp = glm::vec3(0, 1, 0);
	pitch = -10.0f;
	yaw = -90.0f;
}

void init(void)
{
	//Specifying the name of vertex and fragment shaders.
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};
	
	//Loading and compiling shaders
	program = LoadShaders(shaders);
	glUseProgram(program);	//My Pipeline is set up
	resetView();


	modelID = glGetUniformLocation(program, "model");
	projID = glGetUniformLocation(program, "projection");
	viewID = glGetUniformLocation(program, "view");

	// Setting material values.
	glUniform1f(glGetUniformLocation(program, "specularStrength"), mat.speculatStrength);
	glUniform1f(glGetUniformLocation(program, "shininess"), mat.shininess);

	//// Setting point light
	glUniform3f(glGetUniformLocation(program, "ambientColour"), pLight.ambientColour.x, pLight.ambientColour.y, pLight.ambientColour.z);
	glUniform1f(glGetUniformLocation(program, "ambientStrength"), pLight.ambientStrength);
	glUniform3f(glGetUniformLocation(program, "diffuseColour"), pLight.diffuseColour.x, pLight.diffuseColour.y, pLight.diffuseColour.z);
	glUniform1f(glGetUniformLocation(program, "diffuseStrength"), pLight.diffuseStrength);

	glUniform3f(glGetUniformLocation(program, "lightPosition"), pLight.position.x, pLight.position.y, pLight.position.z);
	glUniform1f(glGetUniformLocation(program, "falloffStart"), pLight.falloffStart);
	glUniform1f(glGetUniformLocation(program, "falloffEnd"), pLight.falloffEnd);

	projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	
	// Camera is set up in the display function
		
		GLint width, height;
		unsigned char* image = SOIL_load_image("Leather.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
		if (!image)
		{
			cout << "Image failed to load" << endl;
		}

		glActiveTexture(GL_TEXTURE0);
		GLuint leather_tex = 0;
		glGenTextures(1, &leather_tex);
		glBindTexture(GL_TEXTURE_2D, leather_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glUniform1i(glGetUniformLocation(program, "texture0"), 0);

		image = SOIL_load_image("Fence.png", &width, &height, 0, SOIL_LOAD_RGBA);
		if (!image)
		{
			cout << "Image failed to load" << endl;
		}

		glActiveTexture(GL_TEXTURE1);
		GLuint fence_tex = 0;
		glGenTextures(1, &fence_tex);
		glBindTexture(GL_TEXTURE_2D, fence_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glUniform1i(glGetUniformLocation(program, "texture0"), 1);
	
	g.GenrateShape(Cylinder, glm::vec3(0.5f, 0.5f, 0.0f));
	// Enable depth test.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	// Enable face culling.
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
}

//---------------------------------------------------------------------
//
// calculateView
//
void calculateView()
{
	frontVec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontVec.y = sin(glm::radians(pitch));
	frontVec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontVec = glm::normalize(frontVec);
	rightVec = glm::normalize(glm::cross(frontVec, worldUp));
	upVec = glm::normalize(glm::cross(rightVec, frontVec));

	// Update the eye (or camera) position and the direction
	view = glm::lookAt(position, position + frontVec, upVec);
	glUniform3f(glGetUniformLocation(program, "eyePosition"), position.x, position.y, position.z);
	glUniform3f(glGetUniformLocation(program, "eyeDirection"), frontVec.x, frontVec.y, frontVec.z);
	
	// Updates the light's position as well
	glUniform3f(glGetUniformLocation(program, "lightPosition"), pLight.position.x, pLight.position.y, pLight.position.z);

}


//---------------------------------------------------------------------
//
// transformModel
//

void transformObject(float scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 translation) {
	glm::mat4 Model;
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, translation);
	Model = glm::rotate(Model, glm::radians(rotationAngle), rotationAxis);
	Model = glm::scale(Model, glm::vec3(scale));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(projID, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
}

void transformObject(glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 translation) {
	glm::mat4 Model;
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, translation);
	Model = glm::rotate(Model, glm::radians(rotationAngle), rotationAxis);
	Model = glm::scale(Model, scale);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(projID, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
}

//---------------------------------------------------------------------
//
// display
//

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Camera matrix
	calculateView();

	glBindVertexArray(g.GetShape(0).getVao());
	
	glUniform1i(glGetUniformLocation(program, "texture0"), 0);

	transformObject(0.5f, Y_AXIS, 0, glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, g.GetShape(0).getIndices(), GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0); // Can optionally unbind the vertex array to avoid modification.

	glutSwapBuffers(); // Now for a potentially smoother render.
}

void idle()
{
	// glutPostRedisplay();
}

void timer(int id)
{
	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);
}

void keyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		position += frontVec * moveSpeed;
		break;
	case 's':
		position -= frontVec * moveSpeed;
		break;
	case 'a':
		position -= rightVec * moveSpeed;
		break;
	case 'd':
		position += rightVec * moveSpeed;
		break;
	case 'i':
		pLight.position.x += moveSpeed;
		break;
	case 'j':
		pLight.position.x -= moveSpeed;
		break;
	case 'k':
		pLight.position.y += moveSpeed;
		break;
	case 'l':
		pLight.position.y -= moveSpeed;
		break;
	case ' ':
		resetView();
		break;
	}
}

void mouseMove(int x, int y)
{
	//cout << "Mouse pos: " << x << "," << y << endl;
	if (mouseClicked)
	{
		pitch -= (GLfloat)((y - lastY) * 0.1);
		yaw += (GLfloat)((x - lastX) * 0.1);
		lastY = y;
		lastX = x;
	}
}

void mouseClick(int btn, int state, int x, int y)
{
	/*cout << "Clicked: " << (btn == 0 ? "left " : "right ") << (state == 0 ? "down " : "up ") <<
		"at " << x << "," << y << endl;*/
	if (state == 0)
	{
		lastX = x;
		lastY = y;
		mouseClicked = true;
		glutSetCursor(GLUT_CURSOR_NONE);
		cout << "Mouse clicked." << endl;
	}
	else
	{
		mouseClicked = false;
		glutSetCursor(GLUT_CURSOR_INHERIT);
		cout << "Mouse released." << endl;
	}
}

void clean()
{
	cout << "Cleaning up!" << endl;
}

//---------------------------------------------------------------------
//
// main
//

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1024, 1024);
	glutCreateWindow("Araujo Silva Flavio Jorge 101173562");

	glewInit();	//Initializes the glew and prepares the drawing pipeline.

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	init();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutTimerFunc(30, timer, 0);
	glutKeyboardFunc(keyDown);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);

	atexit(clean); // This GLUT function calls specified function before terminating program. Useful!
	glutMainLoop();
}

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vec3.hpp"
#include <iostream>

# define M_PI           3.14159265358979323846  /* pi */

using namespace std;

//Test2 oder fksjdölgvksjgfölsjgölgjsödlgjslöjk

static double window_width_ = 1024;
static double window_height_ = 768;
bool rotation = false;
bool xrotate_bool = false;
bool yrotate_bool = false;
bool zrotate_bool = false;
double xrotate = 0;
double yrotate = 0;
double zrotate = 0;
double xscale = 1;
double yscale = 1;
double zscale = 1;
double xtranslate = 0;
double ytranslate = 0;
double winkelDeckel = 360;
bool deckelOeffnen = false;
bool deckelSchliessen = false;

void SetMaterialColor(int side, double r, double g, double b) {
	float	amb[4], dif[4], spe[4];
	int mat;

	dif[0] = r;
	dif[1] = g;
	dif[2] = b;

	for (int i = 0; i < 3; i++) {
		amb[i] = .1 * dif[i];
		spe[i] = .5;
	}
	amb[3] = dif[3] = spe[3] = 1.0;

	switch (side){
	case 1:	mat = GL_FRONT;
		break;
	case 2:	mat = GL_BACK;
		break;
	default: mat = GL_FRONT_AND_BACK;
	}

	glMaterialfv(mat, GL_AMBIENT, amb);
	glMaterialfv(mat, GL_DIFFUSE, dif);
	glMaterialfv(mat, GL_SPECULAR, spe);
	glMaterialf(mat, GL_SHININESS, 20);
}



void Quad() {

	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();						    // Reset The Current Modelview Matrix

	glTranslated(xtranslate, ytranslate, -10.0);      // Move 10 units backwards in z,

	glScalef(xscale, yscale, zscale);

	if (xrotate != 0 || yrotate != 0 || zrotate != 0){
		glRotated(alpha_, xrotate, yrotate, zrotate);
		alpha_ += .5;
	}

	if(xrotate == 0 || yrotate == 0 || zrotate == 0){
		glRotated(0, 0, 0, 0);
	}



	SetMaterialColor(1, 0, 0, 1);
	SetMaterialColor(2, 1, 0, 0);

	glBegin(GL_QUADS);

	//GRUNDFLÄCHE
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, -1);

	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);

	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, -1, 1);

	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);

	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);

	glEnd();

	glPushMatrix();
	glTranslated(1, 1, 0);
	glRotated(winkelDeckel, 0, 0, 1);
	glTranslated(-1, 0, 0);

	if (deckelOeffnen == true) {
		if (winkelDeckel != 225) {
			winkelDeckel = winkelDeckel - .5;
		}
		if (winkelDeckel == 225) {
			deckelOeffnen = false;
		}
	}

	if (deckelSchliessen == true) {
		if (winkelDeckel != 360) {
			winkelDeckel = winkelDeckel + .5;
		}
		if (winkelDeckel == 360) {
			deckelSchliessen = false;
		}
	}

	//Ausgabe des bool-Wertes
	cout << deckelOeffnen;
	cout << deckelSchliessen;
	//***********************

	glBegin(GL_QUADS);

	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);
	glEnd();

	glPopMatrix();
	glPopMatrix();

}


// set viewport transformations and draw objects
void InitLighting() {
	GLfloat lp1[4] = { 10, 5, 10, 0 };
	GLfloat lp2[4] = { -5, 5, -10, 0 };
	GLfloat red[4] = { 1.0, .8, .8, 1 };
	GLfloat blue[4] = { .8, .8, 1.0, 1 };
	GLfloat white[4] = { 1, 1, 1.0, 1 };

	//***************************************
	//Aufgabe 1a: Ändern der Farbe der Beleuchtung
	//Grün und Gelb als Farben hinzugefügt
	//***************************************
	GLfloat green[4] = { 0.196, 0.804, 0.196, 1 };
	GLfloat yellow[4] = { 1.000, 1.000, 0.000, 1 };

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT1, GL_POSITION, lp1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_POSITION, lp2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT2, GL_SPECULAR, white);
	glEnable(GL_LIGHT2);

	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// init viewport to canvassize
	glViewport(0, 0, window_width_, window_height_);

	// init coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15, 15, -10, 10, -20, 20);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

	if (xrotate == 0 && key == GLFW_KEY_X && action == GLFW_PRESS) {
			xrotate = 1;
			cout << "Rotation x: " << xrotate << "\n";
	}

	if (yrotate == 0 && key == GLFW_KEY_Z && action == GLFW_PRESS) {
		yrotate = 1;
	}

	if (zrotate == 0 && key == GLFW_KEY_Y && action == GLFW_PRESS) {
		zrotate = 1;
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		xrotate = 0;
		yrotate = 0;
		zrotate = 0;
		xscale = 1.0;
		yscale = 1.0;
		zscale = 1.0;
		xtranslate = 0;
		ytranslate = 0;
		winkelDeckel = 360;
		deckelOeffnen = false;
		deckelSchliessen = false;

	}

	if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS) {
		xscale = xscale + .25;
		yscale = yscale + .25;
		zscale = zscale + .25;
	}

	if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS) {
		xscale = xscale - .25;
		yscale = yscale - .25;
		zscale = zscale - .25;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		xtranslate = xtranslate - .25;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		xtranslate = xtranslate + .25;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		ytranslate = ytranslate + .25;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		ytranslate = ytranslate - .25;
	}

	if (key == GLFW_KEY_O && action == GLFW_PRESS) {
		deckelSchliessen = false;
		deckelOeffnen = true;
	}

	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		deckelOeffnen = false;
		deckelSchliessen = true;
	}

}



int main() {
	GLFWwindow* window = NULL;

	printf("Here we go!\n");

	if (!glfwInit()){
		return -1;
	}

	window = glfwCreateWindow(window_width_, window_height_,
		"Simple 3D Animation", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {
		// switch on lighting (or you don't see anything)
		InitLighting();

		// set background color
		glClearColor(0.8, 0.8, 0.8, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw the scene
		Quad();

		// make it appear (before this, it's hidden in the rear buffer)
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	printf("Goodbye!\n");

	return 0;
}

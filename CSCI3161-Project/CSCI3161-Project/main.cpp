/*
File: main.cpp
Author: Jonathan Ignacio
Date: December 3, 2017

This is the main source file for the flight simulator project for CSCI 3161.
*/

/*---------------------- Big Ol' To-do list ----------------------*/
/*
*************TODO***************
Exercise 2

Exercise 3:
Allow for camera translation, current challege is movement idepenedent of the scene

END:
Maybe change window name? ...but it's great
Clear all TODO list items
*/

#include <iostream>
#include <freeglut.h>

#include "Generation.h"
#include "constants.h"
#include "camera.h"

using namespace std;

/* global variables for tracking states */
GLboolean fullscreen = false; //variable for tracking if the program is in fullscreen
GLboolean wireframe = true; //toggles GL_LINES or GL_FILL for the grid
GLint windowWidth = WINDOW_INIT_WIDTH, windowHeight = WINDOW_INIT_HEIGHT; //tracks the window height and width

																		  /* camera control variables*/
Camera* camera; //the camera object
GLint lastX = 0; //stores the most recent X position for reference;

				 /* display function for rendering all objects */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear frame and z buffer

	camera->draw(); //sets the camera, all objects following are drawn in reference to it

	drawAxis(); //draw the reference axis and the sphere

				/* draw the grid, filled or wireframe based on toggle*/
	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //change polygon mode to wireframe
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //change to solid
	}
	drawGrid(); //draw the grid

	glutSwapBuffers(); //swap buffers
}

/* idle function for updating values in between frames */
void idle()
{
	camera->update(); //updates the camera with the latest changes
	glutPostRedisplay(); //force redraw
}

/* window resize, taken from lecture code */
void reshape(int w, int h)
{
	/* update the window height and width with the new values */
	windowWidth = w;
	windowHeight = h;

	glViewport(0, 0, windowWidth, windowHeight); //reset the viewport to still contain the whole window

	glMatrixMode(GL_PROJECTION); //switch to projection matrix mode
	glLoadIdentity(); //reset the projection

	gluPerspective(DEFAULT_FOV, (float)windowWidth / (float)windowHeight, Z_NEAR, Z_FAR); //set the scaled perspective

	glMatrixMode(GL_MODELVIEW); //switch back to model matrix mode
}

/* basic keyboard key controls */
void keys(unsigned char key, int x, int y) {

	switch (key) {
	case 'w':
		wireframe = !wireframe; //toggle wireframe on or off
		break;

	case 'f':
		if (!fullscreen) {
			glutFullScreen();
		}
		else {
			glutReshapeWindow(windowWidth, windowHeight); //change window size back to previous
			glutPositionWindow(WINDOW_INIT_X, WINDOW_INIT_Y); //reset position
		}
		//glutFullScreenToggle(); //this function works, but perhaps we were intended to do it manually?
		fullscreen = !fullscreen;
		break;

	case 'q':
		exit(1); //closes the program
		break;
	}
	glutPostRedisplay(); //force re-display
}

/* special key controls */
void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_PAGE_UP:
		camera->adjustFlightSpeed(CAMERA_FLIGHT_SPEED_ADJUST);
		break;
	case GLUT_KEY_PAGE_DOWN:
		camera->adjustFlightSpeed(-CAMERA_FLIGHT_SPEED_ADJUST);
		break;
	case GLUT_KEY_UP:
		camera->adjustHeight(-CAMERA_FLIGHT_SPEED_ADJUST);
		break;
	case GLUT_KEY_DOWN:
		camera->adjustHeight(CAMERA_FLIGHT_SPEED_ADJUST);
		break;
	}
}

/* function to handle mouse control */
void mouseMotion(int x, int y) {
	GLint midPoint = windowWidth / 2; //get the midpoint of the screen
	GLint centerLeft = midPoint - (windowWidth * WINDOW_CENTER_WIDTH); //left x coord of the center area
	GLint centerRight = midPoint + (windowWidth * WINDOW_CENTER_WIDTH); //right x coord of the center area

	if (x < centerLeft) { //cursor is left of screen
		if (x < lastX) { //cursor moved more left than last time
			camera->adjustRotateSpeed(-1, CAMERA_ROTATE_SPEED_ADJUST); //since even more left, increase left speed
		}
		else if (x > lastX) { //cursor moved more right than last time
			camera->adjustRotateSpeed(-1, -CAMERA_ROTATE_SPEED_ADJUST); //since less left, decrease left speed
		}
		else { //x did not change
			camera->adjustRotateSpeed(-1, 0); //no speed change
		}
	}
	else if (x > centerRight) {
		if (x > lastX) { //cursor moved more right than last time
			camera->adjustRotateSpeed(1, CAMERA_ROTATE_SPEED_ADJUST); //since more right, increase right speed
		}
		else if (x < lastX) { //cursor moved more left than last time
			camera->adjustRotateSpeed(1, -CAMERA_ROTATE_SPEED_ADJUST); //since less right, decrease left speed
		}
		else { //x did not change
			camera->adjustRotateSpeed(1, 0); //no speed change
		}
	}
	else { //cursor is within center
		camera->adjustRotateSpeed(0, -CAMERA_ROTATE_SPEED_MAX); //if the mouse passes through center, rotation speed is set to 0
	}

	lastX = x; //update the most recent x value
}

/* initialization function, adpated from lecture notes*/
void initializeGL()
{
	glEnable(GL_DEPTH_TEST); //enables hidden surface removal

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //set initial polygon modes

											   /* set states as default*/
	glClearColor(BLACK, 1.0); //set background to black
	glLineWidth(DEFAULT_LINE_WIDTH);

	glMatrixMode(GL_PROJECTION); // go into projection mode to change the camera properties
	glLoadIdentity(); // load identity into projection matrix
					  //arguments gluPerspective(fovy, aspect, near, far)
	gluPerspective(DEFAULT_FOV, windowWidth / windowHeight, Z_NEAR, Z_FAR); //set perspective projection

	camera = new Camera(CAMERA_INIT_EYE_X, CAMERA_INIT_EYE_Y, CAMERA_INIT_EYE_Z); //initialize the camera object providing its initial position

	glMatrixMode(GL_MODELVIEW); // go into model-view mode to change the object’s position
}

//main function
void main(int argc, char **argv) {
	glutInit(&argc, argv);	// Intialize GLUT command line arguments

							/* window intitialzation */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //double buffering, z-depth, RGB color
	glutInitWindowSize(WINDOW_INIT_WIDTH, WINDOW_INIT_HEIGHT); //starting window size
	glutInitWindowPosition(WINDOW_INIT_X, WINDOW_INIT_Y); //set the initial window position
	glutCreateWindow("2k17 Flight Simulator: Electric Boogaloo"); //create the named window

																  /* callback registrations */
	glutReshapeFunc(reshape); //window resizing function 
	glutDisplayFunc(display); //display function 
	glutIdleFunc(idle); //idle function 
	glutKeyboardFunc(keys); //normal keyboard function
	glutSpecialFunc(specialKeys); //special keyboard function
	glutPassiveMotionFunc(mouseMotion); //passive mouse motion function

	initializeGL(); //run initialization
	glutMainLoop(); //start looping
}
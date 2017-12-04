/*
File: main.cpp
Author: Jonathan Ignacio
Date: December 3, 2017

This is the main source file for the flight simulator project for CSCI 3161. Handles windowing, rendering and other GLUT processes
*/

#include <freeglut.h>

#include "scene.h"
#include "utility.h"
#include "camera.h"

/* global variables for tracking states */
GLboolean fullscreen = false; //variable for tracking if the program is in fullscreen
GLint windowWidth = WINDOW_INIT_WIDTH, windowHeight = WINDOW_INIT_HEIGHT; //tracks the window height and width
GLint previousWindowWidth, previousWindowHeight; //for saving window dimensions before fullscreen

/* camera control variables*/
Camera* camera; //the camera object
Scene* scene; //the scene object

/* display function for rendering all objects */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear frame and z buffer

	camera->draw(); //sets the camera, all objects following are drawn in reference to it
	scene->draw(); //renders the scene based on its current states

	glutSwapBuffers(); //swap buffers
}

/* idle function for updating values in between frames */
void idle() {
	camera->update(); //updates the camera with the latest changes
	glutPostRedisplay(); //force redraw
}

/* window resize, taken from lecture code */
void reshape(int w, int h) {
	/* update the window height and width with the new values */
	windowWidth = w;
	windowHeight = h;

	glViewport(0, 0, windowWidth, windowHeight); //reset the viewport to still contain the whole window

	glMatrixMode(GL_PROJECTION); //switch to projection matrix mode
	glLoadIdentity(); //reset the projection

	gluPerspective(DEFAULT_FOV, (float)windowWidth / (float)windowHeight, Z_NEAR, Z_FAR); //set the scaled perspective

	glMatrixMode(GL_MODELVIEW); //switch back to model matrix mode
}

/* basic key press controls */
void downKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		exit(1); //closes the program
		break;
	}
	glutPostRedisplay(); //force re-display
}

/* basic key release controls */
void upKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 'f':
		if (!fullscreen) {
			/*save window dimensions pre-fullscreen*/
			previousWindowWidth = windowWidth;
			previousWindowHeight = windowHeight;
			glutFullScreen();
		}
		else {
			glutReshapeWindow(previousWindowWidth, previousWindowHeight); //change window size back to previous
			glutPositionWindow(WINDOW_INIT_X, WINDOW_INIT_Y); //reset position
		}
		fullscreen = !fullscreen;
		break;
	case 'w':
		scene->toggleWireframe(); //toggle scene wireframe on or off
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
		camera->adjustHeight(CAMERA_FLIGHT_SPEED_UP);
		break;
	case GLUT_KEY_DOWN:
		camera->adjustHeight(-CAMERA_FLIGHT_SPEED_UP);
		break;
	}
	glutPostRedisplay(); //force re-display
}

/* function to handle mouse control */
void mouseMotion(int x, int y) {
	GLint midPoint = windowWidth / 2; //get the midpoint of the screen
	GLint centerLeft = midPoint - (windowWidth * WINDOW_CENTER_WIDTH); //left x coord of the center area
	GLint centerRight = midPoint + (windowWidth * WINDOW_CENTER_WIDTH); //right x coord of the center area
	GLfloat portion; //percentage distance of cursor from center to edge

	if (x < centerLeft) { //cursor is left of screen
		portion = 1 - (GLfloat) x / (GLfloat) centerLeft; //get the percentage for left side
		camera->tiltControl(-1, portion); //adjust speed based on percentage
	}
	else if (x > centerRight) {
		portion = ((GLfloat) x - (GLfloat) centerRight) / ((GLfloat) windowWidth - (GLfloat) centerRight); //get the percentage for right side
		camera->tiltControl(1, portion); //adjust speed based on percentage
	}
	else { //cursor is within center
		camera->tiltControl(0, 0); //if the mouse passes through center, rotation speed is set to 0
	}
}

/* initialization function, adpated from lecture notes*/
void initializeGL()
{
	glEnable(GL_DEPTH_TEST); //enables hidden surface removal
	glClearColor(BLACK, 1.0); //set background to black
	glLineWidth(DEFAULT_LINE_WIDTH); //defaults stored in utility.h file

	/* set up projection mode */
	glMatrixMode(GL_PROJECTION); // go into projection mode to change the camera properties
	glLoadIdentity(); // load identity into projection matrix
	gluPerspective(DEFAULT_FOV, windowWidth / windowHeight, Z_NEAR, Z_FAR); //set perspective projection

	/* object instantiations go here */
	camera = new Camera(); //initialize the camera object
	scene = new Scene(); //no arg constructor to object used for scene rendering

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

	printControls(); //print controls from the utility file to the console

	/* callback registrations */
	glutReshapeFunc(reshape); //window resizing function 
	glutDisplayFunc(display); //display function 
	glutIdleFunc(idle); //idle function 
	glutKeyboardFunc(downKeys); //normal keyboard function for presses
	glutKeyboardUpFunc(upKeys); //normal keyboard function for releases
	glutSpecialFunc(specialKeys); //special keyboard function
	glutPassiveMotionFunc(mouseMotion); //passive mouse motion function

	initializeGL(); //run initialization
	glutMainLoop(); //start looping
}


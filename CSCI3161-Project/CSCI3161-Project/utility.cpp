/*
File: utility.cpp
Author: Jonathan Ignacio
Date: December 3, 2017

This source file contains all common utility functions (added as needed).
*/

#include "utility.h"

using namespace std;

/* checks that an angle falls between 0 and 360 */
GLfloat validDegree(GLfloat angle) {
	if (angle >= 360) {
		angle = angle - 360;
	}
	else if (angle < 0) {
		angle = angle + 360;
	}
	return angle;
}

GLfloat degreesToRadians(GLfloat angle) {
	return angle*((GLfloat)PI/(GLfloat)180); //returns radians
}

/* place description for keyboard controls here */
void printControls() {
	system("CLS"); //clear the console
	cout << "CONTROLS: \n"
		<< "q: quits the application\n"
		<< "f: toggles fullscreen\n"
		<< "w: toggles wireframe grid\n";
}


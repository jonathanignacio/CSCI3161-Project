/*
File: camera.h
Author: Jonathan Ignacio
Date: December 3, 2017

This header file defines the camera class
*/

#pragma once //prevents defining more than once
#include <freeglut.h>
#include "constants.h"

using namespace std;

class Camera {
	GLdouble currentX, currentY, currentZ; //member for tracking current camera position
	GLdouble lookX, lookY, lookZ; //member to set where the camera is looking
	GLdouble lookOffsetX, lookOffsetY, lookOffsetZ; //members to track the difference between subject and camera
	GLdouble upX, upY, upZ; //member for keeping track of the camera up direction

	GLint rotateDirection; //tracks the current camera rotation direction
	GLfloat rotateAmount; //tracks the current camera rotation
	GLfloat rotateSpeed; //tracks the current speed for camera rotation
	GLfloat maxRotateSpeed; //upper limit to the camera rotational speed
	GLfloat minRotateSpeed; //loswer limit to the camera rotational speed


	GLfloat flightSpeed; //tracks the current speed of the camera
	GLfloat maxFlightSpeed; //upper limit to the camera flight speed
	GLfloat minFlightSpeed; //lower limit to the camera flight speed

public:
	Camera(GLdouble, GLdouble, GLdouble); //constuctor sets the member variables to defaults for gluLookAt
	void update(); //updates variables as though a time step passed
	void draw(void); //'draws' the camera using it's current state
	void adjustRotateSpeed(GLint, GLfloat); //changes the rotation direction of the camera
	void adjustFlightSpeed(GLfloat); //adjust flight speed within min and max
	void adjustHeight(GLfloat); //adjust the height of the camera
	void updateRotate(void); //updates camera rotation amount based on current rotate speed and direction
	void updateDistance(); //updates the camera position based on the current flight speed
};
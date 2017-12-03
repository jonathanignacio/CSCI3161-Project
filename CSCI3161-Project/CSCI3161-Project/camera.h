/*
File: camera.h
Author: Jonathan Ignacio
Date: December 3, 2017

This header file defines the camera class
*/

#pragma once //prevents defining more than once
#include <freeglut.h>
#include "utility.h"
#include <math.h>

/* Camera Control Constants */
#define CAMERA_INIT_EYE_X 0.0 //initial X pos of the camera eye
#define CAMERA_INIT_EYE_Y 3.0 //initial Y pos of the camera eye
#define CAMERA_INIT_EYE_Z 5.0 //initial Z pos of the camera eye
#define CAMERA_UP 0,1,0 //default setting for camera 'up'
#define CAMERA_ROTATE_SPEED_ADJUST 0.01 //amount that the rotation speed is increased by per step 
#define CAMERA_ROTATE_SPEED_MAX 3 //rotation maximum speed
#define CAMERA_ROTATE_SPEED_MIN 0 //rotation minimum speed (generally should be 0 for no rotation as the minimum)
#define CAMERA_FLIGHT_SPEED_UP 0.5 //camera speed used for upward translation
#define CAMERA_FLIGHT_SPEED_ADJUST 0.01 //camera speed decrement or increment amount per step
#define CAMERA_FLIGHT_SPEED_MAX 1 //camera flight maximum speed
#define CAMERA_FLIGHT_SPEED_MIN 0.01 //camera flight minimum speed
#define PLANE_ROLL_RANGE 45 //degree of rotation for plane roll in one direction (total range is *2)
#define PLANE_INITIAL_HEIGHT 5 //height from the apparent axis

using namespace std;

class Camera {
public:
	/* public functions */
	Camera(void); //constuctor sets the member variables to defaults for gluLookAt
	void update(void); //updates variables as though a time step passed
	void draw(void); //'draws' the camera using it's current state
	void tiltControl(GLint, GLfloat); //changes the rotation direction of the camera and tilt of the plane
	void adjustFlightSpeed(GLfloat); //adjust flight speed within min and max
	void adjustHeight(GLfloat); //adjust the height of the camera

private:
	/* private functions */
	void updateRotate(void); //updates camera rotation amount based on current rotate speed and direction
	void updateDistance(void); //updates the camera position based on the current flight speed

	/* private variables */
	GLdouble currentX, currentY, currentZ; //members for tracking current camera position
	GLdouble lookX, lookY, lookZ; //members to set where the camera is looking
	GLfloat translateX, translateY, translateZ; //tracks the translation of the whole scene

	GLint rotateDirection; //tracks the current camera rotation direction
	GLfloat pastRotate; //tracks the camera rotation before update for calculating change in angle
	GLfloat currentRotate; //tracks the current camera rotation
	GLfloat rotateSpeed; //tracks the current speed for camera rotation
	GLfloat maxRotateSpeed; //upper limit to the camera rotational speed
	GLfloat minRotateSpeed; //lower limit to the camera rotational speed
	GLfloat planeRoll; //value for tracking the plane's roll

	GLfloat flightSpeed; //tracks the current speed of the camera
	GLfloat maxFlightSpeed; //upper limit to the camera flight speed
	GLfloat minFlightSpeed; //lower limit to the camera flight speed
};
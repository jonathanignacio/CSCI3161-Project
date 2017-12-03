/*
File: camera.cpp
Author: Jonathan Ignacio
Date: December 3, 2017

This source file contains all functions and variables related to the camera
*/

#include "camera.h"

Camera::Camera() {
	/* initialize the starting eye position from the origin*/
	currentX = CAMERA_INIT_EYE_X;
	currentY = CAMERA_INIT_EYE_Y;
	currentZ = CAMERA_INIT_EYE_Z;

	/* initialize the starting look at position (the plane is drawn here) */
	lookX = 0;
	lookY = 0;
	lookZ = 0;

	/* tracks translation of the rest of the scene */
	translateX = 0;
	translateY = -PLANE_INITIAL_HEIGHT; //the Y translation of the scene to give the plane the specified height
	translateZ = 0;

	/* set the intial camera movement variables */
	pastRotate = 0;
	currentRotate = 0; //camera begins facing forward
	rotateDirection = 0; //camera begins facing forward (-1 for left, +1 for right)
	rotateSpeed = 0; //camera begins by not rotating 
	flightSpeed = CAMERA_FLIGHT_SPEED_MIN; //camera is moving as slowly as allowed
	planeRoll = 0; //plane roll initially 0
	
	/* set the movement limits from constants */
	maxRotateSpeed = CAMERA_ROTATE_SPEED_MAX; //the fastest that the camera is allowed to rotate
	minRotateSpeed = CAMERA_ROTATE_SPEED_MIN; //the slowest that the camera is allowed to rotate
	maxFlightSpeed = CAMERA_FLIGHT_SPEED_MAX; //upper limit to the camera speed
	minFlightSpeed = CAMERA_FLIGHT_SPEED_MIN; //lower limit to the camera speed
}

/* function to set the camera using the paramters stored in the camera object */
void Camera::update() {
	this->updateRotate(); //calls function to update the rotateAmount within limits
	this->updateDistance(); //calls function to update the flight translation
	cout << "Translate X: " << translateX << ", Z: " << translateZ << "\n";
	cout << "Direction of rotation: " << currentRotate << "\n";
}

/* draws the camera using its current state*/
void Camera::draw() {
	glMatrixMode(GL_MODELVIEW); //load model view
	glLoadIdentity(); //reset transformations

	gluLookAt(currentX, currentY, currentZ, //new camera eye
		lookX, lookY, lookZ,				//camera look at
		CAMERA_UP);							//camera up direction

	/* plane goes here */
	glPushMatrix(); //push matrix so that only the plane is rotated
		glRotatef(90, 0, 1, 0); //spout facing forward (yaw)
		glRotatef(planeRoll, 1, 0, 0); //roll according to the rotation value
		glColor3f(BLUE); 
		glutSolidTeapot(1); //a nice blue teapot plane
	glPopMatrix(); //pop back to transform scene

	glRotatef(currentRotate, 0, 1, 0); //rotate scene based on current value, about the y axis
	glTranslatef(translateX, translateY, translateZ); //translate scene based on movement of camera
}

/* function that sets camera rotation variables and plane tilt */
void Camera::tiltControl(GLint dir, GLfloat portion) {
	rotateDirection = dir; //current rotational direction
	rotateSpeed = portion * CAMERA_ROTATE_SPEED_MAX; //should be positive

	planeRoll = validDegree(portion * dir * PLANE_ROLL_RANGE); //change plane roll based on where the mouse is relative to the edge of the screen
}

/* function to adjust flight speed within minimum and maximum values */
void Camera::adjustFlightSpeed(GLfloat change) {
	if (change > 0) { //speed increase
		if (flightSpeed + change < maxFlightSpeed) { //if change does not violate maximum
			flightSpeed += change; //go ahead with adjustment
		}
		else { //is at or near max speed
			flightSpeed = maxFlightSpeed; //clamp the flight speed
		}
	}
	else { //speed decrease
		if (flightSpeed + change > minFlightSpeed) { //if change does not violate minimum
			flightSpeed += change; //go ahead with adjustment
		}
		else { //is at or near min speed
			flightSpeed = minFlightSpeed; //clamp the flight speed
		}
	}
}

/* function to adjust the height of the camera */
void Camera::adjustHeight(GLfloat change) {
	translateY -= change; //adjust the height of the camera by change the distance between what is rendered
}

/* updates rotateAmount within the restrictions for the next time the camera is drawn*/
void Camera::updateRotate() {
	currentRotate = validDegree(currentRotate + (rotateSpeed * rotateDirection)); //changes the rotation based on rotation speed and direction
}

/* updates camera position variables based on current speed and rotation*/
void Camera::updateDistance() {
	//determine x and z coordinate difference based on current rotation and speed
	GLfloat radians = degreesToRadians(currentRotate); //convert degrees to radians
	/* add the rotation values */
	translateX -= (GLfloat)flightSpeed * sin(radians);
	translateZ += (GLfloat)flightSpeed * cos(radians);
}


/*
File: camera.cpp
Author: Jonathan Ignacio
Date: December 3, 2017

This source file contains all functions and variables related to the camera
*/

#include "camera.h"

Camera::Camera(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ) {
	/* initialize the starting eye position from the origin*/
	currentX = eyeX;
	currentY = eyeY;
	currentZ = eyeZ;

	/* initialize the starting look at position (the plane is drawn here) */
	lookX = 0;
	lookY = 0;
	lookZ = 0;

	/* initialize the look offsets to lock the camera angle*/
	translateX = 0;
	translateY = 0;
	translateZ = 0;

	/* initialize the up direction */
	upX = 0;
	upY = 1;
	upZ = 0;

	/* set the intial camera movement variables */
	rotateAmount = 0; //camera begins facing forward
	rotateDirection = 0; //camera begins facing forward (-1 for left, +1 for right)
	rotateSpeed = 0; //camera begins by not rotating 
	flightSpeed = 0; //camera is initialially not moving
	
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
}

/* draws the camera using its current state*/
void Camera::draw() {
	glMatrixMode(GL_MODELVIEW); //load model view
	glLoadIdentity(); //reset transformations

	gluLookAt(currentX, currentY, currentZ, //new camera eye
		lookX, lookY, lookZ,				//camera look at
		upX, upY, upZ);						//camera up direction

	glRotatef(rotateAmount, 0, 1, 0); //rotate based on current value, about the y axis
	glTranslatef(translateX, translateY, translateZ); //translate scene based on movement of camera
}

/* function that sets camera rotation variables, speedChange is positive for increasing speeds */
void Camera::adjustRotateSpeed(GLint dir, GLfloat speedChange) {
	rotateDirection = dir; //current rotational direction

	if (speedChange > 0) { //speed increase
		if (rotateSpeed + speedChange < maxRotateSpeed) { //if change does not violate maximum
			rotateSpeed += speedChange; //go ahead with adjustment
		}
		else { //is at or near max speed
			rotateSpeed = maxRotateSpeed; //clamp the rotation speed
		}
	}
	else { //speed decrease
		if (rotateSpeed + speedChange > minRotateSpeed) { //if change does not violate minimum
			rotateSpeed += speedChange; //go ahead with adjustment
		}
		else { //is at or near min speed
			rotateSpeed = minRotateSpeed; //clamp the rotation speed
		}
	}
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
	translateY += change; //adjust the height of the camera by change the distance between what is rendered
}

/* updates rotateAmount within the restrictions for the next time the camera is drawn*/
void Camera::updateRotate() {
	if (rotateAmount + (rotateSpeed * rotateDirection) >= 360.0) { //value would exceed 360
		rotateAmount += (rotateSpeed * rotateDirection) - 360.0; //bring rotation back to 0 and adjust by remainder
	}
	else if (rotateAmount + (rotateSpeed * rotateDirection) < 0.0) { //value would fall below 0
		rotateAmount += (rotateSpeed * rotateDirection) + 360.0; //bring rotation back to 360 and adjust by remainder
	}
	else { //rotation is okay to apply
		rotateAmount += (rotateSpeed * rotateDirection);
	}
}

/* updates camera position variables based on current speed and rotation*/
void Camera::updateDistance() {

}
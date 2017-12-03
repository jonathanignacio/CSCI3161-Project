/*
File: constants.h
Author: Jonathan Ignacio
Date: December 3, 2017

This header file contains globally accessible constants that are referenced throughout the project.
*/

#pragma once //prevents defining more than once

/* Colours */
#define WHITE 1,1,1
#define RED 1,0,0
#define GREEN 0,1,0
#define BLUE 0,0,1
#define YELLOW 1,1,0
#define GRAY 0.5,0.5,0.5
#define BLACK 0,0,0

/* Axis and Grid Drawing Constants*/
#define SPHERE_SLICES 20
#define SPHERE_STACKS 20
#define AXIS_SPHERE_RADIUS 0.15 //radius for the white ball positioned at the origin
#define AXIS_LINE_WIDTH 5.0 //line width for the direction vectors, specified by project description
#define AXIS_LINE_LENGTH 2.0 //line length for each of the direction vectors for the axis
#define AXIS_ADJUST_Y 0.1 //ajdustment on Y for the axis to appear slightly above the grid (to prevent overlap)
#define GRID_SIZE 100 // X by X vertices for drawing the grid

/* Camera Control Constants */
#define CAMERA_INIT_EYE_X 0.0 //initial X pos of the camera eye
#define CAMERA_INIT_EYE_Y 5.0 //initial Y pos of the camera eye
#define CAMERA_INIT_EYE_Z 3.0 //initial Z pos of the camera eye
#define CAMERA_ROTATE_SPEED_ADJUST 0.01 //amount that the rotation speed is increased by per step 
#define CAMERA_ROTATE_SPEED_MAX 3 //rotation maximum speed
#define CAMERA_ROTATE_SPEED_MIN 0 //rotation minimum speed (generally should be 0 for no rotation as the minimum)
#define CAMERA_FLIGHT_SPEED_ADJUST 0.1 //camera speed decrement or increment amount per step
#define CAMERA_FLIGHT_SPEED_MAX 10 //camera flight maximum speed
#define CAMERA_FLIGHT_SPEED_MIN 0 //camera flight minimum speed

/* Misc Constants */
#define Z_NEAR 0.1 //lowest z value
#define Z_FAR 200.0 //highest z value
#define DEFAULT_FOV 90 //FOV used by the gluPerspective function
#define DEFAULT_LINE_WIDTH 1.0
#define WINDOW_INIT_WIDTH 1024 //default window width
#define WINDOW_INIT_HEIGHT 576 //default window height
#define WINDOW_INIT_X 100 //default window position, x
#define WINDOW_INIT_Y 100 //default window position, y
#define WINDOW_CENTER_WIDTH 0.05 //the % width of the area in the center of the screen that counts as 'center' for camera control

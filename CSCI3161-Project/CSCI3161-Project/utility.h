/*
File: utility.h
Author: Jonathan Ignacio
Date: December 3, 2017

This header file contains constants that are referenced throughout the project
as well as some protoypes to utility functions.
*/

#pragma once //prevents defining more than once

#include <freeglut.h>
#include <iostream>

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

/* Misc Constants */
#define PI 3.14159265 //for radian calculations
#define Z_NEAR 0.1 //lowest z value
#define Z_FAR 200.0 //highest z value
#define DEFAULT_FOV 90 //FOV used by the gluPerspective function
#define DEFAULT_LINE_WIDTH 1.0
#define WINDOW_INIT_WIDTH 1024 //default window width
#define WINDOW_INIT_HEIGHT 576 //default window height
#define WINDOW_INIT_X 100 //default window position, x
#define WINDOW_INIT_Y 100 //default window position, y
#define WINDOW_CENTER_WIDTH 0.005 //the % width of the area in the center of the screen that counts as 'center' for camera control

/* utility functions */
GLfloat validDegree(GLfloat); //ensures that angle falls between 0 and 360
GLfloat degreesToRadians(GLfloat); //converts degrees to radians for math functions
void printControls();

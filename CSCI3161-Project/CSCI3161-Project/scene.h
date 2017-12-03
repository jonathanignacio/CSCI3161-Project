/*
File: generation.h
Author: Jonathan Ignacio
Date: December 3, 2017

This header file contains prototypes and dependencies for the generation.cpp file.
*/

#pragma once //prevents defining more than once

#include <freeglut.h>
#include "utility.h"
#include <math.h>

using namespace std;

/* class for handling the basic scene generation */
class Scene{
public:
	/* public functions */
	Scene(void); //no args contructor
	void draw(void); //renders the enitre scene (grid, axis and sphere)
	void toggleWireframe(); //controls whether the scene is rendered in wireframe or solid

private:
	/* private functions */
	void drawAxisLines(); //draws the axis lines and the sphere
	void drawGrid(); 
	void drawSphere(GLdouble);

	/* private variables */
	GLboolean wireframe; //controls if the scene is rendered as wireframe or solid
};
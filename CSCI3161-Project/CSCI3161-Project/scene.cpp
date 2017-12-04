/*
File: generation.cpp
Author: Jonathan Ignacio
Date: December 3, 2017

This source file contains all of the functions used for generating and drawing shapes.
Is generally called directly in the display function.
*/

#include "scene.h"

/* constructor for the scene object */
Scene::Scene() {
	wireframe = true; //default draw as a wireframe
}

void Scene::toggleWireframe() {
	wireframe = !wireframe; //toggles the wireframe state
}

void Scene::draw() {
	drawAxisLines(); //draw the axis lines
	drawGrid(); //draw the grid
	glColor3f(WHITE); //set sphere drawing color to white
	drawSphere(AXIS_SPHERE_RADIUS); //draw the sphere
}

/* draws 3 lines and a sphere to represent the origin and axis*/
void Scene::drawAxisLines() {
	glMatrixMode(GL_MODELVIEW); //set matrix mode to model view
	glPushMatrix(); //push the matrix to prevent modifying other transformations
		//glTranslatef(0, 0, 0.1); //TODO unsure of purpose

		//drawSphere(AXIS_SPHERE_RADIUS); //draw the sphere

		/* draw the three axis lines */
		glLineWidth(AXIS_LINE_WIDTH); //set line drawing width for the axis

		/* x direction */
		glColor3f(RED);
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0); //draw the start point for the line
			glVertex3f(AXIS_LINE_LENGTH, 0, 0); //draw the end point for the line
		glEnd();

		/* y direction */
		glColor3f(GREEN);
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0); //draw the start point for the line
			glVertex3f(0, AXIS_LINE_LENGTH, 0); //draw the end point for the line
		glEnd();

		/* z direction */
		glColor3f(BLUE);
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0); //draw the start point for the line
			glVertex3f(0, 0, AXIS_LINE_LENGTH); //draw the end point for the line
		glEnd();
	glPopMatrix(); //pop the matrix back to previous state

	glLineWidth(DEFAULT_LINE_WIDTH); //return the line width to previous state
}

/* draw the frame of reference grid */
void Scene::drawGrid() {
	wireframe ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //set polygon mode for this drawing

	GLfloat gridHalf = (GLfloat)GRID_SIZE / 2; // varible for splitting the vertices evenly
	glColor3f(GRAY); //gray grid

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			glBegin(GL_QUADS); //draws the individual quad based on the dimensions (drawn counterclockwise)
			glVertex3f(-gridHalf + i, 0, gridHalf - j);			//top left
			glVertex3f(-gridHalf + i, 0, gridHalf - j - 1);		//bottom left
			glVertex3f(-gridHalf + i + 1, 0, gridHalf - j - 1);	//bottom right
			glVertex3f(-gridHalf + i + 1, 0, gridHalf - j);		//top right
			glEnd();
		}
	}
}

/* draws a sphere, adapted from Assignment 2 code */
void Scene::drawSphere(GLdouble radius) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //make sure the sphere is solid

	GLUquadricObj *quadric = NULL; //needed to draw the sphere

	quadric = gluNewQuadric(); //instantiate the quadric
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //make sure this sphere is filled

	gluSphere(quadric, radius, SPHERE_SLICES, SPHERE_STACKS); //render the sphere

	gluDeleteQuadric(quadric); //delete the quadric reference
}
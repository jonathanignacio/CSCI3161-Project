/*
File: model.h
Author: Jonathan Ignacio
Date: December 3, 2017

This header file defines the model class, used for loading complex models from a file and drawing them
*/

#pragma once //prevents defining more than once

/* file name constants */
#define PLANE_FILE_NAME "cessna.txt"
#define PROPELLER_FILE_NAME "propeller.txt"

#include <freeglut.h>
#include <vector> //using vectors to store vertices, faces and normals. Behaves like a java arraylist
#include <array> //c++ object for arrays
#include <fstream> //for reading data from a file
#include <sstream> //for reading data from a string (each line of the file)
#include <string>
#include <ostream>
#include <iostream>

class Model {
public:
	Model(std::string); //constructor that takes the filename of the model
	void draw(void); //render the model

private:
	/* private functions */
	void readFile(void); //uses the stored filename to read a file and load the model

	/* private variables */
	std::string filename; //the stored name of the file being loaded
	std::vector<std::array<GLfloat, 3>> vertices; //vector containing arrays of vertex coordinates
	std::vector<std::array<GLfloat, 3>> normals; //vector containing arrays of normal coordinates
	std::vector<std::vector<GLint>> faces; //2D vector of faces stored as integers
};
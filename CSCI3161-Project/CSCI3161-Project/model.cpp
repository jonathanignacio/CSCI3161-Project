/*
File: model.cpp
Author: Jonathan Ignacio
Date: December 3, 2017

This source file contains all functions and variables related to the model objects
*/

#include "model.h"

/* constructor that loads the file and populates the model vectors */
Model::Model(std::string filename) {
	this->filename = filename; //save our file name
	readFile(); //reads the file and stores the data in the vectors
}

void Model::readFile() {
	std::ifstream fileStream(filename); //create a new filestream using the specified file

	std::string line; //the current line being read by the file
	char flag; //the current flag for what type of data is being read

	/* file operation loop */
	while (std::getline(fileStream, line)) { //read line by line until end of file is reached
		std::stringstream lineStream(line); //create a stream for the particular line
		if (lineStream >> flag) { //if the flag is successfully read, proceed reading the line
			//would like to use switch statment here, but visual studio does not like skipping object instantiations
			if (flag == 'v') { //vertex, has 3 coordinate values
				std::array<GLfloat, 3> currentVertex; //current vertex, 3 coordinates as GLfloats
				lineStream >> currentVertex[0] >> currentVertex[1] >> currentVertex[2]; //read the three coordinates
				vertices.push_back(currentVertex); //add the current vertex to back of vector
			}
			if (flag == 'n') { //normal, has 3 coordinate values
				std::array<GLfloat, 3> currentNormal; //current normal, 3 coordinates as GLfloats
				lineStream >> currentNormal[0] >> currentNormal[1] >> currentNormal[2]; //read the three coordinates
				normals.push_back(currentNormal); //add the current normal to back of vector
			}
			if (flag == 'g') { //sub-object and name
				//need to differentiate sub-object for colouring
			}
			if (flag == 'f') { //face, slightly trickier because any number of vertices can be present
				std::vector<GLint> currentFace; //current face, has minimum of 3 values
				GLint currentValue; //for storing the current token
				while (lineStream >> currentValue) { //read values until the end of the line is reached
					currentFace.push_back(currentValue); //push the value to the back of the vector (will maintain correct order)
				}
				faces.push_back(currentFace); //add face to the list of faces
			}
		}
	} //end of loop, get next line
	fileStream.close(); //close the file
}

void Model::draw() {
	//ignoring subobjects for now
	/* use a random access iterator to iterate through all faces */
	for (std::vector<std::vector<GLint>>::iterator face = faces.begin(); face != faces.end(); ++face) { //++face is more efficient because it doesn't require copying the data
		/* this particular face needs to be drawn */
		glBegin(GL_POLYGON); //start drawing the face using the vertex coordinates
		for (std::vector<GLint>::iterator vertexReference = face->begin(); vertexReference != face->end(); ++vertexReference) { //gets the integer references to the vertex
			std::array<GLfloat, 3> vertexArray = vertices.at(*vertexReference - 1); //returns the vertex array at the reference (minus one to avoid franken plane shape)
			std::array<GLfloat, 3> normalArray = normals.at(*vertexReference - 1); //returns the normal array at the reference
			glNormal3f(normalArray[0], normalArray[1], normalArray[2]); //set the normal
			glVertex3f(vertexArray[0], vertexArray[1], vertexArray[2]); //set the vertex
		}
		glEnd(); //move onto next face
	}
}
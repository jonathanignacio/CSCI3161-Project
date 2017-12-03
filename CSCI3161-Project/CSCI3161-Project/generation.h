/*
File: generation.h
Author: Jonathan Ignacio
Date: December 3, 2017

This header file contains prototypes and dependencies for the generation.cpp file.
*/

#pragma once //prevents defining more than once


#include <freeglut.h>
#include "constants.h"
#include <math.h>

/* FUNCTION PROTOTYPES */


/* Shape rendering functions */
void drawAxis(void);
void drawSphere(GLdouble);
void drawGrid(void);

/* Misc. functions*/

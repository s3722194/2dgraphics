#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "vectors.h"
#include "setup.h"
#include "input.h"
#include "rendering.h"
#include "logic.h"

#if _WIN32
#include <windows.h>
#endif
#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


vector2 vector_addition(vector2 v1, vector2 v2) {
	vector2 answer;
	answer.x = v1.x + v2.x;
	answer.y = v1.y + v2.y;
	return answer;
}

vector2 vector_subtraction(vector2 v1, vector2 v2) {
	vector2 answer;
	answer.x = v1.x - v2.x;
	answer.y = v1.y - v2.y;
	return answer;
}

vector2 vector_scalar(vector2 v1, float scalar) {
	vector2 answer;
	answer.x = v1.x * scalar;
	answer.y = v1.y * scalar;
	return answer;
}

float vector_length(vector2 v1) {
	return sqrt(v1.x * v1.x + v1.y * v1.y);
}

vector2 vector_normalise(vector2 v1) {
	float length = vector_length(v1);
	vector2 answer;
	if (length != 0)
	{
		answer.x = v1.x / length;
		answer.y = v1.y / length;
	}
	else
	{
		// not sure if this is the right this to do when its zero
		//test to see
		answer.x = 1;
		answer.y = 1;
	}
	return answer;
}

// since this is in 2d but we still need to provide the z value
//the z is irrevelant for culautions and only there for depth reasons
vector2 vector3_to_vector2(vector3 v1) {
	vector2 answer;
	answer.x = v1.x;
	answer.y = v1.y;
	return answer;
}

float dot_product(vector2 v1, vector2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}


float vector_angle_rad(vector2 v1, vector2 v2) {
	return acos(dot_product(v1, v2) / (vector_length(v1) * vector_length(v2)));
}

float degree_to_rad(float a) {
	return a * (M_PI / 180);
}

float rad_to_degree(float a) {
	return a * (180 / M_PI);
}


float vector_angle_degree(vector2 v1, vector2 v2) {
	return rad_to_degree(acos(dot_product(v1, v2) / (vector_length(v1) * vector_length(v2))));
}

vector2 rad_angle_to_direction(float angle) {
	vector2 answer;
	answer.x = cos(angle);
	answer.y = sin(angle);
	return answer;
}

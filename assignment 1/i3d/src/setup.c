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


#ifndef MAX_BULLETS
#define MAX_BULLETS 20
#endif


void create_ship() {

	//set up ship

	ship.transform.scale.x = 1;
	ship.transform.scale.y = 1;

	ship.transform.rotation = 0;

	ship.transform.position.x = 0;
	ship.transform.position.y = 0;

	ship.transform.position.x = 0;

	// creating shape of the ship

	//point 1
	vector3 point1;
	point1.x = -0.1;
	point1.y = -0.1;
	point1.z = 0;

	ship.points[0] = point1;

	//point 2
	vector3 point2;
	point2.x = 0;
	point2.y = -0.05;
	point2.z = 0;

	ship.points[1] = point2;

	//point3
	vector3 point3;
	point3.x = 0;
	point3.y = 0.1;
	point3.z = 0;

	ship.points[2] = point3;

	//point 4
	vector3 point4;
	point4.x = 0;
	point4.y = 0.1;
	point4.z = 0;

	ship.points[3] = point4;

	//point 5
	vector3 point5;
	point5.x = 0.1;
	point5.y = -0.1;
	point5.z = 0;

	ship.points[4] = point5;

	//point 6
	vector3 point6;
	point6.x = 0;
	point6.y = -0.05;
	point6.z = 0;

	ship.points[5] = point6;

	ship.number_of_points = 6;

	//colour of the ship

	//fill colouris black
	ship.fill_colour.r = 0.325;
	ship.fill_colour.g = 0.1098;
	ship.fill_colour.b = 0.70196;

	//outline colour is light purple
	ship.outline_colour.r = 0.6666;
	ship.outline_colour.g = 0.482;
	ship.outline_colour.b = 0.7647;

	ship.bounds.origin.x = 0;
	ship.bounds.origin.y = 0;
	ship.bounds.radius = 0.5;

	ship.move_down = false;
	ship.move_up = false;
	ship.turn_left = false;
	ship.turn_right = false;

	ship.speed = 0.001;

	ship.bottom_wall = false;
	ship.top_wall = false;
	ship.right_wall = false;
	ship.left_wall = false;

}

void create_bullets() {
	bullets.active = false;
	bullets.add_new_bullet = false;
	bullets.fire_rate = 500;
	bullets.number_of_bullets = 0;
	bullets.time_between_bullets = 0;


}

void create_asteroid() {
	asteroids.lauch_radius = 1.5;
	asteroids.wave = 1;
	asteroids.wave_finished = false;
	asteroids.number_of_asteroids = 0;
	asteroids.create_more_asteroids = true;
	asteroids.max_wave = 10;
}

void create_wall() {

	//point 1
	vector3 point1;
	point1.x = -1;
	point1.y = -1;
	point1.z = 0;
	wall.points[0] = point1;

	//point 2
	vector3 point2;
	point2.x = 1;
	point2.y = -1;
	point2.z = 0;
	wall.points[1] = point2;

	//point 3
	vector3 point3;
	point3.x = 1;
	point3.y = 1;
	point3.z = 0;
	wall.points[2] = point3;

	//point 4
	vector3 point4;
	point4.x = -1;
	point4.y = 1;
	point4.z = 0;
	wall.points[3] = point4;

	wall.number_of_points = 4;

	wall.fill_colour.r = 0.8588;
	wall.fill_colour.g = 0.658;
	wall.fill_colour.b = 0.6745;

	wall.outline_colour.r = 0.192;
	wall.outline_colour.g = 0.5176;
	wall.outline_colour.b = 0.988;

}

void setup_game() {

	create_ship();
	create_wall();
	create_bullets();
	create_asteroid();
	delta_time = 0;
	total_time = 0;
}

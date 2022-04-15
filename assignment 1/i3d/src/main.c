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

#ifndef GAME_TITLE
#define GAME_TITLE "Asteroid Arena"
#endif

#ifndef KEY_ESC
#define KEY_ESC 27
#endif

#ifndef MAX_BULLETS
#define MAX_BULLETS 20
#endif




circle_t g_rand_circles[5];
circle_t g_user_circle;

float world_size = 1.0f;




//typedef struct Windows
//{
//	int width, height, x_pos, y_pos;
//	bool is_fullscreen;
//} window_t;

//typedef struct Colour
//{
//	float r, g, b;
//} colour;
//
//typedef struct Vector3
//{
//	float x, y, z;
//
//} vector3;
//
//typedef struct Vector2
//{
//	float x, y;
//
//} vector2;
//
//typedef struct Point
//{
//	float x, y, z;
//
//} point;
//
//typedef struct Circle {
//	vector2 origin;
//	float radius;
//} circle;
//
//typedef struct Transform
//{
//	vector3 position;
//	float rotation;
//	vector3 scale;
//
//} transform2d;
//
//typedef struct Player {
//	vector3 points[6];
//	int number_of_points;
//	transform2d transform;
//	circle bounds;
//	colour outline_colour;
//	colour fill_colour;
//	float speed;
//	bool move_up;
//	bool move_down;
//	bool turn_left;
//	bool turn_right;
//
//	//track which wall its close to
//	bool top_wall;
//	bool bottom_wall;
//	bool right_wall;
//	bool left_wall;
//} player;
//
//typedef struct Asteroid {
//	transform2d transform;
//	circle point;
//	colour outline_colour;
//	colour fill_colour;
//	float speed;
//	vector2 direction;
//} asteroid;
//
//
//
//typedef struct Wall {
//	vector3 points[4];
//	int number_of_points;
//	colour outline_colour;
//	colour fill_colour;
//} wall2d;
//
//typedef struct Bullet {
//	transform2d transform;
//	bool active;
//	float speed;
//} bullet;
//
//typedef struct Collection_Bullets {
//	bullet bullets[20];
//	int number_of_bullets;
//	bool active;
//	bool add_new_bullet;
//	float fire_rate;
//	int time_between_bullets;
//	
//} collection_of_bullets;
//
//typedef struct Collection_Asteroid {
//	int wave;
//	asteroid asteroids[20];
//	int number_of_asteroids;
//	float lauch_radius;
//	bool wave_finished;
//	bool create_more_asteroids;
//	int max_wave;
//
//
//} collection_of_asteroids;
//
//
//typedef struct
//{
//	int width, height, x_pos, y_pos;
//	bool is_fullscreen;
//} window_t;
//
//typedef struct
//{
//	float pos_x;
//	float pos_y;
//	float radius;
//} circle_t;
//
//void render_circle(circle_t circle, float cr, float cg, float cb);
//
//circle_t g_rand_circles[5];
//circle_t g_user_circle;
//window_t g_mainwin;
//float world_size = 1.0f;
//
//player ship;
//collection_of_asteroids asteroids;
//wall2d wall;
//int total_time;
//int delta_time;
//collection_of_bullets bullets;
//
//
//vector2 vector_addition(vector2 v1, vector2 v2) {
//	vector2 answer;
//	answer.x = v1.x + v2.x;
//	answer.y = v1.y + v2.y;
//	return answer;
//}
//
//vector2 vector_subtraction(vector2 v1, vector2 v2) {
//	vector2 answer;
//	answer.x = v1.x - v2.x;
//	answer.y = v1.y - v2.y;
//	return answer;
//}
//
//vector2 vector_scalar(vector2 v1, float scalar) {
//	vector2 answer;
//	answer.x = v1.x * scalar;
//	answer.y = v1.y * scalar;
//	return answer;
//}
//
//float vector_length(vector2 v1) {
//	return sqrt(v1.x * v1.x + v1.y * v1.y);
//}
//
//vector2 vector_normalise(vector2 v1) {
//	float length = vector_length(v1);
//	vector2 answer;
//	if (length != 0)
//	{
//		answer.x = v1.x / length;
//		answer.y = v1.y / length;
//	}
//	else
//	{
//		// not sure if this is the right this to do when its zero
//		//test to see
//		answer.x = 1;
//		answer.y = 1;
//	}
//	return answer;
//}
//
//// since this is in 2d but we still need to provide the z value
////the z is irrevelant for culautions and only there for depth reasons
//vector2 vector3_to_vector2(vector3 v1) {
//	vector2 answer;
//	answer.x = v1.x;
//	answer.y = v1.y;
//	return answer;
//}
//
//float dot_product(vector2 v1, vector2 v2) {
//	return v1.x * v2.x + v1.y * v2.y;
//}
//
//
//float vector_angle_rad(vector2 v1, vector2 v2) {
//	return acos(dot_product(v1, v2) / (vector_length(v1) * vector_length(v2)));
//}
//
//float degree_to_rad(float a) {
//	return a * (M_PI/180);
//}
//
//float rad_to_degree(float a) {
//	return a * (180/M_PI);
//}
//
//
//float vector_angle_degree(vector2 v1, vector2 v2) {
//	return rad_to_degree( acos(dot_product(v1, v2) / (vector_length(v1) * vector_length(v2))));
//}
//
//vector2 rad_angle_to_direction(float angle) {
//	vector2 answer;
//	answer.x = cos(angle);
//	answer.y = sin(angle);
//	return answer;
//}
//
//
////float map(float x, float in_min, float in_max, float out_min, float out_max)
////{
////	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
////}
//
////circle_t init_circle(float posX, float posY, float radius)
////{
////	circle_t circle;
////
////	circle.pos_x = posX;
////	circle.pos_y = posY;
////	circle.radius = radius;
////
////	return circle;
////}
//
//void create_ship() {
//
//	//set up ship
//
//	ship.transform.scale.x = 1;
//	ship.transform.scale.y = 1;
//
//	ship.transform.rotation = 0;
//
//	ship.transform.position.x = 0;
//	ship.transform.position.y = 0;
//
//	ship.transform.position.x = 0;
//
//	// creating shape of the ship
//
//	//point 1
//	vector3 point1;
//	point1.x = -0.1;
//	point1.y = -0.1;
//	point1.z = 0;
//
//	ship.points[0] = point1;
//
//	//point 2
//	vector3 point2;
//	point2.x = 0;
//	point2.y = -0.05;
//	point2.z = 0;
//
//	ship.points[1] = point2;
//
//	//point3
//	vector3 point3;
//	point3.x = 0;
//	point3.y = 0.1;
//	point3.z = 0;
//
//	ship.points[2] = point3;
//
//	//point 4
//	vector3 point4;
//	point4.x = 0;
//	point4.y = 0.1;
//	point4.z = 0;
//
//	ship.points[3] = point4;
//
//	//point 5
//	vector3 point5;
//	point5.x = 0.1;
//	point5.y = -0.1;
//	point5.z = 0;
//
//	ship.points[4] = point5;
//
//	//point 6
//	vector3 point6;
//	point6.x = 0;
//	point6.y = -0.05;
//	point6.z = 0;
//
//	ship.points[5] = point6;
//
//	ship.number_of_points = 6;
//
//	//colour of the ship
//
//	//fill colouris black
//	ship.fill_colour.r = 0.325;
//	ship.fill_colour.g = 0.1098;
//	ship.fill_colour.b = 0.70196;
//
//	//outline colour is light purple
//	ship.outline_colour.r = 0.6666;
//	ship.outline_colour.g = 0.482;
//	ship.outline_colour.b = 0.7647;
//
//	ship.bounds.origin.x = 0;
//	ship.bounds.origin.y = 0;
//	ship.bounds.radius = 0.5; 
//
//	ship.move_down = false;
//	ship.move_up = false;
//	ship.turn_left = false;
//	ship.turn_right = false;
//
//	ship.speed = 0.001;
//
//	ship.bottom_wall = false;
//	ship.top_wall = false;
//	ship.right_wall = false;
//	ship.left_wall = false;
//
//}
//
//void create_bullets() {
//	bullets.active = false;
//	bullets.add_new_bullet = false;
//	bullets.fire_rate = 500;
//	bullets.number_of_bullets = 0;
//	bullets.time_between_bullets = 0;
//	
//	
//}
//
//void create_asteroid() {
//	asteroids.lauch_radius = 1.5;
//	asteroids.wave = 1;
//	asteroids.wave_finished = false;
//	asteroids.number_of_asteroids = 0;
//	asteroids.create_more_asteroids = true;
//	asteroids.max_wave = 10;
//}
//
//void create_wall() {
//
//	//point 1
//	vector3 point1;
//	point1.x = -1;
//	point1.y = -1;
//	point1.z = 0;
//	wall.points[0] = point1;
//
//	//point 2
//	vector3 point2;
//	point2.x = 1;
//	point2.y = -1;
//	point2.z = 0;
//	wall.points[1] = point2;
//
//	//point 3
//	vector3 point3;
//	point3.x = 1;
//	point3.y = 1;
//	point3.z = 0;
//	wall.points[2] = point3;
//
//	//point 4
//	vector3 point4;
//	point4.x = -1;
//	point4.y = 1;
//	point4.z = 0;
//	wall.points[3] = point4;
//
//	wall.number_of_points = 4;
//
//	wall.fill_colour.r = 0.8588;
//	wall.fill_colour.g = 0.658;
//	wall.fill_colour.b = 0.6745;
//
//	wall.outline_colour.r = 0.192;
//	wall.outline_colour.g = 0.5176;
//	wall.outline_colour.b = 0.988;
//
//}
//
//void setup_game() {
//
//	create_ship();
//	create_wall();
//	create_bullets();
//	create_asteroid();
//	delta_time = 0;
//	total_time = 0;
//}
//
//void render_asteroids() {
//
//	if (asteroids.number_of_asteroids > 0) {
//		for (int i = 0; i < asteroids.number_of_asteroids; i++) {
//			glPushMatrix();
//			glLoadIdentity();
//			circle_t c;
//			c.pos_x = asteroids.asteroids[i].transform.position.x;
//			c.pos_y = asteroids.asteroids[i].transform.position.y;
//			c.radius = asteroids.asteroids[i].point.radius;
//
//			render_circle(c, 1, 0, 1);
//			glPopMatrix();
//		}
//	}
//}
//
//void render_string(float x, float y, void* font, const char* string)
//{
//	glMatrixMode(GL_PROJECTION);
//	glPushMatrix();
//	glLoadIdentity();
//
//	// Set the projection - use this to render text
//	gluOrtho2D(0, g_mainwin.width, 0, g_mainwin.height);
//	glMatrixMode(GL_MODELVIEW);
//
//	glRasterPos2f(x, y);
//	int len = (int)strlen(string);
//	for (int i = 0; i < len; i++)
//	{
//		glutBitmapCharacter(font, string[i]);
//	}
//
//	glMatrixMode(GL_PROJECTION);
//
//	// Restore the original projection matrix for rendering everything else
//	glPopMatrix();
//
//	glMatrixMode(GL_MODELVIEW);
//}
//
//void render_ship() {
//
//	glPushMatrix();
//	glLoadIdentity();
//
//	//tranformation
//	glTranslatef(ship.transform.position.x, ship.transform.position.y, 0.0f);
//	glRotatef(ship.transform.rotation, 0.0f, 0.0f, 1.0f);
//	glScalef(1, 1, 1);
//
//	//render the trianges
//	glBegin(GL_POLYGON);
//	glColor3f(ship.fill_colour.r, ship.fill_colour.g, ship.fill_colour.b);
//	glVertex3f(ship.points[0].x, ship.points[0].y, ship.points[0].z);
//	glVertex3f(ship.points[1].x, ship.points[1].y, ship.points[1].z);
//	glVertex3f(ship.points[2].x, ship.points[2].y, ship.points[2].z);
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(ship.fill_colour.r, ship.fill_colour.g, ship.fill_colour.b);
//	glVertex3f(ship.points[3].x, ship.points[3].y, ship.points[3].z);
//	glVertex3f(ship.points[4].x, ship.points[4].y, ship.points[4].z);
//	glVertex3f(ship.points[5].x, ship.points[5].y, ship.points[5].z);
//	glEnd();
//
//	//render the outline
//
//	glBegin(GL_LINES);
//	glColor3f(1, 0, 1);
//	//glLineWidth(2.0);
//	glVertex3f(ship.points[0].x, ship.points[0].y, ship.points[0].z);
//	glVertex3f(ship.points[1].x, ship.points[1].y, ship.points[1].z);
//	glVertex3f(ship.points[2].x, ship.points[2].y, ship.points[2].z);
//	glEnd();
//
//	glBegin(GL_LINES);
//	glColor3f(1, 0, 1);
//	glVertex3f(ship.points[1].x, ship.points[1].y, ship.points[1].z);
//	glVertex3f(ship.points[2].x, ship.points[2].y, ship.points[2].z);
//	glEnd();
//
//	glBegin(GL_LINES);
//	glColor3f(1, 0, 1);
//	glVertex3f(ship.points[3].x, ship.points[3].y, ship.points[3].z);
//	glVertex3f(ship.points[2].x, ship.points[2].y, ship.points[2].z);
//	glEnd();
//
//	glBegin(GL_LINES);
//	glColor3f(1, 0, 1);
//	glVertex3f(ship.points[3].x, ship.points[3].y, ship.points[3].z);
//	glVertex3f(ship.points[4].x, ship.points[4].y, ship.points[4].z);
//	glEnd();
//
//	glBegin(GL_LINES);
//	glColor3f(1, 0, 1);
//	glVertex3f(ship.points[4].x, ship.points[4].y, ship.points[4].z);
//	glVertex3f(ship.points[5].x, ship.points[5].y, ship.points[5].z);
//	glEnd();
//
//	glBegin(GL_LINES);
//	glColor3f(1, 0, 1);
//	glVertex3f(ship.points[0].x, ship.points[0].y, ship.points[0].z);
//	glVertex3f(ship.points[2].x, ship.points[2].y, ship.points[2].z);
//	glEnd();
//
//	//ship gun
//	glBegin(GL_POLYGON);
//	glColor3f(0.3, 0.4, 0.1);
//	glVertex3f(0.1, 0.05, 1);
//	glVertex3f(0.05, 0.05, 1);
//	glVertex3f(0.05, 0.1, 1);
//	glVertex3f(0.1, 0.1, 1);
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(0.3, 0.4, 0.1);
//	glVertex3f(0.0666, 0.1, 1);
//	glVertex3f(0.08333, 0.1, 1);
//	glVertex3f(0.0833, 0.11, 1);
//	glVertex3f(0.0666, 0.11, 1);
//	glEnd();
//
//
//	//// this is just so we can see where its pointing
//	//glBegin(GL_LINES);
//	//glColor3f(1.0, 1.0, 0.0);
//	//glVertex3f(0, 0, 0.0);
//	//glVertex3f(0, 0.1, 0.0);
//	//glEnd();
//
//
//	glPopMatrix();
//
//	//circle_t c;
//	//c.pos_x = ship.bounds.origin.x;
//	//c.pos_y = ship.bounds.origin.y;
//	//c.radius = ship.bounds.radius;
//
//	//render_circle(c, 0, 0, 1);
//}
//
//void render_bullets() {
//
//	if (bullets.active == true && bullets.number_of_bullets!=0) 
//	{
//		for (int i = 0; i < bullets.number_of_bullets; i++) 
//		{
//			//printf("create bullets!!\n");
//			glPushMatrix();
//			glLoadIdentity();
//			circle_t c;
//			c.radius = 0.01;
//			c.pos_x = bullets.bullets[i].transform.position.x;
//			c.pos_y = bullets.bullets[i].transform.position.y;
//			render_circle(c, 0, 0.8, 0);
//
//			glPopMatrix();
//
//		}
//	}
//
//}
//
//void render_wall() {
//	glPushMatrix();
//	glLoadIdentity();
//	
//
//	glBegin(GL_POLYGON);
//	//glColor3f(wall.fill_colour.r, wall.fill_colour.g, wall.fill_colour.b);
//	glColor3f(wall.fill_colour.r, wall.fill_colour.g, wall.fill_colour.b);
//	//glLineWidth(20.0);
//	glVertex3f(wall.points[0].x, wall.points[0].y, wall.points[0].z);
//	glVertex3f(wall.points[1].x, wall.points[1].y, wall.points[1].z);
//	glVertex3f(wall.points[2].x, wall.points[2].y, wall.points[2].z);
//	glVertex3f(wall.points[3].x, wall.points[3].y, wall.points[3].z);
//
//	glEnd();
//
//	//bottom wall
//	glBegin(GL_LINES);
//	if (ship.bottom_wall) 
//	{
//		glColor3f(1, 0, 0);
//	}
//	else
//	{
//		glColor3f(wall.outline_colour.r, wall.outline_colour.g, wall.outline_colour.b);
//	}
//	//GLfloat gl
//	//glLineWidth((GLfloat)20.0);
//	glVertex3f(wall.points[0].x, wall.points[0].y, wall.points[0].z);
//	glVertex3f(wall.points[1].x, wall.points[1].y, wall.points[1].z);
//	glEnd();
//
//	//right wall
//	glBegin(GL_LINES);
//	if (ship.right_wall)
//	{
//		glColor3f(1, 0, 0);
//	}
//	else
//	{
//		glColor3f(wall.outline_colour.r, wall.outline_colour.g, wall.outline_colour.b);
//	}
//	glVertex3f(wall.points[2].x, wall.points[2].y, wall.points[2].z);
//	glVertex3f(wall.points[1].x, wall.points[1].y, wall.points[1].z);
//	glEnd();
//
//	//top wall
//	glBegin(GL_LINES);
//	if (ship.top_wall)
//	{
//		glColor3f(1, 0, 0);
//	}
//	else
//	{
//		glColor3f(wall.outline_colour.r, wall.outline_colour.g, wall.outline_colour.b);
//	}
//	glVertex3f(wall.points[2].x, wall.points[2].y, wall.points[2].z);
//	glVertex3f(wall.points[3].x, wall.points[3].y, wall.points[3].z);
//	glEnd();
//
//	//left wall
//	glBegin(GL_LINES);
//	if (ship.left_wall)
//	{
//		glColor3f(1, 0, 0);
//	}
//	else
//	{
//		glColor3f(wall.outline_colour.r, wall.outline_colour.g, wall.outline_colour.b);
//	}
//	glVertex3f(wall.points[0].x, wall.points[0].y, wall.points[0].z);
//	glVertex3f(wall.points[3].x, wall.points[3].y, wall.points[3].z);
//	glEnd();
//
//
//	glPopMatrix();
//}
//
//int detect_overlap(circle_t c1, circle_t c2)
//{
//	const float dx = c2.pos_x - c1.pos_x;
//	const float dy = c2.pos_y - c1.pos_y;
//	const float radii = c1.radius + c2.radius;
//
//	if ((radii * radii) <= (dx * dx) + (dy * dy))
//	{
//		return 0;
//	}
//
//	return 1;
//}
//
//// See circle.c from Week 2 material
//void draw_circle_cartesian(float r, int n)
//{
//	float x, y;
//
//	glLineWidth(2.0);
//	glBegin(GL_LINE_LOOP);
//
//	n /= 2;
//
//	for (int i = 0; i < n; i++)
//	{
//		x = ((i / (float)n - 0.5) * 2.0) * r;
//		y = sqrt(r * r - x * x);
//		glVertex2f(x, y);
//	}
//
//	for (int i = n; i > 0; i--)
//	{
//		x = (i / (float)n - 0.5) * 2.0 * r;
//		y = -sqrt(r * r - x * x);
//		glVertex2f(x, y);
//	}
//
//	glEnd();
//}
//
//void render_circle(circle_t circle, float cr, float cg, float cb)
//{
//	glPushMatrix();
//	glLoadIdentity();
//	glTranslatef(circle.pos_x, circle.pos_y, 0.0f);
//	glScalef(circle.radius, circle.radius, 1.0f);
//	glColor3f(cr, cg, cb);
//	// draw a unit circle
//	draw_circle_cartesian(1.0, 64);
//	glPopMatrix();
//}
//
//void render_launch_position() {
//	circle_t c;
//	c.radius = asteroids.lauch_radius;
//	c.pos_x = 0;
//	c.pos_y = 0;
//	render_circle(c, 1, 0, 0);
//}
//
//void end_app()
//{
//	exit(EXIT_SUCCESS);
//}
//
//void render_frame()
//{
//	render_wall();
//	render_ship();
//	render_circle(g_rand_circles[4], 1.0f, 0.0f, 0.0f);
//	render_asteroids();
//	render_bullets();
//	render_launch_position();
//
//	//glPushMatrix();
//	//glLoadIdentity();
//
//	//glPointSize(2.0);
//	/*glBegin(GL_POINT);
//	glColor3f(1, 1, 0);
//	glVertex2f(0.5, 0.5);
//	glEnd();
//
//	glPopMatrix();*/
//	
//}
//
//void on_display()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	render_frame();
//
//	int err;
//	while ((err = glGetError()) != GL_NO_ERROR)
//	{
//		printf("error: %s\n", gluErrorString(err));
//	}
//
//	glutSwapBuffers();
//}
//
//void ship_movement() {
//	float rotation = 0.5 *delta_time;
//
//	if (ship.move_up)
//	{
//		//ship.transform.position.y += 0.001;
//		float rad = degree_to_rad(ship.transform.rotation + 90);
//		vector2 normalised = rad_angle_to_direction(rad);
//
//		ship.transform.position.x += normalised.x * ship.speed * delta_time;
//		ship.transform.position.y += normalised.y * ship.speed * delta_time;
//		//printf("normalise: %f , %f. angle: %f\n", normalised.x, normalised.y, rad);
//	}
//	else if (ship.move_down)
//	{
//		float rad = degree_to_rad(ship.transform.rotation + 90);
//		vector2 normalised = rad_angle_to_direction(rad);
//		ship.transform.position.x -= normalised.x * ship.speed * delta_time;
//		ship.transform.position.y -= normalised.y * ship.speed * delta_time;
//		printf("normalise: %f , %f. angle: %f\n", normalised.x, normalised.y, rad);
//	}
//	else if (ship.turn_left)
//	{
//		ship.transform.rotation += rotation;
//	}
//	else if (ship.turn_right)
//	{
//		ship.transform.rotation -= rotation;
//	}
//}
//
//void reset_player() {
//	ship.transform.rotation = 0;
//
//	ship.transform.position.x = 0;
//	ship.transform.position.y = 0;
//
//	ship.transform.position.x = 0;
//	ship.bottom_wall = false;
//	ship.top_wall = false;
//	ship.right_wall = false;
//	ship.left_wall = false;
//
//}
//
//void check_wall(vector2 point) {
//
//
//	if (point.x < -0.9) {
//		ship.left_wall = true;
//	}
//
//	if (point.x > 0.8) {
//		ship.right_wall = true;
//	}
//
//	if (point.y > 0.9) {
//		ship.top_wall = true;
//	}
//
//	if (point.y < -0.9) {
//		ship.bottom_wall = true;
//	}
//
//	if (point.y < -1) {
//		reset_player();
//	}
//
//	if (point.y > 1) {
//		reset_player();
//	}
//
//	if (point.x > 0.95) {
//		reset_player();
//	}
//
//	if (point.x < -1) {
//		reset_player();
//	}
//}
//
//void update_astroids() {
//
//	if (asteroids.create_more_asteroids == true) {
//		asteroids.create_more_asteroids = false;
//		for (int i = 0; i < asteroids.wave; i++) {
//			srand(time(0)+i);
//			printf("create asteroid!\n");
//			asteroid new_astreroid;
//			int max_number = 360;
//			int minimum_number = 0;
//
//			//this is so we get some good vaules for rand 
//			//i find the first few can see quite smiliar
//			rand();
//			rand();
//			int degree = rand() % (max_number + 1 - minimum_number) + minimum_number;
//			//printf("degree %f\n", degree);
//			float rad = degree_to_rad(degree);
//
//			vector2 normalised = rad_angle_to_direction(rad);
//
//			new_astreroid.transform.position.x = normalised.x*asteroids.lauch_radius;
//			new_astreroid.transform.position.y = normalised.y * asteroids.lauch_radius;
//			new_astreroid.transform.position.z = 1;
//
//			int min_speed = 10;
//			int max_speed = 100;
//			int speed = rand() % (max_speed + 1 - min_speed) + min_speed;
//			new_astreroid.speed = (float)speed / 100000.0f;
//			printf("speed %f\n", new_astreroid.speed);
//			circle c;
//			c.origin.x = 0;
//			c.origin.y = 0;
//			int min_radius = 5;
//			int max_radius = 100;
//			int radius = rand() % (max_radius + 1 - min_radius) + min_radius;
//			
//			c.radius = (float)radius / 1000;
//			
//
//			new_astreroid.point = c;
//			printf("radius %f\n", new_astreroid.point.radius);
//
//			vector2 ship_to_local_world = vector_subtraction(vector3_to_vector2(ship.transform.position),
//				vector3_to_vector2(new_astreroid.transform.position));
//			new_astreroid.direction = vector_normalise(ship_to_local_world);
//
//			asteroids.asteroids[asteroids.number_of_asteroids] = new_astreroid;
//			asteroids.number_of_asteroids += 1;
//		}
//		
//
//
//	}
//
//	if (asteroids.number_of_asteroids > 0) {
//		for (int i = 0; i < asteroids.number_of_asteroids; i++) {
//
//			vector2 normalised = asteroids.asteroids[i].direction;
//			asteroids.asteroids[i].transform.position.x += normalised.x * asteroids.asteroids[i].speed * delta_time;
//			asteroids.asteroids[i].transform.position.y += normalised.y * asteroids.asteroids[i].speed * delta_time;
//			//printf(" bullet normalise: %f , %f. angle: %f\n", normalised.x, normalised.y, rad);
//
//			float x = asteroids.asteroids[i].transform.position.x;
//			float y = asteroids.asteroids[i].transform.position.y;
//
//			
//			//printf("move astroid %f , %f\n" ,x,y);
//			//if a bullet it out of bounds
//			if (x < -1.5 || x>1.5 || y > 1.5 || y < -1.5) {
//				printf("delete astroid\n");
//				for (int j = i + 1; j < asteroids.number_of_asteroids; j++) {
//					asteroids.asteroids[j - 1] = asteroids.asteroids[j];
//				}
//				asteroids.number_of_asteroids -= 1;
//
//				if (asteroids.number_of_asteroids == 0) {
//					if (asteroids.wave != asteroids.max_wave) {
//						asteroids.wave += 1;
//					}
//					asteroids.create_more_asteroids = true;
//				}
//				if (i != 0) {
//					i -= 1;
//				}
//				else {
//					return;
//				}
//
//				
//			}
//		}
//	}
//}
//
//void near_wall() {
//
//	ship.bottom_wall = false;
//	ship.top_wall = false;
//	ship.right_wall = false;
//	ship.left_wall = false;
//
//	//outer most points of the triangle ship
//	vector2 point1, point2, point3;
//
//	point1.x = ship.transform.position.x + ship.points[0].x;
//	point1.y = ship.transform.position.y + ship.points[0].y;
//
//	point2.x = ship.transform.position.x + ship.points[2].x;
//	point2.y = ship.transform.position.y + ship.points[2].y;
//
//	point3.x = ship.transform.position.x + ship.points[3].x;
//	point3.y = ship.transform.position.y + ship.points[3].y;
//
//	check_wall(point1);
//	check_wall(point2);
//	check_wall(point3);
//
//}
//
//collection_of_bullets delete_bullet(collection_of_bullets b, int index) {
//	for (int i = index + 1; i < b.number_of_bullets; i++) {
//		b.bullets[i - 1] = b.bullets[i];
//	}
//	b.number_of_bullets -= 1;
//	return b;
//}
//
//void update_bullets() 
//{
//	if (bullets.active == true) 
//	{
//		if (bullets.add_new_bullet == true) 
//		{
//			bullets.time_between_bullets += delta_time;
//			if (bullets.number_of_bullets < MAX_BULLETS && bullets.time_between_bullets>bullets.fire_rate) 
//			{
//				printf("create new bullet\n");
//				bullet new_bullet;
//				new_bullet.speed = 0.001;
//				new_bullet.transform = ship.transform;
//				new_bullet.active = true;
//				bullets.bullets[bullets.number_of_bullets] = new_bullet;
//				bullets.number_of_bullets += 1;
//				bullets.time_between_bullets = 0;
//			}
//		}
//		if (bullets.number_of_bullets > 0) {
//			for (int i = 0; i < bullets.number_of_bullets; i++)
//			{
//				float rad = degree_to_rad(bullets.bullets[i].transform.rotation + 90);
//				vector2 normalised = rad_angle_to_direction(rad);
//				bullets.bullets[i].transform.position.x += normalised.x * bullets.bullets[i].speed * delta_time;
//				bullets.bullets[i].transform.position.y += normalised.y * bullets.bullets[i].speed * delta_time;
//				//printf(" bullet normalise: %f , %f. angle: %f\n", normalised.x, normalised.y, rad);
//
//				float x = bullets.bullets[i].transform.position.x;
//				float y = bullets.bullets[i].transform.position.y;
//
//				//if a bullet it out of bounds
//				if (x < -1 || x>1 || y > 1 || y < -1) {
//					printf("delete bullet\n");
//					bullets = delete_bullet(bullets, i);
//					if (i != 0) {
//						i -= 1;
//					}
//					else {
//						return;
//					}
//					
//				}
//
//			}
//		}
//	}
//}
//
//
//void update_game_state()
//{
//	delta_time = glutGet(GLUT_ELAPSED_TIME) - total_time;
//	total_time = glutGet(GLUT_ELAPSED_TIME);
//	
//
//	ship_movement();
//	near_wall();
//	update_bullets();
//	update_astroids();
//
//}
//
//void on_idle()
//{
//	update_game_state();
//	glutPostRedisplay();
//}
//
//void on_key_press(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case 'w':
//		//ship.transform.position.y += 0.05;
//		ship.move_up = true;
//		break;
//	case 'a':
//		ship.turn_left = true;
//		break;
//	case 's':
//		ship.move_down = true;
//		break;
//	case 'd':
//		ship.turn_right = true;
//		break;
//	case KEY_ESC:
//	case 'q':
//		end_app();
//		break;
//	default:
//		break;
//	}
//}
//
//void on_special_key_press(int key, int x, int y)
//{
//}
//
//void on_key_release(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case 'w':
//		//ship.transform.position.y += 0.05;
//		ship.move_up = false;
//		break;
//	case 'a':
//		ship.turn_left = false;
//		break;
//	case 's':
//		ship.move_down = false;
//		break;
//	case 'd':
//		ship.turn_right = false;
//		break;
//	default:
//		break;
//	}
//}
//
//void on_special_key_release(int key, int x, int y)
//{
//}
//
//void on_mouse_button(int button, int state, int x, int y)
//{
//	if (button == GLUT_LEFT_BUTTON) {
//		printf("left mouse click!\n");
//		bullets.active = true;
//		if (bullets.add_new_bullet == true) {
//			bullets.add_new_bullet = false;
//			printf("no bullets\n");
//		}
//		else {
//			bullets.add_new_bullet = true;
//			bullets.time_between_bullets = bullets.fire_rate;
//			printf("new bullets\n");
//		}
//		//bullets.add_new_bullet = true;
//
//	}
//}
//
//void on_mouse_move(int x, int y)
//{
//
//}
//
//void on_mouse_drag(int x, int y)
//{
//}

void on_reshape(int w, int h)
{
	g_mainwin.width = w;
	g_mainwin.height = h;

	const float half_world_size = world_size;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		float aspect = (float)h / (float)w;
		glOrtho(-half_world_size, half_world_size, -half_world_size * aspect, half_world_size * aspect, -half_world_size, half_world_size);
	}
	else
	{
		float aspect = (float)w / (float)h;
		glOrtho(-half_world_size * aspect, half_world_size * aspect, -half_world_size, half_world_size, -half_world_size, half_world_size);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init_app(int* argcp, char** argv, window_t* mainwinp)
{
	// GLUT & OpenGL setup
	glutInit(argcp, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// Display related setup
	glutInitWindowPosition(mainwinp->x_pos, mainwinp->y_pos);
	glutInitWindowSize(mainwinp->width, mainwinp->height);
	glutCreateWindow(GAME_TITLE);

	if (mainwinp->is_fullscreen == true)
	{
		glutFullScreen();
	}

	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);

	// Keyboard and Mouse related setup
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(on_key_press);
	glutSpecialFunc(on_special_key_press);
	glutKeyboardUpFunc(on_key_release);
	glutSpecialUpFunc(on_special_key_release);
	glutMouseFunc(on_mouse_button);
	
	glutPassiveMotionFunc(on_mouse_move);
	glutMotionFunc(on_mouse_drag);

	// Define the idle function
	glutIdleFunc(on_idle);
}

void run_app()
{
	/*g_rand_circles[0] = init_circle(10.0f, 10.0f, 5.0f);
	g_rand_circles[1] = init_circle(-10.0f, 10.0f, 4.0f);
	g_rand_circles[2] = init_circle(-10.0f, -10.0f, 3.0f);
	g_rand_circles[3] = init_circle(10.0f, -10.0f, 2.0f);
	g_rand_circles[4] = init_circle(0.0f, 0.0f, 0.1f);
	g_user_circle = init_circle(0.0f, 0.0f, 3.0f);*/


	setup_game();
	glutMainLoop();
}

void load_config(int* argcp, char** argv, window_t* mainwin_p)
{
	mainwin_p->width = 1024;
	mainwin_p->height = 768;
	mainwin_p->is_fullscreen = false;
}

int main(int argc, char** argv)
{
	load_config(&argc, argv, &g_mainwin);
	init_app(&argc, argv, &g_mainwin);
	run_app();
	return (EXIT_SUCCESS);
}

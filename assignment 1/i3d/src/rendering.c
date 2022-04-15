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

#ifndef Z_LAYER
#define Z_LAYER 0
#endif

void render_asteroids() {

	if (asteroids.number_of_asteroids > 0) {
		for (int i = 0; i < asteroids.number_of_asteroids; i++) {
			glPushMatrix();
			glLoadIdentity();
			circle_t c;
			c.pos_x = asteroids.asteroids[i].transform.position.x;
			c.pos_y = asteroids.asteroids[i].transform.position.y;
			c.radius = asteroids.asteroids[i].point.radius;

			render_circle(c, 1, 0, 1);
			glPopMatrix();
		}
	}
}

void render_string(float x, float y, void* font, const char* string)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// Set the projection - use this to render text
	gluOrtho2D(0, g_mainwin.width, 0, g_mainwin.height);
	glMatrixMode(GL_MODELVIEW);

	glRasterPos2f(x, y);
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}

	glMatrixMode(GL_PROJECTION);

	// Restore the original projection matrix for rendering everything else
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}

void render_ship() {

	glPushMatrix();
	glLoadIdentity();

	//tranformation
	glTranslatef(ship.transform.position.x, ship.transform.position.y, 0.0f);
	glRotatef(ship.transform.rotation, 0.0f, 0.0f, 1.0f);
	glScalef(1, 1, 1);

	//render the trianges
	glBegin(GL_POLYGON);
	glColor3f(ship.fill_colour.r, ship.fill_colour.g, ship.fill_colour.b);
	glVertex3f(ship.points[0].x, ship.points[0].y, ship.points[0].z);
	glVertex3f(ship.points[1].x, ship.points[1].y, ship.points[1].z);
	glVertex3f(ship.points[2].x, ship.points[2].y, ship.points[2].z);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(ship.fill_colour.r, ship.fill_colour.g, ship.fill_colour.b);
	glVertex3f(ship.points[3].x, ship.points[3].y, ship.points[3].z);
	glVertex3f(ship.points[4].x, ship.points[4].y, ship.points[4].z);
	glVertex3f(ship.points[5].x, ship.points[5].y, ship.points[5].z);
	glEnd();

	//render the outline

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	//glLineWidth(2.0);
	glVertex3f(ship.points[0].x, ship.points[0].y, ship.points[0].z);
	glVertex3f(ship.points[1].x, ship.points[1].y, ship.points[1].z);
	glVertex3f(ship.points[2].x, ship.points[2].y, ship.points[2].z);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex3f(ship.points[1].x, ship.points[1].y, ship.points[1].z);
	glVertex3f(ship.points[2].x, ship.points[2].y, ship.points[2].z);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex3f(ship.points[3].x, ship.points[3].y, ship.points[3].z);
	glVertex3f(ship.points[2].x, ship.points[2].y, ship.points[2].z);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex3f(ship.points[3].x, ship.points[3].y, ship.points[3].z);
	glVertex3f(ship.points[4].x, ship.points[4].y, ship.points[4].z);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex3f(ship.points[4].x, ship.points[4].y, ship.points[4].z);
	glVertex3f(ship.points[5].x, ship.points[5].y, ship.points[5].z);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex3f(ship.points[0].x, ship.points[0].y, ship.points[0].z);
	glVertex3f(ship.points[2].x, ship.points[2].y, ship.points[2].z);
	glEnd();

	//ship gun
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.4, 0.1);
	glVertex3f(0.025, 0, 1);
	glVertex3f(0.025, -0.05, 1);
	glVertex3f(-0.025, -0.05, 1);
	glVertex3f(-0.025, 0, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.4, 0.1);
	glVertex3f(0.01, 0, 1);
	glVertex3f(0.01, 0.01, 1);
	glVertex3f(-0.01, 0.01, 1);
	glVertex3f(-0.01, 0.0, 1);
	glEnd();


	//// this is just so we can see where its pointing
	//glBegin(GL_LINES);
	//glColor3f(1.0, 1.0, 0.0);
	//glVertex3f(0, 0, 0.0);
	//glVertex3f(0, 0.1, 0.0);
	//glEnd();


	glPopMatrix();

	//circle_t c;
	//c.pos_x = ship.bounds.origin.x;
	//c.pos_y = ship.bounds.origin.y;
	//c.radius = ship.bounds.radius;

	//render_circle(c, 0, 0, 1);
}

void render_bullets() {

	if (bullets.active == true && bullets.number_of_bullets != 0)
	{
		for (int i = 0; i < bullets.number_of_bullets; i++)
		{
			//printf("create bullets!!\n");
			glPushMatrix();
			glLoadIdentity();
			circle_t c;
			c.radius = bullets.bullets[i].radius;
			c.pos_x = bullets.bullets[i].transform.position.x;
			c.pos_y = bullets.bullets[i].transform.position.y;
			render_circle_rotation(c, 0, 0.8, 0, ship.transform.rotation);

			glPopMatrix();

		}
	}

}

void render_wall() {
	glPushMatrix();
	glLoadIdentity();


	glBegin(GL_POLYGON);
	//glColor3f(wall.fill_colour.r, wall.fill_colour.g, wall.fill_colour.b);
	glColor3f(wall.fill_colour.r, wall.fill_colour.g, wall.fill_colour.b);
	//glLineWidth(20.0);
	glVertex3f(wall.points[0].x, wall.points[0].y, wall.points[0].z);
	glVertex3f(wall.points[1].x, wall.points[1].y, wall.points[1].z);
	glVertex3f(wall.points[2].x, wall.points[2].y, wall.points[2].z);
	glVertex3f(wall.points[3].x, wall.points[3].y, wall.points[3].z);

	glEnd();

	//bottom wall
	glBegin(GL_LINES);
	if (ship.bottom_wall)
	{
		glColor3f(1, 0, 0);
	}
	else
	{
		glColor3f(wall.outline_colour.r, wall.outline_colour.g, wall.outline_colour.b);
	}
	//GLfloat gl
	//glLineWidth((GLfloat)20.0);
	glVertex3f(wall.points[0].x, wall.points[0].y, wall.points[0].z);
	glVertex3f(wall.points[1].x, wall.points[1].y, wall.points[1].z);
	glEnd();

	//right wall
	glBegin(GL_LINES);
	if (ship.right_wall)
	{
		glColor3f(1, 0, 0);
	}
	else
	{
		glColor3f(wall.outline_colour.r, wall.outline_colour.g, wall.outline_colour.b);
	}
	glVertex3f(wall.points[2].x, wall.points[2].y, wall.points[2].z);
	glVertex3f(wall.points[1].x, wall.points[1].y, wall.points[1].z);
	glEnd();

	//top wall
	glBegin(GL_LINES);
	if (ship.top_wall)
	{
		glColor3f(1, 0, 0);
	}
	else
	{
		glColor3f(wall.outline_colour.r, wall.outline_colour.g, wall.outline_colour.b);
	}
	glVertex3f(wall.points[2].x, wall.points[2].y, wall.points[2].z);
	glVertex3f(wall.points[3].x, wall.points[3].y, wall.points[3].z);
	glEnd();

	//left wall
	glBegin(GL_LINES);
	if (ship.left_wall)
	{
		glColor3f(1, 0, 0);
	}
	else
	{
		glColor3f(wall.outline_colour.r, wall.outline_colour.g, wall.outline_colour.b);
	}
	glVertex3f(wall.points[0].x, wall.points[0].y, wall.points[0].z);
	glVertex3f(wall.points[3].x, wall.points[3].y, wall.points[3].z);
	glEnd();


	glPopMatrix();
}

int detect_overlap(circle_t c1, circle_t c2)
{
	const float dx = c2.pos_x - c1.pos_x;
	const float dy = c2.pos_y - c1.pos_y;
	const float radii = c1.radius + c2.radius;

	if ((radii * radii) <= (dx * dx) + (dy * dy))
	{
		return 0;
	}

	return 1;
}

// See circle.c from Week 2 material
void draw_circle_cartesian(float r, int n)
{
	float x, y;

	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);

	n /= 2;

	for (int i = 0; i < n; i++)
	{
		x = ((i / (float)n - 0.5) * 2.0) * r;
		y = sqrt(r * r - x * x);
		glVertex2f(x, y);
	}

	for (int i = n; i > 0; i--)
	{
		x = (i / (float)n - 0.5) * 2.0 * r;
		y = -sqrt(r * r - x * x);
		glVertex2f(x, y);
	}

	glEnd();
}

void render_circle_rotation(circle_t circle, float cr, float cg, float cb, float rotation)
{
	glPushMatrix();
	glLoadIdentity();
	
	glTranslatef(circle.pos_x, circle.pos_y, 0.0f);
	glRotatef(rotation + degree_to_rad(90), 0.0f, 0.0f, 1.0f);
	//glrotationf(rotation, 0.0f, 0.0f, 1.0f);
	glScalef(circle.radius, circle.radius, 1.0f);
	glColor3f(cr, cg, cb);
	// draw a unit circle
	draw_circle_cartesian(1.0, 64);
	glPopMatrix();
}

void render_circle(circle_t circle, float cr, float cg, float cb)
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(circle.pos_x, circle.pos_y, 0.0f);
	glScalef(circle.radius, circle.radius, 1.0f);
	glColor3f(cr, cg, cb);
	// draw a unit circle
	draw_circle_cartesian(1.0, 64);
	glPopMatrix();
}

void render_launch_position() {
	circle_t c;
	c.radius = asteroids.lauch_radius;
	c.pos_x = 0;
	c.pos_y = 0;
	render_circle(c, 1, 0, 0);
}



void render_frame()
{
	render_wall();
	render_ship();
	//render_circle(g_rand_circles[4], 1.0f, 0.0f, 0.0f);
	render_asteroids();
	render_bullets();
	render_launch_position();

	//glPushMatrix();
	//glLoadIdentity();

	//glPointSize(2.0);
	/*glBegin(GL_POINT);
	glColor3f(1, 1, 0);
	glVertex2f(0.5, 0.5);
	glEnd();

	glPopMatrix();*/

}

void on_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	render_frame();

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("error: %s\n", gluErrorString(err));
	}

	glutSwapBuffers();
}
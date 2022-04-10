#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

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

#define GAME_TITLE "Asteroid Arena"
#define KEY_ESC 27

//typedef struct Windows
//{
//	int width, height, x_pos, y_pos;
//	bool is_fullscreen;
//} window_t;

typedef struct Colour
{
	float r, g, b;
} colour;

typedef struct Vector3
{
	float x, y, z;

} vector3;

typedef struct Vector2
{
	float x, y;

} vector2;

typedef struct Point
{
	float x, y, z;

} point;

typedef struct Circle {
	vector2 origin;
	float radius;
} circle;

typedef struct Transform
{
	vector3 position;
	float rotation;
	vector3 scale;

} transform2d;

typedef struct Player {
	vector3 points[6];
	int number_of_points;
	transform2d transform;
	circle bounds;
	colour outline_colour;
	colour fill_colour;
	float speed;
	bool move_up;
	bool move_down;
	bool turn_left;
	bool turn_right;
} player;

typedef struct Asteroid {
	//vector3 points[6];
	int number_of_points;
	transform2d transform;
	circle bounds;
	colour outline_colour;
	colour fill_colour;
} asteroid;



typedef struct Wall {
	vector3 points[4];
	int number_of_points;
	colour outline_colour;
	colour fill_colour;
} wall2d;

typedef struct
{
	int width, height, x_pos, y_pos;
	bool is_fullscreen;
} window_t;

typedef struct
{
	float pos_x;
	float pos_y;
	float radius;
} circle_t;

circle_t g_rand_circles[5];
circle_t g_user_circle;
window_t g_mainwin;
float world_size = 1.0f;

player ship;
asteroid ast;
wall2d wall;
int total_time;
int delta_time;

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

circle_t init_circle(float posX, float posY, float radius)
{
	circle_t circle;

	circle.pos_x = posX;
	circle.pos_y = posY;
	circle.radius = radius;

	return circle;
}

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
	ship.fill_colour.r = 0.3;
	ship.fill_colour.g = 0.3;
	ship.fill_colour.b = 0;

	//outline colour is red
	ship.outline_colour.r = 232 / 255;
	ship.outline_colour.g = 72 / 255;
	ship.outline_colour.b = 85 / 255;

	ship.bounds.origin.x = 0;
	ship.bounds.origin.y = 0;
	ship.bounds.radius = 0.5; 

	ship.move_down = false;
	ship.move_up = false;
	ship.turn_left = false;
	ship.turn_right = false;

}

void create_asteroid() {

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

	wall.fill_colour.r = 64 / 255;
	wall.fill_colour.g = 63 / 255;
	wall.fill_colour.b = 76 / 255;

	wall.outline_colour.r = 49 / 255;
	wall.outline_colour.g = 133 / 255;
	wall.outline_colour.b = 252 / 255;


	/*	glColor3f(0, 0.05, 0.09);
	glBegin(GL_POLYGON);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glEnd();*/

}

void setup_game() {

	create_ship();
	create_wall();
	delta_time = 0;
	total_time = 0;
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

	// this is just so we can see where its pointing
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0, 0, 0.0);
	glVertex3f(0, 0.1, 0.0);
	glEnd();


	glPopMatrix();

	circle_t c;
	c.pos_x = ship.bounds.origin.x;
	c.pos_y = ship.bounds.origin.y;
	c.radius = ship.bounds.radius;

	//render_circle(c, 0, 0, 1);
}

void render_wall() {
	glPushMatrix();
	glLoadIdentity();
	

	glBegin(GL_POLYGON);
	//glColor3f(wall.fill_colour.r, wall.fill_colour.g, wall.fill_colour.b);
	glColor3f(0.4, 0.4, 0.4);
	//glLineWidth(200.0);
	glVertex3f(wall.points[0].x, wall.points[0].y, wall.points[0].z);
	glVertex3f(wall.points[1].x, wall.points[1].y, wall.points[1].z);
	glVertex3f(wall.points[2].x, wall.points[2].y, wall.points[2].z);
	glVertex3f(wall.points[3].x, wall.points[3].y, wall.points[3].z);
	/*glVertex3f(-1, -1, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(-1, 1, 0);*/
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	//glLineWidth(200.0);
	glVertex3f(wall.points[0].x, wall.points[0].y, wall.points[0].z);
	glVertex3f(wall.points[1].x, wall.points[1].y, wall.points[1].z);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex3f(wall.points[2].x, wall.points[2].y, wall.points[2].z);
	glVertex3f(wall.points[1].x, wall.points[1].y, wall.points[1].z);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex3f(wall.points[2].x, wall.points[2].y, wall.points[2].z);
	glVertex3f(wall.points[3].x, wall.points[3].y, wall.points[3].z);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
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

void end_app()
{
	exit(EXIT_SUCCESS);
}

void render_frame()
{
	render_wall();
	render_ship();
	render_circle(g_rand_circles[4], 1.0f, 0.0f, 0.0f);
	/*int is_main_collided = 0;

	for (int i = 0; i < 5; i++)
	{
		int is_collided = detect_overlap(g_user_circle, g_rand_circles[i]);

		if (is_collided > 0)
		{
			render_circle(g_rand_circles[i], 1.0f, 0.0f, 0.0f);
		}
		else
		{
			render_circle(g_rand_circles[i], 0.0f, 1.0f, 0.0f);
		}

		is_main_collided += is_collided;
	}

	if (is_main_collided > 0)
	{
		render_circle(g_user_circle, 1.0f, 0.0f, 0.0f);
	}
	else
	{
		render_circle(g_user_circle, 0.0f, 1.0f, 0.0f);
	}*/
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

void update_game_state()
{
	delta_time = glutGet(GLUT_ELAPSED_TIME) - total_time;
	total_time = glutGet(GLUT_ELAPSED_TIME); 


	if (ship.move_up) {
		ship.transform.position.y += 0.001;
	}
	else if (ship.move_down) {
		ship.transform.position.y -= 0.001;
	}
	else if (ship.turn_left) {
		ship.transform.rotation -= 1;
	}
	else if (ship.turn_right) {
		ship.transform.rotation += 1;
	}

}



void on_idle()
{
	update_game_state();
	glutPostRedisplay();
}

void on_key_press(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		//ship.transform.position.y += 0.05;
		ship.move_up = true;
		break;
	case 'a':
		ship.turn_right = true;
		break;
	case 's':
		ship.move_down = true;
		break;
	case 'd':
		ship.turn_left = true;
		break;
	case KEY_ESC:
	case 'q':
		end_app();
		break;
	default:
		break;
	}
}

void on_special_key_press(int key, int x, int y)
{
}

void on_key_release(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		//ship.transform.position.y += 0.05;
		ship.move_up = false;
		break;
	case 'a':
		ship.turn_right = false;
		break;
	case 's':
		ship.move_down = false;
		break;
	case 'd':
		ship.turn_left = false;
		break;
	default:
		break;
	}
}

void on_special_key_release(int key, int x, int y)
{
}

void on_mouse_button(int button, int state, int x, int y)
{
}

void on_mouse_move(int x, int y)
{
	// map between screen coordinates to our current world size
	// HINT: an additional step is needed to do this mapping correctly :)
	// for students to figure out (if needed)
	//float mx = map(x, 0.0, g_mainwin.width, -world_size / 2.0, world_size / 2.0);
	//float my = map(y, 0.0, g_mainwin.height, -world_size / 2.0, world_size / 2.0);
	//g_user_circle.pos_x = mx;
	//g_user_circle.pos_y = -my;
}

void on_mouse_drag(int x, int y)
{
}

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
	g_rand_circles[0] = init_circle(10.0f, 10.0f, 5.0f);
	g_rand_circles[1] = init_circle(-10.0f, 10.0f, 4.0f);
	g_rand_circles[2] = init_circle(-10.0f, -10.0f, 3.0f);
	g_rand_circles[3] = init_circle(10.0f, -10.0f, 2.0f);
	g_rand_circles[4] = init_circle(0.0f, 0.0f, 0.1f);
	g_user_circle = init_circle(0.0f, 0.0f, 3.0f);


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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

#define GAME_TITLE "Asteroid Arena"
#define KEY_ESC 27

typedef struct Windows
{
	int width, height, x_pos, y_pos;
	bool is_fullscreen;
} window_t;

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



window_t g_mainwin;
player ship;
asteroid ast;
wall2d wall;

void create_ship() {

	//set up ship

	ship.transform.scale.x=1;
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
	ship.outline_colour.r = 232/255;
	ship.outline_colour.g = 72/255;
	ship.outline_colour.b = 85/255;
	
	ship.bounds.origin.x=0;
	ship.bounds.origin.y = 0;
	ship.bounds.radius = 0.5;

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

	wall.fill_colour.r = 64/255;
	wall.fill_colour.g = 63/255;
	wall.fill_colour.b = 76/255;

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
}


bool detect_overlap(circle c1, circle c2)
{
	const float dx = c2.origin.x - c1.origin.y;
	const float dy = c2.origin.x - c1.origin.y;
	const float combine_radius = c1.radius + c2.radius;

	if ((combine_radius * combine_radius) <= (dx * dx) + (dy * dy))
	{
		return false;
	}

	return true;
}

void end_app()
{
	exit(EXIT_SUCCESS);
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

void render_circle(circle circle1, float cr, float cg, float cb)
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(circle1.origin.x, circle1.origin.y, 0.0f);
	glScalef(circle1.radius, circle1.radius, 1.0f);
	glColor3f(cr, cg, cb);
	// draw a unit circle
	draw_circle_cartesian(1.0, 64);
	glPopMatrix();
}

void render_ship() {

	glPushMatrix();
	glLoadIdentity();

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

	render_circle(ship.bounds, 0, 0, 1);
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


void render_frame()
{
	render_wall();
	render_ship();
	// arena

	//dark blue
	//glColor3f(0, 0.05, 0.09);
	//glBegin(GL_POLYGON);
	//glVertex3f(-1, -1, -1);
	//glVertex3f(1, -1, -1);
	//glVertex3f(1, 1, -1);
	//glVertex3f(-1, 1, -1);
	//glEnd();

	//player
	//glColor3f(0.9, 0.1, 0.9);
	//glBegin(GL_POLYGON);
	//glVertex3f(-0.1, -0.1, -1);
	//glVertex3f(0, 0, -1);
	//glVertex3f(0, 0.1, -1);
	//glEnd();

	//glColor3f(0.9, 0.1, 0.9);
	//glBegin(GL_POLYGON);
	//glVertex3f(0, 0.1, -1);
	//glVertex3f(0.1, -0.1, -1);
	//glVertex3f(0, 0, -1);
	//glEnd();

	//lec3();

	//glVertex3f(-0.1, -0.1, -1);
	
	

	//// Red quad
	//glColor3f(1.0, 0.0, 0.0);
	//glBegin(GL_POLYGON);
	//glVertex3f(-0.5, -0.5, -0.5);
	//glVertex3f(0.5, -0.5, -0.5);
	//glVertex3f(0.5, 0.5, -0.5);
	//glVertex3f(-0.5, 0.5, -0.5);
	//glEnd();

	//// Green quad
	//glColor3f(0.0, 1.0, 0.0);
	//glBegin(GL_POLYGON);
	//glVertex3f(-0.25, -0.25, -0.75);
	//glVertex3f(0.75, -0.25, -0.75);
	//glVertex3f(0.75, 0.75, -0.75);
	//glVertex3f(-0.25, 0.75, -0.75);
	//glEnd();

	//glColor3f(1.0, 1.0, 1.0);
	//// render our string in center of window
	//render_string(g_mainwin.width / 2.0, g_mainwin.height / 2.0, GLUT_BITMAP_TIMES_ROMAN_24, "The quick brown fox jumps");
	//render_string(g_mainwin.width / 2.0, (g_mainwin.height / 2.0) - 25, GLUT_BITMAP_TIMES_ROMAN_24, "over the lazy dog");


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
}

void on_special_key_release(int key, int x, int y)
{
}

void on_mouse_button(int button, int state, int x, int y)
{
}

void on_mouse_move(int x, int y)
{
}

void on_mouse_drag(int x, int y)
{
}

void on_reshape(int w, int h)
{
	g_mainwin.width = w;
	g_mainwin.height = h;


	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		float aspect = (float)h / (float)w;
		glOrtho(-1.0, 1.0, -1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
	}
	else
	{
		float aspect = (float)w / (float)h;
		glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -1.0, 1.0);
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
	setup_game();
	run_app();
	return (EXIT_SUCCESS);
}

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

#ifndef KEY_ESC
#define KEY_ESC 27
#endif

bool mouseleft = false;

void on_key_press(unsigned char key, int x, int y)
{
	
	
		switch (key)
		{
		case 'w':
			printf("press w \n");
			//ship.transform.position.y += 0.05;
			ship.move_foward = true;
			break;
		case 'a':
			printf("press a \n");
			ship.turn_left = true;
			break;
		case 's':
			printf("press s \n");
			ship.move_back = true;
			break;
		case 'd':
			printf("press d \n");
			ship.turn_right = true;
			break;
		case 'q':
			printf("press q \n");
			ship.move_up = true;
			break;
		case 'e':
			printf("press e \n");
			ship.move_down = true;
			break;
		case 'x':
			printf("press x \n");
			if (cam_foward > 5) {
				cam_foward -= delta_time * 0.01;
			}
			
			break;
		case 'z':
			cam_foward += delta_time * 0.01;
			break;
		case KEY_ESC:
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
	printf("press relasse key \n");
	switch (key)
	{
	case 'w':
		//ship.transform.position.y += 0.05;
		ship.move_foward = false;
		break;
	case 'a':
		ship.turn_left = false;
		break;
	case 's':
		ship.move_back = false;
		break;
	case 'd':
		ship.turn_right = false;
		break;
	case 'q':
		ship.move_up = false;
		break;
	case 'e':
		ship.move_down = false;
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
	if (button == GLUT_LEFT_BUTTON) {
		printf("left mouse click!\n");
		bullets.active = true;
		if (mouseleft) {
			bullets.add_new_bullet = false;
			printf("no bullets\n");
			mouseleft = false;
		}
		else {
			mouseleft = true;
			bullets.add_new_bullet = true;
			bullets.time_between_bullets = 0;
			printf("new bullets\n");
		}
		//bullets.add_new_bullet = true;

	}
	else if (button == GLUT_RIGHT_BUTTON) {
		printf("right mouse");
		if (ship.move_foward) {
			ship.move_foward = false;
		}
		else {
			ship.move_foward = true;
		}
		//ship.move_foward = !ship.move_foward;
	}
}

void end_app()
{
	exit(EXIT_SUCCESS);
}

void on_mouse_move(int x, int y)
{

}

void on_mouse_drag(int x, int y)
{
}

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



void ship_movement() {
	float rotation = 0.5 * delta_time;
	

	if (ship.turn_left)
	{
		ship.transform.rotation += rotation;
	} 
	else if (ship.turn_right)
	{
		ship.transform.rotation -= rotation;
	} 
	else if (ship.move_up)
	{
		move_up(true);
	} 
	else if (ship.move_down)
	{
		move_down(true);
		
	}
	else {
		if (ship.speed > ship.min_speed) {
			if (ship.last_move_up) {
				move_up(false);
			}
			else {
				move_down(false);
			}
		}
	}
}

void decrease_speed() 
{
	if (ship.speed > ship.min_speed) {
		float decrease_speed = ship.speed / 7;
		ship.speed -= decrease_speed;
	}
}

void increase_speed() {
	if (ship.speed < ship.max_speed) {
		float inxrease_speed = ship.speed / 15;
		ship.speed += inxrease_speed;
	}
}

void move_down(bool increase)
{
	float rad = degree_to_rad(ship.transform.rotation + 90);
	vector2 normalised = rad_angle_to_direction(rad);
	if (increase) 
	{
		increase_speed();
	}
	else 
	{
		decrease_speed();
	}
	
	ship.transform.position.x -= normalised.x * ship.speed * delta_time;
	ship.transform.position.y -= normalised.y * ship.speed * delta_time;
	ship.last_move_up = false;
}

void move_up(bool increase)
{
	
	float rad = degree_to_rad(ship.transform.rotation + 90);
	vector2 normalised = rad_angle_to_direction(rad);

	if (increase)
	{
		increase_speed();
	}
	else
	{
		decrease_speed();
	}

	ship.transform.position.x += normalised.x * ship.speed * delta_time;
	ship.transform.position.y += normalised.y * ship.speed * delta_time;
	ship.last_move_up = true;
}



void reset_player() {
	ship.transform.rotation = 0;

	ship.transform.position.x = 0;
	ship.transform.position.y = 0;

	ship.transform.position.x = 0;
	ship.bottom_wall = false;
	ship.top_wall = false;
	ship.right_wall = false;
	ship.left_wall = false;
	
	//asteroids.create_more_asteroids = true;

}

void check_wall(vector2 point) {

	if (point.x < -0.9) {
		ship.left_wall = true;
	}

	if (point.x > 0.8) {
		ship.right_wall = true;
	}

	if (point.y > 0.9) {
		ship.top_wall = true;
	}

	if (point.y < -0.9) {
		ship.bottom_wall = true;
	}

	if (point.y < -1) {
		reset_player();
	}

	if (point.y > 1) {
		reset_player();
	}

	if (point.x > 0.95) {
		reset_player();
	}

	if (point.x < -1) {
		reset_player();
	}
}

void initialise_random()
{
	rand();
	rand();
}

void create_new__asteroid(int i)
{
	srand(time(0) + i);
	printf("create asteroid!\n");
	asteroid new_astreroid;
	int max_number = 360;
	int minimum_number = 0;

	//this is so we get some good vaules for rand 
	//i find the first few can see quite smiliar
	initialise_random();
	int degree = rand() % (max_number + 1 - minimum_number) + minimum_number;
	//printf("degree %f\n", degree);
	float rad = degree_to_rad(degree);

	vector2 normalised = rad_angle_to_direction(rad);

	new_astreroid.transform.position.x = normalised.x * asteroids.lauch_radius;
	new_astreroid.transform.position.y = normalised.y * asteroids.lauch_radius;
	new_astreroid.transform.position.z = 1;

	int min_speed = 10;
	int max_speed = 100;
	int speed = rand() % (max_speed + 1 - min_speed) + min_speed;
	new_astreroid.speed = (float)speed / 100000.0f;
	printf("speed %f\n", new_astreroid.speed);
	circle c;
	c.origin.x = 0;
	c.origin.y = 0;
	int min_radius = 5;
	int max_radius = 100;
	int radius = rand() % (max_radius + 1 - min_radius) + min_radius;

	c.radius = (float)radius / 1000;


	new_astreroid.point = c;
	printf("radius %f\n", new_astreroid.point.radius);

	vector2 ship_to_local_world = vector_subtraction(vector3_to_vector2(ship.transform.position),
		vector3_to_vector2(new_astreroid.transform.position));
	new_astreroid.direction = vector_normalise(ship_to_local_world);

	asteroids.asteroids[asteroids.number_of_asteroids] = new_astreroid;
	asteroids.number_of_asteroids += 1;
}

void update_astroids() {

	if (asteroids.create_more_asteroids == true) {
		asteroids.create_more_asteroids = false;
		for (int i = 0; i < asteroids.wave; i++) {
			create_new__asteroid(i);
		}
	}

	if (asteroids.number_of_asteroids > 0) {
		for (int i = 0; i < asteroids.number_of_asteroids; i++) {

			move_asteroid(i);

			float x = asteroids.asteroids[i].transform.position.x;
			float y = asteroids.asteroids[i].transform.position.y;

			//if a bullet it out of bounds
			if (x < -2 || x>2 || y > 2 || y < -2) {
				printf("delete astroid\n");
				delete_asteroid(i);

				if (i != 0) {
					i -= 1;
				}
				else {
					return;
				}
			}
		}
	}

	if (asteroids.number_of_asteroids == 0) {
		if (asteroids.wave != asteroids.max_wave) {
			asteroids.wave += 1;
		}
		asteroids.create_more_asteroids = true;
	}
}

void delete_asteroid(int i)
{
	for (int j = i + 1; j < asteroids.number_of_asteroids; j++) {
		asteroids.asteroids[j - 1] = asteroids.asteroids[j];
	}
	asteroids.number_of_asteroids -= 1;
}

void move_asteroid(int i)
{
	vector2 normalised = asteroids.asteroids[i].direction;
	asteroids.asteroids[i].transform.position.x += normalised.x * asteroids.asteroids[i].speed * delta_time;
	asteroids.asteroids[i].transform.position.y += normalised.y * asteroids.asteroids[i].speed * delta_time;
	//printf(" bullet normalise: %f , %f. angle: %f\n", normalised.x, normalised.y, rad);
}

void near_wall() {

	ship.bottom_wall = false;
	ship.top_wall = false;
	ship.right_wall = false;
	ship.left_wall = false;

	//outer most points of the triangle ship
	vector2 point1, point2, point3;

	point1.x = ship.transform.position.x + ship.points[0].x;
	point1.y = ship.transform.position.y + ship.points[0].y;

	point2.x = ship.transform.position.x + ship.points[2].x;
	point2.y = ship.transform.position.y + ship.points[2].y;

	point3.x = ship.transform.position.x + ship.points[3].x;
	point3.y = ship.transform.position.y + ship.points[3].y;

	check_wall(point1);
	check_wall(point2);
	check_wall(point3);

}

collection_of_bullets delete_bullet(collection_of_bullets b, int index) {
	for (int i = index + 1; i < b.number_of_bullets; i++) {
		b.bullets[i - 1] = b.bullets[i];
	}
	b.number_of_bullets -= 1;
	return b;
}

void update_bullets()
{
	if (bullets.active == true)
	{
		if (bullets.add_new_bullet == true)
		{
			bullets.time_between_bullets += delta_time;
			if (bullets.number_of_bullets < MAX_BULLETS && bullets.time_between_bullets>bullets.fire_rate)
			{
				printf("create new bullet\n");
				bullet new_bullet;
				new_bullet.speed = 0.001;
				new_bullet.transform = ship.transform;
				new_bullet.radius = 0.01;
				
				new_bullet.active = true;
				bullets.bullets[bullets.number_of_bullets] = new_bullet;
				bullets.number_of_bullets += 1;
				bullets.time_between_bullets = 0;

			}
		}
		if (bullets.number_of_bullets > 0) {
			for (int i = 0; i < bullets.number_of_bullets; i++)
			{
				float rad = degree_to_rad(bullets.bullets[i].transform.rotation + 90);
				vector2 normalised = rad_angle_to_direction(rad);
				bullets.bullets[i].transform.position.x += normalised.x * bullets.bullets[i].speed * delta_time;
				bullets.bullets[i].transform.position.y += normalised.y * bullets.bullets[i].speed * delta_time;
				//printf(" bullet normalise: %f , %f. angle: %f\n", normalised.x, normalised.y, rad);

				float x = bullets.bullets[i].transform.position.x;
				float y = bullets.bullets[i].transform.position.y;

				//if a bullet it out of bounds
				if (x < -1 || x>1 || y > 1 || y < -1) {
					printf("delete bullet\n");
					bullets = delete_bullet(bullets, i);
					if (i != 0) {
						i -= 1;
					}
					else {
						return;
					}
				}
			}
		}
	}
}

void check_collisions() {

	check_player_asteroid_collision();
	check_bullet_asteroid_collision();
	
}

void check_bullet_asteroid_collision() {

	if (bullets.number_of_bullets > 0 && asteroids.number_of_asteroids > 0) {
		for (int i = 0; i < bullets.number_of_bullets; i++) {
			circle_t bullet_bounds;
			bullet_bounds.pos_x = bullets.bullets[i].transform.position.x;
			bullet_bounds.pos_y = bullets.bullets[i].transform.position.y;
			bullet_bounds.radius = bullets.bullets[i].radius;

			for (int j = 0; j < asteroids.number_of_asteroids; j++) {
				circle_t asteroid_bounds;
				asteroid_bounds.pos_x = asteroids.asteroids[j].point.origin.x + asteroids.asteroids[j].transform.position.x;
				asteroid_bounds.pos_y = asteroids.asteroids[j].point.origin.y + asteroids.asteroids[j].transform.position.y;
				asteroid_bounds.radius = asteroids.asteroids[j].point.radius;


				int overlap = detect_overlap(asteroid_bounds, bullet_bounds);
				if (overlap == 1) {
					printf("collison with asteroid and bullet!\n");

					bullets = delete_bullet(bullets, i);
					delete_asteroid(j);
					if (i != 0) {
						i -= 1;
					}
					else {
						return;
					}

					//stop checking bc this bullet and asteroid are destoried
					break;
				}
			}
		}
	}

	
}

void check_player_asteroid_collision() {

	circle_t player_bounds;
	player_bounds.pos_x = ship.bounds.origin.x+ship.transform.position.x;
	player_bounds.pos_y = ship.bounds.origin.y+ ship.transform.position.y;
	player_bounds.radius = ship.bounds.radius;
	for (int i = 0; i < asteroids.number_of_asteroids; i++) {
		circle_t asteroid_bounds;
		asteroid_bounds.pos_x = asteroids.asteroids[i].point.origin.x+ asteroids.asteroids[i].transform.position.x;
		asteroid_bounds.pos_y = asteroids.asteroids[i].point.origin.y+ asteroids.asteroids[i].transform.position.y;
		asteroid_bounds.radius = asteroids.asteroids[i].point.radius;


		int overlap = detect_overlap(asteroid_bounds, player_bounds);
		if (overlap == 1) {
			printf("collison with asteroid and player!\n");
			reset_player();
			return;
		}
	}
}


void update_game_state()
{
	delta_time = glutGet(GLUT_ELAPSED_TIME) - total_time;
	total_time = glutGet(GLUT_ELAPSED_TIME);


	ship_movement();
	near_wall();
	update_bullets();
	update_astroids();
	check_collisions();

}

void on_idle()
{
	update_game_state();
	glutPostRedisplay();
}
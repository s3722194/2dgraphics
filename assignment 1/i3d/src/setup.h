#ifndef SETUP_H
#define SETUP_H


#ifndef MAX_BULLETS
#define MAX_BULLETS 20
#endif

typedef struct Colour
{
	float r, g, b;
} colour;

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

	//track which wall its close to
	bool top_wall;
	bool bottom_wall;
	bool right_wall;
	bool left_wall;
} player;

typedef struct Asteroid {
	transform2d transform;
	circle point;
	colour outline_colour;
	colour fill_colour;
	float speed;
	vector2 direction;
} asteroid;



typedef struct Wall {
	vector3 points[4];
	int number_of_points;
	colour outline_colour;
	colour fill_colour;
} wall2d;

typedef struct Bullet {
	transform2d transform;
	bool active;
	float speed;
} bullet;

typedef struct Collection_Bullets {
	bullet bullets[20];
	int number_of_bullets;
	bool active;
	bool add_new_bullet;
	float fire_rate;
	int time_between_bullets;

} collection_of_bullets;

typedef struct Collection_Asteroid {
	int wave;
	asteroid asteroids[20];
	int number_of_asteroids;
	float lauch_radius;
	bool wave_finished;
	bool create_more_asteroids;
	int max_wave;


} collection_of_asteroids;


typedef struct
{
	float pos_x;
	float pos_y;
	float radius;
} circle_t;

typedef struct
{
	int width, height, x_pos, y_pos;
	bool is_fullscreen;
} window_t;


player ship;
collection_of_asteroids asteroids;
wall2d wall;
int total_time;
int delta_time;
collection_of_bullets bullets;
window_t g_mainwin;

void create_ship();
void create_bullets();
void create_asteroid();
void create_wall();
void setup_game();

#endif
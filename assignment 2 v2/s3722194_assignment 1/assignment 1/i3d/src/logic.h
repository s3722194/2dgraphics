#ifndef LOGIC_H
#define LOGIC_H

void ship_movement();
void move_down(bool increase);
void move_up(bool increase);
void reset_player();
void check_wall(vector2 point);
void initialise_random();
void create_new_asteroid(int i);
void update_astroids();
void delete_asteroid(int i);
void move_asteroid(int i);
void near_wall();
collection_of_bullets delete_bullet(collection_of_bullets b, int index);
void update_bullets();
void move_bullet(int i);
void create_new_bullet();
void update_game_state(); 
void on_idle();
void check_player_asteroid_collision();
void check_collisions();
void check_bullet_asteroid_collision();
void move_asteroid(int i);
void delete_asteroid(int i);
int random_range(int min_number, int max_number);
void increase_speed();
void create_new_bullet();
void move_bullet(int i);
void create_new_asteroid(int i);


#endif
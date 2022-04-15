#ifndef LOGIC_H
#define LOGIC_H

void ship_movement();
void reset_player();
void check_wall(vector2 point);
void update_astroids();
void near_wall();
collection_of_bullets delete_bullet(collection_of_bullets b, int index);
void update_bullets();
void update_game_state(); 
void on_idle();

#endif
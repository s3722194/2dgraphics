#ifndef RENDER_H
#define RENDER_H

void render_asteroids();
void render_string(float x, float y, void* font, const char* string);
void render_ship();
void render_gun();
void render_bullets();
void render_wall();
int detect_overlap(circle_t c1, circle_t c2);
void draw_circle_cartesian(float r, int n);
void render_circle(circle_t circle, float cr, float cg, float cb);
void render_launch_position();
void render_frame();
void on_display();
void render_circle_rotation(circle_t circle, float cr, float cg, float cb, float rotation);
void render_UI();
void render_asteroid_shape(int i, float r, float g, float b);

#endif
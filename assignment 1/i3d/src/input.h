#ifndef INPUT_H
#define INPUT_H

void on_key_press(unsigned char key, int x, int y);
void on_special_key_press(int key, int x, int y);
void on_key_release(unsigned char key, int x, int y);
void on_special_key_release(int key, int x, int y);
void on_mouse_button(int button, int state, int x, int y);
void end_app();
void on_mouse_move(int x, int y);
void on_mouse_drag(int x, int y);

#endif
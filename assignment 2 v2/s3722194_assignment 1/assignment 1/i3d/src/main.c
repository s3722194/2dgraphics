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

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef GAME_TITLE
#define GAME_TITLE "Asteroid Arena"
#endif

#ifndef KEY_ESC
#define KEY_ESC 27
#endif

#ifndef MAX_BULLETS
#define MAX_BULLETS 20
#endif




#define PLATFORM_ROTATION_DELTA 5.0
#define CANNON_ROTATION_DELTA 5.0
#define CAMERA_ROTATION_DELTA 5.0

bool g_show_axes = true;


float g_camera_rotation = 0.0;

float g_platform_rotation = 0.0;
float g_cannon_rotation = 0.0;
float time = 0;

typedef struct
{
    float x;
    float y;
    float z;
} vec3f;

#define WALL_LEFT -15
#define WALL_RIGHT 15
#define WALL_BOTTOM 0
#define WALL_TOP 15
#define WALL_Z -15

#define WALL_DIVISIONS 50
vec3f wall_vertices[WALL_DIVISIONS + 1][WALL_DIVISIONS + 1];




void on_key_press_prac(unsigned char key, int x, int y)
{
    switch (key) {
        // toggle axes display
    case 'X':
    case 'x':
        g_show_axes = !g_show_axes;
        break;
        // rotate platform clockwise
    case 'A':
    case 'a':
        g_platform_rotation -= PLATFORM_ROTATION_DELTA;
        break;
        // rotate platform counter-clockwise
    case 'D':
    case 'd':
        g_platform_rotation += PLATFORM_ROTATION_DELTA;
        break;
        // rotate cannon up
    case 'W':
    case 'w':
        g_cannon_rotation += CANNON_ROTATION_DELTA;
        break;
        // rotate cannon down
    case 'S':
    case 's':
        g_cannon_rotation -= CANNON_ROTATION_DELTA;
        break;
        // rotate camera clockwise
    case '<':
    case ',':
        g_camera_rotation -= CAMERA_ROTATION_DELTA;
        break;
        // rotate camera counterclockwise
    case '>':
    case '.':
        g_camera_rotation += CAMERA_ROTATION_DELTA;
        break;
        // quit
    case KEY_ESC:
        exit(EXIT_SUCCESS);
        break;
    default:
        break;
    }
}

void draw_platform()
{
    float mat_colour[] = { 0.8, 0.8, 0.8, 0.5 };   
    float mat_close[] = { 1.0, 0.0, 0.0, 1.0 };
    float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };         
    float mat_shininess[] = { 100.0 };                     

      // setup materials
      //glColor3fv(mat_colour);                             // *** EXERCISE 1
  

    // position and draw
   // glRotatef(0, 0.0, 1.0, 0.0);
    float roomsize = 25.0;

    float platformsize = 10.0;
   
    //down
    glPushMatrix();
    if (ship.bottom_wall) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_close);
    }
    else {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_colour);
    }
           
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);    // *** EXERCISE 4
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  // *** EXERCISE 4
    glTranslatef(0, -wall.size, 0.0);
    glScalef(platformsize, 1.0, platformsize);
    glutSolidCube(1.0);
    glPopMatrix();

    //up
    glPushMatrix();
    if (ship.top_wall) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_close);
    }
    else {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_colour);
    }     
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);    // *** EXERCISE 4
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  // *** EXERCISE 4
    glTranslatef(0, wall.size, 0.0);
    glScalef(platformsize, 1.0, platformsize);
    glutSolidCube(1.0);
    glPopMatrix();

    //east
    glPushMatrix();
    if (ship.left_wall) 
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_close);
    }
    else 
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_colour);
    }        
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);    // *** EXERCISE 4
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  // *** EXERCISE 4
    glTranslatef(-wall.size, 0, 0.0);
    glScalef(1.0, platformsize, platformsize);
    glutSolidCube(1.0);
    glPopMatrix();

    //west
    glPushMatrix();
    if (ship.right_wall)
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_close);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_colour);
    }
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);    // *** EXERCISE 4
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  // *** EXERCISE 4
    glTranslatef(wall.size, 0, 0.0);
    glScalef(1.0, platformsize, platformsize);
    glutSolidCube(1.0);
    glPopMatrix();

    //south
    glPushMatrix();
    if (ship.north_wall)
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_close);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_colour);
    }     
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);    // *** EXERCISE 4
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  // *** EXERCISE 4
    glTranslatef(0, 0, wall.size);
    glScalef(platformsize, platformsize, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    

    //north
    glPushMatrix();
    if (ship.south_wall)
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_close);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_colour);
    }
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);    // *** EXERCISE 4
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  // *** EXERCISE 4
    glTranslatef(0, 0, -wall.size);
    glScalef(platformsize, platformsize, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}


void draw_mesh_walls()
{
    glPushMatrix();
    float mat_colour[] = { 0.0, 0.8, 0.8, 1.0 };
    float mat_close[] = { 1.0, 0.0, 0.0, 1.0 };
    float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_shininess[] = { 100.0 };

    glDisable(GL_LIGHTING);
    
    //down
    for (int i = 0-wall.size; i <= wall.size; i++) {
        glBegin(GL_LINES);
        if (ship.bottom_wall) {
            glColor3f(1.0, 0.0, 0.0);
        }
        else {
            glColor3f(0.8, 0.8, 0.8);
        }
        
        glVertex3f(i, -wall.size, -wall.size);
        glVertex3f(i, -wall.size, wall.size);
        glEnd();
    }
    
    //up
    for (int i = - wall.size; i <= wall.size; i++) {
        glBegin(GL_LINES);
        if (ship.top_wall) {
            glColor3f(1.0, 0.0, 0.0);
        }
        else {
            glColor3f(0.8, 0.8, 0.8);
        }

        glVertex3f(i, wall.size, -wall.size);
        glVertex3f(i, wall.size, wall.size);
        glEnd();
    }
    //right
    for (int i = - wall.size; i <= wall.size; i ++) {
        glBegin(GL_LINES);
        if (ship.right_wall) {
            glColor3f(1.0, 0.0, 0.0);
        }
        else {
            glColor3f(0.8, 0.8, 0.8);
        }

        glVertex3f(wall.size, wall.size, i);
        glVertex3f(wall.size, -wall.size, i);
        glEnd();
    }

    //left
    for (int i = - wall.size; i <= wall.size; i++) {
        glBegin(GL_LINES);
        if (ship.left_wall) {
            glColor3f(1.0, 0.0, 0.0);
        }
        else {
            glColor3f(0.8, 0.8, 0.8);
        }

        glVertex3f(-wall.size, wall.size, i);
        glVertex3f(-wall.size, -wall.size, i);
        glEnd();
    }

    //north
    for (int i = -wall.size; i <= wall.size; i++) {
        glBegin(GL_LINES);
        if (ship.north_wall) {
            glColor3f(1.0, 0.0, 0.0);
        }
        else {
            glColor3f(0.8, 0.8, 0.8);
        }

        glVertex3f(wall.size, i, wall.size);
        glVertex3f(-wall.size, i, wall.size);
        glEnd();
    }

    //south
    for (int i = -wall.size; i <= wall.size; i++) {
        glBegin(GL_LINES);
        if (ship.south_wall) {
            glColor3f(1.0, 0.0, 0.0);
        }
        else {
            glColor3f(0.8, 0.8, 0.8);
        }

        glVertex3f(wall.size, i, -wall.size);
        glVertex3f(-wall.size, i, -wall.size);
        glEnd();
    }


   /* glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, -10.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -10.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 10.0);*/
    
    glEnable(GL_LIGHTING);
   

    glPopMatrix();
}


void draw_ship()
{
    glPushMatrix();
    float mat_colour[] = { 0.0, 0.5, 0.2, 1.0 };
    float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_shininess[] = { 100.0 };

    // setup materials
    //glColor3fv(mat_colour);                            
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_colour);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // position and draw
    glRotatef(0, 0.0, 0, 0.0);
    glTranslatef(ship.transform.position.x, ship.transform.position.y, ship.transform.position.z);

    //printf("x of the ship %f \n", ship.transform.position.x);

    glPushMatrix();

    glScalef(2.0, 2.0, 3.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_colour);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glTranslatef(0, 1.0, -1.0);
    glScalef(1.0, 1.0, 1.0);
    glutSolidCube(1.0);

    glPopMatrix();
    glPopMatrix();

}

void traingle_ship() {

    float mat_colour[] = { 0.0, 0.5, 0.2, 1.0 };
    float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_shininess[] = { 100.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_colour);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
 
}

void draw_barrel()
{
    float mat_colour[] = { 0.8, 0.8, 0.0, 1.0 };            // *** EXERCISE 2
    float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };          // *** EXERCISE 4
    float mat_shininess[] = { 100.0 };                      // *** EXERCISE 4

      // setup materials
      //glColor3fv(mat_colour);                             // *** EXERCISE 2
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_colour);       // *** EXERCISE 4
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);    // *** EXERCISE 4
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  // *** EXERCISE 4

    // position and draw
    glRotatef(g_cannon_rotation, 0.0, 0.0, 1.0);
    glTranslatef(2.5, 2.0, 0.0);
    glPushMatrix();
    glScalef(5.0, 2.0, 2.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

void draw_wall()
{
    //float mat_colour[] = { 0.8, 0.8, 0.0, 1.0 };
    //float mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    //float mat_diffuse[] = { 1.0, 0.8, 0.2, 1.0 };
    //float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    //float mat_shininess[] = { 100.0 };

    //// setup materials
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_colour);
    //glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //// draw
    //glPushMatrix();
    //for (int row = 0; row < WALL_DIVISIONS; ++row) {
    //    glBegin(GL_TRIANGLE_STRIP);
    //    for (int col = 0; col <= WALL_DIVISIONS; ++col) {
    //        glNormal3f(0, 0, 1);
    //        glVertex3f(wall_vertices[row][col].x, wall_vertices[row][col].y, wall_vertices[row][col].z);
    //        glVertex3f(wall_vertices[row][col].x, wall_vertices[row + 1][col].y, wall_vertices[row][col].z);
    //    }
    //    glEnd();
    //}
    //glPopMatrix();


}



void draw_asteroid() {
    float g_rotation = 0.0f;
    int g_tesselation = 16;
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

    for (int i = 0; i < asteroids.number_of_asteroids; i++) {
        
        asteroid a = asteroids.asteroids[i];

        printf("asteroid render %f , %f, %f \n", a.transform.position.x, a.transform.position.y, a.transform.position.z);
        glPushMatrix();
       glTranslatef(a.transform.position.x, a.transform.position.y, a.transform.position.z);
       //  glTranslatef(1.0, a.transform.position.y,10.0);
        glRotatef(a.transform.rotation, 0, 1, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
        glutSolidSphere(1.0, g_tesselation, g_tesselation);
        glPopMatrix();
    }

   

}

void draw_axes()
{
   
    glDisable(GL_LIGHTING);                
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-10.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, -10.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -10.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
    glEnable(GL_LIGHTING);                     
}

void place_camera()
{
    gluLookAt(g_camera_position_x, g_camera_position_y, g_camera_position_z,
        0, 0, 0,
        0, 1, 0);
}

void render_frame_prac()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    place_camera();
    //draw_axes();
   // draw_cannon();
    draw_ship();
    draw_platform();
    draw_asteroid();
    draw_mesh_walls();
    //traingle_ship();
    //draw_wall();
}



void on_display_prac()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    render_frame_prac();
    glutSwapBuffers();
    int err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("Error: %s\n", gluErrorString(err));
    }
}

void on_idle_prac()
{
    update_camera_position();
    glutPostRedisplay();
}

void on_reshape(int w, int h)
{
    // Setup the viewport transform
    glViewport(0, 0, w, h);

    // Setup the projection transform
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 1000.0);
}

void init_lighting()                             // *** EXERCISE 3 ...
{
    float ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat position[] = { 50.0, 50.0, 50.0, 0.0 };

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_LIGHT0);
}

void init_app(int* argcp, char** argv)
{
    glutInit(argcp, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1200, 1200);
    glutCreateWindow("Assignment 2");
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display_prac);
    glutKeyboardFunc(on_key_press);
    
   

    glutSpecialFunc(on_special_key_press);
    glutKeyboardUpFunc(on_key_release);
    glutSpecialUpFunc(on_special_key_release);
    glutMouseFunc(on_mouse_button);

    glutPassiveMotionFunc(on_mouse_move);
    glutMotionFunc(on_mouse_drag);

    glutIdleFunc(on_idle);
    init_lighting();                                       // *** EXERCISE 3
}

int main(int argc, char** argv)
{
    init_app(&argc, argv);
    setup_game();
    glutMainLoop();
    return(EXIT_SUCCESS);
}

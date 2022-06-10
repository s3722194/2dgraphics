#ifndef VECTOR_H
#define VECTOR_H

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

vector2 vector2d_addition(vector2 v1, vector2 v2);
vector2 vector2d_subtraction(vector2 v1, vector2 v2);
vector2 vector2d_scalar(vector2 v1, float scalar);
float vector2d_length(vector2 v1);
vector2 vector2d_normalise(vector2 v1);
vector2 vector3_to_vector2(vector3 v1);
float dot_product_vector2d(vector2 v1, vector2 v2);
float vector2d_angle_rad(vector2 v1, vector2 v2);
float degree_to_rad(float a);
float rad_to_degree(float a);
float vector2d_angle_degree(vector2 v1, vector2 v2);
vector2 rad_angle_to_direction_vector2d(float angle);

vector3 vector3d_addition(vector3 v1, vector3 v2);
vector3 vector3d_subtraction(vector3 v1, vector3 v2);
vector3 vector3d_scalar(vector3 v1, float scalar);
float vector3d_length(vector3 v1);
vector3 vector3d_normalise(vector3 v1);
vector2 vector3_to_vector2(vector3 v1);
float dot_product_vector3d(vector3 v1, vector3 v2);
float vector3d_angle_rad(vector3 v1, vector3 v2);
float vector3d_angle_degree(vector3 v1, vector3 v2);


#endif

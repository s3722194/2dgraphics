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

vector2 vector_addition(vector2 v1, vector2 v2);
vector2 vector_subtraction(vector2 v1, vector2 v2);
vector2 vector_scalar(vector2 v1, float scalar);
float vector_length(vector2 v1);
vector2 vector_normalise(vector2 v1);
vector2 vector3_to_vector2(vector3 v1);
float dot_product(vector2 v1, vector2 v2);
float vector_angle_rad(vector2 v1, vector2 v2);
float degree_to_rad(float a);
float rad_to_degree(float a);
float vector_angle_degree(vector2 v1, vector2 v2);
vector2 rad_angle_to_direction(float angle);


#endif

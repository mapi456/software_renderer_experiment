#pragma once

#include <SDL.h>
#include <stdio.h>

// This module includes vector/matrix multiplcation math, structures for matrices and vectors

// A Vector4 represents a 4x1 column vector -> 4 rows by 1 column.
// Often used as 3x1 with w = 1 in order to represent points in cartesian space
struct Vector4 { 
	float x;
	float y;
	float z;
	float w; // not applicable in cartesian space, has to do with matrix multiplication

	Vector4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void translate(float x, float y, float z, float w) {
		this->x += x;
		this->y += y;
		this->z += z;
		this->w += w;
	}
};

struct Vector2 {
	float x;
	float y;
};

// A Matrix4 represents a 4x4 matrix -> 4 column vectors -> 4 4x1 vectors.
// PLEASE REMEMBER ALL THE VECTORS ARE STORED AS POINTERS
// functions: Mult_Vec4
struct Matrix4 {
	Vector4 *col1;
	Vector4 *col2;
	Vector4 *col3;
	Vector4 *col4;

	Matrix4(float x1, float y1, float z1, float w1,
			float x2, float y2, float z2, float w2,
			float x3, float y3, float z3, float w3,
			float x4, float y4, float z4, float w4) {
		col1 = new Vector4(x1, y1, z1, w1);
		col2 = new Vector4(x2, y2, z2, w2);
		col3 = new Vector4(x3, y3, z3, w3);
		col4 = new Vector4(x4, y4, z4, w4);
	}

	Matrix4(Vector4* set1, Vector4* set2, Vector4* set3, Vector4* set4) {
		col1 = set1;
		col2 = set2;
		col3 = set3;
		col4 = set4;
	}

	~Matrix4(){
		delete col1;
		delete col2;
		delete col3;
		delete col4;
	}

	// Mult_Vec4 multiplies v by this matrix
	// Note: modifies *v
	void Mult_Vec4(Vector4 *v) {
		float new_x = col1->x * v->x + col2->x * v->y + col3->x * v->z + col4->x * v->w;
		float new_y = col1->y * v->x + col2->y * v->y + col3->y * v->z + col4->y * v->w;
		float new_z = col1->z * v->x + col2->z * v->y + col3->z * v->z + col4->z * v->w;
		float new_w = col1->w * v->x + col2->w * v->y + col3->w * v->z + col4->w * v->w;

		v->x = new_x;
		v->y = new_y;
		v->z = new_z;
		v->w = new_w;
	}
};

// A Triangle represents 3 points in space -> each point represented by a Vector4
// Even when projected to screen space, need z-coord for computation (visibility, ...)
struct Triangle_3D {
	Vector4 *vertex1;
	Vector4 *vertex2;
	Vector4 *vertex3;

	Triangle_3D(float x1, float y1, float z1,
			    float x2, float y2, float z2, 
				float x3, float y3, float z3) {
		vertex1 = new Vector4(x1, y1, z1, 1);
		vertex2 = new Vector4(x2, y2, z2, 1);
		vertex3 = new Vector4(x3, y3, z3, 1);
	}

	Triangle_3D(Vector4* v1, Vector4* v2, Vector4* v3) {
		vertex1 = v1;
		vertex2 = v2;
		vertex3 = v3;
	}

	~Triangle_3D() {
		delete vertex1;
		delete vertex2;
		delete vertex3;
	}

	void copy(Triangle_3D* out) {
		out->vertex1->x = vertex1->x;
		out->vertex2->x = vertex2->x;
		out->vertex3->x = vertex3->x;
		out->vertex1->y = vertex1->y;
		out->vertex2->y = vertex2->y;
		out->vertex3->y = vertex3->y;
		out->vertex1->z = vertex1->z;
		out->vertex2->z = vertex2->z;
		out->vertex3->z = vertex3->z;
		out->vertex1->w = vertex1->w;
		out->vertex2->w = vertex2->w;
		out->vertex3->w = vertex3->w;
	}
};

// edge_function computes the signed area of the triangel v1v2p
float edge_function(Vector4 *v1, Vector4 *v2, Vector4 *p);

float edge_function(Vector4* v1, Vector4* v2, float x, float y);

float edge_function(Vector4* v1, Vector4* v2, int x, int y);


// determines whether the two vectors compose a top or left edge
// Note: our triangles are declared counter clockwise in the regular cartesian plane,
//       so a top edge has dy = 0, dx < 0
//       a left edge has dy < 0;
int top_left(Vector4* v1, Vector4* v2);
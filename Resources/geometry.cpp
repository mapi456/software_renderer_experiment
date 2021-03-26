#include "geometry.h"


int top_left(Vector4* v1, Vector4* v2) {
	if (v2->y - v1->y == 0 ? v2->x - v1->x < 0 : v2->y - v1->y < 0) {
		return 1;
	}
	return 0;
}

// Changing the edge_functions to return positive values with counter-clockwise triangles.
//     The earlier version return positive values with points within clockwise triangles, and negative values for counter-clockwise.
//     This should be easiser to work with.
float edge_function(Vector4* v1, Vector4* v2, Vector4* p) {
	return (v2->x - v1->x) * (p->y - v1->y) - (v2->y - v1->y) * (p->x - v1->x);
}

float edge_function(Vector4* v1, Vector4* v2, float x, float y) {
	return (v2->x - v1->x) * (y - v1->y) - (v2->y - v1->y) * (x - v1->x);
}

float edge_function(Vector4* v1, Vector4* v2, int x, int y) {
	return (v2->x - v1->x) * (y - v1->y) - (v2->y - v1->y) * (x - v1->x);
}
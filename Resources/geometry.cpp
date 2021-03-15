#include "geometry.h"


int top_left(Vector4* v1, Vector4* v2) {
	if (v2->y - v1->y == 0 ? v2->x - v1->x < 0 : v2->y - v1->y < 0) {
		return 1;
	}
	return 0;
}


float edge_function(Vector4* v1, Vector4* v2, Vector4* p) {
	return (p->x - v1->x) * (v2->y - v1->y) - (p->y - v1->y) * (v2->x - v1->x);
}

float edge_function(Vector4* v1, Vector4* v2, float x, float y) {
	return (x - v1->x) * (v2->y - v1->y) - (y - v1->y) * (v2->x - v1->x);
}

float edge_function(Vector4* v1, Vector4* v2, int x, int y) {
	return (x - v1->x) * (v2->y - v1->y) - (y - v1->y) * (v2->x - v1->x);
}
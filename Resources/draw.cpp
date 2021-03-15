#include "draw.h"
#include <SDL.h>
#include <stdlib.h>
#include <algorithm>

void draw_triangle(Triangle_3D* triangle, Uint32 pixels[], int width, int height, SDL_Surface *screen) {
	Vector4* v1 = triangle->vertex1;
	Vector4* v2 = triangle->vertex2;
	Vector4* v3 = triangle->vertex3;
	
	int min_x = floor(fmax(fmin(fmin(v1->x, v2->x), v3->x), 0));
	int max_x = ceil(fmin(fmax(fmax(v1->x, v2->x), v3->x), (float)width));
	int min_y = floor(fmax(fmin(fmin(v1->y, v2->y), v3->y), 0));
	int max_y = ceil(fmin(fmax(fmax(v1->y, v2->y), v3->y), (float)height));

	float c1 = ((v1->y - v2->y) * (v1->x + v2->x) + (v2->x - v1->x) * (v1->y + v2->y)) / 2;
	float c2 = ((v2->y - v3->y) * (v2->x + v3->x) + (v3->x - v2->x) * (v2->y + v3->y)) / 2;
	float c3 = ((v3->y - v1->y) * (v3->x + v1->x) + (v1->x - v3->x) * (v3->y + v1->y)) / 2;
	float area = -1 * ((c1 + c2 + c3) / 2);

	//check if backfacing; only one triangle so maybe comment this out and see what happens
	//if (area < 0) {
	//	return;
	//}

	int bias_1 = top_left(v1, v2);
	int bias_2 = top_left(v2, v3);
	int bias_3 = top_left(v3, v1);

	for (int x = min_x; x < max_x; ++x) {
		for (int y = min_y; y < max_y; ++y) {

			//Later, we can optimise this process by adding a constant x, y, each pixel step
			// Also note: our bias is -1 because a point within the triangle should produce a negatively signed area
			float w1 = edge_function(v1, v2, x, y) - bias_1;
			float w2 = edge_function(v2, v3, x, y) - bias_2;
			float w3 = edge_function(v3, v1, x, y) - bias_3;

			if ((w1 < 0 && w2 < 0 && w3 < 0) || (w1 >= 0 && w2 >= 0 && w3 >= 0)) {
				// now we can finally draw the pixel!
				//for now, just a random colour, but later will be based on triangle vertex properties
                putpixel(screen, x, y, SDL_MapRGB(screen->format, 0, 0, 0));
			}

			// later, when we want to find the colour attribute of a pixel
			// we use the following equation
			// C = L_1 * C_1 + L_2 * C_2 + L_3 * C_3
			// where C_x is the colour attribute associated with the x vertex
			// and L_x is the area of the triangle associated with the other two vertices 
			//     and the current pixel point divided by the area of the whole triangle
			//     which works out to (for example vertex = 1):
			//    edge_function(vertex_2, vertex_3, point) / edge_function(vertex_2, vertex_3, vertex_1)

		}
	}
}


// Shamelessly stolen from http://sdl.beuc.net/sdl.wiki/Pixel_Access because too many bugs at once and i need to find the critical issues
void putpixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16*)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32*)p = pixel;
        break;
    }
}

void fill_surface(SDL_Surface* surface, Uint32 pixels[], int width, int height) {
    int num_pixels = width * height;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int bpp = surface->format->BytesPerPixel;
            /* Here p is the address to the pixel we want to set */
            Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
            int index = y * width + x;
            switch (bpp) {
            case 1:
                *(Uint16*)p = pixels[index];
                break;

            case 2:
                *(Uint16*)p = pixels[index];
                break;

            case 3:
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                    p[0] = (pixels[index] >> 16) & 0xff;
                    p[1] = (pixels[index] >> 8) & 0xff;
                    p[2] = pixels[index] & 0xff;
                }
                else {
                    p[0] = pixels[index] & 0xff;
                    p[1] = (pixels[index] >> 8) & 0xff;
                    p[2] = (pixels[index] >> 16) & 0xff;
                }
                break;

            case 4:
                *(Uint32*)p = pixels[index];
                break;
            }
        }
    }
}
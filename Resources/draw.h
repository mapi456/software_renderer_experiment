#pragma once

#include <SDL.h>
#include <stdio.h>
#include "geometry.h"

// This module includes methods for drawing straight to an SDL surface.


// This method fills every pixel in surface with the data from pixels. Use this to draw every
//      frame, and simply modify a pixel array before drawing to surface.
// Note: in huge projects (beyond the scope of this experiment), waiting for all calculations before drawing the frame
//       would be framerate suicide
void fill_surface(SDL_Surface* surface, Uint32 pixels[], int width, int height);


// This method draws all pixels that lie within the projected triangle.
// Note: we only need width and height because we skipped the clipping stage. Otherwise, all pixels are guaranteed
//       to lie within viewing space.
void draw_triangle(Triangle_3D* triangle, int width, int height, SDL_Surface *screen);
//				  (Triangle_3D* triangle, Uint32 pixels[], int width, int height, const SDL_PixelFormat format)

// This method taken from external source at http://sdl.beuc.net/sdl.wiki/Pixel_Access. 
// Draws to a single pixel.
void putpixel(SDL_Surface* surface, int x, int y, Uint32 pixel);
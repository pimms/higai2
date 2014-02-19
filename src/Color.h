#pragma once

#include <SDL2/SDL.h>

typedef unsigned char byte;

// Color 
// Class used when rendering stuff in various colors.
class Color {
public:
	Color();
	Color(byte pr, byte pg, byte pb, byte pa=255);

	void Set(byte pr, byte pg, byte pb, byte pa=255);
	void Assign(SDL_Renderer *renderer);

	byte r;
	byte g;
	byte b;
	byte a;
};

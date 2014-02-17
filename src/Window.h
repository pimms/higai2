#pragma once

#include <SDL2/SDL.h>


class Window {
public:
	// TODO:
	// Return the current resolution of the window
	void GetResolution(int *x, int *y) {} 
	
	// TODO:
	// Move this method to the cpp file 
	SDL_Renderer* GetRenderer() {return _renderer;}


private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
};

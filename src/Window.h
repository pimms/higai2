#pragma once

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif


class Window {
public:
	// TODO:
	// Assign the current resolution of the window
	void GetResolution(int *x, int *y) {} 
	
	// TODO:
	// Move this method to the cpp file 
	SDL_Renderer* GetRenderer() {return _renderer;}
	
	// TODO: 
	// Return a proper value
	bool ShouldQuit() { return true; }

	// TODO:
	// Handle all events
	void HandleEvents() {}

private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
};

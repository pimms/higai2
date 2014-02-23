#pragma once

#include <SDL2/SDL.h>
#include "Vec.h"


class Window {
public:
	Window();
	~Window();

	bool Init(int width, int height);

	void GetResolution(int *x, int *y) const;
	Vec GetResolution() const;

	SDL_Renderer* GetRenderer() const;
	
	bool ShouldQuit() const;

	void HandleEvents(); 

	void ClearRenderer();
	void PresentRenderer();

private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;

	Vec _resolution;
	bool _shouldQuit;
};

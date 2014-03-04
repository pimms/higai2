#include "Window.h"

Window::Window()
	:	_window(NULL),
	    _renderer(NULL),
	    _shouldQuit(false),
	    _resolution(0, 0)
{
}

Window::~Window()
{
	if (_window) {
		SDL_DestroyWindow(_window);
	}

	if (_renderer) {
		SDL_DestroyRenderer(_renderer);
	}
}


bool Window::Init(int width, int height)
{
	if (_window || _renderer) {
		printf("Error: Window::Init() has been called before\n");
		return false;
	}

	_window = SDL_CreateWindow(
	              "AI Assignment 2, Group 2",
	              SDL_WINDOWPOS_UNDEFINED,
	              SDL_WINDOWPOS_UNDEFINED,
	              width, height,
	              SDL_WINDOW_SHOWN);
	if (!_window) {
		printf("Error: Window::Init(): Failed to create window\n");
		return false;
	}

	_renderer = SDL_CreateRenderer(
	                _window,
	                -1,
	                SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (!_renderer) {
		printf("Error: Window::Init(): Failed to create renderer\n");
		return false;
	}

	_resolution = Vec(width, height);
	return true;
}


void Window::GetResolution(int *x, int *y) const
{
	Vec v = GetResolution();
	*x = v.x;
	*y = v.y;
}

Vec Window::GetResolution() const
{
	return _resolution;
}


SDL_Renderer* Window::GetRenderer() const
{
	return _renderer;
}


bool Window::ShouldQuit() const
{
	return _shouldQuit;
}


void Window::HandleEvents()
{
	SDL_Event evt;

	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
		case SDL_QUIT:
			_shouldQuit = true;

		case SDL_MOUSEBUTTONDOWN:
			DispatchMouseClick(evt.button.x, evt.button.y);
			break;

		case SDL_KEYDOWN:
			DispatchKeyDown(evt.key.keysym.sym);
			break;

		default:
			/* Don't handle */
			break;
		}
	}
}


void Window::ClearRenderer()
{
	SDL_RenderClear(_renderer);
}

void Window::PresentRenderer()
{
	SDL_RenderPresent(_renderer);
}


void Window::AddListener(InputListener *listener)
{
	_listeners.push_back(listener);
}

void Window::RemoveListener(InputListener *listener)
{
	_listeners.remove(listener);
}


/***** Private Methods *****/
void Window::DispatchMouseClick(int x, int y)
{
	list<InputListener*>::iterator it;

	for (it=_listeners.begin(); it!=_listeners.end(); it++) {
		(*it)->OnMouseClick(Vec(x,y));
	}
}

void Window::DispatchKeyDown(int key)
{
	list<InputListener*>::iterator it;

	for (it=_listeners.begin(); it!=_listeners.end(); it++) {
		(*it)->OnKeyDown(key);
	}

}

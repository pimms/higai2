#pragma once

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <list>
using std::list;

#include "Vec.h"

// Forward declarations
class InputListener;

class Window
{
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

	void AddListener(InputListener *listener);
	void RemoveListener(InputListener *listener);
		
private:
	void DispatchMouseClick(int x, int y);
	void DispatchKeyDown(int key);

    SDL_Window *_window;
    SDL_Renderer *_renderer;

    Vec _resolution;
    bool _shouldQuit;

	list<InputListener*> _listeners;
};

/* Virtual callback class
 */
class InputListener
{
public:
    virtual void OnMouseClick(Vec pos) = 0;
	virtual void OnKeyDown(int key) = 0;
};

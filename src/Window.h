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
class MouseListener;

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

	void AddListener(MouseListener *listener);
	void RemoveListener(MouseListener *listener);
		
private:
	void DispatchMouseClick(int x, int y);

    SDL_Window *_window;
    SDL_Renderer *_renderer;

    Vec _resolution;
    bool _shouldQuit;

	list<MouseListener*> _listeners;
};

/* Virtual callback class
 */
class MouseListener
{
public:
    virtual void OnMouseClick(Vec pos) = 0;
};

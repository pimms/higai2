#pragma once

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "Vec.h"

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

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;

    Vec _resolution;
    bool _shouldQuit;
};

/* Virtual callback class
 */
class MouseListener
{
public:
    virtual void OnMouseClick(Vec pos) = 0;
};

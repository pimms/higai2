#pragma once

#include <SDL2/SDL.h>

// Forward declarations
class Window;
class PathNode;
class World;


class Renderer {
public:
	Renderer(Window *Window);
	
	void DrawWorld(World *world);

private:
	void DrawPathNode(PathNode *node, int worldSizeX, int worldSizeY);
	
	void SetRenderColor(PathNode *node);
	void DrawRect(int x, int y, int w, int h);

	Window *_window;
};

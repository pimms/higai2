#pragma once

#include <SDL2/SDL.h>
#include "Vec.h"
#include "Color.h"

#include <list>
using std::list;

// Forward declarations
class Window;
class PathNode;
class World;


class Renderer {
public:
	Renderer(Window *Window);
	
	void DrawWorld(World *world);
	void DrawPath(World *world, const list<PathNode*> &path, Color=Color(0,0,0));

private:
	void DrawPathNode(World *world, PathNode *node);
	
	void SetRenderColor(PathNode *node);
	void DrawRect(Vec pos, Vec dim);
	
	Vec GetTileDimensions(World *world);

	/* If center is true, the center of the tile is returned. Otherwise, the 
	 * top left corner is returned. */
	 Vec GetTileCoordinate(World *world, PathNode *node, bool center);

	Window *_window;
};

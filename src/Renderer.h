#pragma once

#ifdef WIN32
#include <SDL.h>
#else
#include "SDL2/SDL.h"
#endif

#include "Vec.h"
#include "Color.h"

#include <list>
using std::list;

// Forward declarations
class Window;
class PathNode;
class World;
class Path;


class Renderer
{
public:
	Renderer(Window *Window);

	void DrawWorld(World *world);
	void DrawPath(World*, const Path*);
	void DrawPath(World*, const list<PathNode*>&, const PathNode *div,
	              Color orig=Color(0,0,0), Color split=Color(1,1,1));

	void DrawPathNode(World *world, PathNode *node);
	void DrawPathNode(World *world, PathNode *node, Color c);

	void SetRenderColor(PathNode *node);
	void SetRenderColor(Color color);
	void DrawRect(Vec pos, Vec dim);

	void Present();

private:
	Vec GetTileDimensions(World *world);

	/* If center is true, the center of the tile is returned.
	 * Otherwise, the top left corner is returned. */
	Vec GetTileCoordinate(World *world, PathNode *node, bool center);

	Window *_window;
};

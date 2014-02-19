#pragma once

#include <SDL2/SDL.h>
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
	void DrawPath(World *world, const list<PathNode*> &path);

private:
	void DrawPathNode(World *world, PathNode *node);
	
	void SetRenderColor(PathNode *node);
	void DrawRect(int x, int y, int w, int h);
	
	/* Assigns the pixel size of each tile to W and H.
	 */
	void GetTileDimensions(World *world, int *w, int *h);

	/* Assigns the screen coordinates of the path node "node" to X and Y.
	 * If center is true, the center of the tile is assigned to the variables.
	 * Otherwise, the top left position is assigned.
	 */
	void GetTileCoordinate(World *world, PathNode *node, 
							bool center, int *x, int *y);

	Window *_window;
};

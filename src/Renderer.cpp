#include "Renderer.h"
#include "World.h"
#include "Window.h"
#include "PathNode.h"
#include "Path.h"

#include <map>
#include <queue>
using std::map;
using std::queue;


Renderer::Renderer(Window *window)
	:	_window(window)
{

}


void Renderer::DrawWorld(World *world)
{
	int sizeX, sizeY;
	world->GetSize(&sizeX, &sizeY);

	_window->ClearRenderer();

	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			PathNode *node = world->GetNode(x, y);
			DrawPathNode(world, node);
		}
	}

	Present();
}

void Renderer::DrawPath(World *world, const Path *path)
{
	DrawPath(world, path->GetNodes(), path->GetSplitDivisor(),
	         Color(255, 0, 0), Color(255, 0, 0));
	DrawPath(world, path->GetOptimized(), path->GetSplitDivisor(),
	         Color(0, 0, 255), Color(0, 255, 255));
}

void Renderer::DrawPath(World *world, const list<PathNode*> &path,
                        const PathNode *div, Color orig, Color split)
{
	int sizeX, sizeY;
	world->GetSize(&sizeX, &sizeY);

	list<PathNode*>::const_iterator cur = path.begin();
	list<PathNode*>::const_iterator next = path.begin();
	next++;

	orig.Assign(_window->GetRenderer());

	while (next != path.end()) {
		if (*next == div) {
			split.Assign(_window->GetRenderer());
		}

		Vec cp, np;
		cp = GetTileCoordinate(world, *cur, true);
		np = GetTileCoordinate(world, *next, true);

		SDL_RenderDrawLine(_window->GetRenderer(),cp.x,cp.y,np.x,np.y);

		next++;
		cur++;
	}

	Color(0,0,0,255).Assign(_window->GetRenderer());
	Present();
}


void Renderer::DrawPathNode(World *world, PathNode *node)
{
	Color c = node->GetColor();
	DrawPathNode(world, node, c);
}

void Renderer::DrawPathNode(World *world, PathNode *node, Color c)
{
	Vec dim = GetTileDimensions(world);
	Vec pos = GetTileCoordinate(world, node, false);

	// Draw a black 1px outline
	SetRenderColor(Color(0,0,0));
	DrawRect(pos, dim);

	// Draw the tile
	pos.x += 1;
	pos.y += 1;
	dim.x -= 2;
	dim.y -= 2;

	SetRenderColor(c);
	DrawRect(pos, dim);

	// Return to black color
	SetRenderColor(Color(0,0,0));

}


void Renderer::SetRenderColor(PathNode *node)
{
	Color color = node->GetColor();
	color.Assign(_window->GetRenderer());
}

void Renderer::SetRenderColor(Color color)
{
	SDL_SetRenderDrawColor(_window->GetRenderer(),
	                       color.r, color.g, color.b, color.a);
}

void Renderer::DrawRect(Vec pos, Vec dim)
{
	SDL_Rect rect = {pos.x, pos.y, dim.x, dim.y};
	SDL_RenderFillRect(_window->GetRenderer(), &rect);
}


Vec Renderer::GetTileDimensions(World *world)
{
	int sizeX, sizeY;
	world->GetSize(&sizeX, &sizeY);

	int resX, resY;
	_window->GetResolution(&resX, &resY);

	return Vec(resX/sizeX, resY/sizeY);
}

Vec Renderer::GetTileCoordinate(World *world, PathNode *node, bool center)
{
	int posX, posY;
	Vec size;

	size = GetTileDimensions(world);
	node->GetPosition(&posX, &posY);

	Vec v(size.x * posX, size.y * posY);

	if (center) {
		v.x += size.x / 2;
		v.y += size.y / 2;
	}

	return v;
}


void Renderer::Present()
{
	_window->PresentRenderer();
}

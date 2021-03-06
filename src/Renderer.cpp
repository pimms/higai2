#include "Renderer.h"
#include "World.h"
#include "Window.h"
#include "PathNode.h"
#include "Path.h"

#include <map>
#include <queue>
using std::map;
using std::queue;

const char *RENDERER_HELP =
	"RENDERING AND COLOR CODES\n"
	"All aspects of paths are rendered over one another, meaning \n"
	"that some attributes of a path may be hidden. The attributes\n"
	"are rendered from least important to most important.\n"
	"If you think something is missing, it is being drawn\n"
	"over.\n"
	"\n"
	"The color codes are:\n"
	"\tRED\n"
	"\tThe unoptimized path. This path consist only of straight\n"
	"\tlines, and is the direct output from the algorithm.\n"
	"\n"
	"\tBLUE\n"
	"\tThe optimized path. Wherever possible, diagonals replace\n"
	"\tstraight lines.\n"
	"\n"
	"\tTURQUOISE\n"
	"\tWhen a wall is inserted and is obstructing the OPTIMIZED path,\n"
	"\tthe agent stops at this point and attempts to find another \n"
	"\tway. The original, untouched segment of the path is blue, \n"
	"\tthe newly found path is turquoise.\n"
	"\n";


Renderer::Renderer(Window *window)
	:	_window(window)
{
	printf("%s", RENDERER_HELP);
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
	
		cp.x -= 3;
		cp.y -= 3;
		DrawRect(cp, Vec(6,6));
			
		np.x -= 3;
		np.y -= 3;
		DrawRect(np, Vec(6,6));

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

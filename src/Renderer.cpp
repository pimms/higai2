#include "Renderer.h"
#include "World.h"
#include "Window.h"
#include "PathNode.h"


Renderer::Renderer(Window *window) 
	:	_window(window)
{
	
}


void Renderer::DrawWorld(World *world) {
	int sizeX, sizeY;
	world->GetSize(&sizeX, &sizeY);

	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			PathNode *node = world->GetNode(x, y);
			DrawPathNode(world, node);
		}
	}
}

void Renderer::DrawPath(World *world, const list<PathNode*> &path) {
	int sizeX, sizeY;
	world->GetSize(&sizeX, &sizeY);
	
	list<PathNode*>::const_iterator cur = path.begin();
	list<PathNode*>::const_iterator next = path.begin();
	next++;
	
	while (next != path.end()) {
		int x1, y1, x2, y2;
		GetTileCoordinate(world, *cur, true, &x1, &y1);
		GetTileCoordinate(world, *next, true, &x2, &y2);

		SDL_RenderDrawLine(_window->GetRenderer(), x1, y1, x2, y2);

		next++;
		cur++;
	}
}


/**** Private Methods *****/
void Renderer::DrawPathNode(World *world, PathNode *node) {
	// The screen coordinate of the node
	int topX, topY;

	// The size of the node
	int sizeX, sizeY;
	
	GetTileDimensions(world, &sizeX, &sizeY);
	GetTileCoordinate(world, node, false, &topX, &topY);

	// Draw a black 1px outline
	SDL_SetRenderDrawColor(_window->GetRenderer(), 0, 0, 0, 255);
	DrawRect(topX, topY, sizeX, sizeY);
	
	// Draw the tile
	SetRenderColor(node);
	DrawRect(topX+1, topY+1, sizeX-1, sizeY-1);
}


void Renderer::SetRenderColor(PathNode *node) {
	int r, g, b;
	node->GetColor(&r, &g, &b);
	SDL_SetRenderDrawColor(_window->GetRenderer(), r, g, b, 255);
}

void Renderer::DrawRect(int x, int y, int w, int h) {
	SDL_Rect rect = {x, y, w, h};
	SDL_RenderDrawRect(_window->GetRenderer(), &rect);
}


void Renderer::GetTileDimensions(World *world, int *x, int *y) {
	int sizeX, sizeY;
	world->GetSize(&sizeX, &sizeY);
	
	int resX, resY;
	_window->GetResolution(&resX, &resY);
	
	*x = resX / sizeX;
	*y = resY / sizeY;
}

void Renderer::GetTileCoordinate(World *world, PathNode *node, 
								bool center, int *x, int *y) {
	int sizeX, sizeY;
	int posX, posY;

	world->GetSize(&sizeX, &sizeY);
	node->GetPosition(&posX, &posY);
	
	*x = sizeX * posX; 
	*y = sizeY * posY;

	if (center) {
		*x += sizeX / 2;
		*y += sizeY / 2;
	}
}

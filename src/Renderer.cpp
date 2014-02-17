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
			DrawPathNode(node, sizeX, sizeY);
		}
	}
}


/**** Private Methods *****/
void Renderer::DrawPathNode(PathNode *node, int worldSizeX, int worldSizeY) {
	// The screen coordinate of the node
	int topX, topY;

	// The grid indices of the node
	int posX, posY;

	// The size of the node
	int sizeX, sizeY;

	// The resolution of the screen
	int resX, resY;

	_window->GetResolution(&resX, &resY);
	sizeX = resX/worldSizeX;
	sizeY = resY/worldSizeY;

	node->GetPosition(&posX, &posY);
	topX = sizeX * posX;
	topY = sizeY * posY;

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

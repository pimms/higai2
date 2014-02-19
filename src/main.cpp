#include "World.h"
#include "Window.h"
#include "Renderer.h"
#include "PathNode.h"


void InitializeWorld(World *world) {
	int sx, sy;
	world->GetSize(&sx, &sy);

	for (int x=2; x < sx-2; x++) {
		for (int y=2; y<sy-2; y++) {
			world->GetNode(x, y)->SetType(PathNode::WALL);
		}
	}
}



int main() {
	World world(20, 20);
	InitializeWorld(&world);

	Window window;
	Renderer renderer(&window);

	while (window.ShouldQuit() == false) {
		window.HandleEvents();
		renderer.DrawWorld(&world);
	}

	return 0;
}

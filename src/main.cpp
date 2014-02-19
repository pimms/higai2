#include "World.h"
#include "Window.h"
#include "Renderer.h"


int main() {
	World world(20, 20);
	Window window;
	Renderer renderer(&window);


	while (window.ShouldQuit() == false) {
		window.HandleEvents();
		renderer.DrawWorld(&world);
	}

	return 0;
}

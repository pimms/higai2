#include "World.h"
#include "Window.h"
#include "Renderer.h"
#include "PathNode.h"
#include "GraphMapper.h"
#include "Path.h"
#include <string>

void InitializeWorld(World *world)
{
    int sx, sy;
    world->GetSize(&sx, &sy);

    for (int x=2; x < sx-2; x++) {
        for (int y=2; y<sy-2; y++) {
			if ((rand())%8 <= 2) {
            	world->GetNode(x, y)->SetType(PathNode::WALL);
			}
        }
    }
}

#define WORLD_SIZE 8
int ai_main(int argc, char *argv[])
{
	// Initialize the world
    World world(WORLD_SIZE, WORLD_SIZE);
    InitializeWorld(&world);

	// Initialize the window
    Window window;
    if (!window.Init(750, 750)) {
        return 1;
    }

	// Initialize the renderer
    Renderer renderer(&window);

	// Initialize the graph mapper
	GraphMapper mapper(&world, &window, &renderer);
	window.AddListener(&mapper);
	
	// Enter the simulation loop
    while (window.ShouldQuit() == false) {
        window.HandleEvents();
        renderer.DrawWorld(&world);
	
		const Path *path = mapper.GetPath();
		if (path) {
			renderer.DrawPath(&world, path);
		}
	
		SDL_Delay(50);
    }

    return 0;
}

#ifdef main
#undef main
#endif
int main(int argc, char *argv[])
{
    int ret = 0;

    try {
        ret = ai_main(argc, argv);
    } catch (const char *ex) {
        printf("Exception caught:\n%s\n", ex);
    } catch (std::string ex) {
        printf("Exception caught:\n%s\n", ex.c_str());
    } catch (...) {
        printf("Unkown exception caught: no info available\n");
    }
	
	if (ret)
	    printf("ai_main terminated with status %i\n", ret);
	return ret;
}

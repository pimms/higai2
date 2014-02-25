#include "World.h"
#include "Window.h"
#include "Renderer.h"
#include "PathNode.h"
#include <string>

void InitializeWorld(World *world)
{
    int sx, sy;
    world->GetSize(&sx, &sy);

    for (int x=2; x < sx-2; x++) {
        for (int y=2; y<sy-2; y++) {
            world->GetNode(x, y)->SetType(PathNode::WALL);
        }
    }

	PathNode *nodes[4];
	nodes[0] = world->GetNode(0, 0);
	nodes[1] = world->GetNode(19, 1);
	nodes[2] = world->GetNode(18, 19);
	nodes[3] = world->GetNode(0, 19);

	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			if (j!=i) {
				nodes[i]->AddNeighbour(world, nodes[j]);
			}
		}
	}
}


int ai_main(int argc, char *argv[])
{
    World world(20, 20);
    InitializeWorld(&world);

    Window window;
    if (!window.Init(600, 600)) {
        return 1;
    }

    Renderer renderer(&window);

    while (window.ShouldQuit() == false) {
        window.HandleEvents();
        renderer.DrawWorld(&world);
    }
    return 0;
}


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

    printf("ai_main terminated with status %i\n", ret);
}

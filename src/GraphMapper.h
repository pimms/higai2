#pragma once

#include "Window.h"


// Forward declarations
class World;

class GraphMapper : public MouseListener {
public:
	GraphMapper(World *world);

	void OnMouseClick(Vec pos);

private:
	World *_world;
};

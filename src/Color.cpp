#include "Color.h"


Color::Color()
	: 	r(0),
	    g(0),
	    b(0),
	    a(255)
{

}

Color::Color(byte pr, byte pg, byte pb, byte pa)
	:	r(pr),
	    g(pg),
	    b(pb),
	    a(pa)
{

}



void Color::Set(byte pr, byte pg, byte pb, byte pa)
{
	r = pr;
	g = pg;
	b = pb;
	a = pa;
}

void Color::Assign(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

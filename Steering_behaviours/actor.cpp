#include "actor.h"



actor::actor(aie::Renderer2D* a_renderer, aie::Texture* a_texture, const Vector2 a_position) : 
	game_object(a_renderer, a_texture, a_position)
{
}


actor::~actor()
{
}

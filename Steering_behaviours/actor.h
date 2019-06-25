#pragma once


#include "game_object.h"
class actor : public game_object
{
public:
	actor(aie::Renderer2D* a_renderer, aie::Texture* a_texture, const Vector2 a_position);
	~actor();
};


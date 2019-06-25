#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"
#include "Input.h"

class player : public game_object
{
public:
	player(aie::Renderer2D* a_renderer, aie::Input* a_input ,aie::Texture* a_texture, const Vector2 a_position);

	void update(float a_delta_time);
	~player();

private:

	aie::Input* m_input;

};

#endif // !PLAYER_H

#pragma once
#include "Matrix3.h"
#include "Vector2.h"
#include <ctime>
#include <cstdlib>

class Agent
{
public:
	Matrix3 m_transform;
	//Vector2& m_position = Vector2(m_transform.position);

	const float m_max_speed = 50.f; // Units per second 
	const float m_turn_speed = 1.5f; // Radians per second
	const float m_arrival_distance = 50.f;

	const float m_wander_projection = 100.f;
	const float m_wander_radus = 25.f;

	float m_wander_rotation = 0;

	const float m_wander_min_rand = -0.1;
	const float m_wander_max_rand = 0.1;
	const int m_wander_rand = 200;

	const float m_min_wander_timer = 5.f;
	const float m_max_wander_timer = 10.f;
	float m_current_wander_timer = 0.f;

	Vector2 m_target_position;
	Vector2 m_screen_center = Vector2(1280, 720) * 0.5f;

	enum STEERING_STATE : char
	{
		NONE,
		SEEK,
		FLEE,
		WANDER
	};


	STEERING_STATE m_current_state = NONE;

	Agent();
	~Agent();


	void update(float a_delta_time);

	void seek(float a_delta_time);
	void flee(float a_delta_time);
	void wander(float a_delta_time);
};


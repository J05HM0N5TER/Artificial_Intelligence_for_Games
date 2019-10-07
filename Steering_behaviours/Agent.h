#pragma once
#include "Matrix3.h"
#include "Vector2.h"

class Agent
{
public:
	Matrix3 m_transform;
	//Vector2& m_position = Vector2(m_transform.position);

	float m_max_speed = 10.f; // Units per second 
	float m_turn_speed = 1.5f; // Radians per second

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


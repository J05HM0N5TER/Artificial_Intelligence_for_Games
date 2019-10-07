#include "Agent.h"



Agent::Agent()
{
	m_transform.position = Vector3(m_screen_center.x, m_screen_center.y, 1);
	m_target_position = m_screen_center * 0.5f;
	m_current_state = SEEK;
}


Agent::~Agent()
{
}

void Agent::update(float a_delta_time)
{
	if (m_current_state == NONE)
	{
		m_current_state = WANDER;
	}

	switch (m_current_state)
	{
	case Agent::NONE:
		break;
	case Agent::SEEK:
		this->seek(a_delta_time);
		break;
	case Agent::FLEE:
		this->flee(a_delta_time);
		break;
	case Agent::WANDER:
		this->wander(a_delta_time);
		break;
	default:
		break;
	}
}

void Agent::seek(float a_delta_time)
{
	Vector2 target_direction = m_target_position - Vector2(m_transform.position.x, m_transform.position.y);

	// Rotate towards
	float dot_fowards = target_direction.dot(Vector2(m_transform.forwards.x, m_transform.forwards.y));
	float dot_right = target_direction.dot(Vector2(m_transform.right.x, m_transform.right.y));

	// Turn right
	if (dot_right > 0.f)
	{
		Matrix3 rotation_matrix = Matrix3();
		rotation_matrix.setRotateZ(-m_turn_speed * a_delta_time);
		m_transform = m_transform * rotation_matrix;
	}
	// Turn left
	else
	{
		Matrix3 rotation = Matrix3();
		rotation.setRotateZ(m_turn_speed * a_delta_time);
		m_transform = m_transform * rotation;
	}

}

void Agent::flee(float a_delta_time)
{
}

void Agent::wander(float a_delta_time)
{
}

#include "Agent.h"

Agent::Agent()
{
	m_transform.position = Vector3(m_screen_center.x, m_screen_center.y, 1);
	m_target_position = m_screen_center * 0.5f;
	m_current_state = SEEK;
	srand(time(NULL));
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
	float distance = target_direction.magnitude();
	target_direction.normalise();

	// Rotate towards
	float dot_fowards = target_direction.dot(Vector2(m_transform.forwards.x, m_transform.forwards.y));
	float dot_right = target_direction.dot(Vector2(m_transform.right.x, m_transform.right.y));

	// If not facing target
	if (dot_fowards < 0.995f)
	{
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

	// Move towards
	m_transform.position += m_transform.forwards * a_delta_time * m_max_speed * dot_fowards;

	// Check if arrived
	if (distance < m_arrival_distance)
	{
		// If arrived - Wander
		m_current_state = WANDER;
		m_current_wander_timer = rand() % int(m_max_wander_timer - m_min_wander_timer) + m_min_wander_timer;
	}
}

void Agent::flee(float a_delta_time)
{
	Vector2 target_direction = m_target_position - Vector2(m_transform.position.x, m_transform.position.y);
	float distance = target_direction.magnitude();
	target_direction.normalise();

	// Rotate towards
	float dot_fowards = target_direction.dot(Vector2(m_transform.forwards.x, m_transform.forwards.y));
	float dot_right = target_direction.dot(Vector2(m_transform.right.x, m_transform.right.y));

	// If not facing away from target -- NEGATORY HEADING
	if (dot_fowards > -0.995f)
	{
		// Turn right
		if (dot_right > 0.f)
		{
			Matrix3 rotation_matrix = Matrix3();
			rotation_matrix.setRotateZ(m_turn_speed * a_delta_time); // NEGATORY SPEED
			m_transform = m_transform * rotation_matrix;
		}
		// Turn left
		else
		{
			Matrix3 rotation = Matrix3();
			rotation.setRotateZ(-m_turn_speed * a_delta_time); // NEGATORY SPEED 
			m_transform = m_transform * rotation;
		}
	}

	// Move towards
	m_transform.position += m_transform.forwards * a_delta_time * m_max_speed * -dot_fowards; // NEGATORY DOT

	// Check if arrived
	if (distance < m_arrival_distance)
	{
		// If arrived - Wander
		m_current_state = WANDER;
	}

	// Bounds check
	if (m_transform.position.x < 0 || m_transform.position.x > 1280
		|| m_transform.position < 0 || m_transform.position.y > 720)
	{
		m_current_state = SEEK;
		// Seek to center of screen
		m_target_position = m_screen_center;
	}
}

void Agent::wander(float a_delta_time)
{
	m_current_wander_timer -= a_delta_time;

	if (m_current_wander_timer <= 0)
	{
		m_current_state = FLEE;
		return;
	}

	Matrix3 vector_rotator = Matrix3();

	m_wander_rotation += ((rand() % 200) - 100) / 1000.f; // -0.1 to 0.099;

	//wander_rotation += *random range*;

	vector_rotator.setRotateZ(m_wander_rotation);
	Vector3 wander_vector = vector_rotator * Vector3(m_transform.forwards.x, m_transform.forwards.y);
	wander_vector = wander_vector * m_wander_radus;

	// Adjust the wander point
	m_target_position = 
		// Wander position
		Vector2(m_transform.position.x, this->m_transform.position.y) +
		// Objects fowards * distance to wander circle origin
		Vector2(m_transform.forwards.x, m_transform.forwards.y) * m_wander_projection +
		// Vector of lengthredus with wanser rotation applied
		Vector2(wander_vector.x, wander_vector.y);

	seek(a_delta_time);
}

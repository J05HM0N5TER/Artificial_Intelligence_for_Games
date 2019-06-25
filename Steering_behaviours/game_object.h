#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Circle.h"
#include "Matrix3.h"
#include "Renderer2D.h"
#include "Vector2.h"
#include "Texture.h"
#include <vector>

class game_object
{
public:
	// Delete default constructor because class doesn't work without renderer, texture and position.
	game_object() = delete;

	/*!	\brief Constructor for game_object.
		\param a_renderer A pointer to the renderer that is being used in the project, this is used to draw itself on screen.
		\param a_texture A pointer to the aie::Texture that you want the game_object to be displayed as.
		\param a_position The position on screen that you want the game_object to be displayed at (does not include transformations).
		\param a_z_rotation The rotation that you want the object to be placed at.
		\param a_size The size that you want the game_object to be drawn at.
		\param a_spin_speed The speed that the game_object spins around itself.
		\param a_orbit_speed The speed that the game_object rotates around it's parent game_object.
	*/
	game_object(aie::Renderer2D* a_renderer, aie::Texture* a_texture, const Vector2 a_position, const float a_z_rotation = 0.0f, 
		const Vector2 a_size = { 0.0f, 0.0f }, const float a_spin_speed = 0.0f, const float a_orbit_speed = 0.0f);


	// \brief Updates the position for the game_object.
	void update(const float a_delta_time);


	// \brief Draws the object on screen.
	void draw();

	// \brief Returns the world position of the object.
	const Matrix3& get_world_matrix() const;

	//void set_position(const Vector2& a_position);
	void set_local_position(const Vector2& a_position);
	const Vector2 get_local_position() const;

	/*!	\brief Manually sets the rotation of the game_object
		\param a_rotation The rotation that is being set in radians.
	*/
	void set_local_rotation(const float& a_rotation);

	// \brief Gets the rotation of the object with the transforms of the parents into account.
	const float get_global_rotation() const;
	// \brief Sets the rotation that doesn't get affected by the transforms of the parent objects.
	void set_global_rotation(const float& a_rotaion_speed);
	// \brief Sets the orbit speed that doesn't get affected by the transforms of the parent objects.
	void set_global_orbit(const float& a_orbit_speed);

	// -Orbit speed setters and getters-
	void set_orbit_speed(const float& a_orbit_speed);
	const float& get_orbit_speed() const;

	// \brief Gets the local rotation speed.
	const float& get_rotation_speed() const;
	void set_rotation_speed(const float a_rotation_speed);


	// -Parent setters and getters-
	void set_parent(game_object* a_parent);
	game_object* get_parent() const;

	// -Display size setters and getters-
	void set_size(const Vector2& a_size);
	const Vector2& get_size() const;

	// -Acceleration setters and getters-
	void set_acceleration(const float a_acceleration);
	const float get_acceleration() const;

	// -Speed setters and getters-
	void set_speed(const float& a_speed);
	const float & get_speed() const;

	// -Getters and setters for collider-
	void set_collider(circle * a_colider);
	const circle* get_collider() const;

	// -Getters and setters for texture-
	void set_texture(aie::Texture* a_texture);
	const aie::Texture* get_texture() const;

	// Getters and setters for max speed.
	void set_max_speed(const float a_max_speed);
	const float get_max_speed() const;

	const Matrix3 & get_local_transform() const;
	void set_local_transform(const Matrix3 & a_local_transform);

	// If the game_objetct is still valid.
	bool is_valid;

private:

	// The collision detector for the game_object.
	circle* m_collider;

	// The transform that has all the parents transforms taken into account.
	Matrix3 m_world_transform;
	// The transform that has not taken all the parents transforms into account.
	Matrix3 m_local_transform;

	// How quick the object orbits the parent in radians per second.
	float m_orbit_speed;
	// How quick the object rotates in radians per second.
	float m_rotation_speed;

	// The current linear speed (DOES NOT INCLUDE PARENT TRANSFORM AND ORBIT CHANGES.)
	float m_speed;
	// The linear acceleration over time.
	float m_acceleration;
	// The maximum linear speed that the object is allowed to achieve.
	float m_max_speed;


	// The size the object will be displayed at.
	Vector2 m_size;

	// The current local rotation.
	float m_current_rotation;

	// The parent that this object has to take into account when creating the world_transform.
	game_object* m_parent;

	// What the object is being drawn as.
	aie::Texture* m_texture;

	// The pointer to the renderer so it can draw itself.
	aie::Renderer2D* m_renderer;

	// A vector of all the object that are using this objects transform in there calculations for there world_transform.
	std::vector<game_object*> m_children;

	// \brief Added a child to the object.
	void add_child(game_object* a_child);
};

#endif // !GAME_OBJECT_H

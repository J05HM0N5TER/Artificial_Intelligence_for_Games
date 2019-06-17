#include "collider.h"



const collider::shape collider::get_shape() const
{
	return m_shape;
}

collider::collider(shape a_shape) : m_shape(a_shape)
{}


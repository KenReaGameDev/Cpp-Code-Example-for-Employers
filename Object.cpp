#include "Object.h"
#include <new>

Object::Object(Structs::L_POINT pos, Structs::L_POINT vel, bool enabled)
	: m_Position(pos)
	, m_Velocity(vel)
	, m_Enabled(enabled)
	, m_ConsecutiveCollisions(0)
	, m_ConsecutiveNonCollisions(0)
	, m_CollidedThisFrame(false)
{
		
}

Object::Object()
{
}

Object::~Object()
{

}

void Object::InverseVelocity()
{
	m_Velocity = m_Velocity * -1; 
	m_Position = m_Position + m_Velocity;
	m_CollidedThisFrame = true; 
	m_ConsecutiveCollisions++;

}

void Object::ResetCollsion()
{
	if (m_ConsecutiveCollisions == 0 && !m_CollidedThisFrame)
		m_ConsecutiveNonCollisions++;
	else
		m_ConsecutiveNonCollisions = 0;

	if (!m_CollidedThisFrame)
		m_ConsecutiveCollisions = 0;

	m_CollidedThisFrame = false;
}

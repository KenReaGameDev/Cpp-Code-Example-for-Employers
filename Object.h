#ifndef OBJECT_H
#define OBJECT_H

#include "Structs.h"

class BoxCollider;

// Screen Space Only
class Object {

public:
	
	Object(Structs::L_POINT pos, Structs::L_POINT vel, bool enabled);
	Object();
	virtual ~Object();

	Structs::L_POINT GetPosition() { return m_Position; };
	Structs::L_POINT GetVelocity() { return m_Velocity; };

	void InverseVelocity();
	void SetVelocity(Structs::L_POINT vel) { m_Velocity = vel; };
	void SetVelocityCollision(Structs::L_POINT vel) { m_Velocity = vel; m_CollidedThisFrame = true; m_ConsecutiveCollisions++; };
	void ResetCollsion();

	BoxCollider* m_Collider;
	bool	m_Enabled;
	bool	m_CollidedThisFrame;
	int		m_ConsecutiveCollisions;
	int		m_ConsecutiveNonCollisions;

private:
	
protected:

	Structs::L_POINT	m_Position;
	Structs::L_POINT	m_Velocity;
	
};

#endif // #ifndef OBJECT_H
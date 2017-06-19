#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Structs.h"
#include "Object.h"
#include  <cmath>

// Screen Space Only
class BoxCollider {

public:

	BoxCollider(Object owner, Structs::L_POINT top, Structs::L_POINT bottom);
	BoxCollider(Object owner);
	BoxCollider();
	~BoxCollider();

	Structs::L_POINT m_TopLeft;
	Structs::L_POINT m_BottomRight;

	// For Barrier
	Structs::L_POINT m_Repulse;
	// For Use when pushed inside wall.
	Structs::L_POINT m_ResetDirection;

	void SetOwner(Object own) { m_Owner = own; };
	
	// For Box Collider Only
	bool CheckCollision(const BoxCollider& col) const;
	bool CheckCollision(const Structs::L_POINT& point) const;
	
	int		m_Radius;

private:

	Object m_Owner;
	bool CheckCollides(const int& value, const int& min, const int& max) const;
};

#endif // #ifndef BOXCOLLIDER_H
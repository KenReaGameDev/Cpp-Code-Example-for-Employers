#include "BoxCollider.h"

BoxCollider::BoxCollider(Object owner, Structs::L_POINT top, Structs::L_POINT bottom)
	: m_TopLeft(top)
	, m_BottomRight(bottom)
	, m_Owner(owner)
{
	m_Radius = abs(top.x - bottom.x) / 2;	
	m_Owner = owner;
}

BoxCollider::BoxCollider(Object owner)
	: m_Owner(owner)
{

}

BoxCollider::BoxCollider()	
{
	m_Owner = Object();
}

BoxCollider::~BoxCollider()
{

}


bool BoxCollider::CheckCollides(const int& value, const int& min, const int& max) const
{
	return (value >= min) && (value <= max);
}


bool BoxCollider::CheckCollision(const BoxCollider& col) const
{
	bool collidesX = CheckCollides(m_TopLeft.x, col.m_TopLeft.x, col.m_TopLeft.x + (col.m_BottomRight.x - col.m_TopLeft.x)) ||
		CheckCollides(col.m_TopLeft.x, m_TopLeft.x, m_TopLeft.x + (m_BottomRight.x - m_TopLeft.x));

	// Early Out to Avoid 2nd Check
	if (!collidesX)
		return false;

	bool collidesY = CheckCollides(m_TopLeft.y, col.m_TopLeft.y, col.m_TopLeft.y + (col.m_BottomRight.y - col.m_TopLeft.y)) ||
		CheckCollides(col.m_TopLeft.y, m_TopLeft.y, m_TopLeft.y + (m_BottomRight.y - m_TopLeft.y));


	// If Collided with Barrier, Repulse Object
	return (collidesX && collidesY);

}

bool BoxCollider::CheckCollision(const Structs::L_POINT& point) const
{
	if (point.x > m_TopLeft.x && point.x < m_BottomRight.x
		&& point.y > m_TopLeft.y && point.y < m_BottomRight.y)
		return true;

		return false;
}

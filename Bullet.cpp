#include "Bullet.h"
#include "graphics.h"

Bullet::Bullet(Structs::L_POINT pos, Structs::L_POINT vel, int size, bool enabled) : Object(pos, vel, enabled)
	, m_Size(size)
{

}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Enable(Structs::L_POINT pos, Structs::L_POINT vel)
{
	m_Position = pos;
	m_Velocity = vel;
	m_Enabled = true;
}

void Bullet::Update()
{
	m_Position = m_Position + m_Velocity;
}

const void Bullet::Draw()
{
	Structs::L_POINT nVelocity = Structs::Normalize(m_Velocity) * m_Size;
	DrawLine(m_Position.x, m_Position.y, m_Position.x- nVelocity.x, m_Position.y - nVelocity.y, GetRGB(255,255,255));
}

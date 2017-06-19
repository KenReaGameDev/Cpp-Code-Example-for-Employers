#include "Clock.h"
#include "graphics.h"
#include "time.h"
#include <random>

Structs::LINE_COORDINATES Clock::m_MinuteHand;
Structs::LINE_COORDINATES Clock::m_SecondsHand;
Structs::LINE_COORDINATES Clock::m_HourHand;
float		Clock::m_AngleHours;
float		Clock::m_AngleMinutes;
float		Clock::m_AngleSeconds;
Clock::Clock(int size, Structs::L_POINT startPos, Structs::L_POINT vel, bool enabled) : Object(startPos, vel, enabled)
{
	m_SizeIndex = size;
	m_Size = m_Sizes[m_SizeIndex];
	m_Collider = new BoxCollider(*this);
	m_Collider->m_Radius = 50 / m_Size;
	SetCollider();	
}

Clock::Clock()
{
}

Clock::~Clock()
{

}

// Set the Collider information during Initialization.
void Clock::SetCollider()
{
	m_Collider->m_TopLeft.x = m_Position.x - 50 / m_Size;
	m_Collider->m_TopLeft.y = m_Position.y - 50 / m_Size;

	m_Collider->m_BottomRight.x = m_Position.x + 50 / m_Size;
	m_Collider->m_BottomRight.y = m_Position.y + 50 / m_Size;	
}

void Clock::UpdatePosition()
{
	m_Position = m_Position + m_Velocity;
	m_Collider->m_TopLeft = m_Collider->m_TopLeft + m_Velocity;
	m_Collider->m_BottomRight = m_Collider->m_BottomRight + m_Velocity;
}

// Reset Hands so calculation can be done from 0 base otherwise hands can get skewed.
void Clock::ResetHands()
{
	Clock::m_MinuteHand.p1	= Structs::L_POINT(0, 0);
	Clock::m_MinuteHand.p2	= Structs::L_POINT(0, Clock::m_MinuteSize);

	Clock::m_SecondsHand.p1 = Structs::L_POINT(0, 0);
	Clock::m_SecondsHand.p2 = Structs::L_POINT(0, Clock::m_SecondsSize);

	Clock::m_HourHand.p1	= Structs::L_POINT(0, 0);
	Clock::m_HourHand.p2	= Structs::L_POINT(0, Clock::m_HourSize);
}

// When Split, Clocks need to be set to new parameters to be properly utilized.
void  Clock::Reconstruct(bool enabled, int size, Structs::L_POINT pos, Structs::L_POINT velocity)
{
	m_Enabled = enabled;
	m_SizeIndex = size;
	m_Size = m_Sizes[m_SizeIndex];
	m_Collider->m_Radius = 50 / m_Size;
	m_Position = pos;
	m_Velocity = velocity;
	SetCollider();
}

// Splits clocks using disabled clocks.
void Clock::SplitClock(std::vector<Clock*> &m_ClocksUnused, std::vector<Clock*> &m_ClocksUsed)
{
	if (m_SizeIndex >= 5)
		return;

	m_SizeIndex++;
	int newSize = m_Sizes[m_SizeIndex];


	// Re-use disabled clocks as to not instantiate a clock every time one is hit.
	Clock& c = *m_ClocksUnused.back();	
	c.Reconstruct(true, m_SizeIndex, Structs::L_POINT(m_Position.x - 80 / newSize,  m_Position.y - 25),
		Structs::L_POINT(Structs::RandomNumber(-3, 3, false), Structs::RandomNumber(-3, 3, false)));
	m_ClocksUsed.push_back(&c);
	m_ClocksUnused.pop_back();
	

	Clock& c2 = *m_ClocksUnused.back();	
 	c2.Reconstruct(true, m_SizeIndex, Structs::L_POINT(m_Position.x + 80 / newSize, m_Position.y +25),
		Structs::L_POINT(Structs::RandomNumber(-3, 3, false), Structs::RandomNumber(-3, 3, false)));
	m_ClocksUsed.push_back(&c2);
	m_ClocksUnused.pop_back();

}

// Calculate angle in which line will be drawn and set line up for drawing.
void Clock::UpdateLine(Structs::LINE_COORDINATES &line, const float& angle)
{
	float s = sin(angle);
	float c = cos(angle);

	// rotate point
	float p2_newX = line.p2.x * c - line.p2.y * s;
	float p2_newY = line.p2.x * s + line.p2.y * c;

	// translate point back:
	line.p2.x = p2_newX;
	line.p2.y = p2_newY;
}

// Called Once Per Frame, Update the hands positioning
void Clock::UpdateHands()
{
	ResetHands();

	int seconds, minutes, hours;
	GetTime(hours, minutes, seconds);

	// Calculate degrees of clock hands and account for minutes affecting
	// hours and seconds affecting minutes for a more accurate clock. 
	m_AngleSeconds	= seconds * 360 / 60;
	m_AngleMinutes	= (minutes + (seconds / 60)) * 360 / 60;
	m_AngleHours	= (hours + (minutes / 60)) * 360 / 24;

	// Convert from Degrees to Radians.
	m_AngleSeconds	= m_AngleSeconds * (M_PI / 180);
	m_AngleMinutes	= m_AngleMinutes * (M_PI / 180);
	m_AngleHours	= m_AngleHours	 * (M_PI / 180);

	UpdateLine(Clock::m_SecondsHand, m_AngleSeconds);
	UpdateLine(Clock::m_MinuteHand, m_AngleMinutes);
	UpdateLine(Clock::m_HourHand, m_AngleHours);
}

// Draws the Clock, called once per frame.
const void Clock::Draw()
{
	int offset = 50 / m_Size;

	// Draw Outline
	DrawLine(m_Position.x - offset, m_Position.y - offset, m_Position.x + offset, m_Position.y - offset, GetRGB(255, 0, 0));
	DrawLine(m_Position.x - offset, m_Position.y + offset, m_Position.x + offset, m_Position.y + offset, GetRGB(255, 0, 0));
	DrawLine(m_Position.x - offset, m_Position.y - offset, m_Position.x - offset, m_Position.y + offset, GetRGB(255, 0, 0));
	DrawLine(m_Position.x + offset, m_Position.y - offset, m_Position.x + offset, m_Position.y + offset, GetRGB(255, 0, 0));


	// Draw Clock Hands
	// Compenate for m_Size in Point 2 Values
	DrawLine(Clock::m_SecondsHand.p1.x + m_Position.x,
		Clock::m_SecondsHand.p1.y + m_Position.y,
		(Clock::m_SecondsHand.p2.x / m_Size) + m_Position.x,
		(Clock::m_SecondsHand.p2.y / m_Size) + m_Position.y,
		GetRGB(255, 255, 255));

	DrawLine(Clock::m_HourHand.p1.x + m_Position.x,
		Clock::m_HourHand.p1.y + m_Position.y,
		(Clock::m_HourHand.p2.x / m_Size) + m_Position.x,
		(Clock::m_HourHand.p2.y / m_Size) + m_Position.y,
		GetRGB(255, 255, 0));

	DrawLine(Clock::m_MinuteHand.p1.x + m_Position.x,
		Clock::m_MinuteHand.p1.y + m_Position.y,
		(Clock::m_MinuteHand.p2.x / m_Size) + m_Position.x,
		(Clock::m_MinuteHand.p2.y / m_Size) + m_Position.y,
		GetRGB(0, 255, 255));
}

const void Clock::Draw(float colors[3])
{
	int offset = 50 / m_Size;

	// Draw Outline
	DrawLine(m_Position.x - offset, m_Position.y - offset, m_Position.x + offset, m_Position.y - offset, GetRGB(colors[0], colors[1], colors[2]));
	DrawLine(m_Position.x - offset, m_Position.y + offset, m_Position.x + offset, m_Position.y + offset, GetRGB(colors[0], colors[1], colors[2]));
	DrawLine(m_Position.x - offset, m_Position.y - offset, m_Position.x - offset, m_Position.y + offset, GetRGB(colors[0], colors[1], colors[2]));
	DrawLine(m_Position.x + offset, m_Position.y - offset, m_Position.x + offset, m_Position.y + offset, GetRGB(colors[0], colors[1], colors[2]));


	// Draw Clock Hands
	// Compenate for m_Size in Point 2 Values
	DrawLine(Clock::m_SecondsHand.p1.x + m_Position.x,
		Clock::m_SecondsHand.p1.y + m_Position.y,
		(Clock::m_SecondsHand.p2.x / m_Size) + m_Position.x,
		(Clock::m_SecondsHand.p2.y / m_Size) + m_Position.y,
		GetRGB(255, 255, 255));

	DrawLine(Clock::m_HourHand.p1.x + m_Position.x,
		Clock::m_HourHand.p1.y + m_Position.y,
		(Clock::m_HourHand.p2.x / m_Size) + m_Position.x,
		(Clock::m_HourHand.p2.y / m_Size) + m_Position.y,
		GetRGB(255, 255, 0));

	DrawLine(Clock::m_MinuteHand.p1.x + m_Position.x,
		Clock::m_MinuteHand.p1.y + m_Position.y,
		(Clock::m_MinuteHand.p2.x / m_Size) + m_Position.x,
		(Clock::m_MinuteHand.p2.y / m_Size) + m_Position.y,
		GetRGB(0, 255, 255));
}

// Sets new position of clock
void Clock::MovePosition(Structs::L_POINT pos)
{
	m_Position = m_Position + pos;
	m_Collider->m_TopLeft = m_Collider->m_TopLeft + pos;
	m_Collider->m_BottomRight = m_Collider->m_BottomRight + pos;
}

void Clock::SetPosition(Structs::L_POINT pos)
{
	m_ConsecutiveNonCollisions = 0;
	m_ConsecutiveCollisions = 0;
	m_Position = pos;
	SetCollider();
}
void Clock::ResetPosition()
{
	m_ConsecutiveNonCollisions = 0;
	m_ConsecutiveCollisions = 0;
	m_Position = Structs::L_POINT(51, 51);
	SetCollider();
}


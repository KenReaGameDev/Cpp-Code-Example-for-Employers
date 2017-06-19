#ifndef TEST_C_CLOCK_H
#define TEST_C_CLOCK_H


#define M_PI           3.14159265358979323846  /* pi */
#include <vector>
#include "Structs.h"
#include "Object.h"
#include "BoxCollider.h"

class  Clock : public Object{

public:

	 Clock (int size, Structs::L_POINT startPos, Structs::L_POINT vel, bool enabled);
	 Clock();
	 ~ Clock();

	void Reconstruct(bool enabled, int size, Structs::L_POINT pos, Structs::L_POINT velocity);
	void SplitClock(std::vector<Clock*> &m_ClocksUnused, std::vector<Clock*> &m_ClocksUsed);
	void UpdateLine(Structs::LINE_COORDINATES &line, const float& angle);
	void UpdateHands();
	const void Draw();
	const void Draw(float colors[3]);
	void ResetHands();
	void SetPosition(Structs::L_POINT pos);
	void MovePosition(Structs::L_POINT pos);
	void ResetPosition();
	void SetCollider();
	void UpdatePosition();
	int GetSize() { return m_Size; };

	static const int			Clock::m_MinuteSize = -32;
	static const int			Clock::m_HourSize = -20;
	static const int			Clock::m_SecondsSize = -44;

	
	static float		m_AngleHours;
	static float		m_AngleMinutes;
	static float		m_AngleSeconds;

	static Structs::LINE_COORDINATES Clock::m_MinuteHand;
	static Structs::LINE_COORDINATES Clock::m_HourHand;
	static Structs::LINE_COORDINATES Clock::m_SecondsHand;

private:

	int						m_Size;
	int						m_SizeIndex;
	int						m_Sizes[6] = {0, 1, 2, 4, 7, 10 };
	bool					m_CollisionEnabled;

};


#endif // #ifndef TEST_C_CLOCK_H
#include "C_Application.h"
#include "graphics.h"
#include "time.h"
#include <random>


static const float k_PI = 3.1415926536f;


C_Application::C_Application(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
	, m_CannonX(m_ScreenWidth / 2)
	, m_CannonY(m_ScreenHeight * 0.9)
	, m_CurrentAngle(0)
	, m_CanFire(true)
	, m_BulletVelocity(8)
	, m_BulletSize(3)
	, m_Fired(0)
	, m_Pivot(Structs::L_POINT(m_CannonX, m_CannonY + 15))
	, m_DebugAngling(false)
	, m_CaseTest(false)
	, m_Title(screenWidth, screenHeight)
{
	SetupLines();
	SetBoundries();
	CreateInitialBullets();
	CreateInitialClocks();
	
}

// Create Total Amount of bullets neccesary to now have to create any during play under any circumstance.
void C_Application::CreateInitialBullets()
{
	m_BulletCount = sqrt(pow(m_ScreenHeight,2) + pow(m_ScreenWidth,2)) / m_BulletSize / 2;
	
	for (int i = 0; i < m_BulletCount; i++)
		m_BulletsUnused.push_back(Bullet(m_Cannon[0].p1 , m_Cannon[0].p1 * m_BulletVelocity, m_BulletSize, false));
}

// Resets Original 2 Clocks and Randomizes their positions / velocities.
void C_Application::ResetClocks()
{
	for (int i = 0; i < 2; i++)
	{
		Clock* c = m_ClocksUnused.back();
		c->Reconstruct(true, 1, Structs::L_POINT(Structs::RandomNumber(250 * i + 50, 300 * (i + 1), false), Structs::RandomNumber(250 * i + 50, 250 * (i + 1), false)),
			Structs::L_POINT(Structs::RandomNumber(-3, 3, true), Structs::RandomNumber(-3, 3, true)));
		m_ClocksUnused.pop_back();
		m_ClocksUsed.push_back(c);
	}
}

// Create First 2 Clocks and All other Unused Clocks
void C_Application::CreateInitialClocks()
{
	
	// Enabled
	for (int i = 0; i < 2; i++)
	{
		// Make sure clocks cannot spawn inside of each other
		m_ClocksUsed.push_back(new Clock(1, Structs::L_POINT(Structs::RandomNumber(250 * i + 50, 300 * (i + 1), false), Structs::RandomNumber(250 * i + 50, 250 * (i + 1), false)),
			Structs::L_POINT(Structs::RandomNumber(-3, 3, true), Structs::RandomNumber(-3, 3, true)), true));
	}

	// 2^6-2 total possible clocks	
	for (int i = 0; i < pow(2, 5) - 2; i++)
	{
		m_ClocksUnused.push_back(new Clock(1, Structs::L_POINT(Structs::RandomNumber(250 * i + 50, 300 * (i + 1), false), Structs::RandomNumber(250 * i + 50, 250 * (i + 1), false)),
			Structs::L_POINT(Structs::RandomNumber(-2, 2, true), Structs::RandomNumber(-2, 2, true)), false));
	}
}

// Set up the boundries
void C_Application::SetBoundries()
{
	for (int i = 0; i < 4; i++)
		m_Boundries[i] = BoxCollider();

	//Top
	m_Boundries[0].m_TopLeft = Structs::L_POINT(-500, -500);
	m_Boundries[0].m_BottomRight = Structs::L_POINT(m_ScreenWidth + 500, 0);
	m_Boundries[0].m_Repulse = Structs::L_POINT(1, -1);
	m_Boundries[0].m_ResetDirection = Structs::L_POINT(0, 1);
	//Left
	m_Boundries[1].m_TopLeft = Structs::L_POINT(-500, 0);
	m_Boundries[1].m_BottomRight = Structs::L_POINT(0, m_ScreenHeight);
	m_Boundries[1].m_Repulse = Structs::L_POINT(-1, 1);
	m_Boundries[1].m_ResetDirection = Structs::L_POINT(1, 0);

	//Right
	m_Boundries[2].m_TopLeft = Structs::L_POINT(m_ScreenWidth, 0);
	m_Boundries[2].m_BottomRight = Structs::L_POINT(m_ScreenWidth + 500, m_ScreenHeight);
	m_Boundries[2].m_Repulse = Structs::L_POINT(-1, 1);
	m_Boundries[2].m_ResetDirection = Structs::L_POINT(-1, 0);

	//Bottom
	m_Boundries[3].m_TopLeft = Structs::L_POINT(-500, m_ScreenHeight);
	m_Boundries[3].m_BottomRight = Structs::L_POINT(m_ScreenWidth + 500, m_ScreenHeight + 500);
	m_Boundries[3].m_Repulse = Structs::L_POINT(1, -1);
	m_Boundries[3].m_ResetDirection = Structs::L_POINT(0, -1);
}

// Do Cannon Manually as there will be no Re-Use
void C_Application::SetupLines()
{
	Structs::LINE_COORDINATES L1, L2, L3;

	// Setup Line 1
	L1.p1.x = m_CannonX;
	L1.p1.y = m_CannonY;
	L1.p2.x = m_CannonX - 10;
	L1.p2.y = m_CannonY + 30;

	// Setup Line 2
	L2.p1.x = m_CannonX;
	L2.p1.y = m_CannonY;
	L2.p2.x = m_CannonX + 10;
	L2.p2.y = m_CannonY + 30;

	// Setup Line 3
	L3.p1.x = m_CannonX - 10;
	L3.p1.y = m_CannonY + 30;
	L3.p2.x = m_CannonX + 10;
	L3.p2.y = m_CannonY + 30;

	m_Cannon[0] = L1;
	m_Cannon[1] = L2;
	m_Cannon[2] = L3;

	// DEBUG
	m_InitCannon[0] = L1;
	m_InitCannon[1] = L2;
	m_InitCannon[2] = L3;
}

C_Application::~C_Application()
{

}

void C_Application::ClearScreen()
{
	FillRect(0, 0, m_ScreenWidth, m_ScreenHeight, GetRGB(0, 0, 0));
}

void C_Application::RotateTriangle(float angle)
{
	m_CurrentAngle += angle;

	for (int i = 0; i < 3; i++)
		m_Cannon[i] = RotateLine(m_CurrentAngle, m_InitCannon[i]);
}


// Rotate Point around Point.
void C_Application::RotatePoint(float angle, float &x, float &y)
{
	angle = angle * (M_PI / 180);

	float s = sin(angle);
	float c = cos(angle);

	x -= m_Pivot.x;
	y -= m_Pivot.y;

	float newX = x * c - y * s;
	float newY = x * s + y * c;

	x = newX + m_Pivot.x;
	y = newY + m_Pivot.y;
}

// DEBUG
Structs::LINE_COORDINATES C_Application::RotateLine(float angle, Structs::LINE_COORDINATES line)
{
	// Convert to Radians.
	angle = angle * (M_PI / 180);

	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	line.p1.x -= m_Pivot.x;
	line.p1.y -= m_Pivot.y;
	line.p2.x -= m_Pivot.x;
	line.p2.y -= m_Pivot.y;

	// rotate point
	float p1_newX = line.p1.x * c - line.p1.y * s;
	float p1_newY = line.p1.x * s + line.p1.y * c;
	float p2_newX = line.p2.x * c - line.p2.y * s;
	float p2_newY = line.p2.x * s + line.p2.y * c;

	// translate point back:
	line.p1.x = p1_newX + m_Pivot.x;
	line.p1.y = p1_newY + m_Pivot.y;
	line.p2.x = p2_newX + m_Pivot.x;
	line.p2.y = p2_newY + m_Pivot.y;

	return line;
}

void C_Application::DrawClocks()
{
	int ClocksOnScreen = 0;
	

	for (int i = 0; i < m_ClocksUsed.size(); i++)
	{
		m_ClocksUsed[i]->Draw();
		m_ClocksUsed[i]->UpdatePosition();
		ClocksOnScreen++;
	}

	if (ClocksOnScreen == 0)
		ResetClocks();
}

void C_Application::FireBullet()
{
 	Structs::L_POINT dir = m_Cannon[0].p1 - m_Pivot;
	
	// bullet unused to used
	m_BulletsUsed.push_back(m_BulletsUnused.back());
	m_BulletsUnused.pop_back();
	m_BulletsUsed.back().Enable(m_Cannon[0].p1 + dir, Structs::Normalize(dir) * m_BulletVelocity);

	m_CanFire = false;
	m_FramesSinceFired = 0;

}

// Used for Testing the Game
void C_Application::CaseTesting()
{
	FireBullet();

	if (m_DebugAngling && m_CurrentAngle > -m_LimitAngle)
		RotateTriangle(-1);

	if (!m_DebugAngling && m_CurrentAngle < m_LimitAngle)
		RotateTriangle(1);

	if (m_DebugAngling && m_CurrentAngle <= -m_LimitAngle)
		m_DebugAngling = !m_DebugAngling;

	if (!m_DebugAngling && m_CurrentAngle >= m_LimitAngle)
		m_DebugAngling = !m_DebugAngling;
}

void C_Application::ParseKeys(T_PressedKey pressedKeys)
{		
	if (pressedKeys & s_KeyLeft && m_CurrentAngle > -m_LimitAngle)
		RotateTriangle(-2);

	if (pressedKeys & s_KeyRight && m_CurrentAngle < m_LimitAngle)
		RotateTriangle(2);

	if (pressedKeys & s_KeyUp)
		m_CaseTest = true;

	if (pressedKeys & s_KeyDown)
		m_CaseTest = false;

	// Create bullets
	if (pressedKeys & s_KeySpace && m_CanFire)
		FireBullet();

}

void C_Application::CheckClockCollisions()
{
	for (int i = 0; i < m_ClocksUsed.size(); i++)
	{		
		m_ClocksUsed[i]->ResetCollsion();
		for (int n = i + 1; n < m_ClocksUsed.size(); n++)
		{
			if (m_ClocksUsed[i]->m_Collider->CheckCollision(*m_ClocksUsed[n]->m_Collider))
			{
				m_ClocksUsed[i]->InverseVelocity();
				m_ClocksUsed[n]->InverseVelocity();

				if (m_ClocksUsed[i]->m_ConsecutiveCollisions > 5)
				{
					Structs::L_POINT  iPos = m_ClocksUsed[i]->GetPosition();
					Structs::L_POINT  nPos = m_ClocksUsed[n]->GetPosition();
					m_ClocksUsed[i]->SetPosition(Structs::L_POINT(nPos.x + 25, nPos.y + 25));
					m_ClocksUsed[n]->SetPosition(Structs::L_POINT(iPos.x - 25, iPos.y - 25));
				}
			}
		}

		// Only Allow 1 Boundry Collision Per Frame
		for (int n = 0; n < 4; n++)
		{
			if (m_ClocksUsed[i]->m_Collider->CheckCollision(m_Boundries[n]))
			{
				m_ClocksUsed[i]->SetVelocityCollision(m_ClocksUsed[i]->GetVelocity() * m_Boundries[n].m_Repulse);

				if (m_ClocksUsed[i]->m_ConsecutiveCollisions > 5)
					m_ClocksUsed[i]->MovePosition(m_Boundries[n].m_ResetDirection * 3);

				break;
			}
		}
	}	

	if (m_ClocksUsed.size() == 0)
		ResetClocks();
}


void C_Application::UpdateClocks()
{	
	CheckClockCollisions();
	m_ClocksUsed[0]->UpdateHands();
}

void C_Application::UpdateBullets()
{
	int bulletCount = m_BulletsUsed.size();
	bool collided;
	for (int i = m_BulletsUsed.size() - 1; i >= 0; i--)
	{
 		m_BulletsUsed[i].Update();
		collided = false;
		

		// Check Against Clock
		for (int n = m_ClocksUsed.size() - 1; n >= 0; n--)
		{
			if (m_ClocksUsed[n]->m_Collider->CheckCollision(m_BulletsUsed[i].GetPosition()))
			{	
				// Pop and Swap Clock to Unused
				m_ClocksUnused.push_back(m_ClocksUsed[n]);
				std::iter_swap(m_ClocksUsed.begin() + n, m_ClocksUsed.end() - 1);
				m_ClocksUsed.pop_back();
				m_ClocksUnused.back()->SplitClock(m_ClocksUnused, m_ClocksUsed);
				
				// Pop and Swap Bullet to Unused
				std::iter_swap(m_BulletsUsed.begin() + i, m_BulletsUsed.end() - 1);
				m_BulletsUnused.push_back(m_BulletsUsed.back());
				m_BulletsUsed.pop_back();
				collided = true;
         		break;					
			}
		}

		if (collided)
			continue;

		// Check Against Boundries. Bottom Boundry is 4. Skip Bottom
		for (int n = 0; n < 3; n++)
		{
			if (m_Boundries[n].CheckCollision(m_BulletsUsed[i].GetPosition()))
			{

					// Pop and Swap Bullet to Unused
				std::iter_swap(m_BulletsUsed.begin() + i, m_BulletsUsed.end() - 1);
				m_BulletsUnused.push_back(m_BulletsUsed.back());
				m_BulletsUsed.pop_back();
				break;
			}
		}
	}

	for (int i = m_BulletsUsed.size() - 1; i > 0; i--)
	{
		m_BulletsUsed[i].Draw();
	}
}

void C_Application::DrawCannon() const
{
	for (int i = 0; i < 3; i++)
		DrawLine(m_Cannon[i].p1.x, m_Cannon[i].p1.y, m_Cannon[i].p2.x, m_Cannon[i].p2.y, GetRGB(0, 0, 255));
}

void C_Application::UpdateCannon(T_PressedKey pressedKeys)
{
	if (m_FramesSinceFired++ > 1)
		m_CanFire = true;

	if (m_CaseTest)
		CaseTesting();

	// Key processing
	ParseKeys(pressedKeys);	
}

void C_Application::Tick(T_PressedKey pressedKeys)
{

	//if (m_Title.m_Enabled)
	//{
	//	m_Title.DrawTitle();
	//	return;
	//}

	ClearScreen();
	UpdateCannon(pressedKeys);
	UpdateClocks();
	UpdateBullets();

	DrawCannon();
	DrawClocks();
}

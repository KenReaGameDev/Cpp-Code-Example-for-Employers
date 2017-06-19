#ifndef TEST_C_APPLICATION_H
#define TEST_C_APPLICATION_H

#define M_PI           3.14159265358979323846  /* pi */

#include <vector>
#include "Clock.h"
#include "Structs.h"
#include "BoxCollider.h"
#include "Object.h"
#include "Bullet.h"
#include "TitleScreen.h"

class C_Application
{
public:
	


	typedef unsigned int T_PressedKey;

	C_Application(int screenWidth, int screenHeight);
	~C_Application();	

	/// Tick is called on fix framerate (50fps)
	void Tick(T_PressedKey pressedKeys);
	void UpdateClocks();
	void UpdateCannon(T_PressedKey pressedKeys);
	void DrawCannon() const;
	void UpdateBullets();

	// Rendering
	void ClearScreen();
	void DrawClocks();
	void CreateInitialClocks();
	void CreateInitialBullets();
	void ResetClocks();
	void SetBoundries();
	void FireBullet();
	void CaseTesting();
	void ParseKeys(T_PressedKey pressedKeys);
	void CheckClockCollisions();
	void RotateTriangle(float angle);	
	Structs::LINE_COORDINATES RotateLine(float angle, Structs::LINE_COORDINATES line);
	void RotatePoint(float angle, float &x, float &y);

	void SetupLines();

	static const T_PressedKey s_KeyLeft  = 0x01;
	static const T_PressedKey s_KeyUp    = 0x02;
	static const T_PressedKey s_KeyRight = 0x04;
	static const T_PressedKey s_KeyDown  = 0x08;
	static const T_PressedKey s_KeySpace = 0x10;
	

private:

	const int	m_ScreenWidth;
	const int	m_ScreenHeight;
	const double m_LimitAngle = 90;

	// Members for sample tick
	int			m_CannonX;
	int			m_CannonY;
	int			m_FramesSinceFired;
	int			m_BulletVelocity;
	int			m_BulletSize;
	int			m_BulletCount;
	int			m_Fired;	
	bool		m_CanFire;
	bool		m_DebugAngling;
	bool		m_CaseTest;
	float		m_CurrentAngle;

	Structs::L_POINT		m_Pivot;
	Structs::LINE_COORDINATES	m_Cannon[3], m_InitCannon[3];
	std::vector<Clock*> m_ClocksUnused, m_ClocksUsed;
	std::vector<Bullet> m_BulletsUsed, m_BulletsUnused;
	
	BoxCollider		   m_Boundries[4];

	TitleScreen m_Title;

};

#endif // #ifndef TEST_C_APPLICATION_H

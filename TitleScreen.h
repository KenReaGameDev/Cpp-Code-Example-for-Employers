
#ifndef TITLE_H
#define TITLE_H

#include "Structs.h"
#include "Object.h"
#include "Clock.h"
#include <vector>

class TitleScreen
{

public:


	TitleScreen(int width, int height);
	~TitleScreen();

	void AdjustColor(int multiplier);
	bool ToBlack();
	void DrawTitle();
	void GenerateClock();
	void GenerateLetters();
	void GenerateLines(int row, int column, Structs::LINE_COORDINATES line);
	Structs::LINE_COORDINATES GenerateLine(int x1, int y1, int x2, int y2);	

	bool	m_Enabled;
	int		m_ScreenWidth;
	int		m_ScreenHeight;
	int		m_CurrentColor;
	int		m_Cycled;
	float	m_Color[3];
	Clock	m_Clock;

	std::vector<std::vector<Structs::LINE_COORDINATES>> m_LetterLines;

	Structs::L_POINT	m_FirstLetterOffset;
	
private:
	

};

#endif // #ifndef TITLE_H
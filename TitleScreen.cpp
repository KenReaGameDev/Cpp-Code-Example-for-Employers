#include "TitleScreen.h"
#include "graphics.h"
TitleScreen::TitleScreen(int width, int height)
	: m_Enabled(true)
	, m_ScreenWidth(width)
	, m_ScreenHeight(height)
	, m_CurrentColor(0)
	, m_Cycled(0)
	, m_Clock(Clock())
{
	m_Color[0] = 255;
	m_Color[1] = 0;
	m_Color[2] = 0;
	
	GenerateLetters();
	GenerateClock();
}

void TitleScreen::GenerateClock()
{
	m_Clock = Clock(1, Structs::L_POINT(m_LetterLines[3][3].p1.x+50, m_LetterLines[3][3].p1.y-50), Structs::L_POINT(0, 0), true);
}

void TitleScreen::GenerateLetters()
{


	m_FirstLetterOffset.x = (m_ScreenWidth - (4 * 100) - (3 * 20)) / 2;
	m_FirstLetterOffset.y = (m_ScreenHeight - (3 * 100) - (2 * 25)) / 2;
	m_LetterLines.resize(9, std::vector<Structs::LINE_COORDINATES>(0));

	// T
	GenerateLines(0, 0, GenerateLine(0, 0, 100, 0));
	GenerateLines(0, 0, GenerateLine(50, 0, 50, 100));
	// I
	GenerateLines(0, 1, GenerateLine(50, 0, 50, 100));
	GenerateLines(0, 1, GenerateLine(0, 0, 100, 0));
	GenerateLines(0, 1, GenerateLine(0, 100, 100, 100));
	// M
	GenerateLines(0, 2, GenerateLine(0, 0, 0, 100));
	GenerateLines(0, 2, GenerateLine(100, 0, 100, 100));
	GenerateLines(0, 2, GenerateLine(0, 0, 50, 100));
	GenerateLines(0, 2, GenerateLine(50, 100, 100, 0));
	// E
	GenerateLines(0, 3, GenerateLine(0, 0, 100, 0));
	GenerateLines(0, 3, GenerateLine(0, 50, 100, 50));
	GenerateLines(0, 3, GenerateLine(0, 100, 100, 100));
	GenerateLines(0, 3, GenerateLine(0, 0, 0, 100));

	// T
	GenerateLines(3, 1, GenerateLine(0, 0, 100, 0));
	GenerateLines(3, 1, GenerateLine(50, 0, 50, 100));
	// O
	GenerateLines(3, 2, GenerateLine(0, 0, 100, 0));
	GenerateLines(3, 2, GenerateLine(0, 100, 100, 100));
	GenerateLines(3, 2, GenerateLine(0, 0, 0, 100));
	GenerateLines(3, 2, GenerateLine(100, 0, 100, 100));

	// K
	GenerateLines(6, 0, GenerateLine(15, 0, 15, 100));
	GenerateLines(6, 0, GenerateLine(15, 50, 85, 0));
	GenerateLines(6, 0, GenerateLine(15, 50, 85, 100));
	// I
	GenerateLines(6, 1, GenerateLine(50, 0, 50, 100));
	GenerateLines(6, 1, GenerateLine(0, 0, 100, 0));
	GenerateLines(6, 1, GenerateLine(0, 100, 100, 100));
	// L
	GenerateLines(6, 2, GenerateLine(0, 0, 0, 100));
	GenerateLines(6, 2, GenerateLine(0, 100, 100, 100));
	// L
	GenerateLines(6, 3, GenerateLine(0, 0, 0, 100));
	GenerateLines(6, 3, GenerateLine(0, 100, 100, 100));
}

// Output a Line Co-ordinate based on input.
Structs::LINE_COORDINATES TitleScreen::GenerateLine(int x1, int y1, int x2, int y2)
{
	Structs::LINE_COORDINATES line;

	line.p1 = Structs::L_POINT(x1, y1);
	line.p2 = Structs::L_POINT(x2, y2);

	return line;

}

// Adjust Generated Line based on Row and Column Position + Initial Offsets
void TitleScreen::GenerateLines(int row, int column, Structs::LINE_COORDINATES line)
{

	Structs::L_POINT letterOffset;
	letterOffset.x = (column * 100) + (20 * column);

	int y_line = row / 3;
	int y_spacing = y_line * 25;
	y_line *= 100;
	letterOffset.y = y_line + y_spacing;

	line.p1 = line.p1 + m_FirstLetterOffset + letterOffset;
	line.p2 = line.p2 + m_FirstLetterOffset + letterOffset;
	m_LetterLines[row].push_back(line);

}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::AdjustColor(int multiplier)
{
	if (m_Color[m_CurrentColor] >= 255)
		m_CurrentColor++;

	if (m_CurrentColor > 2)
	{
		m_CurrentColor = 0;
		m_Cycled++;
	}

	if (m_CurrentColor == 0)
	{
		m_Color[m_CurrentColor] += 0.1f * multiplier;
		m_Color[2] -= 0.1f * multiplier;
	}
	else {
		m_Color[m_CurrentColor] += 0.1f * multiplier;
		m_Color[m_CurrentColor - 1] -= 0.1f * multiplier;
	}
}

bool TitleScreen::ToBlack()
{
	for (int i = 0; i < 3; i++)
	{
		m_Color[i] = (m_Color[i] - 0.5f > 0) ? m_Color[i] - 0.5f: 0;
	}

	if (m_Color[0] + m_Color[1] + m_Color[2] == 0)
	{
		m_Cycled++;
		return true;
	}
	return false;
}

void TitleScreen::DrawTitle()
{
	FillRect(m_Clock.GetPosition().x - 48, m_Clock.GetPosition().y - 48, 98, 98, GetRGB(0, 0, 0));

	if (m_Cycled < 1)
	{
		AdjustColor(10);
	}
	else if (ToBlack() && m_Cycled > 260)
	{
		m_Enabled = false;
		return;
	}

	for (int i = 0; i < m_LetterLines.size(); i++)
	{
		for (int n = 0; n < m_LetterLines[i].size(); n++)
		{
			DrawLine(m_LetterLines[i][n].p1.x, m_LetterLines[i][n].p1.y, m_LetterLines[i][n].p2.x, m_LetterLines[i][n].p2.y, GetRGB(m_Color[0], m_Color[1], m_Color[2]));
		}
	}

	m_Clock.UpdateHands();
	m_Clock.Draw(m_Color);
	
}

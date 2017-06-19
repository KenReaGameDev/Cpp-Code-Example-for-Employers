#include "time.h"

#undef UNICODE
#include <windows.h>


//get system time
void GetTime(int& hr, int& min, int& sec)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	// 24 Hour Time
	hr  = time.wHour;
	min = time.wMinute;
	sec = time.wSecond;
}

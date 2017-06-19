#ifndef STRUCTS_H
#define STRUCTS_H

#include  <cmath>

// 
class Structs
{

public:

	struct L_POINT {
		float x;
		float y;	

		L_POINT(float inX, float inY)
		{
			x = inX; 
			y = inY;
		};

		L_POINT();
		~L_POINT();

		friend L_POINT operator+ (const L_POINT& point, const L_POINT& point2);
		friend L_POINT operator- (const L_POINT& point, const L_POINT& point2);
		friend L_POINT operator* (const L_POINT& point, const L_POINT& point2);
		friend L_POINT operator* (const L_POINT& point, const float point2);

	};

	struct LINE_COORDINATES {
		L_POINT p1;
		L_POINT p2;
	};

	// Local 
	struct BOX_COLLIDER {

	};

	static const int RandomNumber(const int min, int max, const bool& edgeCases);
	static L_POINT Normalize(L_POINT point);


private:

};

#endif // #ifndef STRUCTS_H

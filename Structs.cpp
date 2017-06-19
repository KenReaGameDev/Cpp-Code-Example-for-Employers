#include "Structs.h"
#include "time.h"
#include <random>

Structs::L_POINT::L_POINT()
{
}

Structs::L_POINT::~L_POINT()
{
}

Structs::L_POINT operator+ (const Structs::L_POINT& point, const Structs::L_POINT& point2)
{
	return (Structs::L_POINT(point.x + point2.x, point.y + point2.y));
}

Structs::L_POINT operator- (const Structs::L_POINT& point, const Structs::L_POINT& point2)
{
	return (Structs::L_POINT(point.x - point2.x, point.y - point2.y));
}

Structs::L_POINT operator* (const Structs::L_POINT& point, const Structs::L_POINT& point2)
{
	return (Structs::L_POINT(point.x * point2.x, point.y * point2.y));
}

Structs::L_POINT operator* (const Structs::L_POINT & point, const float point2)
{
	return (Structs::L_POINT(point.x * point2, point.y * point2));
}

const int Structs::RandomNumber(const int min, int max, const bool& edgeCases)
{

	if (min >= max)
		max = min + 1;

	std::random_device rdev;
	std::seed_seq  seeder{ rdev(),rdev() };
	std::mt19937 my_rng(seeder);
	std::uniform_int_distribution<int> num(min, max);

	int r = num(my_rng);

	// Dont Allow 0 Speeds
	while (r == 0)
		r = num(my_rng);

	if (edgeCases)
		r = (r < 0) ? min : max;

	
	return r;
}

Structs::L_POINT Structs::Normalize(L_POINT point)
{
	Structs::L_POINT temp = point;
	float length = sqrt(temp.x * temp.x + temp.y * temp.y);
	temp.x /= length;
	temp.y /= length;
	return temp;
}

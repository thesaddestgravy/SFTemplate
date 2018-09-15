#include "MathUtil.h"

float getDistance(Vec2 pointOne, Vec2 pointTwo)
{
	return sqrt(pow(pointTwo.x - pointOne.x, 2) + pow(pointTwo.y - pointOne.y, 2) * 1.0);
}

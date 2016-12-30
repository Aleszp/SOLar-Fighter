#include <cmath>
#include "math.hpp"

void overflow(double* deg)
{
	while(std::abs(*deg)>PI)
	{
		*deg-=PI2*copysign(1,*deg);
	}
}

double overflow(double deg)
{
	while(std::abs(deg)>PI)
	{
		deg-=PI2*copysign(1,deg);
	}
	return deg;
}

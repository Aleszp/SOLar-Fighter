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

void overflow(double *deg1, double *deg2, double *deg3)
{
	while(std::abs(*deg1)>PI)
	{
		*deg1-=PI2*copysign(1,*deg1);
		//*deg2-=PI*copysign(1,*deg2);
		//*deg3-=PI*copysign(1,*deg3);
	}
}

void overflow2(double *deg1, double *deg2, double *deg3)
{
	while(std::abs(*deg1)>PI05)
	{
		*deg1-=(-PI05*copysign(1,*deg1)+*deg1);
		*deg2-=PI*copysign(1,*deg2);
		*deg3-=PI*copysign(1,*deg3);
	}
}

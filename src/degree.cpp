#include <cmath>
#include "degree.hpp"

void overflow(double* deg)
{
	while(std::abs(*deg)>PI)
	{
		*deg-=PI2*copysign(1,*deg);
	}
	
	//if(std::abs(*deg)>180.0)
	/*if(*deg>=360.0)
	{
		*deg=*deg-360.0;
		// *deg-=180.0*floor(1.0+std::abs(*deg/180.0))*copysign(1, *deg);
	}
	if(*deg<0.0)
		*deg=360+*deg;*/
}

double overflow(double deg)
{
	while(std::abs(deg)>PI)
	{
		deg-=PI2*copysign(1,deg);
	}
	return deg;
	//if(std::abs(deg)>180.0)
	//	deg-=180.0*floor(1.0+std::abs(deg/180.0))*copysign(1, deg);
	//if(deg>=360.0)
	//	deg=deg-360.0;
	//if(deg<0.0)
	//	deg=360.0+deg;
	//return deg;
}

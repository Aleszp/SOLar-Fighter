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

void overflow2(double *deg1, double *deg2)
{
	while(std::abs(*deg1)>PI05)
	{
		*deg1-=(-PI05*copysign(1,*deg1)+*deg1);
		*deg2-=PI*copysign(1,*deg2);
	}
}

double cam_orb_dist(Camera* cam, Orb* orb)
{
	double R=0;
	double tmp;
	tmp=cam->get_x()-orb->get_r()*sin(orb->get_alfa());
	R=+tmp*tmp;
	tmp=cam->get_y()-orb->get_r()*cos(orb->get_alfa());
	R=+tmp*tmp;
	tmp=cam->get_z()-orb->get_z();
	R=+tmp*tmp;
	return sqrt(R);
}

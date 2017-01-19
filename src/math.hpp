#ifndef _MATH_HPP_
#define _MATH_HPP

#include <cstdlib>
#include "orb.hpp"

#define PI05 1.57079632680
#define PI 3.14159265359
#define PI2 6.28318530718

void overflow(double* deg);
double overflow(double deg);
void overflow2(double *deg1, double *deg2);

inline double rnd0_1(){return((double)std::rand()/RAND_MAX);}
inline double deg2rad(double deg){return deg/180.0*PI;}
inline double rad2deg(double rad){return rad/PI*180.0;}

double cam_orb_dist(Camera* cam, Orb* orb);

#endif

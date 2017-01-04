#include <cmath>
#include <stdio.h>
#include "camera.hpp"

Camera::Camera(double x, double y, double z, double yaw, double pitch, double roll, double fov_x, double fov_y, double render_dist, BITMAP* scr, double res_x, double res_y)
:SimpleObject(x,y,z,yaw,pitch,roll),fov_x2_(fov_x/2.0),fov_y2_(fov_y/2.0),render_dist_(render_dist),scr_(scr), res_x_(res_x), res_y_(res_y)
{
	x_sin_fov_const_=res_x_/2.0/sin(fov_x2_);
	y_sin_fov_const_=res_y_/2.0/sin(fov_y2_);
	//fprintf(stderr,"fov consts: %lf %lf\n",x_sin_fov_const_,y_sin_fov_const_);
}


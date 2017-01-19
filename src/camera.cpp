#include <cmath>
#include <stdio.h>
#include "camera.hpp"

/**
* Konstruktor klasy Camera
* @param x - położenie w osi x
* @param y - położenie w osi y
* @param z - położenie w osi z
* @param yaw - obrót w osi z
* @param pitch - obrót w osi xy
* @param roll - obrót wokół własnej osi
* @param fov_x - szerokość kątowa pola widzenia w poziomie
* @param fov_y - szerokość kątowa pola widzenia w pionie
* @param render_dist - zasięg rysowania
* @param scr - bitmapa do której rysuje kamera (z założenia ekran)
* @param res_x - rozdzielczość pozioma bitmapy
* @param res_y - rozdzielczość pionowa bitmapy
* @return obiekt typu Camera
*/ 
Camera::Camera(double x, double y, double z, double yaw, double pitch, double roll, double fov_x, double fov_y, double render_dist, BITMAP* scr, double res_x, double res_y)
:SimpleObject(x,y,z,yaw,pitch,roll),fov_x2_(fov_x/2.0),fov_y2_(fov_y/2.0),render_dist_(render_dist),scr_(scr), res_x_(res_x), res_y_(res_y), res_x2_(res_x/2), res_y2_(res_y/2)
{
	x_sin_fov_const_=res_x_/2.0/sin(fov_x2_);
	y_sin_fov_const_=res_y_/2.0/sin(fov_y2_);
	vx_=0;
	vy_=0;
	vz_=0;
	vyaw_=0;
	vpitch_=0;
	vroll_=0;
}

void Camera::accel_line(double a)
{
	double tmp=a*sin(SimpleObject::pitch_);
	vx_+=(tmp*cos(SimpleObject::yaw_));
	vy_+=(tmp*sin(SimpleObject::yaw_));
	vz_+=(a*cos(SimpleObject::pitch_));
}

void Camera::accel_deg(double ayaw, double apitch)
{
	vyaw_+=(ayaw*cos(SimpleObject::roll_));
	vpitch_+=(ayaw*sin(SimpleObject::roll_));
	vyaw_+=(apitch*sin(SimpleObject::roll_));
	vpitch_+=(apitch*cos(SimpleObject::roll_));
}		

void Camera::accel_roll(double aroll)
{
	vroll_+=aroll;
}

/**
 * Aktualizuje położenie zmienne w czasie
 * @param dt - krok czasowy
 */ 
void Camera::update(double dt)
{
	x_+=vx_*dt;
	y_+=vy_*dt;
	z_+=vz_*dt;
	
	rotate_yaw(vyaw_*dt);
	rotate_pitch(vpitch_*dt);
	rotate_roll(vroll_*dt);
}

#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <allegro.h>
#include "simple_object.hpp"

class Object;
class Star;

class Camera: public SimpleObject
{
	private:
		double fov_x2_;	
		double fov_y2_;	
		double render_dist_;
		BITMAP* scr_;
		unsigned res_x_;
		unsigned res_y_;
		double x_sin_fov_const_;
		double y_sin_fov_const_;
	public:
		Camera(double x, double y, double z, double yaw, double pitch, double roll, double fov_x, double fov_y, double render_dist, BITMAP* scr, double res_x, double res_y);
		virtual ~Camera(){}
		inline double get_x_sin_fov_const()const {return x_sin_fov_const_;}
		inline double get_y_sin_fov_const()const {return y_sin_fov_const_;}
				
		friend Object;
		friend Star;
		
};
#endif

#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <allegro.h>
#include "simple_object.hpp"

class Camera: public SimpleObject
{
	protected:
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
		inline double get_render_dist() const {return render_dist_;}
		inline unsigned get_res_x() const {return res_x_;}
		inline unsigned get_res_y() const {return res_y_;}
		inline double get_fov_x2() const {return fov_x2_;}
		inline double get_fov_y2() const {return fov_y2_;}
		inline void putpixel(int xx, int yy, int col) const {::putpixel(scr_,xx,yy,col);}
		inline void ellipsefill(int xx,int yy,int rad_x, int rad_y, int col) const {::ellipsefill(scr_,xx,yy,rad_x, rad_y, col);}
};
#endif

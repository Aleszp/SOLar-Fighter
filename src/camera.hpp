#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <allegro.h>
#include "simple_object.hpp"

/**
 * Klasa kamery - punktu widzenia gracza
 */ 
class Camera: public SimpleObject
{
	protected:
		double fov_x2_;	
		double fov_y2_;	
		double render_dist_;
		BITMAP* scr_;
		unsigned res_x_;
		unsigned res_y_;
		unsigned res_x2_;
		unsigned res_y2_;
		double x_sin_fov_const_;
		double y_sin_fov_const_;
	public:
		Camera(double x, double y, double z, double yaw, double pitch, double roll, double fov_x, double fov_y, double render_dist, BITMAP* scr, double res_x, double res_y);
		virtual ~Camera(){}
		/**
		 * @return stała niezbędna do wyznaczania położeń gwiazd w osi poziomej ekranu
		 */ 
		inline double get_x_sin_fov_const()const {return x_sin_fov_const_;}
		/**
		 * @return stała niezbędna do wyznaczania położeń gwiazd w osi pionowej ekranu
		 */ 
		inline double get_y_sin_fov_const()const {return y_sin_fov_const_;}
		/**
		 * @return zasięg renderowania
		 */ 
		inline double get_render_dist() const {return render_dist_;}
		/**
		 * @return rozdzielczość pozioma ekranu
		 */ 
		inline unsigned get_res_x() const {return res_x_;}
		/**
		 * @return rozdzielczość pionowa ekranu
		 */ 
		inline unsigned get_res_y() const {return res_y_;}
		/**
		 * @return rozdzielczość pozioma połówki ekranu
		 */ 
		inline unsigned get_res_x2() const {return res_x2_;}
		/**
		 * @return rozdzielczość pionowa połówki ekranu
		 */ 
		inline unsigned get_res_y2() const {return res_y2_;}
		/**
		 * @return szerokość kątowa pola widzenia w poziomie
		 */ 
		inline double get_fov_x2() const {return fov_x2_;}
		/**
		 * @return szerokość kątowa pola widzenia w pionie
		 */ 
		inline double get_fov_y2() const {return fov_y2_;}
		/**
		 * @return umieszcza piksel na ekranie bez bezpośredniego dostępu do prywatnej bitmapy
		 */ 
		inline void putpixel(int xx, int yy, int col) const {::putpixel(scr_,xx,yy,col);}
		/**
		 * @return rysuje wypełnioną elipsę na ekranie bez bezpośredniego dostępu do prywatnej bitmapy
		 */ 
		inline void ellipsefill(int xx,int yy,int rad_x, int rad_y, int col) const {::ellipsefill(scr_,xx,yy,rad_x, rad_y, col);}
		virtual void update(double dt){}
};
#endif

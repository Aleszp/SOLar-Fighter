#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include "star.hpp"
#include "camera.hpp"
#include "math.hpp"

Star::Star(double alfa, double beta)
:alfa_(alfa), beta_(beta){r_=192;g_=192;b_=255;}

Star::Star(double alfa, double beta, uint_fast8_t r, uint_fast8_t g, uint_fast8_t b)
:alfa_(alfa), beta_(beta), r_(r),g_(g),b_(b){}

bool Star::is_visible(const Camera* camera)
{
	if((abs(overflow(alfa_-camera->get_yaw()))<=camera->get_fov_x2())&&(abs(overflow(beta_-camera->get_pitch()))<=camera->get_fov_y2()))
		return true;
	return false;
}

void Star::render(const Camera* camera)
{
	double x=camera->get_x_sin_fov_const()*sin(alfa_-camera->get_yaw());
	double y=camera->get_y_sin_fov_const()*sin(beta_-camera->get_pitch());

	double r=sqrt(x*x+y*y);
	double theta=atan2(y,x);
	unsigned xx=round(r*cos(theta+camera->get_roll())+camera->get_res_x()/2.0);
	unsigned yy=round(r*sin(theta+camera->get_roll())+camera->get_res_y()/2.0);
	uint_fast8_t col_r,col_g,col_b;
	col_r=r_+std::rand()%64;
	col_g=g_+std::rand()%64;
	col_b=b_+std::rand()%64;
	if(xx>=camera->get_res_x()||yy>=camera->get_res_y()||xx<0||yy<0)
		return;
	camera->putpixel(xx,yy,makecol(col_r,col_g,col_b));
	camera->putpixel(xx+1,yy,makecol(col_r>>1,col_g>>1,col_b>>1));
	camera->putpixel(xx-1,yy,makecol(col_r>>1,col_g>>1,col_b>>1));
	camera->putpixel(xx,yy+1,makecol(col_r>>1,col_g>>1,col_b>>1));
	camera->putpixel(xx,yy-1,makecol(col_r>>1,col_g>>1,col_b>>1));
	camera->putpixel(xx,yy-1,makecol(col_r>>1,col_g>>1,col_b>>1));
	//ellipsefill(camera->scr_,xx,yy,1.5, 1.5, makecol(std::rand()%256,std::rand()%256,std::rand()%256));
	//ellipsefill(camera->scr_,xx,yy,1.8, 1.8, makecol(r_+std::rand()%64,g_+std::rand()%64,b_+std::rand()%64));

}

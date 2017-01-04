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
	if((abs(overflow(alfa_-camera->yaw_))<=camera->fov_x2_)&&(abs(overflow(beta_-camera->pitch_))<=camera->fov_y2_))
		return true;
	return false;
}

void Star::render(const Camera* camera)
{
	double x=camera->get_x_sin_fov_const()*sin(alfa_-camera->yaw_);
	double y=camera->get_y_sin_fov_const()*sin(beta_-camera->pitch_);

	double r=sqrt(x*x+y*y);
	double theta=atan2(y,x);
	unsigned xx=round(r*cos(theta+camera->roll_)+camera->res_x_/2);
	unsigned yy=round(r*sin(theta+camera->roll_)+camera->res_y_/2);

	if(xx>=camera->res_x_||yy>=camera->res_y_||xx<0||yy<0)
		return;
	/*putpixel(camera->scr_,xx,yy,makecol(r_+std::rand()%64,g_+std::rand()%64,b_+std::rand()%64));
	putpixel(camera->scr_,xx+1,yy,makecol(r_>>1,g_>>1,b_>>1));
	putpixel(camera->scr_,xx-1,yy,makecol(r_>>1,g_>>1,b_>>1));
	putpixel(camera->scr_,xx,yy+1,makecol(r_>>1,g_>>1,b_>>1));
	putpixel(camera->scr_,xx,yy-1,makecol(r_>>1,g_>>1,b_>>1));*/
	ellipsefill(camera->scr_,xx,yy,1, 1, makecol(r_+std::rand()%64,g_+std::rand()%64,b_+std::rand()%64));
}

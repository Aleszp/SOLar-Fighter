#include <cmath>
#include <stdio.h>
#include "star.hpp"
#include "camera.hpp"
#include "degree.hpp"

Star::Star(double alfa, double beta)
:alfa_(alfa), beta_(beta){makecol(color_=192,192,255);}

Star::Star(double alfa, double beta, int color)
:alfa_(alfa), beta_(beta), color_(color){}

bool Star::is_visible(const Camera* camera)
{
	//if(((camera->yaw_-alfa_)<=camera->fov_x2_)&&((camera->pitch_-beta_)<=camera->fov_y2_))
	//	return true;
	//return false;	
	
	//if((abs(alfa_-camera->yaw_)<=camera->fov_x2_)&&(abs(beta_-camera->pitch_)<=camera->fov_y2_))
	//	return true;
	//return false;
}

void Star::render(const Camera* camera)
{
	unsigned xx=round(camera->res_x_/2+camera->get_x_sin_fov_const()*sin(alfa_-camera->yaw_));
	unsigned yy=round(camera->res_y_/2+camera->get_y_sin_fov_const()*sin(beta_-camera->pitch_));
	
	/*unsigned xx=round(camera->res_x_*((overflow(alfa_-camera->yaw_))/camera->fov_x2_));
	unsigned yy=round(camera->res_y_*((overflow(beta_-camera->pitch_))/camera->fov_y2_));*/
	//fprintf(stderr,"sinuses: %lf %lf\n",sin(alfa_-camera->yaw_),sin(beta_-camera->pitch_));
	//fprintf(stderr,"%04u %04u\n",xx,yy);
	if(xx>=camera->res_x_||yy>=camera->res_y_||xx<0||yy<0)
		return;
	putpixel(camera->scr_,xx,yy,color_);
}

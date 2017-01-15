#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include "star.hpp"
#include "camera.hpp"
#include "math.hpp"

Star::Star(double alfa, double beta)
:alfa_(alfa), beta_(beta){r_=192;g_=192;b_=192;}

Star::Star(double alfa, double beta, uint_fast8_t r, uint_fast8_t g, uint_fast8_t b)
:alfa_(alfa), beta_(beta), r_(r),g_(g),b_(b){}

bool Star::is_visible(const Camera* camera)
{
	double alfa=alfa_, beta=beta_-camera->get_pitch();
	overflow2(&beta,&alfa);
	//if((abs(overflow(alfa-camera->get_yaw()))<=camera->get_fov_x2())&&(abs(overflow(beta))<=camera->get_fov_y2()))
		return true;
	return false;
}

void Star::render(const Camera* camera)
{
	/*double Dalfa=alfa_-camera->get_yaw();
	double Dbeta=beta_; //-camera->get_pitch();
	//overflow2(&Dbeta,&Dalfa);
	if(abs(overflow(Dalfa))>camera->get_fov_x2())
		return;
	
	Dbeta-=camera->get_pitch();
	
	double x=camera->get_x_sin_fov_const()*sin(Dalfa);
	double y=copysign(1,cos(Dalfa))*camera->get_y_sin_fov_const()*sin(Dbeta);

	double r=sqrt(x*x+y*y);
	double theta=atan2(y,x);
	unsigned xx=round(r*cos(theta+camera->get_roll())+camera->get_res_x2());
	unsigned yy=round(copysign(1,cos(Dbeta))*r*sin(theta+camera->get_roll())+camera->get_res_y2());*/
	
	double Dalfa=alfa_-camera->get_yaw();
	double Dbeta;
	if(copysign(1,cos(overflow(Dalfa)))>0)
	{
		Dbeta=beta_-camera->get_pitch();
		//if(copysign(1,cos(Dbeta))>0)
		//	return;
	}
	else
	{
		Dbeta=PI-beta_-camera->get_pitch();
		//if(copysign(1,cos(Dbeta))>0)
		//	return;
	}
	
	double x=camera->get_x_sin_fov_const()*sin(Dalfa);
	double y=camera->get_y_sin_fov_const()*sin(Dbeta);

	double r=sqrt(x*x+y*y);
	double theta=atan2(y,x);
	
	x=copysign(1,cos(Dalfa))*r*cos(theta+camera->get_roll());
	y=copysign(1,cos(Dbeta))*r*sin(theta+camera->get_roll());
	
	int xx=round(x+camera->get_res_x()/2);
	int yy=round(y+camera->get_res_y()/2);
	
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
}

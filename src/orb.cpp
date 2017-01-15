#include <cmath>
#include <cstdio>
#include "orb.hpp"
#include "math.hpp"

Orb::Orb(double m, double radius, double r, double alfa, double z, double yaw, double pitch, double roll, double vr, double valfa, double vz, double vyaw, double vpitch, double vroll)
:m_(m), radius_(radius), r_(r), alfa_(alfa), z_(z), yaw_(yaw), pitch_(pitch), roll_(roll), vr_(vr), valfa_(valfa), vz_(vz), vyaw_(vyaw), vpitch_(vpitch), vroll_(vroll){}

Orb::Orb(const Orb &src)
:m_(src.m_), radius_(src.radius_), r_(src.r_), alfa_(src.alfa_), z_(src.z_), yaw_(src.yaw_), pitch_(src.pitch_), roll_(src.roll_), vr_(src.vr_), valfa_(src.valfa_), vz_(src.vz_), vyaw_(src.vyaw_), vpitch_(src.vpitch_), vroll_(src.vroll_){}


void Orb::update(double dt)
{
	r_+=vr_*dt;
	alfa_+=valfa_*dt;
	z_+=vz_*dt;
	
	//yaw_+=vyaw_*dt;
	//pitch_+=pitch_*dt;
	//roll_+=roll_*dt;
}

bool Orb::is_visible(const Camera* camera)
{
	double xx=r_*cos(alfa_);
	double yy=xx*sin(alfa_);
	xx-=camera->get_x();
	yy-=camera->get_y();
	double zz=z_-camera->get_z();
	
	double dist=sqrt(xx*xx+yy*yy+zz*zz);
	if(dist<camera->get_render_dist())
		return true;
	
	return false;
}

void Orb::render(const Camera* camera)
{
	double x=r_*cos(alfa_)-camera->get_x();
	double y=r_*sin(alfa_)-camera->get_y();
	double z=z_-camera->get_z();

	double r=sqrt(x*x+y*y);
	double R=sqrt(r*r+z*z);
	
	double Dalfa=atan2(y,x)-camera->get_yaw();
	if(copysign(1,cos(Dalfa))<0)
		return;
	double Dbeta=atan2(r,z)-camera->get_pitch();
	
	x=camera->get_x_sin_fov_const()*sin(Dalfa);
	y=camera->get_y_sin_fov_const()*sin(Dbeta);

	r=sqrt(x*x+y*y);
	double theta=atan2(y,x);
	
	x=r*cos(theta+camera->get_roll());
	y=copysign(1,cos(Dbeta))*r*sin(theta+camera->get_roll());
	
	int xx=round(x+camera->get_res_x()/2);
	int yy=round(y+camera->get_res_y()/2);
	
	//int xx=round(R*sin(beta)*sin(alfa)+camera->get_res_x()/2);
	//int yy=round(R*cos(beta)+camera->get_res_y()/2);

	//fprintf(stderr,"(%lf,%lf)   ",x,y);
	//fprintf(stderr,"(%i,%i) ",xx,yy);
	//fprintf(stderr,"(%lf,%lf)    ",rad2deg(alfa), rad2deg(beta));
	
	double sigma=atan2(radius_,R);
	/*if(!((abs(overflow(Dalfa))<=camera->get_fov_x2())&&(abs(overflow(Dbeta))<=camera->get_fov_y2())))
	{	
		//fprintf(stderr,"\n");
		//return;
	}*/
	double rad_x=sigma*camera->get_res_x()/camera->get_fov_x2() *cos(x/camera->get_res_x()*camera->get_fov_x2());
	double rad_y=sigma*camera->get_res_y()/camera->get_fov_y2() *cos(y/camera->get_res_y()*camera->get_fov_y2());
	
	//fprintf(stderr,"(%lf,%lf)\n",rad_x, rad_y);
	
	//if(xx-rad_x>=camera->get_res_x()||yy-rad_y>=camera->get_res_y()||xx<-rad_x||yy<-rad_y)
	//if(abs((xx-camera->get_res_x()/2)+rad_x>camera->get_res_x()/2)||abs((yy-camera->get_res_y()/2)+rad_y>camera->get_res_y()/2))
		//return;
	camera->ellipsefill(xx,yy,rad_x, rad_y, makecol(0xFF,0xFF,0x00));
	
	//pewnie się przyda 
	//void masked_stretch_blit(BITMAP *source, BITMAP *dest, int source_x, source_y, source_w, source_h, int dest_x, dest_y, dest_w, dest_h);
	
	//znajdź średnicę kuli na podstawie odległości
	//narysuj w tymczasowej bitmapie
	//blituj z wycinka bitmapy
	
	//wariant 2:
	//renderuj piklel po pikselu
	//pewnie wolniejsze
	//ale łatwo zaimplementować bufor z
}

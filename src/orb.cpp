#include <cmath>
#include "orb.hpp"

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
	
	double dist=sqrt(xx*xx+yy*yy);
	if(dist<camera->get_render_dist());
	
	
	return false;
}

void Orb::render(const Camera* camera)
{
	double x=r_*cos(alfa_)-camera->get_x();
	double y=r_*sin(alfa_)-camera->get_y();
	double z=z_-camera->get_z();

	double r=sqrt(x*x+y*y+z*z);
	
	double theta=atan2(y,x);
	unsigned xx=round(r*cos(theta+camera->roll_)+camera->res_x_/2);
	unsigned yy=round(r*sin(theta+camera->roll_)+camera->res_y_/2);

	if(xx>=camera->res_x_||yy>=camera->res_y_||xx<0||yy<0)
		return;
	ellipsefill(camera->scr_,xx,yy,100, 100, makecol(0xFF,0xFF,0x00));
	
	//znajdź średnicę kuli na podstawie odległości
	//narysuj w tymczasowej bitmapie
	//blituj z wycinka bitmapy
	
	//wariant 2:
	//renderuj piklel po pikselu
	//pewnie wolniejsze
	//ale łatwo zaimplementować bufor z
}

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
	
	double dist=sqrt(xx*xx+yy*yy);
	if(dist<camera->get_render_dist())
		return true;
	
	return false;
}

void Orb::render(const Camera* camera)
{
	double dx=r_*cos(alfa_)-camera->get_x();
	double dy=r_*sin(alfa_)-camera->get_y();
	double dz=z_-camera->get_z();

	double r=sqrt(dx*dx+dy*dy);
	double R=sqrt(r*r+dz*dz);
	
	double alfa=atan2(dy,dx)-camera->get_yaw();
	double beta=atan2(r,dz)-camera->get_pitch();
	
	int xx=round(R*sin(beta)*sin(alfa)+camera->res_x_/2);
	int yy=round(R*cos(beta)+camera->res_y_/2);

	//fprintf(stderr,"%lf %lf %lf\n",dx,dy,r);
	//fprintf(stderr,"%i %i\n",xx,yy);
	fprintf(stderr,"%lf %lf\n",rad2deg(alfa), rad2deg(beta));
	double rad_x=radius_, rad_y=radius_;
	
	if(xx-rad_x>=camera->res_x_||yy-rad_y>=camera->res_y_||xx<-rad_x||yy<-rad_y)
		return;
	ellipsefill(camera->scr_,xx,yy,rad_x, rad_y, makecol(0xFF,0xFF,0x00));
	
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

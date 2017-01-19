#include <cmath>
#include <cstdio>
#include "orb.hpp"
#include "math.hpp"

/**
 * Konstruktor klasy Orb
 * @param m - masa ciała
 * @param radius - promień ciała
 * @param r - położenie radialne (wsp. walcowe)
 * @param alfa - położenie kątowe (wsp. walcowe)
 * @param z - położenie w osi z
 * @param yaw - obrót w osi z
 * @param pitch - obrót w osi xy
 * @param roll - obrót wokół własnej osi
 * @param vr - prędkość radialna
 * @param valfa - prędkość kątowa
 * @param vz - prędkość wzdłuż osi z
 * @param vyaw - prędkość obrotu wokół osi z
 * @param vpitch - prędkośćobrotu wokół osi xy
 * @param vroll - prędkość obrotu wokół własnej osi
 * @return obiekt typu Orb
 */ 
Orb::Orb(double m, double radius, int color, double r, double alfa, double z, double yaw, double pitch, double roll, double vr, double valfa, double vz, double vyaw, double vpitch, double vroll)
:m_(m), radius_(radius), color_(color), r_(r), alfa_(alfa), z_(z), yaw_(yaw), pitch_(pitch), roll_(roll), vr_(vr), valfa_(valfa), vz_(vz), vyaw_(vyaw), vpitch_(vpitch), vroll_(vroll){}

/**
 * Konstruktor kopiujący klasy Orb
 * @param src - referencja do oryginalnego obiektu
 * @return obiekt typu Orb
 */ 
Orb::Orb(const Orb &src)
:m_(src.m_), radius_(src.radius_), color_(src.color_), r_(src.r_), alfa_(src.alfa_), z_(src.z_), yaw_(src.yaw_), pitch_(src.pitch_), roll_(src.roll_), vr_(src.vr_), valfa_(src.valfa_), vz_(src.vz_), vyaw_(src.vyaw_), vpitch_(src.vpitch_), vroll_(src.vroll_){}


/**
 * Aktualizuje położenie zmienne w czasie
 * @param dt - krok czasowy
 */ 
void Orb::update(double dt)
{
	move_r(vr_*dt);
	move_alfa(valfa_*dt);
	move_z(vz_*dt);
	
	yaw_+=vyaw_*dt;
	pitch_+=pitch_*dt;
	roll_+=roll_*dt;
	//fprintf(stderr,"alfa= %.2lf\tvalfa=%e\n",rad2deg(alfa_), rad2deg(valfa_));
}

/**
 * Sprawdza czy ciało niebieskie jest widoczne z punktu widzenia kamery
 * @param camera - wskaźnik na kamerę
 * @return fałsz jeśli nie jest możliwe zobaczenie ciała
 */ 
bool Orb::is_visible(const Camera* camera)
{
	double dist=dist_to_cam(camera);
	if(dist<camera->get_render_dist())
		return true;
	return false;
}

/**
 * Rysuje ciało niebieskie w bitmapie kamery
 * @param camera - wskaźnik na kamerę
 */ 
void Orb::render(const Camera* camera)
{
	double x=r_*cos(alfa_)-camera->get_x();
	double y=r_*sin(alfa_)-camera->get_y();
	double z=z_-camera->get_z();

	double r=sqrt(x*x+y*y);
	double R=sqrt(r*r+z*z);
	
	double Dalfa=atan2(y,x)-camera->get_yaw();
	//if(copysign(1,cos(Dalfa))<0)
	//	return;
	double Dbeta=atan2(z,r)-camera->get_pitch();
	
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
	camera->ellipsefill(xx,yy,rad_x, rad_y, color_);
	
	//pewnie się przyda 
	//void masked_stretch_blit(BITMAP *source, BITMAP *dest, int source_x, source_y, source_w, source_h, int dest_x, dest_y, dest_w, dest_h);
	
	//znajdź średnicę kuli na podstawie odległości
	//narysuj w tymczasowej bitmapie
	//blituj z wycinka bitmapy
}

/**
 * Przemieszcza kątowo we współrzędnych walcowych
 * @param Dalfa - wartość przesunięcia
 */ 
void Orb::move_alfa(double Dalfa)
{
	alfa_+=Dalfa;
	if(Dalfa>0)
		if(alfa_>PI)
			alfa_-=PI2;
	if(Dalfa<0)
		if(alfa_<-PI)
			alfa_+=PI2;
}

/**
 * Oblicza odległość między kamerą a ciałem niebieskim
 * @param wskaźnik na kamerę
 * @return odległość w kilometrach
 */ 
double Orb::dist_to_cam(const Camera* cam)
{
	double R=0;
	double tmp;
	tmp=cam->get_x()-r_*sin(alfa_);
	R=+tmp*tmp;
	tmp=cam->get_y()-r_*cos(alfa_);
	R=+tmp*tmp;
	tmp=cam->get_z()-z_;
	R=+tmp*tmp;
	return sqrt(R);
}

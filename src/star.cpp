#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include "star.hpp"
#include "camera.hpp"
#include "math.hpp"

/**
 * Konstruktor domyślny klasy Star przyjmuje kolor biały
 * @param alfa - kąt alfa współrzędnych sferycznych
 * @param beta - kąt beta współrzędnych sferycznych
 * @return - obiekt typu Star koloru białego
 */ 
Star::Star(double alfa, double beta)
:alfa_(alfa), beta_(beta){r_=192;g_=192;b_=192;}

/**
 * Konstruktor domyślny klasy Star pozwalający podać składowe kolorów
 * @param alfa - kąt alfa współrzędnych sferycznych
 * @param beta - kąt beta współrzędnych sferycznych
 * @param r - składowa czerwona koloru
 * @param g - składowa zielona koloru
 * @param b - składowa niebieska koloru
 * @return - obiekt typu Star
 */
Star::Star(double alfa, double beta, uint_fast8_t r, uint_fast8_t g, uint_fast8_t b)
:alfa_(alfa), beta_(beta), r_(r),g_(g),b_(b){}

/**
 * Sprawdza czy gwiazda jest w polu widzenia kamery
 * @param camera - wskaźnik na kamerę
 * @return fałsz - jeśli gwiazda jest poza polem widzenia
 */
bool Star::is_visible(const Camera* camera)
{
	double alfa=alfa_, beta=beta_-camera->get_pitch();
	overflow2(&beta,&alfa);
	if((abs(overflow(alfa-camera->get_yaw()))<=camera->get_fov_x2())&&(abs(overflow(beta))<=camera->get_fov_y2()))
		return true;
	return false;
}

/**
 * Rysuje gwiazdę w polu widzenia kamery
 * @param camera - wskaźnik na kamerę
 */
void Star::render(const Camera* camera)
{
	double Dalfa=alfa_-camera->get_yaw();
	double Dbeta;
	if(copysign(1,cos(overflow(Dalfa)))>0)
	{
		Dbeta=beta_-camera->get_pitch();
	}
	else
	{
		Dbeta=PI-beta_-camera->get_pitch();
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
	col_r=r_+std::rand()%96;
	col_g=g_+std::rand()%96;
	col_b=b_+std::rand()%96;
	if(xx>=(int)camera->get_res_x()||yy>=(int)camera->get_res_y()||xx<0||yy<0)
		return;
	camera->putpixel(xx,yy,makecol(col_r,col_g,col_b));
}

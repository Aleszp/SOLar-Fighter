#include <allegro.h>
#include <alleggl.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <thread>

#include "object.hpp"
#include "camera.hpp"
#include "star.hpp"
#include "math.hpp"
#include "orb.hpp"

/** 
* @mainpage
* Projekt zaliczeniowy z SZPC++ a zarazem odrobina dobrej zabawy - symulator lotu myśliwcem kosmicznym w 3D (na bazie allegro4 i alleggl).
* @author Aleksander Szpakiewicz-Szatan
* @date 2016.12.29
* @version pre-alfa 1.1.5
*/

void render(Camera* cam_, std::vector<Renderable*>* star_);

int main(void)
{
	srand(time(NULL));
	
	allegro_init ();
	install_keyboard ();
	
	if (install_allegro_gl() != 0) 
	{
		std::cerr << "Blad inicjowania biblioteki alleggl!"<<std::endl;
		return 1;
	}
	
	int res_x=1920;
	int res_y=1080;
	bool autodetect=false;
	bool windowed=false;
	bool dbl_buff=1;
	int_fast8_t depth=32;
	
	double fov_x=deg2rad(90);	//90
	double fov_y=deg2rad(59);	//59
	
	if ((depth = desktop_color_depth())==0) 
    {
		depth=8;
		std::cerr << "Nie można wykryć głębi koloru, ładowanie ustawień zgodnościowych."<<std::endl;
	}
	
	if(autodetect)
	{
		if (get_desktop_resolution(&res_x, &res_y) != 0) 
		{
			res_x=640;
			res_y=480;
			windowed=true;
			fov_x=deg2rad(70);
			fov_y=deg2rad(56);
			std::cerr << "Nie można wykryć rozdzielczości pulpitu, ładowanie ustawień zgodnościowych."<<std::endl;
		}
	}
	
	set_color_depth (depth);
	allegro_gl_set(AGL_DOUBLEBUFFER, dbl_buff);
	allegro_gl_set(AGL_WINDOWED, windowed);
	allegro_gl_set(AGL_COLOR_DEPTH, depth);
	allegro_gl_set(AGL_SUGGEST, AGL_DOUBLEBUFFER | AGL_WINDOWED | AGL_COLOR_DEPTH);

	if (set_gfx_mode (GFX_OPENGL, res_x, res_y, 0, 0) != 0)
	{
		std::cerr << "Blad inicjowania trybu graficznego!"<<std::endl;
		return 2;
	}
	
	set_window_title ("Tytul okna"); // ustawia tytuł okna
	
	clear_keybuf ();
	
	Camera cam(5392000, 0.0, 0.0, 0, 0, 0, fov_x, fov_y, 5906423131.0, screen, res_x, res_y);
	std::vector<Renderable*> renderables;
	unsigned obj_count=8192;	//2*8192
	renderables.reserve(obj_count);
	for(unsigned i=0;i<obj_count-1;i++)
	{
		//renderables.push_back(new Star(rnd0_1()*PI2-PI,tmp_rnd*PI-PI05, 0, round(tmp_rnd*255),0));
		renderables.push_back(new Star(rnd0_1()*PI2-PI,rnd0_1()*PI-PI05, std::rand()%128+32,std::rand()%128+32,std::rand()%128+32));
	}
	renderables.push_back(new Orb(1989100000, 1392000.0));
	
	allegro_gl_set_allegro_mode();
	render(&cam,&renderables);
	
	double tmp=0;
	
	while (!key[KEY_ESC]&&!key[KEY_Q])
	{
		//readkey();
		if(key[KEY_UP]||key[KEY_8_PAD])
		{
			cam.rotate_pitch(deg2rad(-0.5*cos(cam.get_roll())));
			cam.rotate_yaw(deg2rad(-0.5*sin(cam.get_roll())));
		}	
		if(key[KEY_DOWN]||key[KEY_2_PAD])
		{
			cam.rotate_pitch(deg2rad(0.5*cos(cam.get_roll())));
			cam.rotate_yaw(deg2rad(0.5*sin(cam.get_roll())));
		}
		if(key[KEY_LEFT]||key[KEY_4_PAD])
		{
			cam.rotate_yaw(deg2rad(-0.5*cos(cam.get_roll())));
			cam.rotate_pitch(deg2rad(0.5*sin(cam.get_roll())));
		}	
		if(key[KEY_RIGHT]||key[KEY_6_PAD])
		{
			cam.rotate_yaw(deg2rad(0.5*cos(cam.get_roll())));
			cam.rotate_pitch(deg2rad(-0.5*sin(cam.get_roll())));
		}
		if(key[KEY_A]||key[KEY_7_PAD])
			cam.rotate_roll(deg2rad(-0.5));	
		if(key[KEY_D]||key[KEY_9_PAD])
			cam.rotate_roll(deg2rad(0.5));
		if(key[KEY_SPACE]||key[KEY_5_PAD])
		{
			tmp=1e5*sin(cam.get_pitch());
			cam.move_x(tmp*cos(cam.get_yaw()));
			cam.move_y(tmp*sin(cam.get_yaw()));
			cam.move_z(1e5*cos(cam.get_pitch()));
			fprintf(stderr, "xyz = (%lf,%lf,%lf)\n",cam.get_x(),cam.get_y(),cam.get_z());
		}
		render(&cam,&renderables);
		std::this_thread::yield();	
	}
	allegro_gl_unset_allegro_mode();
	allegro_exit ();
	return 0;
}
END_OF_MAIN()

void render(Camera* cam_, std::vector<Renderable*>* renderables_)
{
	clear_bitmap(screen);
	
	for(std::vector<Renderable*>::const_iterator it = renderables_->begin();it != renderables_->end(); ++it)
		if(it[0]->is_visible(cam_))
			it[0]->render(cam_);
	
	allegro_gl_flip();	
}

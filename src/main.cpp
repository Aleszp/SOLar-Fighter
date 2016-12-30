#include <allegro.h>
#include <alleggl.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "object.hpp"
#include "camera.hpp"
#include "star.hpp"
#include "math.hpp"

#define RESX 1024
#define RESY 576

/** 
* @mainpage
* Projekt zaliczeniowy z SZPC++ a zarazem odrobina dobrej zabawy - symulator lotu myśliwcem kosmicznym w 3D (na bazie allegro4 i alleggl).
* @author Aleksander Szpakiewicz-Szatan
* @date 2016.12.29
* @version pre-alfa 1.0.2
*/

void render(Camera* cam_, std::vector<Star*>* star_);

int main(void)
{
	srand(time(NULL));
	
	allegro_init ();
	install_keyboard ();
	
	if (install_allegro_gl() != 0) 
	{
		return 1;
	}
	set_color_depth (32);
	allegro_gl_set(AGL_DOUBLEBUFFER, 1);
	allegro_gl_set(AGL_WINDOWED, true);
	allegro_gl_set(AGL_COLOR_DEPTH, 32);
	allegro_gl_set(AGL_SUGGEST, AGL_DOUBLEBUFFER | AGL_WINDOWED | AGL_COLOR_DEPTH);

	if (set_gfx_mode (GFX_OPENGL, RESX, RESY, 0, 0) != 0)
	{
		allegro_message ("Error setting OpenGL graphics mode:\n%s\nAllegro GL error : %s\n",allegro_error, allegro_gl_error);
		std::cerr << "Blad inicjowania trybu graficznego!";
		return 1;
	}
	
	set_window_title ("Tytul okna"); // ustawia tytuł okna
	
	int klawisz = 0;
	clear_keybuf ();
	
	Camera cam(0, 0, 0, 0, 0, 0, deg2rad(70), deg2rad(50), 1000, screen, RESX, RESY);
	std::vector<Star*> test_stars;
	test_stars.reserve(8192);
	for(int i=0;i<8192;i++)
	{
		test_stars.push_back(new Star(2*rnd0_1()*PI-PI,2*rnd0_1()*PI-PI, std::rand()%64+64,std::rand()%64+64,std::rand()%64+64));
	}
	allegro_gl_set_allegro_mode();
	render(&cam,&test_stars);
	
	while ((klawisz >> 8) != KEY_ESC)
	{
		klawisz = readkey ();
		if((klawisz >> 8)==KEY_UP)
			cam.rotate_pitch(deg2rad(-0.5));	
		if((klawisz >> 8)==KEY_DOWN)
			cam.rotate_pitch(deg2rad(0.5));
		if((klawisz >> 8)==KEY_LEFT)
			cam.rotate_yaw(deg2rad(-0.5));	
		if((klawisz >> 8)==KEY_RIGHT)
			cam.rotate_yaw(deg2rad(0.5));
		if((klawisz >> 8)==KEY_A)
			cam.rotate_roll(deg2rad(-0.5));	
		if((klawisz >> 8)==KEY_D)
			cam.rotate_roll(deg2rad(0.5));
		render(&cam,&test_stars);	
	}
	allegro_gl_unset_allegro_mode();
	allegro_exit ();
	return 0;
}
END_OF_MAIN()

void render(Camera* cam_, std::vector<Star*>* star_)
{
	clear_bitmap(screen);
	
	for(std::vector<Star*>::const_iterator it = star_->begin();it != star_->end(); ++it)
		if(it[0]->is_visible(cam_))
			it[0]->render(cam_);
		
	allegro_gl_flip();	
}

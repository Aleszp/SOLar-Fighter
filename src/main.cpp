#include <allegro.h>
#include <alleggl.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>

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
* @version pre-alfa 1.2.3
*/

void render(Camera* cam_, std::vector<Renderable*>* star_);
void update(std::vector<Renderable*>* renderables_, double dt);

int main(int argc, char** argv)
{
	srand(time(NULL));
	
	typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::duration<float> fsec;
	
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
	int depth=32;
	
	double fov_x=deg2rad(90);	//90
	double fov_y=deg2rad(59);	//59
	
	FILE* config;
	
	if(argc==1)
		config=fopen("config.ini","r");
	else
		config=fopen(argv[1],"r");
		
	int tmp_int;
	
	if(!config)
	{
		std::cerr <<"Nie znaleziono pliku konfiguracyjnego :(. Program spróbuje dopasować ustawienia."<<std::endl;
		autodetect=true;
	}
	else
	{
		int a=0;
		a+=fscanf(config,"%i",&res_x);
		a+=fscanf(config,"%i",&res_y);
		a+=fscanf(config,"%i",&depth);
		a+=fscanf(config,"%i",&tmp_int);
		if(tmp_int==0) autodetect=false; else autodetect=true;
		a+=fscanf(config,"%i",&tmp_int);
		if(tmp_int==0) windowed=false; else windowed=true;
		a+=fscanf(config,"%i",&tmp_int);
		if(tmp_int==0) dbl_buff=false; else dbl_buff=true;
		a+=fscanf(config,"%i",&tmp_int);
		fov_x=deg2rad((double)tmp_int);
		a+=fscanf(config,"%i",&tmp_int);
		fov_y=deg2rad((double)tmp_int);
		if(a==0)
			autodetect=true;	//dzięki temu nie czepia się o nieużyte wyniki fscanfa bez wyłączania flagi o nieużytych wynikach funkcji//
		fclose(config);
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
		if ((depth = desktop_color_depth())==0) 
		{
			depth=8;
			std::cerr << "Nie można wykryć głębi koloru, ładowanie ustawień zgodnościowych."<<std::endl;
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
	
	Camera cam(5392000.0, 0.0, 0.0, 0, 0, 0, fov_x, fov_y, 5906423131.0, screen, res_x, res_y);
	std::vector<Renderable*> renderables;
	unsigned obj_count=8192;	//2*8192
	renderables.reserve(obj_count);
	for(unsigned i=0;i<obj_count-4;i++)
	{
		//renderables.push_back(new Star(rnd0_1()*PI2-PI,tmp_rnd*PI-PI05, 0, round(tmp_rnd*255),0));
		//renderables.push_back(new Star(rnd0_1()*PI2-PI,rnd0_1()*PI-PI05, std::rand()%128+32,std::rand()%128+32,std::rand()%128+32));
	}
	//promienie dzielone przez 2, bo z tablic wzięto średnice
	Orb* SOL=new Orb(19891e5, 1392e3/2.0,makecol(0xFF,0xFF,0x00));
	renderables.push_back(SOL);	//Słońce
	
	//Planety:
	renderables.push_back(new Orb( 330.2,  4879.0/2.0,makecol(0xFF,0x0A,0x0A),  5790917.0,0.0,0.0,0.0,0.0,0.0,0,PI2/( 87.969*86400)));		//Merkury
	renderables.push_back(new Orb(4868.5, 12104.0/2.0,makecol(0xAA,0xFF,0xCC),108208926.0,0.0,0.0,0.0,0.0,0.0,0,PI2/(224.701*86400)));		//Wenus
	renderables.push_back(new Orb(5974.2, 12756.0/2.0,makecol(0xAA,0xCC,0xFF),149597887.0,0.0,0.0,0.0,0.0,0.0,0,PI2/(365.256*86400)));		//Ziemia
	renderables.push_back(new Orb( 641.9,  6805.0/2.0,makecol(0xCC,0x0A,0x0A),227936637.0,0.0,0.0,0.0,0.0,0.0,0,PI2/(686.960*86400)));		//Mars
		//Planety - gazowe oblrzymy
	renderables.push_back(new Orb(1898600,8, 142984.0/2.0,makecol(0xBB,0xAA,0x0A),778412027.0,0.0,0.0,0.0,0.0,0.0,0,PI2/( 4333.287*86400)));//Jowisz
	renderables.push_back(new Orb(568516.8, 120536.0/2.0,makecol(0xBB,0xBB,0xDD),1426725413.0,0.0,0.0,0.0,0.0,0.0,0,PI2/(10756.200*86400)));//Saturn
	renderables.push_back(new Orb(86841.0,  51118.0/2.0,makecol(0x0A,0xBB,0xEE),2870972220.0,0.0,0.0,0.0,0.0,0.0,0,PI2/(30707.490*86400)));	//Uran
	renderables.push_back(new Orb(102439.6, 49528.0/2.0,makecol(0x0A,0x0A,0xFF),4498252900.0,0.0,0.0,0.0,0.0,0.0,0,PI2/(60223.353*86400)));	//Neptun
	
	
	allegro_gl_set_allegro_mode();
	render(&cam,&renderables);
	
	double tmp=0;
	double time_compression=1e6;
	
	auto t0 = Time::now();
    auto t1 = Time::now();
    
    fsec dt = t1 - t0;
	
	while (!key[KEY_ESC]&&!key[KEY_Q])
	{
		t1=Time::now();
		dt = t1 - t0;
		t0=Time::now();
		
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
		if(key[KEY_5_PAD])
		{
			tmp=1e5*sin(cam.get_pitch());
			cam.move_x(tmp*cos(cam.get_yaw()));
			cam.move_y(tmp*sin(cam.get_yaw()));
			cam.move_z(1e5*cos(cam.get_pitch()));
			//fprintf(stderr, "xyz = (%lf,%lf,%lf)\n",cam.get_x(),cam.get_y(),cam.get_z());
			fprintf(stderr,"dist to SOL = %lf\n",cam_orb_dist(&cam,SOL));
			
		}
		if(key[KEY_SPACE])
		{
			tmp=-1e5*sin(cam.get_pitch());
			cam.move_x(tmp*cos(cam.get_yaw()));
			cam.move_y(tmp*sin(cam.get_yaw()));
			cam.move_z(-1e5*cos(cam.get_pitch()));
			//fprintf(stderr, "xyz = (%lf,%lf,%lf)\n",cam.get_x(),cam.get_y(),cam.get_z());
			fprintf(stderr,"dist to SOL = %lf\n",cam_orb_dist(&cam,SOL));
		}
		render(&cam,&renderables);
		update(&renderables, dt.count()*time_compression);
		//fprintf(stderr,"FPS: %lf\n",1.0/dt.count());
		
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

void update(std::vector<Renderable*>* renderables_, double dt)
{
	for(std::vector<Renderable*>::const_iterator it = renderables_->begin();it != renderables_->end(); ++it)
		it[0]->update(dt);
}

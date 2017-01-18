#include <ncurses.h>
#include <thread>
#include <cstdio>
#include <chrono>

enum pos {AUTODETECT=1, RES_X=2, RES_Y=3,DEPTH=4,DBL_BUFFED=5,WINDOWED=6,FOV_X=7,FOV_Y=8,SAVE=9, EXIT=10,DEFAULT=11}; 

void little_sleep(std::chrono::microseconds us)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + us;
    do 
    {
        std::this_thread::yield();
    } 
    while (std::chrono::high_resolution_clock::now() < end);
}

int main(int argc, char** argv)
{
	initscr ();
	cbreak ();
	noecho ();
	start_color();
	keypad(stdscr, TRUE);	
	
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	wbkgd(stdscr, COLOR_PAIR(1));
	curs_set(0);
	
	int ch;
	
	int res_x=640;
	int res_y=480;
	bool autodetect=true;
	bool windowed=true;
	bool dbl_buff=true;
	int depth=16;
	int tmp;
	int fov_x=90;
	int fov_y=70;
	
	FILE* config;
	
	if(argc==1)
		config=fopen("config.ini","r");
	else
		config=fopen(argv[1],"r");
		
	if(!config)
	{
		printw("Nie znaleziono pliku konfiguracyjnego :(. Zostanie utworzony nowy.\n");
	}
	else
	{
		int a=0;
		a+=fscanf(config,"%i",&res_x);
		a+=fscanf(config,"%i",&res_y);
		a+=fscanf(config,"%i",&depth);
		a+=fscanf(config,"%i",&tmp);
		if(tmp==0) autodetect=false; else autodetect=true;
		a+=fscanf(config,"%i",&tmp);
		if(tmp==0) windowed=false; else windowed=true;
		a+=fscanf(config,"%i",&tmp);
		if(tmp==0) dbl_buff=false; else dbl_buff=true;
		a+=fscanf(config,"%i",&fov_x);
		a+=fscanf(config,"%i",&fov_y);
		if(a==0)
			noecho ();	//dzięki temu nie czepia się o nieużyte wyniki fscanfa bez wyłączania flagi o nieużytych wynikach funkcji//
		fclose(config);
	}

	nodelay(stdscr,true);
	int offset=1;
	int ptr_max=10;
	int ptr=offset;
	int old=ptr;
	
	do
	{
		ch=getch();
		if(ch==KEY_DOWN)
		{
			old=ptr;
			if(ptr<ptr_max+offset)
				ptr++;
			else
				ptr=offset;
		}
		if(ch==KEY_UP)
		{
			old=ptr;
			if(ptr>offset)
				ptr--;
			else
				ptr=ptr_max+offset;
		}
		
		if(ch==' '||ch==KEY_LEFT||ch==KEY_RIGHT)	//spacja
		{
			if(ptr==AUTODETECT)
				autodetect?autodetect=false:autodetect=true;
			
			if(ptr==DBL_BUFFED)
				dbl_buff?dbl_buff=false:dbl_buff=true;
			
			if(ptr==WINDOWED)
				windowed?windowed=false:windowed=true;
		}
		if(ch==' '&&(ptr==SAVE))
		{
			if(argc==1)
				config=fopen("config.ini","w");
			else
				config=fopen(argv[1],"w");
		
			if(!config)
				{
					printw(":( Nie można utworzyć pliku w lokalizacji%s \nWciśnij dowolny klawisz by zakończyć",argc==1?" domyślnej":argv[1]);
					nodelay(stdscr,false);
					getch();
					endwin();
					return 1;
				}
				else
				{
					fprintf(config,"%i\n",res_x);
					fprintf(config,"%i\n",res_y);
					fprintf(config,"%i\n",depth);
					fprintf(config,"%i\n",autodetect?1:0);
					fprintf(config,"%i\n",windowed?1:0);
					fprintf(config,"%i\n",dbl_buff?1:0);
					fprintf(config,"%i\n",fov_x);
					fprintf(config,"%i\n",fov_y);
					fclose(config);
				}
				break;
		}
		if(ch==' '&&(ptr==DEFAULT))
		{
			res_x=640;
			res_y=480;
			autodetect=true;
			windowed=true;
			dbl_buff=true;
			depth=16;
			fov_x=70;
			fov_y=56;
		}
		if(ch==' '&&(ptr==EXIT))
			break;		
		if(ch=='+'||ch=='=')
		{
			if(ptr==RES_X)
				res_x++;
			if(ptr==RES_Y)
				res_y++;
			if(ptr==DEPTH)
				depth++;
			if(ptr==FOV_X&&fov_x<180)
				fov_x++;
			if(ptr==FOV_Y&&fov_y<180)
				fov_y++;
		}
		if(ch=='-')
		{
			if(ptr==RES_X&&res_x>1)
				res_x--;
			if(ptr==RES_Y&&res_y>1)
				res_y--;
			if(ptr==DEPTH&&depth>1)
				depth--;
			if(ptr==FOV_X&&fov_x>1)
				fov_x--;
			if(ptr==FOV_Y&&fov_y>1)
				fov_y--;
		}
		if(ch==KEY_LEFT)
		{
			if(ptr==RES_X&&res_x>40)
				res_x-=40;
			if(ptr==RES_Y&&res_y>40)
				res_y-=40;
			if(ptr==DEPTH&&depth>8)
				depth-=8;
			if(ptr==FOV_X&&fov_x>15)
				fov_x-=15;
			if(ptr==FOV_Y&&fov_y>15)
				fov_y-=15;
				
		}
		if(ch==KEY_RIGHT)
		{
			if(ptr==RES_X)
				res_x+=40;
			if(ptr==RES_Y)
				res_y+=40;
			if(ptr==DEPTH)
				depth+=8;
			if(ptr==FOV_X&&fov_x<=165)
				fov_x+=15;
			if(ptr==FOV_Y&&fov_y<=165)
				fov_y+=15;
		}
		
		mvprintw(old, 0, " ");
		mvprintw(ptr, 0, "*");
		old=ptr;
		
		mvprintw(AUTODETECT, 2, "Autodetect:\t\t%s",autodetect?"ON ":"OFF");
		mvprintw(RES_X, 2, "Resolution x:\t\t"); autodetect?printw("AUTODETECT"):printw("%3i       ",res_x);
		mvprintw(RES_Y, 2, "Resolution y:\t\t"); autodetect?printw("AUTODETECT"):printw("%3i       ",res_y);
		mvprintw(DEPTH, 2, "Depth:\t\t"); autodetect?printw("AUTODETECT"):printw("%2i        ",depth);
		mvprintw(DBL_BUFFED, 2, "Double buffered:\t%s",dbl_buff?"ON ":"OFF");
		mvprintw(WINDOWED, 2, "Windowed:\t\t%s",windowed?"ON ":"OFF");
		mvprintw(FOV_X, 2, "Horizontal field of view:\t\t"); autodetect?printw("AUTODETECT"):printw("%3i       ",fov_x);
		mvprintw(FOV_Y, 2, "Vertical field of view:\t\t"); autodetect?printw("AUTODETECT"):printw("%3i       ",fov_y);
		mvprintw(SAVE, 2, "Save and exit");
		mvprintw(EXIT, 2, "Exit without saving (you can press Q or ESC too)");
		mvprintw(DEFAULT, 2, "Restore default settings");
		
		refresh();
		std::this_thread::yield();
		std::this_thread::sleep_for(std::chrono::milliseconds(8));
	}
	while(ch!=27&&ch!='q'&&ch!='Q');	//ESC
	
	endwin();
	return 0;
}

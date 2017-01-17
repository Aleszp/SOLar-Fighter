#include <ncurses.h>
#include <cstdio>

enum pos {AUTODETECT=1, RES_X=2, RES_Y=3,DEPTH=4,DBL_BUFFED=5,WINDOWED=6,SAVE=8, EXIT=9}l; 

int main(int argc, char** argv)
{
	initscr ();
	cbreak ();
	noecho ();
	start_color();
	keypad(stdscr, TRUE);	
	
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	wbkgd(stdscr, COLOR_PAIR(1));
	
	int ch;
	
	int res_x=640;
	int res_y=480;
	bool autodetect=true;
	bool windowed=true;
	bool dbl_buff=true;
	int depth=16;
	int tmp;
	
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
		if(a==0)
			noecho ();	//dzięki temu nie czepia się o nieużyte wyniki fscanfa bez wyłączania flagi o nieużytych wynikach funkcji//
		fclose(config);
	}

	nodelay(stdscr,true);
	int offset=1;
	int ptr_max=7;
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
		if(ch==' '&&(ptr==6+offset))
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
					fclose(config);
				}
				break;
		}
		if(ch==' '&&(ptr==7+offset))
			break;		
		if(ch=='+'||ch=='=')
		{
			if(ptr==RES_X)
				res_x++;
			if(ptr==RES_Y)
				res_y++;
			if(ptr==DEPTH)
				depth++;
		}
		if(ch=='-')
		{
			if(ptr==RES_X)
				res_x--;
			if(ptr==RES_Y)
				res_y--;
			if(ptr==DEPTH)
				depth--;
		}
		if(ch==KEY_LEFT)
		{
			if(ptr==RES_X)
				res_x-=40;
			if(ptr==RES_Y)
				res_y-=40;
			if(ptr==DEPTH)
				depth-=8;
		}
		if(ch==KEY_RIGHT)
		{
			if(ptr==RES_X)
				res_x+=40;
			if(ptr==RES_Y)
				res_y+=40;
			if(ptr==DEPTH)
				depth+=8;
		}
		
		mvprintw(old>5+offset?old+1:old, 0, " ");
		mvprintw(ptr>5+offset?ptr+1:ptr, 0, "*");
		old=ptr;
		
		mvprintw(AUTODETECT, 2, "Autodetect:\t\t%s",autodetect?"ON ":"OFF");
		mvprintw(RES_X, 2, "Resolution x:\t\t"); autodetect?printw("AUTODETECT"):printw("%3i       ",res_x);
		mvprintw(RES_Y, 2, "Resolution y:\t\t"); autodetect?printw("AUTODETECT"):printw("%3i       ",res_y);
		mvprintw(DEPTH, 2, "Depth:\t\t"); autodetect?printw("AUTODETECT"):printw("%2i        ",depth);
		mvprintw(DBL_BUFFED, 2, "Double buffered:\t%s",dbl_buff?"ON ":"OFF");
		mvprintw(WINDOWED, 2, "Windowed:\t\t%s",windowed?"ON ":"OFF");
		mvprintw(SAVE, 2, "Save and exit");
		mvprintw(EXIT, 2, "Exit without saving (you can press Q or ESC too)");
		
		refresh();
	}
	while(ch!=27&&ch!='q'&&ch!='Q');	//ESC
	
	endwin();
	return 0;
}

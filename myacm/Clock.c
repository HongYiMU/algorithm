#include "common.h"
#include <process.h>

extern void Clock();

typedef struct _clock{
	UCHAR year;
	UCHAR month;
	UCHAR day;
	UCHAR hour;
	UCHAR min;
	UCHAR second;
	UCHAR week;
	UCHAR status;
	UCHAR choice;
}clock_t;

void ClockRun(void* arg);
void ClockControl(void* arg);
void ClockShow(clock_t* clock);
void Clock()
{
	clock_t clock={14,10,28};
	_beginthread(ClockRun,0,&clock);
	_beginthread(ClockControl,0,&clock);
	_beginthread(ClockShow,0,&clock);
	while(1)
	{
		;
	}
}
void set_console_color(unsigned short color_index)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index);
}
void ClockShow(clock_t* clock)
{

	while(1)
	{
		Sleep(500);
		if(clock->choice == 0)
		{
			printf("\r%02d:%02d:%02d",clock->hour,clock->min,clock->second);
		}
		else if (clock->choice == 1)
		{
			printf("\r%02d:%02d:",clock->hour,clock->min);
				set_console_color(13);
				printf("%02d",clock->second);
				set_console_color(15);
		}
		else if (clock->choice == 2)
		{
			printf("\r%02d:",clock->hour);
			set_console_color(13);
			printf("%02d",clock->min);
			set_console_color(15);
			printf(":%02d",clock->second);

		}
		else if (clock->choice == 3)
		{
			set_console_color(13);
			printf("\r%02d",clock->hour);
			set_console_color(15);
			printf(":%02d:%02d",clock->min,clock->second);
		}
	}
}

void ClockRun(void* arg)
{
	clock_t *clock = (clock_t*)arg;
	while(1)
	{
		Sleep(1000);
		clock->second ++;
		if(clock->second >= 60)
		{
			clock->second = 0;
			clock->min++;
			if (clock->min >= 60)
			{
				clock->min = 0;
				clock->hour ++;
				if(clock->hour == 24)
				{
					clock->hour = 0;
				}
			}
		}
	}
}

void UpDown(char a, clock_t* clock)
{
	if(a == 'w')
	{
		if(clock->choice == 1)
		{
			++clock->second;
			if(clock->second >= 60)
			{
				clock->second = 0;
			}
		}
		else if (clock->choice == 2)
		{
			++(clock->min);
			if(clock->min >= 60)
			{
				clock->min = 0;
			}
		}
		else if(clock->choice == 3)
		{
			++clock->hour;
			if(clock->hour >= 24)
			{
				clock->hour = 0;
			}
		}

	}
	else
	{
		if(clock->choice == 1)
		{
			if (clock->second>0)
			{
				clock->second --;
			}
			else 
			{
				clock->second = 59;
			}
		}
		else if (clock->choice == 2)
		{
			if(clock->min>0)
			{
				clock->min --;
			}
			else 
			{
				clock->min = 59;
			}
		}
		else if(clock->choice == 3)
		{
			if(clock->hour >0)
			{
				clock->hour --;
			}
			else
			{
				clock->hour = 0;
			}
		}
	}
}


void ClockControl(void* arg)
{
	char get,ctrl;
	clock_t *clock = (clock_t*)arg;
	while((get = fgetc(stdin)) != 'b')
	{
		if(get == 'c')
		{
			clock->choice = 1;
			clock->status = 1;
			while((ctrl = fgetc(stdin)) != 'q')
			{
				switch(ctrl)
				{
					case 'a':
						if(clock->choice <3){clock->choice += 1;}
						else{clock->choice = 1;}
						break;
					case 'd':
						if(clock->choice >1){clock->choice -= 1;}
						else{clock->choice = 3;}
						break;
					case 's':
					case 'w':UpDown(ctrl,clock);break;
					default:
						break;
				}
			}
			clock->choice = 0;
			clock->status = 0;
			

		}
	}
}
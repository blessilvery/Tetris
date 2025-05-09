#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

//*********************************
//ªÛºˆ º±æ
//*********************************

#define EXT_KEY			0xffffffe0	//»Æ¿Â≈∞ ¿ŒΩƒ∞™ 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50

//*********************************
//±∏¡∂√º º±æ
//*********************************
struct STAGE{		//∞¢ Ω∫≈◊¿Ã¡ˆ∏∂¥Ÿ¿« ≥≠¿Ãµµ º≥¡§
	int	speed;	//º˝¿⁄∞° ≥∑¿ªºˆ∑œ º”µµ∞° ∫¸∏£¥Ÿ
	int stick_rate;		//∏∑¥Î∞° ≥™ø¿¥¬ »Æ∑¸ 0~99 , 99∏È ∏∑¥Î±‚∏∏ ≥™ø»
	int clear_line;
};

enum { 
		BLACK,      /*  0 : ±Ó∏¡ */ 
		DARK_BLUE,    /*  1 : æÓµŒøÓ ∆ƒ∂˚ */ 
		DARK_GREEN,    /*  2 : æÓµŒøÓ √ ∑œ */ 
		DARK_SKY_BLUE,  /*  3 : æÓµŒøÓ «œ¥√ */ 
		DARK_RED,    /*  4 : æÓµŒøÓ ª°∞≠ */ 
		DARK_VOILET,  /*  5 : æÓµŒøÓ ∫∏∂Û */ 
		DARK_YELLOW,  /*  6 : æÓµŒøÓ ≥Î∂˚ */ 
		GRAY,      /*  7 : »∏ªˆ */ 
		DARK_GRAY,    /*  8 : æÓµŒøÓ »∏ªˆ */ 
		BLUE,      /*  9 : ∆ƒ∂˚ */ 
		GREEN,      /* 10 : √ ∑œ */ 
		SKY_BLUE,    /* 11 : «œ¥√ */ 
		RED,      /* 12 : ª°∞≠ */ 
		VOILET,      /* 13 : ∫∏∂Û */ 
		YELLOW,      /* 14 : ≥Î∂˚ */ 	
		WHITE,      /* 15 : «œæÁ */ 	
}; 

//*********************************
//¿¸ø™∫Øºˆº±æ
//*********************************
int level;
int ab_x,ab_y;	//»≠∏È¡ﬂ ∫Ì∑∞¿Ã ≥™≈∏≥™¥¬ ¡¬«•¿« ¿˝¥Î¿ßƒ°
int block_shape,block_angle,block_x,block_y;
int next_block_shape;
int score;
int lines;
char total_block[21][14];		//»≠∏Èø° «•Ω√µ«¥¬ ∫Ì∑∞µÈ
struct STAGE stage_data[10];
char block[7][4][4][4]={
	//∏∑¥Î∏æÁ
	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

	//≥◊∏∏æÁ
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

	//'§√' ∏æÁ
	0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//'§°'∏æÁ
	1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//'§§' ∏æÁ
	1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

	//'Z' ∏æÁ
	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

	//'S' ∏æÁ
	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0

};
//*********************************
//«‘ºˆ º±æ
//*********************************
int gotoxy(int x,int y);	//ƒøº≠ø≈±‚±‚
void SetColor(int color);	//ªˆ«•«ˆ
int init();					//∞¢¡æ∫Øºˆ √ ±‚»≠
int show_cur_block(int shape,int angle,int x,int y);	//¡¯«‡¡ﬂ¿Œ ∫Ì∑∞¿ª »≠∏Èø° «•Ω√«—¥Ÿ
int erase_cur_block(int shape,int angle,int x,int y);	//∫Ì∑∞ ¡¯«‡¿« ¿‹ªÛ¿ª ¡ˆøÏ±‚ ¿ß«— «‘ºˆ
int show_total_block();	//Ω◊ø©¡Æ¿÷¥¬ ∫Ì∑∞¿ª »≠∏Èø° «•Ω√«—¥Ÿ.
int show_next_block(int shape);
int make_new_block();	//return∞™¿∏∑Œ block¿« ∏æÁπ¯»£∏¶ æÀ∑¡¡‹
int strike_check(int shape,int angle,int x,int y);	//∫Ì∑∞¿Ã »≠∏È ∏« æ∆∑°ø° ∫Œ¥⁄√∆¥¬¡ˆ ∞ÀªÁ ∫Œ¥⁄ƒ°∏È 1¿ª∏Æ≈œ æ∆¥œ∏È 0∏Æ≈œ
int merge_block(int shape,int angle,int x,int y);	//∫Ì∑∞¿Ã πŸ¥⁄ø° ¥Íæ“¿ª∂ß ¡¯«‡¡ﬂ¿Œ ∫Ì∑∞∞˙ Ω◊æ∆¡¯ ∫Ì∑∞¿ª «’ƒß
int block_start(int shape,int* angle,int* x,int* y);	//∫Ì∑∞¿Ã √≥¿Ω ≥™ø√∂ß ¿ßƒ°øÕ ∏æÁ¿ª æÀ∑¡¡‹
int move_block(int* shape,int* angle,int* x,int* y,int* next_shape);	//∞‘¿”ø¿πˆ¥¬ 1¿ª∏Æ≈œ πŸ¥⁄ø° ∫Ì∑∞¿Ã ¥Í¿∏∏È 2∏¶ ∏Æ≈œ
int rotate_block(int shape,int* angle,int* x,int* y);
int show_gameover();
int show_gamestat();
int show_logo();
int input_data();
int check_full_line();	


int main(int argc, char* argv[])
{
	int i;
	int is_gameover=0;
	char keytemp;
	init();
	show_logo();
	while(1)
	{
		
		input_data();
		show_total_block();
		block_shape = make_new_block();
		next_block_shape = make_new_block();
		show_next_block(next_block_shape);
		block_start(block_shape,&block_angle,&block_x,&block_y);
		show_gamestat();
		for(i=1;1;i++)
		{
			if(_kbhit())
			{
				keytemp = _getche();
				if(keytemp == EXT_KEY)
				{
					keytemp = _getche();
					switch(keytemp)
					{
					case KEY_UP:		//»∏¿¸«œ±‚
						
						if(strike_check(block_shape,(block_angle+1)%4,block_x,block_y) == 0)
						{
							erase_cur_block(block_shape,block_angle,block_x,block_y);
							block_angle = (block_angle+1)%4;
							show_cur_block(block_shape,block_angle,block_x,block_y);
						}
						break;
					case KEY_LEFT:		//øﬁ¬ ¿∏∑Œ ¿Ãµø
						if(block_x>1)
						{
							erase_cur_block(block_shape,block_angle,block_x,block_y);
							block_x--;
							if(strike_check(block_shape,block_angle,block_x,block_y) == 1)
								block_x++;
							
							show_cur_block(block_shape,block_angle,block_x,block_y);
						}
						break;
					case KEY_RIGHT:		//ø¿∏•¬ ¿∏∑Œ ¿Ãµø
						
						if(block_x<14)
						{
							erase_cur_block(block_shape,block_angle,block_x,block_y);
							block_x++;
							if(strike_check(block_shape,block_angle,block_x,block_y) == 1)
								block_x--;
							show_cur_block(block_shape,block_angle,block_x,block_y);
						}
						break;
					case KEY_DOWN:		//æ∆∑°∑Œ ¿Ãµø
						is_gameover = move_block(&block_shape,&block_angle,&block_x,&block_y,&next_block_shape);
						show_cur_block(block_shape,block_angle,block_x,block_y);
						break;
					}
				}
				if(keytemp == 32 )	//Ω∫∆‰¿ÃΩ∫πŸ∏¶ ¥≠∑∂¿ª∂ß
				{
					while(is_gameover == 0)
					{
						is_gameover = move_block(&block_shape,&block_angle,&block_x,&block_y,&next_block_shape);
					}
					show_cur_block(block_shape,block_angle,block_x,block_y);
				}
			}
			if(i%stage_data[level].speed == 0)
			{
				is_gameover = move_block(&block_shape,&block_angle,&block_x,&block_y,&next_block_shape);
				
				show_cur_block(block_shape,block_angle,block_x,block_y);
			}
			
			if(stage_data[level].clear_line == lines)	//≈¨∏ÆæÓ Ω∫≈◊¿Ã¡ˆ
			{
				level++;
				lines = 0;
			}
			if(is_gameover == 1)
			{
				show_gameover();
				SetColor(GRAY);
				break;
			}
			
			gotoxy(77,23);
			Sleep(15);
			gotoxy(77,23);
		}
		init();
	}
	return 0;
}

int gotoxy(int x,int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos; 
	pos.Y=y;
	pos.X=x;
	SetConsoleCursorPosition(hConsole, pos); 
	return 0;
}

void SetColor(int color) 

{ 
	static HANDLE std_output_handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color); 
	
} 

int init()
{
	int i,j;

	srand((unsigned)time(NULL));
	
	
	for(i=0;i<20;i++)
	{
		for(j=0;j<14;j++)
		{
			if((j==0) || (j==13))
			{
				total_block[i][j]=1;
			}else{
				total_block[i][j]=0;
			}
		}
	}

	for(j=0;j<14;j++)			//»≠∏È¿« ¡¶¿œ πÿ¿« ¡Ÿ¿∫ 1∑Œ √§øÓ¥Ÿ.
		total_block[20][j]=1;
	
	//¿¸ø™∫Øºˆ √ ±‚»≠
	level=0;
	lines=0;
	ab_x = 5;
	ab_y = 1;

	stage_data[0].speed=40;
	stage_data[0].stick_rate=20;	
	stage_data[0].clear_line=20;
	stage_data[1].speed=38;
	stage_data[1].stick_rate=18;
	stage_data[1].clear_line=20;
	stage_data[2].speed=35;
	stage_data[2].stick_rate=18;
	stage_data[2].clear_line=20;
	stage_data[3].speed=30;
	stage_data[3].stick_rate=17;
	stage_data[3].clear_line=20;
	stage_data[4].speed=25;
	stage_data[4].stick_rate=16;
	stage_data[4].clear_line=20;
	stage_data[5].speed=20;
	stage_data[5].stick_rate=14;
	stage_data[5].clear_line=20;
	stage_data[6].speed=15;
	stage_data[6].stick_rate=14;
	stage_data[6].clear_line=20;
	stage_data[7].speed=10;
	stage_data[7].stick_rate=13;
	stage_data[7].clear_line=20;
	stage_data[8].speed=6;
	stage_data[8].stick_rate=12;
	stage_data[8].clear_line=20;
	stage_data[9].speed=4;
	stage_data[9].stick_rate=11;
	stage_data[9].clear_line=99999;
	return 0;
}

int show_cur_block(int shape,int angle,int x,int y)
{
	int i,j;
	
	switch(shape)
	{
	case 0:
		SetColor(RED);
		break;
	case 1:
		SetColor(BLUE);
		break;
	case 2:
		SetColor(SKY_BLUE);
		break;
	case 3:
		SetColor(WHITE);
		break;
	case 4:
		SetColor(YELLOW);
		break;
	case 5:
		SetColor(VOILET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if( (j+y) <0)
				continue;

			if(block[shape][angle][j][i] == 1)
			{
				gotoxy((i+x)*2+ab_x,j+y+ab_y);
				printf("°·");

			}
		}
	}
	SetColor(BLACK);
	gotoxy(77,23);
	return 0;
}

int erase_cur_block(int shape,int angle,int x,int y)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(block[shape][angle][j][i] == 1)
			{
				gotoxy((i+x)*2+ab_x,j+y+ab_y);
				printf("  ");
				//break;
				
			}
		}
	}
	return 0;	
}



int show_total_block()
{
	int i,j;
	SetColor(DARK_GRAY);
	for(i=0;i<21;i++)
	{
		for(j=0;j<14;j++)
		{
			if(j==0 || j==13 || i==20)		//∑π∫ßø° µ˚∂Û ø‹∫Æ ªˆ¿Ã ∫Ø«‘
			{
				SetColor((level %6) +1);
				
			}else{
				SetColor(DARK_GRAY);
			}
			gotoxy( (j*2)+ab_x, i+ab_y );
			if(total_block[i][j] == 1)
			{	
				printf("°·");
			}else{
				printf("  ");
			}
			
		}
	}
	SetColor(BLACK);
	gotoxy(77,23);
	return 0;
}

int make_new_block()
{
	int shape;
	int i;
	i=rand()%100;
	if(i<=stage_data[level].stick_rate)		//∏∑¥Î±‚ ≥™ø√»Æ∑¸ ∞ËªÍ
		return 0;							//∏∑¥Î±‚ ∏æÁ¿∏∑Œ ∏Æ≈œ

	shape = (rand()%6)+1;		//shapeø°¥¬ 1~6¿« ∞™¿Ã µÈæÓ∞®
	show_next_block(shape);
	return shape;
}


int strike_check(int shape,int angle,int x,int y)
{
	int i,j;
	int block_dat;

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(  ((x+j) == 0)  || ((x+j) == 13) )
				block_dat = 1;
			else
				block_dat = total_block[y+i][x+j];
			
			
			if((block_dat == 1) && (block[shape][angle][i][j] == 1))																							//¡¬√¯∫Æ¿« ¡¬«•∏¶ ª©±‚¿ß«‘
			{
				return 1;
			}
		}
	}
	return 0;
}

int merge_block(int shape,int angle,int x,int y)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			total_block[y+i][x+j] |=  block[shape][angle][i][j];
		}
	}
	check_full_line();
	show_total_block();
	
	return 0;
}

int block_start(int shape,int* angle,int* x,int* y)
{
	
	*x = 5;
	*y = -3;
	*angle = 0;
	return 0;	
}

int show_gameover()
{
	SetColor(RED);
	gotoxy(15,8);
	printf("¶Æ¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶Ø");
	gotoxy(15,9);
	printf("¶≠**************************¶≠");
	gotoxy(15,10);
	printf("¶≠*        GAME OVER       *¶≠");
	gotoxy(15,11);
	printf("¶≠**************************¶≠");
	gotoxy(15,12);
	printf("¶±¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶∞");
	fflush(stdin);
	Sleep(1000);
	
	_getche();
	system("cls");

	return 0;
}

int move_block(int* shape,int* angle,int* x,int* y,int* next_shape)
{
	erase_cur_block(*shape,*angle,*x,*y);
	
	(*y)++;	//∫Ì∑∞¿ª «—ƒ≠ æ∆∑°∑Œ ≥ª∏≤
	if(strike_check(*shape,*angle,*x,*y) == 1)
	{
		if(*y<0)	//∞‘¿”ø¿πˆ
		{
			
			return 1;
		}
		(*y)--;
		merge_block(*shape,*angle,*x,*y);
		*shape = *next_shape;
		*next_shape = make_new_block();
		
		block_start(*shape,angle,x,y);	//angle,x,y¥¬ ∆˜¿Œ≈Õ¿”
		show_next_block(*next_shape);
		return 2;
	}
	return 0;
}

int rotate_block(int shape,int* angle,int* x,int* y)
{
	return 0;
}

int check_full_line()
{
	int i,j,k;
	for(i=0;i<20;i++)
	{
		for(j=1;j<13;j++)
		{
			if(total_block[i][j] == 0)
				break;
		}
		if(j == 13)	//«—¡Ÿ¿Ã ¥Ÿ √§øˆ¡≥¿Ω
		{
			lines++;
			show_total_block();
			SetColor(BLUE);
			gotoxy(1*2+ab_x,i+ab_y);
			for(j=1;j<13;j++)
			{
				printf("°‡");
				Sleep(10);
			}
			gotoxy(1*2+ab_x,i+ab_y);
			for(j=1;j<13;j++)
			{
				printf("  ");
				Sleep(10);
			}

			for(k=i;k>0;k--)
			{
				for(j=1;j<13;j++)
					total_block[k][j] = total_block[k-1][j];
			}
			for(j=1;j<13;j++)
				total_block[0][j] = 0;
			score+= 100+(level*10) + (rand()%10);
			show_gamestat();
		}
	}
	return 0;
}

int show_next_block(int shape)
{
	int i,j;
	SetColor((level+1)%6+1);
	for(i=1;i<7;i++)
	{
		gotoxy(33,i);
		for(j=0;j<6;j++)
		{
			if(i==1 || i==6 || j==0 || j==5)
			{
				printf("°·");				
			}else{
				printf("  ");
			}

		}
	}
	show_cur_block(shape,0,15,1);
	return 0;
}

int show_gamestat()
{
	static int printed_text=0;
	SetColor(GRAY);
	if(printed_text == 0)
	{
		gotoxy(35,7);
		printf("STAGE");

		gotoxy(35,9);
		printf("SCORE");

		gotoxy(35,12);
		printf("LINES");
		

	}
	gotoxy(41,7);
	printf("%d",level+1);
	gotoxy(35,10);
	printf("%10d",score);
	gotoxy(35,13);
	printf("%10d",stage_data[level].clear_line - lines);
	return 0;
}

int input_data()
{
	int i=0;
	SetColor(GRAY);
	gotoxy(10,7);
	printf("¶Æ¶¨¶¨¶¨¶¨<GAME KEY>¶¨¶¨¶¨¶¨¶¨¶Ø");
	Sleep(10);
	gotoxy(10,8);
	printf("¶≠ UP   : Rotate Block        ¶≠");
	Sleep(10);
	gotoxy(10,9);
	printf("¶≠ DOWN : Move One-Step Down  ¶≠");
	Sleep(10);
	gotoxy(10,10);
	printf("¶≠ SPACE: Move Bottom Down    ¶≠");
	Sleep(10);
	gotoxy(10,11);
	printf("¶≠ LEFT : Move Left           ¶≠");
	Sleep(10);
	gotoxy(10,12);
	printf("¶≠ RIGHT: Move Right          ¶≠");
	Sleep(10);
	gotoxy(10,13);
	printf("¶±¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶∞");

	
	while(i<1 || i>8)
	{
		gotoxy(10,3);
		printf("Select Start level[1-8]:       \b\b\b\b\b\b\b");
		scanf_s("%d",&i);
	}
	
	
	level = i-1;
	system("cls");
	return 0;
}

int show_logo()
{
	int i,j;
	gotoxy(13,3);
	printf("¶Æ¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶Ø");
	Sleep(100);
	gotoxy(13,4);
	printf("¶≠°ﬂ°ﬂ°ﬂ  °ﬂ°ﬂ°ﬂ  °ﬂ°ﬂ°ﬂ   °ﬂ°ﬂ     °ﬂ   °ﬂ°ﬂ°ﬂ ¶≠");
	Sleep(100);
	gotoxy(13,5);
	printf("¶≠  °ﬂ    °ﬂ        °ﬂ     °ﬂ °ﬂ    °ﬂ   °ﬂ     ¶≠");
	Sleep(100);
	gotoxy(13,6);
	printf("¶≠  °ﬂ    °ﬂ°ﬂ°ﬂ    °ﬂ     °ﬂ°ﬂ     °ﬂ     °ﬂ   ¶≠");
	Sleep(100);
	gotoxy(13,7);
	printf("¶≠  °ﬂ    °ﬂ        °ﬂ     °ﬂ °ﬂ    °ﬂ       °ﬂ ¶≠");
	Sleep(100);
	gotoxy(13,8);
	printf("¶≠  °ﬂ    °ﬂ°ﬂ°ﬂ    °ﬂ     °ﬂ  °ﬂ   °ﬂ   °ﬂ°ﬂ°ﬂ ¶≠");
	Sleep(100);
	gotoxy(13,9);
	printf("¶±¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶¨¶∞");

	gotoxy(28,20);
	printf("Please Press Any Key~!");

	for(i=0;i>=0;i++){
		if(i%40==0)
		{
			
			
			for(j=0;j<5;j++)
			{
				gotoxy(6,14+j);
				printf("                                                          ");
				
				
			}
			show_cur_block(rand()%7,rand()%4,6,14);
			show_cur_block(rand()%7,rand()%4,12,14);
			show_cur_block(rand()%7,rand()%4,19,14);
			show_cur_block(rand()%7,rand()%4,24,14);
		}
		if(_kbhit())
			break;
		Sleep(30);
	}
	
	_getche();
	system("cls");

	return 0;
}

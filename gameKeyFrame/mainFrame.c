#include<linux/kernel.h>
#include <stdio.h>
#include <linux/input.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <unistd.h>
#include<sys/mman.h>
#include<string.h>
#include"_font.h"
enum color{
	red = 1,
	yellow,
	blue,
	white,
	black
};
int *DISPLAY_MEM_BASE_fb = 0;
int color_trans(enum color co){
	int buf;
	if(co == white)
		buf = 0xffffffff;
	else if(co ==red)
		buf = 0xffff0000;
	else if(co == yellow)
		buf = 0xffffff00;
	else if(co == blue)
		buf = 0xff0000ff;
	else if(co == black)
		buf = 0;
	else buf = 0xffffffff;//default white
	return buf;
}
void pure_color(enum color co){
	int buf;
	buf = color_trans(co);
	for(long int i=0 ; i<= 1376 *768 -1; i++){	
		memcpy((int *)(DISPLAY_MEM_BASE_fb +i), &buf, sizeof(buf));
	}
	munmap(DISPLAY_MEM_BASE_fb, 1376 *768 *4);
        return;
}
void point_draw(int x, int y, enum color co){
	int buf;
	buf = color_trans(co);
	int location = x +y *1376;
	memcpy((int *)(DISPLAY_MEM_BASE_fb +location), &buf, sizeof(buf));
	munmap(DISPLAY_MEM_BASE_fb +location, 4);
        return;
}
void point_buff(int x, int y, enum color co){
	int buf;
	buf = color_trans(co);
	int location = x +y *1376;
	memcpy((int *)(DISPLAY_MEM_BASE_fb +location), &buf, sizeof(buf));
        return;
}
void line_draw(double x1, double y1, double x2, double y2,  enum color co){
	double k = (y2 -y1)/(x2 -x1);
	printf("k = %lf\n",k);
	if(x2 < x1){
		for(int i=0; i<=x1 -x2; i++)
			point_buff(x2 +i, y2+ i*k,co);
	}else{//x1 < x2
		for(int i=0; i<=x2 -x1; i++)
			point_buff((int)(x1 +i), (int)(y1+ (int)(i*k)),co);
	}
	munmap(DISPLAY_MEM_BASE_fb, 1376 *768 *4);
        return;
}
void matrix_draw(int x_start, int y_start, int width, int height, enum color co){
	int buf;
	buf = color_trans(co);
	int location_start = x_start +y_start *1376;
	for(int i=0;i<=height -1;i++)
		for(int j=0; j<=width -1; j++)
			memcpy((int *)(DISPLAY_MEM_BASE_fb +location_start +j+1376*i), &buf, sizeof(buf));

	for(int i=0;i<=height -1;i++)
		for(int j=0; j<=width -1; j++)
			munmap(DISPLAY_MEM_BASE_fb +location_start +j+1376*i, 4);
        return;
}
void char_line_buff(int x, int y, unsigned short code, enum color co){
	int x_now = x +15;
	int code_now = code;
	for(int i=0;i<=15;i++)//a line is 16 pix
		if(code_now %2 == 0){
			x_now --;
			code_now /=2;
		}
		else{ 
			point_buff(x_now--, y, co);
			code_now /=2;
		}
}
void char_draw(int x, int y, char c, enum color co){
	int buf;
	buf = color_trans(co);
	int x_now = x;
	int y_now = y;
	int font_index = (c - 0x20) * CHAR_HEIGHT;
	for(int i=0;i<=CHAR_HEIGHT -1;i++){
		if(helvB12_bits[font_index] == 0)
		{	
			font_index++;
			y_now ++;
		}
		else 
			char_line_buff(x_now, y_now++ ,helvB12_bits[font_index++], co);	
	}	
	munmap(DISPLAY_MEM_BASE_fb, 1376 *768 *4);
        return;
}


void fb_init(char *dev)
{
        int fd;
        struct fb_fix_screeninfo fb_fix;
        struct fb_var_screeninfo fb_var;
        char *buf;

        if ((fd = open(dev, O_RDWR)) < 0){
                printf("Unable to open framebuffer %s\n", dev);
                return;
        }
        if (ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0) {
                printf("Unable to get  FBIOGET_VSCREENINFO %s\n", dev);
                close(fd);
                return;
        }
        if (ioctl(fd, FBIOGET_FSCREENINFO, &fb_fix) < 0) {
                printf("Unable to get  FBIOGET_FSCREENINFO %s\n", dev);
                close(fd);
                return;
        }
        buf = (char *)mmap((void *) NULL, fb_fix.smem_len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
        if((int)buf == -1) {
                printf("Error: failed to map fb buffer to memory.\n");
                close(fd);
                return;
        }
        DISPLAY_MEM_BASE_fb = (int *)buf;
        return;
}

char char_gen_v1(int seed){//regular version
	return seed + 'A';
}
char char_gen_v2(int seed);//random version


int speed_gen(int seed){
	if(seed %3 ==0)
		return CHAR_HEIGHT *1;//slow
	if(seed %3 ==1)
		return CHAR_HEIGHT *2;//moderate
	if(seed %3 ==2)
		return CHAR_HEIGHT *3;//fast
}
//my dell 1366 *768 is event3 keyboard
#define DEV_PATH "/dev/input/event3"
char keys1[10] = {'q','w','e','r','t','y','u','i','o','p'};//16 -25
char keys2[9] = {'a','s','d','f','g','h','j','k','l'};//30 - 38
char keys3[7] = {'z','x','c','v','b','n','m'};//44 - 50


int main(){
	//this code can just run in 1366 *768
	fb_init("/dev/fb0");

	//back ground	
	pure_color(black);
	
	//argument of game
	int right_score = 0;
	int wrong_score = 0;
	int char_width = CHAR_WIDTH;
	int char_height = CHAR_HEIGHT;	
	int numOfColumn = 25;//change this as your will
	int wait_second = 1;//the letter will drop

	int x[25] ={0};
	int y[25] ={0};
	char c[25];
	int speed[25];
	int interval = 30;//30 pixels

	//char and speed prepare
	for(int i=0; i<=numOfColumn -1; i++){
		c[i] = char_gen_v1(i);
		speed[i] = speed_gen(i); 	
	}

	//caculate the X of all the char
	for(int i=0; i<=numOfColumn -1; i++){
		x[i] = x[i-1] +char_width +interval;	
	}
	//open key dev
	int fd;
	struct input_event t;
	fd=open(DEV_PATH, O_RDONLY | O_NONBLOCK);
	if(fd <= 0)
	{
		printf("open device error!\n");
		return -1;
	}
	//Main loop	
	while(1){
		//caculate the Y of all the char
		for(int i=0; i<=numOfColumn -1; i++){
			y[i] += speed[i];	
		}
		//Is it game over? check
		int flag = 0;
		for(int i=0;i<=numOfColumn -1;i++)
			if(y[i] >= 768)
				flag = 1;
		if(flag ==1)
			break;
		//draw
		fb_init("/dev/fb0");
		pure_color(black);
		for(int i=0;i<= numOfColumn -1; i++)
		{
			fb_init("/dev/fb0");
			if(c[i] == 0)
				c[i] = char_gen_v1(i);
			char_draw(x[i], y[i], c[i], red);	
		}
		//right score draw
		int right_tmp = right_score;
		for(int i=0;;i++){
			fb_init("/dev/fb0");
			int right_unit = right_tmp %10;
			char_draw(1300 -i*CHAR_WIDTH, 50, right_unit + '0', red);
			right_tmp/=10;
			if(right_tmp == 0)
				break;
		}
		//wrong score draw
		int wrong_tmp = wrong_score;
		for(int i=0;;i++){
			fb_init("/dev/fb0");
			int wrong_unit = wrong_tmp %10;
			char_draw(1300 -i*CHAR_WIDTH, 100, wrong_unit + '0', red);
			wrong_tmp/=10;
			if(wrong_tmp == 0)
				break;
		}
			
		//key detect
		char user_key = 0;
		int key_detect_wait = 1000;
		while(1){
			if(read(fd, &t, sizeof(t)) == sizeof(t))
			{		
				if(t.type==EV_KEY)
					if(t.value==0)//just push is one score
					{	
						if(t.code <= 25 && t.code >=16)
							user_key = keys1[t.code - 16];
						if(t.code <= 38 && t.code >=30)
							user_key = keys2[t.code - 30];
						if(t.code <= 50 && t.code >=44)
							user_key = keys3[t.code - 44];
						if(t.code == KEY_ESC)
							break;
					}

			}
			usleep(1000);//1 ms == 1000 us
			key_detect_wait --;
			if(key_detect_wait <= 0)break;
			if(user_key != 0)break;
		}
		user_key = user_key - 'a' + 'A';
		//check key
		int wrong_flag = 1;
		for(int i=0;i<=numOfColumn -1;i++){
			if(c[i] == user_key && t.type == EV_KEY){
				right_score ++;
				c[i] = 0;
				y[i] = 0;
				wrong_flag = 0;
			}
		}
		if(wrong_flag == 1 && t.type == EV_KEY)
			wrong_score ++;


	}
	//game over
	fb_init("/dev/fb0");
	pure_color(black);
	printf("RIGHT SCORE :%d\n",right_score);
	printf("WRONG SCORE:%d\n",wrong_score);
	sleep(5);
	
	return 0;
}

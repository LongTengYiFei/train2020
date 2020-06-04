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
enum color{
	red = 1,
	yellow,
	blue,
	white
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
	else buf = 0xffffffff;//default white
	return buf;
}
void pure_color(enum color co){
	int buf;
	buf = color_trans(co);
	//different machine has different resolusion
	for(long int i=0 ; i<= 1376 *768 -1; i++){	
		//printf("base = %ld i = %ld ",DISPLAY_MEM_BASE_fb, i);
		//printf("addr = %ld\n", DISPLAY_MEM_BASE_fb + 1);
		//base + i will reduce base +4
		//i dont know why
		memcpy((int *)(DISPLAY_MEM_BASE_fb +i), &buf, sizeof(buf));
	}
	munmap(DISPLAY_MEM_BASE_fb, 1376 *768 *4);
        return;
}
void point_draw(int x, int y, enum color co){
	int buf;
	buf = color_trans(co);
	//my screen is 1366 *768
	//x is in [0,1365]
	//but line_length is 5504,it means line has 1376 points
	//if you want to show a point x in[1366,1376],it will not show in screen
	//here y *1376 to locate the location
	int location = x +y *1376;
	memcpy((int *)(DISPLAY_MEM_BASE_fb +location), &buf, sizeof(buf));
	munmap(DISPLAY_MEM_BASE_fb +location, 4);
        return;
}
void line_draw(int x1, int y1, int x2, int y2,  enum color co){
	int buf;
	buf = color_trans(co);
	int location1 = x1 +y1 *1376;
	int location2 = x2 +y2 *1376;


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
void char_draw(char c){
        return;
}


void fb_init(char *dev)
{
        int fd;
        struct fb_fix_screeninfo fb_fix;
        struct fb_var_screeninfo fb_var;
        char *buf;

        if ((fd = open(dev, O_RDWR)) < 0)       {
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

        printf("framebuffer info: bits=%d, w=%d, h=%d, mem_line=%d, mem_size=%d\n",
                fb_var.bits_per_pixel, fb_var.xres, fb_var.yres, fb_fix.line_length, fb_fix.smem_len);

        buf = (char *)mmap((void *) NULL, fb_fix.smem_len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
        if((int)buf == -1) {
                printf("Error: failed to map fb buffer to memory.\n");
                close(fd);
                return;
        }

        DISPLAY_MEM_BASE_fb = (int *)buf;
        return;
}
int main(){
	fb_init("/dev/fb0");
	printf("size of base = %d\n",sizeof(DISPLAY_MEM_BASE_fb));	
	printf("base = %p\n",DISPLAY_MEM_BASE_fb);
	int wait_second = 5;
	//task1----------------
	
	pure_color(white);
	printf("pure color show over, wait %d seconds\n", wait_second);
	sleep(wait_second);
	
	//task2 draw point, line, matrix------------------
	//point
	fb_init("/dev/fb0");//last task has unmap fb0,so we need to init agian, unless will be segment fault
	point_draw(1366/2, 768/2, red);	
	printf("a point in the due middle, wait %d seconds\n",wait_second);
	sleep(wait_second);
	
	//line
	fb_init("/dev/fb0");
	line_draw(0,0, 1366/2, 768/2 ,blue);
	printf("line over, wait %d seconds\n",wait_second);
	sleep(wait_second);

	//matrix
	fb_init("/dev/fb0");
	matrix_draw(1366/2,768/2, 10, 10 ,blue);
	printf("matrix over, wait %d seconds\n",wait_second);
	sleep(wait_second);

	//task3 draw character-------------------




	return 0;
}

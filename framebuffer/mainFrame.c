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
	blue
};
void pure_color(enum color co){
        return;
}
void point_draw(int x, int y, enum color co){
        return;
}
void line_draw(int x1, int y1, int x2, int y2,  enum color co){
        return;
}
void matrix_draw(int x_start, int y_start, int width, int height, enum color co){
        return;
}
void char_draw(char c){
        return;
}


int *DISPLAY_MEM_BASE_fb = 0;
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
	int  buf = 0xffffffff;
	
	printf("size of buf = %d\n",sizeof(buf));	
	printf("size of base = %d\n",sizeof(DISPLAY_MEM_BASE_fb));	
	printf("base = %p\n",DISPLAY_MEM_BASE_fb);

	for(long int i=0 ; i<= 800 *600; i++){	
		//printf("base = %ld i = %ld ",DISPLAY_MEM_BASE_fb, i);
		//printf("addr = %ld\n", DISPLAY_MEM_BASE_fb + 1);
		memcpy((int *)(DISPLAY_MEM_BASE_fb +i), &buf, sizeof(buf));
	}
	munmap(DISPLAY_MEM_BASE_fb, 16777216);
	int wait_second1 = 5;
	printf("pure color show over, wait %d seconds\n", wait_second1);
	sleep(wait_second1);




	return 0;
}

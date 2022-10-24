#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>
#include <iostream>
#include <fstream>
#include <string>


#define VIDEO_INT               0x10      /* the BIOS video interrupt. */
#define SET_MODE                0x00      /* BIOS func to set the video mode. */
#define MODE_13H                0x13      /* use to set 256-color mode. */
#define TEXT_MODE               0x03      /* use to set 80x25 text mode. */

#define SCREEN_WIDTH        320       /* width in pixels of mode 0x13 */
#define SCREEN_HEIGHT       200       /* height in pixels of mode 0x13 */

#define SCREEN_SIZE             SCREEN_WIDTH*SCREEN_HEIGHT

#define NUM_COLORS          256       /* number of colors in mode 0x13 */

char *VGA=(char *)0xA0000000L;        /* this points to video memory. */

using namespace std;

void set_mode(char mode)
{
        union REGS regs;

        regs.h.ah = SET_MODE;
        regs.h.al = mode;
        int86(VIDEO_INT, &regs, &regs);
}

void end(){
    set_mode(TEXT_MODE);    //to get back into the normal mode
    exit(0);
}

void pixel(int x,int y,char color)      //Puts a pixel by writing directly to memory
{
        VGA[y*SCREEN_WIDTH+x]=color;
}

void clear(int color)
{
        memset(VGA,color,SCREEN_SIZE);
}

void draw_menu1(){
    for(int y=0; y<SCREEN_HEIGHT; y++){
        pixel(290, y, 0x09);
    }
}
void draw_menu2(){
    for(int x=0; x<SCREEN_WIDTH-30; x++){
        pixel(x, 180, 0x09);
    }
}

void draw_array(char in[16][16]){
    for(int x=0; x<16; x++){
        for(int y=0; y<16; y++){
            pixel(x,y,in[x][y]);
        }
    }
}
int main() {
    set_mode(MODE_13H);             //to get into mode13h
    clear(0x00);
    draw_menu1();
    draw_menu2();
    int c=0;
    /*for(int y=0; y<32; y+=2){
        for(int x=0; x<32; x+=2){
            pixel(x,y,c);
            pixel(x,y+1,c);
            pixel(x+1,y,c);
            pixel(x+1,y+1,c);
            c++;
        }
    }*/
    getc(stdin);
    clear(0x00);
    set_mode(TEXT_MODE);
    return 0;
}


/*
 * This File is Part Of : 
 *      ___                       ___           ___           ___           ___           ___                 
 *     /  /\        ___          /__/\         /  /\         /__/\         /  /\         /  /\          ___   
 *    /  /::\      /  /\         \  \:\       /  /:/         \  \:\       /  /:/_       /  /::\        /  /\  
 *   /  /:/\:\    /  /:/          \  \:\     /  /:/           \__\:\     /  /:/ /\     /  /:/\:\      /  /:/  
 *  /  /:/~/:/   /__/::\      _____\__\:\   /  /:/  ___   ___ /  /::\   /  /:/ /:/_   /  /:/~/::\    /  /:/   
 * /__/:/ /:/___ \__\/\:\__  /__/::::::::\ /__/:/  /  /\ /__/\  /:/\:\ /__/:/ /:/ /\ /__/:/ /:/\:\  /  /::\   
 * \  \:\/:::::/    \  \:\/\ \  \:\~~\~~\/ \  \:\ /  /:/ \  \:\/:/__\/ \  \:\/:/ /:/ \  \:\/:/__\/ /__/:/\:\  
 *  \  \::/~~~~      \__\::/  \  \:\  ~~~   \  \:\  /:/   \  \::/       \  \::/ /:/   \  \::/      \__\/  \:\ 
 *   \  \:\          /__/:/    \  \:\        \  \:\/:/     \  \:\        \  \:\/:/     \  \:\           \  \:\
 *    \  \:\         \__\/      \  \:\        \  \::/       \  \:\        \  \::/       \  \:\           \__\/
 *     \__\/                     \__\/         \__\/         \__\/         \__\/         \__\/                
 *
 * Copyright (c) Rinnegatamante <rinnegatamante@gmail.com>
 *
 */

#include <psp2/types.h>
#include <psp2/display.h>
#include <libk/stdio.h>
#include <libk/string.h>
#include "font.h"
#include "renderer.h"
#include <stdbool.h>
#include "log.h"

bool activeMenu = true;
unsigned int* vram32;
int pwidth, pheight, bufferwidth;
uint32_t color = 0x00FFFFFF;
float ch = 0;
float startCh = 0;
int rgbMode = 0;
bool backgroundMode = 0;
const uint32_t BG_COLOR = 0xFF000000;
const unsigned char transp = 0xAA;
bool importantText = false;

void updateFramebuf(const SceDisplayFrameBuf *param){
	pwidth = param->width;
	pheight = param->height;
	vram32 = param->base;
	bufferwidth = param->pitch;
}

void setTextColor(uint32_t clr){
	color = clr;
}
void setTextImportant(){
	importantText = true;
}
void setTextUnimportant(){
	importantText = false;
}

void resetRgbText(){
	if(rgbMode == 1){
		ch = startCh;
		startCh++;
		if(startCh > 360){
			startCh = 0;
		}
	}else{
		ch = 0;
	}
	
}
void rgbColorText(){
	ch += 2;
	if (ch >= 360) ch = 0;
	uint32_t rgb = hsvToRgb(ch, 255, 255);
	setTextColor(rgb);

}

void drawCharacter(int character, int x, int y){
    for (int yy = 0; yy < 10; yy++) {
        int xDisplacement = x;
        int yDisplacement = (y + (yy<<1)) * bufferwidth;
        uint32_t* screenPos = vram32 + xDisplacement + yDisplacement;

        uint8_t charPos = font[character * 10 + yy];
        for (int xx = 7; xx >= 2; xx--) {
			if(!importantText && rgbMode == 1){
				rgbColorText();
			}
			uint32_t clr = ((charPos >> xx) & 1) ? color : BG_COLOR;
			if(clr == BG_COLOR){
				if(backgroundMode == 0){
					clr = *(screenPos);
					unsigned char r = (clr >> 16) & 0xFF;
					unsigned char g = (clr >> 8) & 0xFF;
					unsigned char b = clr & 0xFF;

					r = (r >= transp) ? (r - transp) : 0;
					g = (g >= transp) ? (g - transp) : 0;
					b = (b >= transp) ? (b - transp) : 0;
					clr = (r << 16) | (g << 8) | b;
				}
				else if(backgroundMode == 1){
					screenPos += 2;
					continue;
				}
			}
			*(screenPos) = clr;
			*(screenPos+1) = clr;
			*(screenPos+bufferwidth) = clr;
			*(screenPos+bufferwidth+1) = clr;			
			screenPos += 2;
        }
    }
}



void drawString(int x, int y, const char *str){
	resetRgbText();
	size_t stringLength = sceClibStrnlen(str, 128);
	//logInfo("stlen : %d , %s", stringLength, str);
    for (size_t i = 0; i < stringLength; i++)
        drawCharacter(str[i], x + i * 12, y);
}

void drawStringF(int x, int y, const char *format, ...){
	
	char str[512] = { 0 };
	va_list va;

	va_start(va, format);
	sceClibVsnprintf(str, 512, format, va);
	va_end(va);

	drawString(x, y, str);
}

void toggleRGBMode(void){
	if(rgbMode == 0){
		rgbMode = 1;
	}else if(rgbMode == 1){
		rgbMode = 0;
	}
}


uint32_t RGB = 0;
uint32_t hsvToRgb(float H, float S, float V)
{
	/* by くりあ */
	float max = V;
	float min = max - ((S / 255) * max);
	int R = 0, G = 0, B = 0;
	
	// RGBの値を求める
	if (0 <= H && H <= 60)
	{ // Hが0～60の場合
		R = max;
		G = (H / 60) * (max - min) + min;
		B = min;
	}
	else if (H <= 120)
	{ // Hが60～120の場合
		R = ((120 - H) / 60) * (max - min) + min;
		G = max;
		B = min;
	}
	else if (H <= 180)
	{
		R = min;
		G = max;
		B = ((H - 120) / 60) * (max - min) + min;
	}
	else if (H <= 240)
	{
		R = min;
		G = ((240 - H) / 60) * (max - min) + min;
		B = max;
	}
	else if (H <= 300)
	{
		R = ((H - 240) / 60) * (max - min) + min;
		G = min;
		B = max;
	}
	else if (H <= 360)
	{
		R = max;
		G = min, B = ((360 - H) / 60) * (max - min) + min;
	}
	
	RGB = R;
	RGB <<= 8;
	RGB += G;
	RGB <<= 8;
	RGB += B;
	return RGB;
}

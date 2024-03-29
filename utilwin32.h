#ifndef UTILWIN32_H
#define UTILWIN32_H

#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y);
void clrscr();
WORD setTextColor(WORD color);

// FOREGROUND_BLUE(0x01), FOREGROUND_GREEN(0x02), FOREGROUND_RED(0x04), FOREGROUND_INTENSITY(0x08),
// BACKGROUND_BLUE(0x10), BACKGROUND_GREEN(0x20), BACKGROUND_RED(0x40), BACKGROUND_INTENSITY(0x80)

void delay(int milliSecond);
void drawBoundary(int orgX=10, int orgY=5, int width=25, int height=16);
#endif
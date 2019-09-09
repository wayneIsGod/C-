#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <conio.h> 
#include <iomanip>
#include <time.h>
#include "Point.h"
#include "Rect.h"
#include "Object.h"
#include "utilwin32.h"
using namespace std;

class game
{
private:
	static const int orgX = 10, orgY = 5, width = 10, height = 20;
	static const int max_object=width*height;
	static const int point_number=4;
	static const int square_number=7;
	static const int total_velocity=110;
	static const int total_delay=total_velocity-10;
	int max_delay;

	Object *square[square_number];
	Rect *canvas;
	Object save_object[max_object];
	int record[height][width];
public:
	game();
	virtual ~game();
    void object();
	void bingo(int object_number);
	void clean(int object_number);
};

#endif

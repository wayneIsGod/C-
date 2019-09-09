#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <cstdio>
using namespace std;

class Rect;
class Point
{
private:
	int m_x;
	int m_y;
public:
	Point();
	Point(const int x,const int y);
	Point operator+(const Point &rhs) const;
	Point operator-(const Point &rhs) const;
	Point operator*(const Point &rhs) const;
	bool operator==(const Point &rhs) const;
	virtual ~Point();
	bool isInside(const Rect &rect) const;
	void next_move();
	int return_x() const;
	int return_y() const;
	Point return_sub_add() const;
	Point return_add_sub() const;
	Point return_sub_sub() const;
	void clean(int orgX, int orgY, int width, int height);
};

#endif

#ifndef RECT_H
#define RECT_H
#include "Point.h"

class Object;
class Rect
{
private:
	int m_left;
	int m_right;
	int m_top;
	int m_bottom;
public:
	Rect(const int left,const int right,const int top,const int bottom);
	virtual ~Rect();
	int return_left() const;
	int return_right() const;
	int return_top() const;
	int return_bottom() const;
	bool contains(const Point &pt) const; 
	bool contains(const Object &obj) const;
	void clean() const; 
	void draw() const; 
};

#endif
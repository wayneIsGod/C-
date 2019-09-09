#include "Point.h"
#include "Rect.h"
#include "utilwin32.h"

Point::Point():m_x(20),m_y(5)
{
}

Point::Point(const int x,const int y):m_x(x),m_y(y)
{
}

Point Point::operator+(const Point &rhs) const
{
    Point ans;
	ans.m_x=m_x+rhs.m_x;
	ans.m_y=m_y+rhs.m_y;
	return ans;
}

Point Point::operator-(const Point &rhs) const
{
    Point ans;
	ans.m_x=m_x-rhs.m_x;
	ans.m_y=m_y-rhs.m_y;
	return ans;
}

Point Point::operator*(const Point &rhs) const
{
    Point ans;
	ans.m_x=m_x*rhs.m_x;
	ans.m_y=m_y*rhs.m_y;
	return ans;
}

bool Point::operator==(const Point &rhs) const
{
	if((m_x==rhs.m_x)&&(m_y==rhs.m_y))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
Point::~Point()
{

}

bool Point::isInside(const Rect &rect) const
{
	if(m_x>rect.return_left()&&m_x<rect.return_right()&&m_y>rect.return_top()&&m_y<rect.return_bottom())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Point::next_move()
{
	m_y++;
}

int Point::return_x() const
{
	return m_x;
}

int Point::return_y() const
{
	return m_y;
}

Point Point::return_sub_add() const
{
	Point temp;
	temp.m_x=m_x*(-1);
	temp.m_y=m_y;
	return temp;
}

Point Point::return_add_sub() const
{
	Point temp;
	temp.m_x=m_x;
	temp.m_y=m_y*(-1);
	return temp;
}

Point Point::return_sub_sub() const
{
	Point temp;
	temp.m_x=m_x*(-1);
	temp.m_y=m_y*(-1);
	return temp;
}

void Point::clean(int orgX, int orgY, int width, int height)
{
	m_x=orgX+width+5;
	m_y=orgY+height;
	gotoxy(m_x,m_y);
	cout<<" ";
	gotoxy(1,orgY+height+2);
}

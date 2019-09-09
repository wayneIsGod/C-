#include "Rect.h"
#include "Object.h"
#include "utilwin32.h"

Rect::Rect(const int left,const int right,const int top,const int bottom):m_left(left),m_right(right),m_top(top),m_bottom(bottom)
{
}

Rect::~Rect()
{
}

int Rect::return_left() const
{
	return m_left;
}
int Rect::return_right() const
{
	return m_right;
}
int Rect::return_top() const
{
	return m_top;
}
int Rect::return_bottom() const
{
	return m_bottom;
}

bool Rect::contains(const Point &pt) const
{
	 int ans=pt.isInside(*this);
	 return ans;
}
bool Rect::contains(const Object &obj) const
{
	 int ans=obj.isInside(*this);
	 return ans;
}

void Rect::clean() const
{
	const int orgX=m_left;
	const int orgY=m_top;
	const int width=m_right-m_left+1;
	const int height=m_bottom-m_top+1;
	gotoxy(orgX-1, orgY-1);
    cout << " ";
    for (int i=0; i<width; i++)
	{
		cout << " ";
	}
    cout << " ";
    for (int i=0; i<height; i++)
    {
        gotoxy(orgX-1, orgY+i); cout << " ";
        gotoxy(orgX+width, orgY+i); cout << " ";
    }
    gotoxy(orgX-1, orgY+height);
    cout << " ";
    for (int i=0; i<width; i++)
	{
		cout << " ";
	}
    cout << " ";
    gotoxy(1,orgY+height+2);
}

void Rect::draw() const
{
	const int orgX=m_left;
	const int orgY=m_top;
	const int width=m_right-m_left+1;
	const int height=m_bottom-m_top+1;
	gotoxy(orgX-1, orgY-1);
    cout << "+";
    for (int i=0; i<width; i++)
	{
		cout << "-";
	}
    cout << "+";
    for (int i=0; i<height; i++)
    {
        gotoxy(orgX-1, orgY+i); cout << "|";
        gotoxy(orgX+width, orgY+i); cout << "|";
    }
    gotoxy(orgX-1, orgY+height);
    cout << "+";
    for (int i=0; i<width; i++)
	{
		cout << "-";
	}
    cout << "+";
    gotoxy(1,orgY+height+2);
}
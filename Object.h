#ifndef OBJECT_H
#define OBJECT_H
#include "Rect.h"

class Object
{
private:
	static const int point_number=4;
	int total_velocity;
	int total_delay;
	int max_delay;
	int count;
	int fast;

	char m_face;
	Point m_position;
	Point m_data[point_number];
public:
	Object();
	Object(const char face, const Point position, const Point data[4], int delay ,int total);
	Object(const Object &rhs, int delay ,int total);
	virtual ~Object();
	bool isInside(const Rect &rect) const;
	bool move_isInside(const Rect &rect) const;
	void control(char direction, const Object other[], const int object_number, const Rect &boundary, int orgX, int orgY, int width, int height);
	bool move(const Point &offset, const Object other[], const int object_number, const Rect &boundary, int faster, int orgX, int orgY, int width, int height);
	void next_move(int orgX, int orgY, int width, int height);
	int hit_edge(const Point &offset, const Object other[], const int object_number, const Rect &boundary, int faster, int orgX, int orgY, int width, int height);
	int hit_object(const Object other[], const int object_number, const Rect &boundary, int faster, int orgX, int orgY, int width, int height);
	void hit_left_right(const Object other[], const int object_number, const Rect &boundary, int hit, int orgX, int orgY, int width, int height);
	void Rotate(const Object other[], const int object_number, const Rect &boundary, int orgX, int orgY, int width, int height);
	Point* return_data();
	void next(int x ,int orgX, int orgY, int width, int height);
	void add_delay();
	void sub_delay();
	void clean(const Point &rhs, int orgX, int orgY, int width, int height);
    void draw(bool show, int orgX, int orgY, int width, int height) const;
};

#endif

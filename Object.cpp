#include "Object.h"
#include "utilwin32.h"

Object::Object()
{
}
Object::Object(const char face, const Point position, const Point data[4] ,int total, int delay):count(0),fast(0),total_velocity(total),total_delay(total-10),max_delay(delay)
{
	m_face=face;
	m_position=position;
	for(int i=0;i<point_number;i++)
	{
		m_data[i]=position+data[i];
	}
}

Object::Object(const Object &rhs ,int total, int delay):count(rhs.count),fast(rhs.fast),total_velocity(total),total_delay(total-10),max_delay(delay)
{
    m_face=rhs.m_face;
	m_position=rhs.m_position;
	for(int i=0;i<point_number;i++)
	{
		m_data[i]=rhs.m_data[i];
	}
}

Object::~Object()
{
}


bool Object::isInside(const Rect &rect) const
{
	for(int i=0;i<point_number;i++)
	{
		if((m_data[i].return_x()<=rect.return_left())||(m_data[i].return_x()>=rect.return_right())||(m_data[i].return_y()<=rect.return_top())||(m_data[i].return_y()>=rect.return_bottom()))
		{
			return 0;
		}
	}
	return 1;
}

bool Object::move_isInside(const Rect &rect) const
{
	for(int i=0;i<point_number;i++)
	{
		if((m_data[i].return_x()<=rect.return_left())||(m_data[i].return_x()>=rect.return_right())||(m_data[i].return_y()<=rect.return_top())||(m_data[i].return_y()>rect.return_bottom()))
		{
			return 0;
		}
	}
	return 1;
}

void Object::control(char direction, const Object other[], const int object_number, const Rect &boundary, int orgX, int orgY, int width, int height)
{
	int go=0;
	if(move_isInside(boundary)==1)
	{
		for(int i=0;i<point_number;i++)
		{
			if(m_face=='3')
			{
				if(m_data[i].return_x()<boundary.return_right()-1)
    			{
    				if(direction==77)
                	{
    					go=1;
                	}
    			}
    			if(m_data[i].return_x()>boundary.return_left()+1)
    			{
    				if(direction==75)
                	{
    					go=2;
            	    }
    			}
    			if(m_data[i].return_y()<boundary.return_bottom())
    			{
    				if(direction==80)
            	    {
    					go=3;
        	        }
    			}
    			if(m_data[i].return_y()>boundary.return_top())
    			{
    				if(direction==72)
            	    {
    					go=4;
            	    }
    			}
			}
			else
			{
				if(m_data[i].return_x()<boundary.return_right()-2)
    			{
    				if(direction==77)
                	{
    					go=1;
                	}
    			}
    			if(m_data[i].return_x()>boundary.return_left()+2)
    			{
    				if(direction==75)
                	{
    					go=2;
            	    }
    			}
    			if(m_data[i].return_y()<boundary.return_bottom())
    			{
    				if(direction==80)
            	    {
    					go=3;
        	        }
    			}
    			if(m_data[i].return_y()>boundary.return_top())
    			{
    				if(direction==72)
            	    {
    					go=4;
            	    }
    			}
			}
		}
		if(go==1)
		{
			Point temp(1,0);
            move(temp,other,object_number,boundary,1,orgX,orgY,width,height);
		}
		if(go==2)
		{
			Point temp(-1,0);
            move(temp,other,object_number,boundary,1,orgX,orgY,width,height);
		}
		if(go==3)
		{
			Point temp(0,1);
            move(temp,other,object_number,boundary,1,orgX,orgY,width,height);
		}
	}
	else 
	{
        return;
	}
}

bool Object::move(const Point &offset, const Object other[], const int object_number, const Rect &boundary, int faster, int orgX, int orgY, int width, int height)
{
	fast=faster;
	Point temp=offset;
	Point fix=offset;
	Point left(-1,0);
	Point right(1,0);
	Point down(0,1);
	Point zore(0,0);
	int next=0;
	int hit=hit_object(other,object_number,boundary,1,orgX,orgY,width,height);
	if(hit==0||hit==5)
	{
		if(move_isInside(boundary)==0)
		{
			next=hit_edge(fix,other,object_number,boundary,faster,orgX,orgY,width,height);
		}
		else
    	{
    		if(fast==0&&count<max_delay)
    		{
    			count++;
    			delay(10);
    		}
    		else if(fast==0)
    		{
    			draw(0,orgX,orgY,width,height);
            	for(int i=0;i<point_number;i++)
        	    {
        		    m_data[i]=m_data[i]+temp;
        		}
            	draw(1,orgX,orgY,width,height);
    			count=0;
    		}
    		else
    		{
    			draw(0,orgX,orgY,width,height);
            	for(int i=0;i<point_number;i++)
        	    {
        		    m_data[i]=m_data[i]+temp;
        		}
            	draw(1,orgX,orgY,width,height);
    		}
    	}
	}
	else if(hit==4)
	{
		if(move_isInside(boundary)==0)
		{
			next=hit_edge(fix,other,object_number,boundary,faster,orgX,orgY,width,height);
		}
		hit_left_right(other,object_number,boundary,hit,orgX,orgY,width,height);
		for(int i=0;i<point_number;i++)
		{
			if((m_data[i].return_y()<boundary.return_bottom()))
			{
				Point fix(0,1);
				temp=fix;
				next=0;
			}
			else
			{
				temp=zore;
				next=1;
				break;
			}
		}
		if(fast==0&&count<max_delay)
		{
			count++;
			delay(10);
		}
		else if(fast==0)
		{
			draw(0,orgX,orgY,width,height);
        	for(int i=0;i<point_number;i++)
    	    {
    		    m_data[i]=m_data[i]+temp;
    		}
        	draw(1,orgX,orgY,width,height);
			count=0;
		}
		else
		{
			draw(0,orgX,orgY,width,height);
        	for(int i=0;i<point_number;i++)
    	    {
    		    m_data[i]=m_data[i]+temp;
    		}
        	draw(1,orgX,orgY,width,height);
		}
	}
	else if((hit==2||hit==6)||(hit==3||hit==7))
	{
		if(move_isInside(boundary)==0)
		{
			next=hit_edge(fix,other,object_number,boundary,faster,orgX,orgY,width,height);
		}
        hit_left_right(other,object_number,boundary,hit,orgX,orgY,width,height);
		for(int i=0;i<point_number;i++)
		{
			if((m_data[i].return_y()<boundary.return_bottom()))
			{
				next=0;
			}
			else
			{
				temp=zore;
				next=1;
				break;
			}
		}
		if((((hit==2||hit==6)&&(offset==left)==0)||((hit==3||hit==7)&&(offset==right)==0))&&(offset==down)==0)
		{
			if(fast==0&&count<max_delay)
    		{
    			count++;
    			delay(10);
    		}
    		else if(fast==0)
    		{
    			draw(0,orgX,orgY,width,height);
            	for(int i=0;i<point_number;i++)
        	    {
        		    m_data[i]=m_data[i]+temp+down;
        		}
            	draw(1,orgX,orgY,width,height);
    			count=0;
    		}
    		else
    		{
    			draw(0,orgX,orgY,width,height);
            	for(int i=0;i<point_number;i++)
        	    {
        		    m_data[i]=m_data[i]+temp+down;
        		}
            	draw(1,orgX,orgY,width,height);
    		}
		}
		else if(((hit==2||hit==6)&&(offset==left))||((hit==3||hit==7)&&(offset==right)))
		{
			if(count<max_delay)
    		{
    			count++;
    			delay(10);
    		}
    		else 
    		{
    			draw(0,orgX,orgY,width,height);
            	for(int i=0;i<point_number;i++)
        	    {
        		    m_data[i]=m_data[i]+down;
        		}
            	draw(1,orgX,orgY,width,height);
    			count=0;
    		}
		}
		else
		{
			if(fast==0&&count<max_delay)
    		{
    			count++;
    			delay(10);
    		}
    		else if(fast==0)
    		{
    			draw(0,orgX,orgY,width,height);
            	for(int i=0;i<point_number;i++)
        	    {
        		    m_data[i]=m_data[i]+down;
        		}
            	draw(1,orgX,orgY,width,height);
    			count=0;
    		}
    		else
    		{
    			draw(0,orgX,orgY,width,height);
            	for(int i=0;i<point_number;i++)
        	    {
        		    m_data[i]=m_data[i]+down;
        		}
            	draw(1,orgX,orgY,width,height);
    		}
		}
		for(int n=0;n<object_number;n++)
		{
			other[n].draw(1,orgX,orgY,width,height);
		}
	}
	return next;
}

void Object::next_move(int orgX, int orgY, int width, int height)
{
	Point zore(1,1);
	Point next(0,1);
	draw(0,orgX,orgY,width,height);
	for(int i=0;i<point_number;i++)
	{
		if((m_data[i]==zore)==0)
		{
			m_data[i]=m_data[i]+next;
		}
	}
	draw(1,orgX,orgY,width,height);
}

int Object::hit_edge(const Point &offset, const Object other[], const int object_number, const Rect &boundary, int faster, int orgX, int orgY, int width, int height)
{
	Point zore(0,0);
	Point down(0,1);
	Point fix=zore;
	int next=0;
	if(isInside(boundary)==0)
    {
	    for(int i=point_number-1;i>=0;i--)
    	{
    		if(m_data[i].return_x()<=boundary.return_left()&&m_data[i].return_y()>=boundary.return_bottom())
	    	{
		    	Point min_fix(1,0);
			    fix=min_fix;
				next=1;
    			break;
	    	}
		    if(m_data[i].return_x()>=boundary.return_right()&&m_data[i].return_y()>=boundary.return_bottom())
    		{
	    		Point min_fix(-1,0);
		    	fix=min_fix;
				next=1;
    			break;
	    	}
		    if(m_data[i].return_y()>=boundary.return_bottom())
    		{
 	    		Point min_fix(0,-1);
				if(fix.return_y()>-1)
				{
					fix=fix+min_fix;
				}
				next=1;
	    	}
	        if(m_data[i].return_x()<=boundary.return_left())
		    {
    			Point min_fix(1,0);
	    		if(fix.return_x()<1)
				{
					fix=fix+min_fix;
				}
				next=0;
		    }
    		if(m_data[i].return_x()>=boundary.return_right())
	    	{
		    	Point min_fix(-1,0);
			    if(fix.return_x()>-1)
				{
					fix=fix+min_fix;
				}
				next=0;
    		}
	    	if(m_data[i].return_y()<=boundary.return_top())
		    {
			    Point min_fix(0,1);
				if(fix.return_y()<1)
				{
					fix=fix+min_fix;
				}
				next=0;
	    	}
		    if(m_data[i]==zore)
			{
				fix=zore;
    		}
		}
		draw(0,orgX,orgY,width,height);
        for(int i=0;i<point_number;i++)
    	{
    		m_data[i]=m_data[i]+fix;
        }
    	draw(1,orgX,orgY,width,height);
		boundary.draw();

		if(offset==down&&count<max_delay)
    	{
    		count++;
    		delay(10);
    	}
    	else if(offset==down)
    	{
    		draw(0,orgX,orgY,width,height);
            for(int i=0;i<point_number;i++)
        	{
        		m_data[i]=m_data[i]+offset;
        	}
            draw(1,orgX,orgY,width,height);
    		count=0;
    	}
    	else
    	{
    		draw(0,orgX,orgY,width,height);
            for(int i=0;i<point_number;i++)
        	{
        		m_data[i]=m_data[i]+offset;
        	}
            draw(1,orgX,orgY,width,height);
    	}
		boundary.draw();
	}
	return next;
}

int Object::hit_object(const Object other[], const int object_number, const Rect &boundary, int faster, int orgX, int orgY, int width, int height)
{
	Point up(0,-1);
	Point test(0,1);
	Point test_left(-1,0);
	Point test_right(1,0);
	Point test_two_left(-2,0);
	Point test_two_right(2,0);
	Point test_three_left(-3,0);
	Point test_three_right(3,0);
	int my_total=0;
	int your_total=0;
	int left=0;
	int right=0;
	int long_left=0;
	int long_right=0;
	int ans=0;
	for(int i=0;i<point_number;i++)
	{
		for(int m=0;m<object_number;m++)
		{
			for(int x=0;x<point_number;x++)
			{
				if((m_data[i])==other[m].m_data[x])
    			{
					draw(0,orgX,orgY,width,height);
					for(int a=0;a<point_number;a++)
					{
						m_data[a]=m_data[a]+up;
					}
					draw(1,orgX,orgY,width,height);
					for(int n=0;n<object_number;n++)
					{
						other[n].draw(1,orgX,orgY,width,height);
					}

    				ans=1;
					for(int n=0;n<object_number;n++)
					{
						for(int j=0;j<point_number;j++)
						{
							if(m_data[i]==other[n].m_data[j])
        					{
        						for(int t=0;t<point_number;t++)
        						{
									if(t==i)
									{
										t++;
									}
									if(((m_data[t].return_x()==(other[n].m_data[j].return_x())-1)||(m_data[t].return_x()==(other[n].m_data[j].return_x())+1))&&((m_data[t]==other[n].m_data[j])==0))
									{
										my_total=0;
										your_total=0;
										for(int a=0;a<point_number;a++)
										{
											my_total=my_total+m_data[a].return_x();
										}
										for(int a=0;a<point_number;a++)
										{
											your_total=your_total+other[n].m_data[a].return_x();
										}
										if(my_total>=your_total)
										{
											ans=2;
										}
										if(my_total<=your_total)
										{
											ans=3;
										}

									}
        							else if(t==point_number-1&&ans==1)
        							{
        								return 1;
        							}
        						}

        					}

						}
						if(ans!=1)
						{
							return ans;
						}
					}
	    			return 1;
			    }
			}
		}
	}

	for(int i=0;i<point_number;i++)
	{
		for(int m=0;m<object_number;m++)
		{
			for(int x=0;x<point_number;x++)
			{
				if((m_data[i]+test)==other[m].m_data[x])
    			{
    				ans=5;
					for(int n=0;n<object_number;n++)
					{
						for(int j=0;j<point_number;j++)
						{
							if(m_data[i]==other[n].m_data[j])
        					{
        						for(int t=0;t<point_number;t++)
        						{
									if(t==i)
									{
										t++;
									}
									if(((m_data[t].return_x()==(other[n].m_data[j].return_x())-1)||(m_data[t].return_x()==(other[n].m_data[j].return_x())+1))&&((m_data[t]+test==other[n].m_data[j])==0))
									{
										my_total=0;
										your_total=0;
										for(int a=0;a<point_number;a++)
										{
											my_total=my_total+m_data[a].return_x();
										}
										for(int a=0;a<point_number;a++)
										{
											your_total=your_total+other[n].m_data[a].return_x();
										}
										if(my_total>=your_total)
										{
											ans=6;
										}
										if(my_total<=your_total)
										{
											ans=7;
										}

									}
        							else if(t==point_number-1&&ans==5)
        							{
        								return 5;
        							}
        						}

        					}

						}
						if(ans!=5)
						{
							return ans;
						}
					}
	    			return 5;
			    }
			}
		}
	}

	left=0;
	right=0;
	for(int i=0;i<point_number;i++)
	{
		for(int n=0;n<object_number;n++)
		{
			for(int j=0;j<point_number;j++)
			{
				if(m_face!='3')
				{
					if((m_data[i]+test_left)==other[n].m_data[j])
        			{
        				left=1;
    	    			ans=6;
    			    }
				}
			}
		}
	}
	for(int i=0;i<point_number;i++)
	{
		for(int n=0;n<object_number;n++)
		{
			for(int j=0;j<point_number;j++)
			{
				if(m_face!='3')
				{
					if((m_data[i]+test_right)==other[n].m_data[j])
        			{
        				right=1;
    	    			ans=7;
    			    }
				}
			}
		}
	}
	if(m_face=='3')
	{
		for(int i=0;i<point_number;i++)
		{
			for(int n=0;n<object_number;n++)
			{
				for(int j=0;j<point_number;j++)
				{
					if((m_data[i]+test_left)==other[n].m_data[j])
					{
						long_left=1;
					}
					if((m_data[i]+test_right)==other[n].m_data[j])
					{
						long_right=1;
					}
				}
			}
			if(long_left==1)
			{
				ans=6;
				left=1;
				for(int n=0;n<object_number;n++)
				{
					for(int j=0;j<point_number;j++)
					{
						if((m_data[i]+test_right)==other[n].m_data[j]||(m_data[i]+test_two_right)==other[n].m_data[j]||(m_data[i]+test_three_right)==other[n].m_data[j])
						{
							ans=2;
							left=0;
						}
					}
				}
				if((m_data[point_number-1].return_x()==m_data[0].return_x())==0)
				{
					ans=6;
    				left=0;
				}
			}
			if(long_right==1)
			{
				ans=7;
				right=1;
				for(int n=0;n<object_number;n++)
				{
					for(int j=0;j<point_number;j++)
					{
						if((m_data[i]+test_left)==other[n].m_data[j]||(m_data[i]+test_two_left)==other[n].m_data[j]||(m_data[i]+test_three_left)==other[n].m_data[j])
						{
							ans=3;
							right=0;
						}
					}
				}
				if((m_data[point_number-1].return_x()==m_data[0].return_x())==0)
				{
					ans=7;
    				right=0;
				}
			}
			for(int n=0;n<object_number;n++)
			{
				for(int j=0;j<point_number;j++)
				{
					if(((m_data[i]+test_two_left)==other[n].m_data[j])&&((m_data[i]+test_two_right)==other[n].m_data[j])&&(m_data[point_number-1].return_x()==m_data[0].return_x()))
					{
						ans=5;
					}
				}
			}
		}
	}
	if(left==1&&right==1)
	{
		if((m_data[point_number-1].return_x()-m_data[0].return_x())==2||(m_data[point_number-1].return_x()-m_data[0].return_x())==-2)
		{
			return ans;
		}
		ans=4;
	}
	return ans; 
}

void Object::hit_left_right(const Object other[], const int object_number, const Rect &boundary, int hit, int orgX, int orgY, int width, int height)
{
	Point test_left(-1,0);
	Point test_right(1,0);
	for(int i=0;i<point_number;i++)
    {
    	for(int n=0;n<object_number;n++)
    	{
    		for(int j=0;j<point_number;j++)
    		{
				if((m_data[i])==other[n].m_data[j])
         		{
	    			Point fix_left(-1,0);
					Point fix_right(1,0);
					if((m_data[i].return_y()<boundary.return_bottom())&&(hit==2||hit==6))
					{
						draw(0,orgX,orgY,width,height);
    	    			for(int t=0;t<point_number;t++)
	    	    		{
		    	    		m_data[t]=m_data[t]+fix_right;
			    	    }
    					draw(1,orgX,orgY,width,height);
	    			}
    	   			if((m_data[i].return_y()<boundary.return_bottom())&&(hit==3||hit==7))
					{
						draw(0,orgX,orgY,width,height);
    	    			for(int t=0;t<point_number;t++)
	    	    		{
		    	    		m_data[t]=m_data[t]+fix_left;
			    	    }
    					draw(1,orgX,orgY,width,height);
					}
	    		}
			}
		}
	}
}
void Object::Rotate(const Object other[], const int object_number, const Rect &boundary, int orgX, int orgY, int width, int height)
{
	int condition=0;
	Point left(-1,0);
	Point right(1,0);
	for(int i=0;i<point_number;i++)
	{
		if((m_data[i].return_x()>boundary.return_left())&&(m_data[i].return_x()<boundary.return_right())&&(m_data[i].return_y()>boundary.return_top())&&(m_data[i].return_y()<boundary.return_bottom()-1))
		{
			condition=1;
		}
		else
		{
			condition=0;
			break;
		}
	}
	if(((hit_object(other,object_number,boundary,1,orgX,orgY,width,height)==0)||(hit_object(other,object_number,boundary,1,orgX,orgY,width,height)==6)||(hit_object(other,object_number,boundary,1,orgX,orgY,width,height)==7))&&condition==1)
	{
		draw(0,orgX,orgY,width,height);
    	for(int i=0;i<point_number;i++)
	    {
		    for(int j=1;j<=point_number;j++)
    		{
	    		Point case1(j*-1,0);
		    	Point case2(0,j);
			    Point case3(j,0);
    			Point case4(0,j*-1);
    			Point case5(j,j);
    			Point case6(j,j*-1);
    			Point case7(j*-1,j*-1);
    			Point case8(j*-1,j);
    			Point ans1(j,j);
    			Point ans2(j,j*-1);
    			Point ans3(j*-1,j*-1);
    			Point ans4(j*-1,j);
    			Point ans5(0,j*-2);
    			Point ans6(j*-2,0);
    			Point ans7(0,j*2);
    			Point ans8(j*2,0);
                if((m_data[i]-m_data[1])==case1)
    			{
    				m_data[i]=m_data[i]+ans1;
    			}
    			else if((m_data[i]-m_data[1])==case2)
    			{
    				m_data[i]=m_data[i]+ans2;
    			}
    			else if((m_data[i]-m_data[1])==case3)
    			{
    				m_data[i]=m_data[i]+ans3;
    			}
    			else if((m_data[i]-m_data[1])==case4)
    			{
    				m_data[i]=m_data[i]+ans4;
    			}
    			else if((m_data[i]-m_data[1])==case5)
    			{
    				m_data[i]=m_data[i]+ans5;
    			}
    			else if((m_data[i]-m_data[1])==case6)
    			{
    				m_data[i]=m_data[i]+ans6;
    			}
    			else if((m_data[i]-m_data[1])==case7)
    			{
    				m_data[i]=m_data[i]+ans7;
    			}
    			else if((m_data[i]-m_data[1])==case8)
    			{
    				m_data[i]=m_data[i]+ans8;
    			}
    		}
    	}
    	draw(1,orgX,orgY,width,height);
	}
	Point fix(0,0);
	hit_edge(fix,other,object_number,boundary,1,orgX,orgY,width,height);
}

Point* Object::return_data()
{
	return m_data;
}

void Object::next(int x, int orgX, int orgY, int width, int height)
{
	draw(0,orgX,orgY,width,height);
	Point move(x,0); 
	for(int i=0;i<point_number;i++)
	{
		m_data[i]=m_data[i]+move;
	}
	draw(1,orgX,orgY,width,height);
}

void Object::add_delay()
{
	if(max_delay>=10&&max_delay<total_delay)
	{
		max_delay=max_delay+10;
	}
}

void Object::sub_delay()
{
	if(max_delay>10&&max_delay<=total_delay)
	{
		max_delay=max_delay-10;
	}
}

void Object::clean(const Point &rhs, int orgX, int orgY, int width, int height)
{
	for(int i=0;i<point_number;i++)
	{
		if(m_data[i]==rhs)
		{
			gotoxy(m_data[i].return_x(),m_data[i].return_y());
			cout<<" ";
			m_data[i].clean(orgX,orgY,width,height);
			gotoxy(1,orgY+height+2);
		}
	}
	gotoxy(1,orgY+height+2);
}
void Object::draw(bool show, int orgX, int orgY, int width, int height) const
{
	Point did(orgX+width+5,orgY+height);
	if(show==1)
	{
		for(int i=0;i<point_number;i++)
		{
			if(m_data[i]==did)
			{
				gotoxy(m_data[i].return_x(),m_data[i].return_y());
    			cout<<" ";
				gotoxy(1,orgY+height+2);
			}
			else
			{
				gotoxy(m_data[i].return_x(),m_data[i].return_y());
    			cout<<m_face;
				gotoxy(1,orgY+height+2);
			}
		}
	}
	else
	{
		for(int i=0;i<point_number;i++)
		{
			gotoxy(m_data[i].return_x(),m_data[i].return_y());
			cout<<" ";
			gotoxy(1,orgY+height+2);
		}
	}
	gotoxy(1,orgY+height+2);
}

#include"game.h"

game::game():max_delay(30)
{
    canvas=new Rect(orgX, orgX+width-1, orgY, orgY+height-1);
	const Point shape1[point_number] = { Point(-1,0), Point(0,0), Point(-1,1), Point(0,1) };
	const Point shape2[point_number] = { Point(-1,0), Point(0,0), Point(0,1), Point(1,0) };
	const Point shape3[point_number] = { Point(0,-1), Point(0,0), Point(0,1), Point(0,2) };
	const Point shape4[point_number] = { Point(-1,0), Point(0,0), Point(0,1), Point(0,2) };
	const Point shape5[point_number] = { Point(1,0), Point(0,0), Point(0,1), Point(0,2) };
	const Point shape6[point_number] = { Point(-1,0), Point(0,0), Point(0,1), Point(1,1) };
	const Point shape7[point_number] = { Point(1,0), Point(0,0), Point(0,1), Point(-1,1) };
	square[0]=new Object('1', Point(orgX+width/2-1,orgY+2), shape1, total_velocity, max_delay);
	square[1]=new Object('2', Point(orgX+width/2-1,orgY+2), shape2, total_velocity, max_delay);
	square[2]=new Object('3', Point(orgX+width/2-1,orgY+2), shape3, total_velocity, max_delay);
	square[3]=new Object('4', Point(orgX+width/2-1,orgY+2), shape4, total_velocity, max_delay);
	square[4]=new Object('5', Point(orgX+width/2-1,orgY+2), shape5, total_velocity, max_delay);
	square[5]=new Object('6', Point(orgX+width/2-1,orgY+2), shape6, total_velocity, max_delay);
	square[6]=new Object('7', Point(orgX+width/2-1,orgY+2), shape7, total_velocity, max_delay);

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
            record[i][j]=0;
		}
	}
}
game::~game()
{
	for(int i=0;i<square_number;i++)
	{
		delete square[i];
	}
	delete canvas;
}

void game::object()
{
    clrscr();
	cout<<endl;
	cout<<"按←,→,↓,↑:移動"<<"    "<<"按空白鍵:旋轉"<<"      "<<"按w:加速"<<"        "<<"按s:減速"<<endl;
	cout<<"按z:暫停/繼續"<<"         "<<"按esc:結束"<<endl;
	gotoxy(orgX+width+3,orgY);
	cout<<"next方塊:";
    (*canvas).draw();
	cout<<endl;
	gotoxy(orgX+width+3,orgY+6);
	cout<<"速度:"<<endl;
	gotoxy(orgX+width+3,orgY+7);
	cout<<max_delay<<endl;

	srand((unsigned)time(NULL)); 
	int sq=rand()%(square_number);
	Object* obj=new Object(*(square[sq]),total_velocity,max_delay);
	sq=rand()%(square_number);
	Object* next_obj=new Object(*(square[sq]),total_velocity,max_delay);
	(*next_obj).next(width,orgX,orgY,width,height);
    assert((*obj).isInside((*canvas)));

    (*obj).draw(1,orgX,orgY,width,height);
	Point velocity(0,1);
	Point save=velocity;
	char input=0;
	char direction=0;
	int tap=0;
	int velocity_tap=0;
	int total_object=0;
	while(1)
	{	
		input=0;
		direction=0;
		if (kbhit()) 
        {
            input = getch();
        }
		if(input==-32&&tap==0)
		{
			direction = getch();
			(*obj).control(direction,save_object,total_object,(*canvas),orgX,orgY,width,height);
		}
 	    if((*obj).hit_object(save_object,total_object,(*canvas),0,orgX,orgY,width,height)==1)
    	{
			save_object[total_object]=(*obj);
			for(int i=0;i<point_number;i++)
			{
				if((*obj).return_data()[i].return_y()==orgY+2)
				{
					gotoxy(1,orgY+height+2);
					cout<<"game over!"<<endl;
					delete obj;
					obj=0;
					delete next_obj;
					next_obj=0;
					return;
				}
			}
			for(int i=0;i<point_number;i++)
			{
				if(total_object<max_object)
				{
     				int x=((save_object[total_object].return_data())[i]).return_x()-orgX;
    				int y=((save_object[total_object].return_data())[i]).return_y()-orgY;
    				record[y-1][x-1]=1;
				}
			}
			for(int y=0;y<height;y++)
					{
						gotoxy(33,y+4);
						for(int x=0;x<width;x++)
						{
							printf("%d",record[y][x]);
						}
						printf("\n");
					} 
			total_object++;
			bingo(total_object);
			for(int y=0;y<height;y++)
					{
						gotoxy(33,y+4);
						for(int x=0;x<width;x++)
						{
							printf("%d",record[y][x]);
						}
						printf("\n");
					} 
			delete obj;
		    obj=0;
			obj=next_obj;
			(*obj).next(width*-1,orgX,orgY,width,height);
			(*next_obj).draw(0,orgX,orgY,width,height);
			sq=rand()%(square_number);
			next_obj=new Object(*(square[sq]),total_velocity,max_delay);
			(*next_obj).next(width,orgX,orgY,width,height);
			clean(total_object);
		}
		else
		{
			    if((*obj).move(velocity,save_object,total_object,(*canvas),0,orgX,orgY,width,height)==1)
			    {
				    save_object[total_object]=(*obj);
					for(int i=0;i<point_number;i++)
    			    {
						if(total_object<max_object)
						{
    	    	    		int x=((save_object[total_object].return_data())[i]).return_x()-orgX;
    		    		    int y=((save_object[total_object].return_data())[i]).return_y()-orgY;
    	    	    		record[y-1][x-1]=1;
						}
        			}
        			for(int y=0;y<height;y++)
					{
						gotoxy(33,y+4);
						for(int x=0;x<width;x++)
						{
							printf("%d",record[y][x]);
						}
						printf("\n");
					} 
    				total_object++;
					bingo(total_object);
					for(int y=0;y<height;y++)
					{
						gotoxy(33,y+4);
						for(int x=0;x<width;x++)
						{
							printf("%d",record[y][x]);
						}
						printf("\n");
					} 
	    			delete obj;
		         	obj=0;
			        obj=next_obj;
					(*obj).next(width*-1,orgX,orgY,width,height);
					(*next_obj).draw(0,orgX,orgY,width,height);
					sq=rand()%(square_number);
        			next_obj=new Object(*(square[sq]),total_velocity,max_delay);
					(*next_obj).next(width,orgX,orgY,width,height);
					clean(total_object);
				}
		}
		if(input==32&&tap==0)
		{
			(*obj).Rotate(save_object,total_object,(*canvas),orgX,orgY,width,height);
		}
		if(input=='z'||input=='Z')
		{
			Point temp(0,0);
			if(tap==0)
			{
				velocity=temp;
				tap=1;
			}
			else
			{
				velocity=save;
				tap=0;
			}
		}
		if(input==27)
		{
			delete obj;
		    obj=0;
			delete next_obj;
		    next_obj=0;
			break;
		}
		if(input=='w'||input=='W')
		{
			(*obj).sub_delay();
			if(max_delay>10&&max_delay<=total_delay)
			{
				max_delay=max_delay-10;
			}
		}
		if(input=='s'||input=='S')
		{
			(*obj).add_delay();
			if(max_delay>=10&&max_delay<total_delay)
			{
				max_delay=max_delay+10;
			}
		}
		gotoxy(orgX+width+3,orgY+7);
		cout<<total_velocity-max_delay<<endl;
		gotoxy(1,orgY+height+2);
		if((total_velocity-max_delay)==100)
		{
			velocity_tap=1;
		}
		if((total_velocity-max_delay)<100&&velocity_tap==1)
		{
			gotoxy(orgX+width+3,orgY+7);
			cout<<"   "<<endl;
			gotoxy(1,orgY+height+2);
			gotoxy(orgX+width+3,orgY+7);
			cout<<total_velocity-max_delay<<endl;
			velocity_tap=0;
			gotoxy(1,orgY+height+2);
		}
		(*canvas).draw();
		gotoxy(1,orgY+height+2);
	}
    gotoxy(1,orgY+height+3);
}

void game::bingo(int object_number)
{
	int pass=0;
	int cleaned=0;
	int num_y=0;
	int record_y[height];
	for(int y=0;y<height;y++)
	{
		record_y[y]=0;
	}
	for(int y=0;y<height;y++)
	{
		for(int x=0;x<width-2;x++)
		{
			if(record[y][x]==1)
			{
				pass=1;
			}
			else
			{
				pass=0;
				break;
			}
		}
		if(pass==1)
		{
			record_y[num_y]=y;
			num_y++;
		}
	}
	for(int y=0;y<num_y;y++)
	{
		for(int n=0;n<object_number;n++)
		{
			for(int i=0;i<point_number;i++)
			{
				if((((save_object[n].return_data())[i]).return_y()-orgY-1)==record_y[y])
     			{
		    		save_object[n].clean(((save_object[n].return_data())[i]),orgX,orgY,width,height);
					cleaned=1;
			    }
		    }
		}
	}
	for(int i=0;i<num_y;i++)
	{
		for(int j=0;j<width-2;j++)
		{
			record[record_y[i]][j]=0;
	    }
	}
 	if(cleaned==1)
	{
		Point zroe(1,1);
		Point next(0,1);
		for(int t=0;t<num_y;t++)
	    {
		    for(int n=0;n<object_number;n++)
			{
				for(int i=0;i<point_number;i++)
				{
					if(((((save_object[n].return_data())[i]).return_y()-orgY-1)<=record_y[t])&&((((save_object[n].return_data())[i])==zroe)==0))
    				{
						save_object[n].draw(0,orgX,orgY,width,height);
						save_object[n].return_data()[i].next_move();
						save_object[n].draw(1,orgX,orgY,width,height);
					}
				}
			}
		}
		for(int t=0;t<num_y;t++)
		{
			for(int y=record_y[t];y>=0;y--)
    	    {
    		    for(int x=0;x<width-2;x++)
    		    {
    				if(record[y][x]==1&&record[y+1][x]==0)
    				{
    					record[y][x]=0;
    					record[y+1][x]=1;
    				}
    			}
    		}
		}
		for(int x=0;x<width-2;x++)
		{
			record[height-1][x]=0;
		}
	}
}

void game::clean(int object_number)
{
	int clear=0;
	Point final(1,1);
	for(int n=0;n<object_number;n++)
	{
		for(int i=0;i<point_number;i++)
		{
			if(((save_object[n].return_data())[i])==final)
			{
				clear=1;
			}
			else
			{
				clear=0;
				break;
			}
		}
		if(clear==1)
		{
			for(int t=n;t<object_number;t++)
			{
				save_object[t]=save_object[t+1];
			}
			Point shace[4] = { Point(0,0), Point(0,0), Point(0,0), Point(0,0) };
			Object temp(' ',Point(1,1),shace,total_velocity,max_delay);
			save_object[object_number]=temp;

		}
		(*canvas).draw();
	}
}

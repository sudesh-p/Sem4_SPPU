//Problem Definition: Write a program to implement Digital Differential Analyzer (DDA) Line drawing algorithm & Bresenham.

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;
class Pixel	//Base Class
{
	protected:
		int x1,x2,y1,y2;
	public:
		Pixel()
		{
			x1=0;
			x2=0;
			y1=0;
			y2=0;
		}
};
class Line: public Pixel //Derived class
{
	//int x1,x2,y1,y2;
  public:
	void drawline();
	void drawline(int ch);
	void DrawLine();
};

void Line::drawline()
{
	float x,y,dx,dy;
	int i,length;
	cout<<"Enter the X1 and Y1 co-ordiates::";   cin>>x1>>y1;
	cout<<"Enter the X2 and Y2 co-ordiates::";   cin>>x2>>y2;
	dx = x2-x1;
	dy = y2-y1;

	if(dx>=dy)
		length = dx;
	else
		length = dy;

	cout<<"\n dx = "<< dx;
	cout<<"\n dy = "<< dy;

	dx = dx/length;
	dy = dy/length;

	x=x1;
	y=y1;
	i=0;
	while(i<=length)
	{
		putpixel(x,y,WHITE);
		x = x + dx;
		y = y + dy;
		i++;
	}
	std::system("gnome-screenshot -f dda.jpg");
	delay(5200);
}

void Line::drawline(int ch)
{

	int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
	dx=x2-x1;
	dy=y2-y1;
	dx1=fabs(dx);
	dy1=fabs(dy);
	px=2*dy1-dx1;
	py=2*dx1-dy1;
 	if(dy1<=dx1)
	{
		if(dx>=0)
		{
   			x=x1;
   			y=y1;
			xe=x2;
  		}
		else
  		{
   			x=x2;
			y=y2;
   			xe=x1;
  		}
  		putpixel(x,y,1);
  		for(i=0;x<xe;i++)
  		{
			x=x+1;
   			if(px<0)
   			{
				px=px+2*dy1;
   			}
   			else
   			{
				if((dx<0 && dy<0) || (dx>0 && dy>0))
     					y=y+1;
                else
     					y=y-1;
    				px=px+2*(dy1-dx1);
			}
			delay(0);
			putpixel(x,y,1);
		}
	}
	else
	{
		if(dy>=0)
		{
			x=x1;
			y=y1;
			ye=y2;
		}
		else
		{
			x=x2;
			y=y2;
			ye=y1;
		}
		putpixel(x,y,1);
		for(i=0;y<ye;i++)
		{
			y=y+1;
			if(py<=0)
				py=py+2*dx1;
			else
			{
				if((dx<0 && dy<0) || (dx>0 && dy>0))
					x=x+1;
				else
					x=x-1;
				py=py+2*(dx1-dy1);
			}
			delay(0);
   			putpixel(x,y,1);
		}
 	}
}

int main()
{
	int gd = DETECT, gm;
	initgraph(&gd,&gm,NULL);
	int ch;
	Line l;
	do
	{
		cout<<"\n_____________________";
		cout<<"\n1. DDA Algorithm::";
		cout<<"\n2. BRESANHAM's Algorithm::\n";
		cout<<"_____________________";
		cout<<"\nEnter ur choice::\t";
		cin>>ch;
        switch(ch)
		 {
			  case 1:
				l.drawline();
				delay(5000);
				std::system("gnome-screenshot -f dda.jpg");
				break;

			  case 2:
				l.drawline(2);
				delay(5000);
				std::system("gnome-screenshot -f bre.jpg");
				break;
		 }
	}while(ch<3);
	closegraph();
	return 0;
}

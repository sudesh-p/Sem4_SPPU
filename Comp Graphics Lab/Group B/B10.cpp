//Problem Definition: Write a program to implement DDA Line drawing algorithm to draw thick lines.
// Exam mei either DDA or Bresenham hai toh code aaadha hoga..

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
  public:
	void drawline(int x1, int y1, int x2, int y2,int gap);
	void drawline(int ch, int x1, int y1, int x2, int y2, int gap);
	void DrawLine();
	void Thicklinestyle(int ch);
	void Thinlinestyle(int ch);
	void Dottedlinestyle(int ch);
	void Dashedlinestyle(int ch);
	void Dashdotlinestyle(int ch);
};

void Line::Thicklinestyle(int ch)
{
	int thickness=0,i;
	int wy=0,wx=0;
	cout<<"\nEnter the X1 and Y1 co-ordiates::";   cin>>x1>>y1;
	cout<<"\nEnter the X2 and Y2 co-ordiates::";   cin>>x2>>y2;
	cout<<"\nEnter a thickness value : ";
	cin>>thickness;
	if((y2-y1)/(x2-x1))<1)
	{
		wy=(thickness-1)*sqrt(pow((x2-x1),2) + pow((y2-y1),2)) / (2*fabs(x2-x1));

		if(ch==1)
		{
			drawline(x1,y1,x2,y2,0);
			for(i=0;i<wy;i++)
			{
				drawline(x1,y1+i,x2,y2+i,0);
				drawline(x1,y1-i,x2,y2-i,0);
			}
		}
		else
		{
			drawline(2,x1,y1,x2,y2,0);
			for(i=0;i<wy;i++)
			{
				drawline(2,x1,y1+i,x2,y2+i,0);
				drawline(2,x1,y1-i,x2,y2-i,0);
			}
		}
	}
	else
	{
		wx=(thickness-1)*sqrt(pow((x2-x1),2) + pow((y2-y1),2)) / (2*fabs(y2-y1));

		if(ch==1)
		{
			drawline(x1,y1,x2,y2,0);
			for(i=0;i<wy;i++)
			{
				drawline(x1-i,y1,x2+i,y2,0);
				drawline(x1+i,y1,x2-i,y2,0);
			}
		}
		else
		{
			drawline(2,x1,y1,x2,y2,0);
			for(i=0;i<wy;i++)
			{
				drawline(2,x1+i,y1,x2+i,y2,0);
				drawline(2,x1-i,y1,x2-i,y2,0);
			}
		}
	}
}
void Line::Thinlinestyle(int ch)
{
	cout<<"\nEnter the X1 and Y1 co-ordiates::";   cin>>x1>>y1;
	cout<<"\nEnter the X2 and Y2 co-ordiates::";   cin>>x2>>y2;
	if(ch==3)
		drawline(x1,y1,x2,y2,0);
	else
		drawline(2,x1,y1,x2,y2,0);
}
void Line::Dottedlinestyle(int ch)
{
	cout<<"\nEnter the X1 and Y1 co-ordiates::";   cin>>x1>>y1;
	cout<<"\nEnter the X2 and Y2 co-ordiates::";   cin>>x2>>y2;
	if(ch==5)
		drawline(x1,y1,x2,y2,1);
	else
		drawline(2,x1,y1,x2,y2,1);
}
void Line::Dashedlinestyle(int ch)
{
	cout<<"\nEnter the X1 and Y1 co-ordinates::";   cin>>x1>>y1;
	cout<<"\nEnter the X2 and Y2 co-ordinates::";   cin>>x2>>y2;
	if(ch==7)
		drawline(x1,y1,x2,y2,2);
	else
		drawline(2,x1,y1,x2,y2,2);
}
void Line::Dashdotlinestyle(int ch)
{
	cout<<"\nEnter the X1 and Y1 co-ordinates::";   cin>>x1>>y1;
	cout<<"\nEnter the X2 and Y2 co-ordinates::";   cin>>x2>>y2;
	if(ch==9)
		drawline(x1,y1,x2,y2,3);
	else
		drawline(2,x1,y1,x2,y2,3);
}
void Line::drawline(int x1, int y1, int x2, int y2,int gap)
{
	float x,y,dx,dy;
	int i,length;
	dx = x2-x1;
	dy = y2-y1;

	if(dx>=dy)
		length = dx;
	else
		length = dy;

	dx = dx/length;
	dy = dy/length;

	x=x1;
	y=y1;
	i=0;
	while(i<=length)
	{
		if(gap == 1)
		{
			if(i%3 == 0)
			{
				putpixel(x,y,WHITE);
				x = x + dx;
				y = y + dy;
			}
			else
			{
				x = x + dx;
				y = y + dy;
			}
		}
		else if(gap == 2)
		{
			if(i%5 != 0)
			{
				putpixel(x,y,WHITE);
				x = x + dx;
				y = y + dy;
			}
			else
			{
				x = x + dx;
				y = y + dy;
			}
		}
		else if(gap == 3)
		{
			if(i%2 != 0 )
			{
				putpixel(x,y,WHITE);
				x = x + dx;
				y = y + dy;
				i++;
			}
			if(i%2 == 0 )
			{
				x = x + dx;
				y = y + dy;
				i++;
			}
			while(i%9 != 0)
			{
				putpixel(x,y,WHITE);
				x = x + dx;
				y = y + dy;
				i++;
			}
			if(i%2 != 0 )
			{
				x = x + dx;
				y = y + dy;
			}
		}
		else if(gap==0)
		{
			putpixel(x,y,WHITE);
			x = x + dx;
			y = y + dy;
		}
		i++;
	}
	std::system("gnome-screenshot -f dda.jpg");
	delay(5200);
}

void Line::drawline(int ch, int x1, int y1, int x2, int y2,int gap)
{

	int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i,flag=0;
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
    				{
     					y=y+1;
    				}
    				else
    				{
     					y=y-1;
    				}
    				px=px+2*(dy1-dx1);
			}
			delay(0);
			if(gap ==0)
				putpixel(x,y,1);
			else if(i%3 == 0 && gap == 1)
				putpixel(x,y,1);
			else if(gap == 2 && i%5 != 0)
				putpixel(x,y,1);
			else if(gap == 3)
			{
				if(flag == 1)
					putpixel(x,y,1);
				else if(flag >=3 && flag <=9)
					putpixel(x,y,1);
				if(flag<9)
					flag++;
				else
					flag=0;
			}
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
			{
				py=py+2*dx1;
			}
			else
			{
				if((dx<0 && dy<0) || (dx>0 && dy>0))
				{
					x=x+1;
				}
				else
				{
					x=x-1;
				}
				py=py+2*(dx1-dy1);
			}
			delay(0);
			if(gap ==0)
				putpixel(x,y,1);
			else if(i%3 == 0 && gap == 1)
				putpixel(x,y,1);
			else if(gap == 2 && i%5 != 0)
				putpixel(x,y,1);
			else if(gap == 3)
			{
				if(flag == 1)
					putpixel(x,y,1);
				else if(flag >=3 && flag <=9)
					putpixel(x,y,1);
				if(flag<9)
					flag++;
				else
					flag=0;
			}
		}
 	}
}

int main()
{
	int gdriver = DETECT, gmode;
	initgraph(&gdriver,&gmode,NULL);
	int ch;
	Line l;
	do
	{
		cout<<"\n_____________________";
		cout<<"\n1. Thick line generation using DDA Algorithm::";
		cout<<"\n2. Thick line generation using BRESANHAM's Algorithm::\n";
		cout<<"\n3. Thin line generation using DDA Algorithm::";
		cout<<"\n4. Thin line generation using BRESANHAM's Algorithm::\n";
		cout<<"\n5. Dotted line generation using DDA Algorithm::";
		cout<<"\n6. Dotted line generation using BRESANHAM's Algorithm::\n";
		cout<<"\n7. Dashed line generation using DDA Algorithm::";
		cout<<"\n8. Dashed line generation using BRESANHAM's Algorithm::\n";
		cout<<"\n9. Dash-Dot line generation using DDA Algorithm::";
		cout<<"\n10. Dash-Dot line generation using BRESANHAM's Algorithm::\n";
		cout<<"_____________________";
		cout<<"\nEnter ur choice::\t";
		cin>>ch;

		switch(ch)
		{
			case 1:
				l.Thicklinestyle(1);
				delay(2000);
				std::system("gnome-screenshot -f dda.jpg");
				break;

			case 2:
				l.Thicklinestyle(2);
				delay(2000);
				std::system("gnome-screenshot -f bre.jpg");
				break;

			case 3:
				l.Thinlinestyle(3);
				delay(2000);
				std::system("gnome-screenshot -f dda.jpg");
				break;

			case 4:
				l.Thinlinestyle(4);
				delay(2000);
				std::system("gnome-screenshot -f bre.jpg");
				break;

			case 5:
				l.Dottedlinestyle(5);
				delay(2000);
				std::system("gnome-screenshot -f dda.jpg");
				break;

			case 6:
				l.Dottedlinestyle(6);
				delay(2000);
				std::system("gnome-screenshot -f bre.jpg");
				break;

			case 7:
				l.Dashedlinestyle(7);
				delay(2000);
				std::system("gnome-screenshot -f dda.jpg");
				break;

			case 8:
				l.Dashedlinestyle(8);
				delay(2000);
				std::system("gnome-screenshot -f bre.jpg");
				break;

			case 9:
				l.Dashdotlinestyle(9);
				delay(2000);
				std::system("gnome-screenshot -f dda.jpg");
				break;

			case 10:
				l.Dashdotlinestyle(10);
				delay(2000);
				std::system("gnome-screenshot -f bre.jpg");
				break;
		}

	}while(ch<11);
	closegraph();
	return 0;
}

#include<iostream>
#include<graphics.h>
#include<cstdlib>
#include<math.h>
#include<stdio.h>
using namespace std;
class Pixel
{
	protected:
		int center_x,center_y,r;
	public:
		Pixel()
		{
			center_x=0;
			center_y=0;
			r=0;
		};
};
class Circle: public Pixel
{
	public:
		void drawCircle()
		{
			int x,y,pk;
			printf("*** Bresenham's Circle Drawing Algorithm in C++ ***\n");
			cout<<"Enter the value of center_x\t";
			cin>>center_x;
			cout<<"Enter the value of center_y\t";
			cin>>center_y;
			cout<<"Enter the Radius of circle\t";
			cin>>r;
			x=0;
			y=r;
			putpixel(center_x+x,center_y-y,1);
			pk=3-(2*r);
			for(x=0;x<=y;x++)
			{
				if (pk<0)
				{
					y=y;
					pk=(pk+(4*x)+6);
				}
				else
				{
					y=y-1;
					pk=pk+((4*(x-y)+10));
				}
				putpixel(center_x+x,center_y-y,7);
				putpixel(center_x-x,center_y-y,7);
				putpixel(center_x+x,center_y+y,7);
				putpixel(center_x-x,center_y+y,7);
				putpixel(center_x+y,center_y-x,7);
				putpixel(center_x-y,center_y-x,7);
				putpixel(center_x+y,center_y+x,7);
				putpixel(center_x-y,center_y+x,7);
				delay(100);
			}
		};
};
int main()
{
	Circle c;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,NULL);
	c.drawCircle();
	std::system("gnome-screenshot -f breCircle.jpg");
	delay(2000);
	return 0;
}

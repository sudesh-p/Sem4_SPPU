//Problem Definition: Write a program to implement Digital Differential Analyzer (DDA) Line drawing algorithm.

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <graphics.h>
#include <string.h>
#include <math.h>
using namespace std;

class Pixel	//Base Class
{
	protected:
		int xc[12],yc[12];
	public:
		Pixel()
		{
			for(int i=0;i<12;i++)
			{
				xc[i]=0;
				yc[i]=0;
			}
		}
};
class Line: public Pixel //Derived class
{
	//int x1,x2,y1,y2;
  public:
	void accept()
	{
		int i,length=0,temp;
		cout<<"Enter co-ordinates of left upper point : ";
		cin>>xc[0]>>yc[0];

		cout<<"Enter co-ordinates of right lower point : ";
		cin>>xc[2]>>yc[2];

		if(xc[0]>xc[2])
		{
			temp=xc[0];
			xc[0]=xc[2];
			xc[2]=temp;

			temp=yc[0];
			yc[0]=yc[2];
			yc[2]=temp;
		}

		/*right most upper point*/
		xc[1]=xc[2];
		yc[1]=yc[0];

		/*left most lower point*/
		xc[3]=xc[0];
		yc[3]=yc[2];

		/////Inner polygon
		xc[4] = xc[0];
		yc[4] = yc[0]+(abs(yc[1]-yc[3])/2);

		xc[5] = xc[0]+(abs(xc[1]-xc[0])/2);
		yc[5] = yc[0];

		xc[6] = xc[1];
		yc[6] = yc[1]+(abs(yc[1]-yc[2])/2);

		xc[7] = xc[3]+(abs(xc[3]-xc[2])/2);
		yc[7] = yc[2];

		/////Innermost polygon

		xc[8] = xc[4]+(abs(xc[4]-xc[5])/2);
		yc[8] = yc[4]-(abs(yc[4]-yc[5])/2);

		xc[9] = xc[6]-(abs(xc[5]-xc[6])/2);
		yc[9] = yc[6]-(abs(yc[5]-yc[6])/2);

		xc[10] = xc[6]-(abs(xc[6]-xc[7])/2);
		yc[10] = yc[6]+(abs(yc[6]-yc[7])/2);

		xc[11] = xc[4]+(abs(xc[4]-xc[7])/2);
		yc[11] = yc[4]+(abs(yc[4]-yc[7])/2);

	};
	void drawline(int ch)
	{
		if(ch==2)
		{
			drawlineDDA(xc[0],yc[0],xc[1],yc[1]);
			drawlineDDA(xc[0],yc[0],xc[3],yc[3]);
			drawlineDDA(xc[1],yc[1],xc[2],yc[2]);
			drawlineDDA(xc[3],yc[3],xc[2],yc[2]);
			drawlineDDA(xc[5],yc[5],xc[4],yc[4]);
			drawlineDDA(xc[4],yc[4],xc[7],yc[7]);
			drawlineDDA(xc[6],yc[6],xc[5],yc[5]);
			drawlineDDA(xc[6],yc[6],xc[7],yc[7]);
			drawlineDDA(xc[8],yc[8],xc[11],yc[11]);
			drawlineDDA(xc[8],yc[8],xc[9],yc[9]);
			drawlineDDA(xc[10],yc[10],xc[11],yc[11]);
			drawlineDDA(xc[9],yc[9],xc[10],yc[10]);
		}
		else
		{
			drawlineBRE(xc[0],yc[0],xc[1],yc[1]);
			drawlineBRE(xc[0],yc[0],xc[3],yc[3]);
			drawlineBRE(xc[1],yc[1],xc[2],yc[2]);
			drawlineBRE(xc[3],yc[3],xc[2],yc[2]);
			drawlineBRE(xc[5],yc[5],xc[4],yc[4]);
			drawlineBRE(xc[4],yc[4],xc[7],yc[7]);
			drawlineBRE(xc[6],yc[6],xc[5],yc[5]);
			drawlineBRE(xc[6],yc[6],xc[7],yc[7]);
			drawlineBRE(xc[8],yc[8],xc[11],yc[11]);
			drawlineBRE(xc[8],yc[8],xc[9],yc[9]);
			drawlineBRE(xc[10],yc[10],xc[11],yc[11]);
			drawlineBRE(xc[9],yc[9],xc[10],yc[10]);
		}

	};

	void drawlineDDA(int x1,int y1,int x2,int y2);
	void drawlineBRE(int x1,int y1,int x2,int y2);

};

void Line::drawlineBRE(int x1,int y1,int x2,int y2)
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
   			putpixel(x,y,1);
		}
 	}
}

void Line::drawlineDDA(int x1,int y1,int x2,int y2)
{
	float x,y,dx,dy;
	int i,length,temp;

	if(x1>x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;

		temp = y1;
		y1 = y2;
		y2 = temp;
	}

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
	i=1;
	while(i<=length)
	{
		putpixel(x,y,WHITE);
		x = x + dx;
		y = y + dy;
		i++;
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
		cout<<"_____________________";
		cout<<"\n1. Accept Coordinates.";
		cout<<"\n2. DDA Algorithm::";
		cout<<"\n3. BRESANHAM's Algorithm::\n";
		cout<<"_____________________";
		cout<<"\nEnter ur choice::\t";
		cin>>ch;

		 switch(ch)
		 {
			  case 1:
				l.accept();
				break;

			  case 2:
				l.drawline(2);
				delay(2000);
				std::system("gnome-screenshot -f dda.jpg");
				break;

			  case 3:
				l.drawline(3);
				delay(2000);
				std::system("gnome-screenshot -f bre.jpg");
				break;
			default: break;
		 }

	}while(ch<4);

	closegraph();
	return 0;
}

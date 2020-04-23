#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include<math.h>

using namespace std;

class SRT
{
            int x1,x2,x3,x4,y1,y2,y3,y4,nx1,nx2,nx3,nx4,ny1,ny2,ny3,ny4,c;
            int xt,yt,r,size,acute,obtuse,DG,dg;
            float t,sx,sy;
	public:
		void accept()
		{
	       cout<<"\t Program for basic transactions";
	       cout<<"\n\t Enter the points of triangle";
	       setcolor(1);
		    cout<<"Enter x1 and y1 coordinates : ";
	        cin>>x1>>y1;
		    cout<<"\nEnter size of a rhombus : ";
		    cin>>size;
		    cout<<"\nEnter an acute angle : ";
		    cin>>acute;

		    t = 3.14 * acute / 180;
		    x2 = x1 + size;
		    y2 = y1;
                    nx1=abs(x1*cos(t)-y1*sin(t));
                    ny1=abs(x1*sin(t)+y1*cos(t));
                    nx2=abs(x2*cos(t)-y2*sin(t));
                    ny2=abs(x2*sin(t)+y2*cos(t));
		    nx3 = nx1 + size;
		    ny3 = ny1;
			nx4 = nx2 +size;
 			ny4 = ny2;
		    x1 = nx1; y1 = ny1;
		    x2 = nx2; y2 = ny2;
		    x3 = nx3; y3 = ny3;
		    x4 = nx4; y4 = ny4;

                    line(x1,y1,x2,y2);
                    line(x1,y1,x3,y3);
                    line(x4,y4,x2,y2);
                    line(x4,y4,x3,y3);

		};

		void operator!()
		{
                    cout<<"\n Enter the translation factor";
                    cin>>xt>>yt;
                    nx1=x1+xt;
                    ny1=y1+yt;
                    nx2=x2+xt;
                    ny2=y2+yt;
                    nx3=x3+xt;
                    ny3=y3+yt;
                    nx4=x4+xt;
                    ny4=y4+yt;

		    setcolor(RED);
                    line(nx1,ny1,nx2,ny2);
                    line(nx1,ny1,nx3,ny3);
                    line(nx4,ny4,nx2,ny2);
                    line(nx4,ny4,nx3,ny3);
		    delay(5000);
		};
		void operator--()
		{
                    cout<<"\n Enter the Angle of rotation";
                    cin>>r;
                    t=3.14*r/180;
                    nx1=abs(x1*cos(t)-y1*sin(t));
                    ny1=abs(x1*sin(t)+y1*cos(t));
                    nx2=abs(x2*cos(t)-y2*sin(t));
                    ny2=abs(x2*sin(t)+y2*cos(t));
                    nx3=abs(x3*cos(t)-y3*sin(t));
                    ny3=abs(x3*sin(t)+y3*cos(t));
                    nx4=abs(x4*cos(t)-y4*sin(t));
                    ny4=abs(x4*sin(t)+y4*cos(t));

		    setcolor(GREEN);
                    line(nx1,ny1,nx2,ny2);
                    line(nx1,ny1,nx3,ny3);
                    line(nx4,ny4,nx2,ny2);
                    line(nx4,ny4,nx3,ny3);
		    delay(5000);
		};
		void operator ++()
		{
                    cout<<"\n Enter the Scaling factor";
                    cin>>sx>>sy;
                    nx1=x1*sx;
                    ny1=y1*sy;
                    nx2=x2*sx;
                    ny2=y2*sy;
                    nx3=x3*sx;
                    ny3=y3*sy;	
                    nx4=x4*sx;
                    ny4=y4*sy;

		    setcolor(WHITE);
                    line(nx1,ny1,nx2,ny2);
                    line(nx1,ny1,nx3,ny3);
                    line(nx4,ny4,nx2,ny2);
                    line(nx4,ny4,nx3,ny3);
		    delay(5000);
		};
};

int main()
{
		int c;
	    SRT s;
            int gm;
            int gd=DETECT;
            initgraph(&gd,&gm,NULL);
		s.accept();
	    do
	    {
	            cout<<"\n 1.Translation\n 2.Rotation\n 3.Scalling\n 4.exit";
        	    cout<<"\n Enter your choice:";
	            cin>>c;
	            switch(c)
	            {
        	        case 1:	!s;	
					break;
        	        case 2: --s;
					break;
        	        case 3:	++s;
					break;
        	      default:
        	                            cout<<"Enter the correct choice";
        	                            break;
                     }
	    }while(c<4);
	//    delay(5000);
            closegraph();
	    return 0;
       }

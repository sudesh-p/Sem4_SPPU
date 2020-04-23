# include <iostream>
# include <stdio.h>
# include <graphics.h>
# include <math.h>
using namespace std;
void Circle(int Radius,int xC,int yC);
void drawtraingle(int Radius,int xC,int yC);
int main()
{
    int gDriver=DETECT, gMode;
    initgraph(&gDriver,&gMode,NULL);
    int Radius, xC, yC;
    cout<< endl << "Enter Center point coordinates...";
    cout<<endl<<"  Xc    : ";
    cin>>xC;
    cout<<endl<<"  Xc    : ";
    cin>>yC;
    cout<<endl<<"Radius  : ";
    cin>>Radius;
    cleardevice();
    Circle(Radius,xC,yC);
    drawtraingle(Radius,xC,yC);

    delay(2000);
    return 0;
}
void Circle(int Radius,int xC,int yC)
{
    int P;
    int x,y;
    void Draw(int x,int y,int xC,int yC);
    P = 1 - Radius;
    x = 0;
    y = Radius;
    Draw(x,y,xC,yC);
    while (x<=y)
    {
        x++;
        if (P<0)
            P += 2 * x + 1;
        else
        {
            P += 2 * (x - y) + 1;
            y--;
        }
        Draw(x,y,xC,yC);
    }
}
void Draw(int x,int y,int xC,int yC)
{
    putpixel(xC + x,yC + y,12);
    putpixel(xC + x,yC - y,12);
    putpixel(xC - x,yC + y,12);
    putpixel(xC - x,yC - y,12);
    putpixel(xC + y,yC + x,12);
    putpixel(xC - y,yC + x,12);
    putpixel(xC + y,yC - x,12);
    putpixel(xC - y,yC - x,12);
}

void drawtraingle(int Radius,int xC,int yC)
{
	int xt[3],yt[3];
	xt[0] = xC;
	yt[0] = yC - Radius;

	xt[1] = xC - (1.732 * Radius / 2);
	yt[1] = yC + Radius/2;

	xt[2] = xC + (1.732 * Radius / 2);
	yt[2] = yC + Radius/2;

	for(int i=0;i<3;i++)
	cout<<"\nxt :"<<xt[i]<<"\tyt :"<<yt[i];
	line(xt[0],yt[0],xt[1],yt[1]);
	line(xt[1],yt[1],xt[2],yt[2]);
	line(xt[0],yt[0],xt[2],yt[2]);
	float iRadius;

	iRadius = 0.288675 * 2 * abs(xt[0]-xt[2]);
	Circle(iRadius,xC,yC);
}


#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <graphics.h>
#include <math.h>
using namespace std;

void bezier (int x[4][4], int y[4][4])
{
int gd = DETECT, gm; int i,j; double t;
initgraph (&gd, &gm, NULL);
setcolor(RED);
drawpoly(4,x[0]);
drawpoly(4,x[1]);
drawpoly(4,x[2]);
drawpoly(4,x[3]);
for(i=0;i<4;i++)
{
	for (t = 0.0; t < 1.0; t += 0.0005)
	{
		double xt = pow (1-t, 3) * x[i][0] + 3 * t * pow (1-t, 2) * x[i][1] + 3 * pow (t, 2) * (1-t) * x[i][2] + pow (t, 3) * x[i][3];
		double yt = pow (1-t, 3) * y[i][0] + 3 * t * pow (1-t, 2) * y[i][1] + 3 * pow (t, 2) * (1-t) * y[i][2] + pow (t, 3) * y[i][3];
		putpixel (xt, yt, WHITE);
               // delay(10);
	}
}
std::system("gnome-screenshot -f /home/CG/flower.jpg");
delay(3000);
 closegraph();

 return;
 }
int main()
{
 int x[4][4], y[4][4]; int i,j,n;
   /* Co-ordinates for four petals total 16. If you want to increase petals increase the size of x & y array. Each petal will add four more points.*/
cout<<"\nEnter total number of petals : ";
cin>>n;
 for (i=0; i<n; i++)
  {
	cout<<"Enter the x- and y-coordinates of the four control points of petal "<<(i+1)<<" : \n";
   for(j=0; j<4; j++)
    {
	cout<<"\nEnter x["<<i<<"] and y["<<j<<"] : ";
      cin>>x[i][j]>>y[i][j];

     }
 }
bezier (x, y);
return 0;
}
/*
4
200 200 160 160 240 160 200 200
200 200 240 160 240 240 200 200
200 200 240 240 160 240 200 200
200 200 160 240 160 160 200 200

5

*/

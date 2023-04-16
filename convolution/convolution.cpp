//============================================================================
// Name        : convolution.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
using namespace std;

struct Point
{
	double x,y,z;
};

Point U = {0., 0., 0.};
Point V = {-1., 1., -4.};
Point C = {-1., -1., -4.};
Point E = {4., 0., 0.};
Point F = {5., 1., -4.};
Point G = {5., -1., -4.};
Point H = {6.5, 0., 1.};
Point J = {7.5, 0., 0.};
Point M = {-2., 0., 1.3};
Point Q = {6.5, -2., 4.};
Point S = {6.5, 2., 4.};
Point W = {9.4, 0., 0.};
Point Y = {9.1, 0., 0.};

double Cauchy(double x0, double y0, double z0, double x1, double y1, double z1, double s, double x, double y, double z)
{
	double num1 = s;
	double num2 = sqrt(x1*x1-2*x1*x0+x0*x0+y1*y1-2*y1*y0+y0*y0+z1*z1-2*z1*z0+z0*z0);
	double num31 = (x0-x1)*(x-x1)+(y0-y1)*(y-y1)+(z0-z1)*(z-z1);
	double denom31 = sqrt(1+s*((x-x1)*(x-x1)+(y-y1)*(y-y1)+(z-z1)*(z-z1)));
	double num32 = (x1-x0)*(x-x0)+(y1-y0)*(y-y0)+(z1-z0)*(z-z0);
	double denom32_carre = 1+s*((x-x0)*(x-x0)+(y-y0)*(y-y0)+(z-z0)*(z-z0));
	double denom = s*((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)+(z1-z0)*(z1-z0))*(denom32_carre)-s*s*((x1-x0)*(x-x0)+(y1-y0)*(y-y0)+(z1-z0)*(z-z0))*((x1-x0)*(x-x0)+(y1-y0)*(y-y0)+(z1-z0)*(z-z0));

	return num1*num2*(num31/denom31+num32/sqrt(denom32_carre))/denom;
}

inline double Cauchy(Point A, Point B, double x, double y, double z, double s = 10.)
{
	return Cauchy(A.x,A.y,A.z,B.x,B.y,B.z,s,x,y,z);
}

double potentiel(double x, double y, double z)
{
	return 4.*Cauchy(U,V,x,y,z) + 4.*Cauchy(U,C,x,y,z) + 90.*Cauchy(U,E,x,y,z) + 4.*Cauchy(E,F,x,y,z) + 4.*Cauchy(E,G,x,y,z) + 4.*Cauchy(E,H,x,y,z) + 90.*Cauchy(H,J,x,y,z) + 1.*Cauchy(H,Q,x,y,z) + 40.*Cauchy(Y,W,x,y,z) + 1.*Cauchy(H,S,x,y,z) + 4.*Cauchy(U,M,x,y,z);
}




int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)640/480,1,1000);
    glEnable(GL_DEPTH_TEST);

	bool dedans[100][100][100];


	for (int x = 0; x < 100; x++)
	{
		double dx = -3. + double(x)*14./100.;
		for (int y = 0; y < 100; y++)
		{
			double dy = -4. + double(y)*6./100.;
			for (int z = 0; z < 100; z++)
			{
				double dz = -5. + double(z)*8./100.;
				double p = potentiel(dx,dy,dz);

/*				if (p >= 1.)
					glVertex3f(dx,dy,dz);*/
				dedans[x][y][z] = p >= 1.;
			}
		}
	}



	for (double theta = 0.; theta < 2.*M_PI; theta += M_PI / 10.)
	{
		std::cout << 10.*cos(theta) << " " << 10.*sin(theta) << std::endl;

	    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	    glMatrixMode( GL_MODELVIEW );
	    glLoadIdentity( );

	    gluLookAt(theta,10,10.,0.,0.,0.,0.,0.,1.);

		glBegin(GL_POINTS);
		glColor3ub(255,255,255);
		if (theta == 0.)
		{
			for (int x = 0; x < 100; x++)
			{
				double dx = -3. + double(x)*14./100.;
				for (int y = 0; y < 100; y++)
				{
					double dy = -4. + double(y)*6./100.;
					for (int z = 0; z < 100; z++)
					{
						double dz = -5. + double(z)*8./100.;
						if (dedans[x][y][z])
							glVertex3f(dx,dy,dz);
		//				dedans[x][y][z] = p >= 1.;
					}
				}
			}
		}
		glFlush();
		SDL_GL_SwapBuffers();

		SDL_Delay(100);

		//std::cout << theta << std::endl;
	}
	return 0;
}

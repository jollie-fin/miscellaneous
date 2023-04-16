
struct double3
{
	double x,y,z;
	double3 (double px,double py,double pz)
	{
		x = px;
		y  = py;
		z = pz;
	}

	double operator/(double3 &t)
	{
		return x*t.x+y*t.y+z*t.z;
	}

	void rendu()
	{
		glVertex3d(x,y,z);
	}
};

struct double4
{
	double x,y,z,w;
	double4 (double px,double py,double pz,double pw)
	{
		x = px;
		y  = py;
		z = pz;
		w = pw;
	}

	double operator/(double4 t)
	{
		return x*t.x+y*t.y+z*t.z+w*t.w;
	}

	inline double3 proj(double4 &xcam, double4 &ycam, double4 &zcam)

	{
		return double3((*this)/xcam, (*this)/ycam, (*this)/zcam);
	}
};


struct tri
{
	double4 t1,t2,t3;
	tri (double4 &pt1,double4 &pt2,double4 &pt3):t1(pt1),t2(pt2),t3(pt3)
	{
	}
	void rendu(double4 &xcam, double4 &ycam, double4 &zcam)
	{
		glBegin(GL_TRIANGLES);
		t1.proj(xcam,ycam,zcam).rendu();
		t2.proj(xcam,ycam,zcam).rendu();
		t3.proj(xcam,ycam,zcam).rendu();
		glEnd();
	}
};

double4 aaaA = double4(0,0,0,0);
double4 aaaA = double4(0,0,0,1);
double4 aaAa = double4(0,0,1,0);
double4 aaAA = double4(0,0,1,1);
double4 aAaa = double4(0,1,0,0);
double4 aAaA = double4(0,1,0,1);
double4 aAAa = double4(0,1,1,0);
double4 aAAA = double4(0,1,1,1);
double4 Aaaa = double4(1,0,0,0);
double4 AaaA = double4(1,0,0,1);
double4 AaAa = double4(1,0,1,0);
double4 AaAA = double4(1,0,1,1);
double4 AAaa = double4(1,1,0,0);
double4 AAaA = double4(1,1,0,1);
double4 AAAa = double4(1,1,1,0);
double4 AAAA = double4(1,1,1,1);

tri monde[32] = {
				tri(aaaa,aaaA,aaAa),tri(aaAA,aaaA,aaAa),
				tri(aAaa,aAaA,aAAa),tri(aAAA,aAaA,aAAa),
				tri(Aaaa,AaaA,AaAa),tri(AaAA,AaaA,AaAa),
				tri(AAaa,AAaA,AAAa),tri(AAAA,AAaA,AAAa),

				tri(aaaa,aaAa,aAaa),tri(aAAa,aaAa,aAaa),
				tri(Aaaa,AaAa,AAaa),tri(AAAa,AaAa,AAaa),
				tri(aaaA,aaAA,aAaA),tri(aAAA,aaAA,aAaA),
				tri(AaaA,AaAA,AAaA),tri(AAAA,AaAA,AAaA),

				tri(aaaa,aAaa,Aaaa),tri(AAaa,aAaa,Aaaa),
				tri(aaaA,aAaA,AaaA),tri(AAaA,aAaA,AaaA),
				tri(aaAa,aAAa,AaAa),tri(AAAa,aAAa,AaAa),
				tri(aaAA,aAAA,AaAA),tri(AAAA,aAAA,AaAA),

				tri(aaaa,Aaaa,aaaA),tri(AaaA,Aaaa,aaaA),
				tri(aaAa,AaAa,aaAA),tri(AaAA,AaAa,aaAA),
				tri(aAaa,AAaa,aAaA),tri(AAaA,AAaa,aAaA),
				tri(aAAa,AAAa,aAAA),tri(AAAA,AAAa,aAAA)};

void affiche_hypercube()
{
	
}

int main()
{
}


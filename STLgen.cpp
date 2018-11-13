/*
HW6: STL File Generator
Author: Christian Jensen
Cite: N/A

Pledge: I pledge my honor that I have abided by the Stevens Honor System
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

const long double PI= 3.14159265358979;
const long double RT2= 1.4142135623731;

class Point{
private:
public:
	double x,y,z;
	Point(double x,double y, double z): x(x),y(y),z(z) {}
	friend ostream& operator <<(ostream& s, const Point& a){
		s << a.x << " " << a.y << " " << a.z;
		return s;
	}
};
class Facet{
private:
	Point a;
	Point b;
	Point c;
public:
	Facet(Point& a, Point& b, Point& c): a(a), b(b), c(c) {}
	Point normal(){
		#if 0
		Point ab(b.x-a.x,b.y-a.y,b.z-a.z);
		Point bc(c.x-a.x,c.y-a.y,c.z-a.z);
		Point norm(ab.y*bc.z-bc.y*ab.z,ab.x*bc.z-bc.x*a.z,ab.x*bc.y-bc.x*ab.y);
		double mag =sqrt(norm.x*norm.x+norm.y*norm.y+norm.z*norm.z);
		#endif
		return Point(0,0,0);
	}
	friend ostream& operator <<(ostream& s, Facet& a){
		s << "facet normal " << a.normal() << '\n'
		<< "\touter loop\n"
		<< "\t\tvertex " << a.a << '\n'
		<< "\t\tvertex " << a.b << '\n'
		<< "\t\tvertex " << a.c << '\n'
		<< "\tendloop\n"
		<< "endfacet\n";
		return s;
	}

};
class Sector{
private:
	Point center;
	double radius,height,sangle,eangle;
public:
	Sector(Point cen=Point(0,0,0),double r=1,double h=1,double sa=0,double ea=PI/2):
		center(cen),radius(r),height(h),sangle(sa),eangle(ea){}
	
	friend ostream& operator <<(ostream& s,Sector& a){
		double ta=a.sangle+a.eangle;
		Point ct(a.center.x,a.center.y,a.center.z+a.height);
		Point bl(a.center.x+a.radius*sin(a.sangle),a.center.y+a.radius*cos(a.sangle),a.center.z);
		Point br(a.center.x+a.radius*sin(ta),a.center.y+a.radius*cos(ta),a.center.z);
		Point tl(a.center.x+a.radius*sin(a.sangle),a.center.y+a.radius*cos(a.sangle),a.center.z+a.height);
		Point tr(a.center.x+a.radius*sin(ta),a.center.y+a.radius*cos(ta),a.center.z+a.height);

		Facet one(a.center,bl,br);
		Facet two(bl,tl,br);
		Facet three(tr,tl,br);
		Facet four(ct,tl,tr);

		s << one << two << three << four;
		return s;
	}
};
class Object{
	private:
	public:
		static int count;
		string solname;
		double x,y,z;
		Object(double x=0, double y=0,double z=0): x(x),y(y),z(z){
			count++;
			solname= "Solid" + to_string(count);
		}
		~Object(){
			count--;
		}
		void translate(double nx=0, double ny=0,double nz=0){
			this->x=nx;
			this->y=ny;
			this->z=nz;
		}
		void position() const{
			cout << "x: " << this->x << endl;
			cout << "y: " << this->y << endl;
			cout << "z: " << this->z << endl;
		}
		static int getCount(){return count;}
		virtual double volume() const=0;
};

class Cube: public Object{
	private:
		double side;
	public:
		Cube(double x=0, double y=0,double z=0, double s=1): Object(x,y,z), side(s){}
		double volume() const{
			return side*side*side;
		}
		friend ostream& operator <<(ostream& s, Cube& a){
			Point c(a.x+a.side/2,a.y+a.side/2,a.z);
			double ang=PI/2;
			s << "solid " << a.solname << '\n';
			for(int i=1; i<=4;i++){
				Sector one(c,a.side/RT2,a.side,ang*i,ang);
				s << one;
			}
			s << "endsolid " << a.solname << '\n';
			return s;
		}
};

class Cylinder: public Object{
	private:
		double r,h;
		int f;
	public:
		Cylinder(double x=0, double y=0,double z=0, double r=1, double h=1, int f=6): Object(x,y,z), r(r),h(h),f(f){}
		double volume() const{
			return PI*r*r*h;
		}
		friend ostream& operator <<(ostream& s, Cylinder& a){
			Point c(a.x,a.y,a.z);
			double ang=(2*PI)/a.f;
			s << "solid " << a.solname << '\n';
			for(int i=1; i<=a.f;i++){
				Sector one(c,a.r,a.h,ang*i,ang);
				s << one;
			}
			s << "endsolid " << a.solname << '\n';
			return s;
		}

};

class Design{
private:
	vector<Cube> cubev;
	vector<Cylinder> cylv;
public:
	Design() {}
	
	void add(Cube& cube) {
		cubev.push_back(cube);
	}

	void add(Cylinder& cyl)	{
		cylv.push_back(cyl);
	}

	void write(const string& name) {
		ofstream f(name);
		for (int i = cubev.size()-1; i >= 0; i--){
			f << cubev[i];
		}
		for (int i = cylv.size()-1; i >= 0; i--){
			f << cylv[i];
		}	
		f.close();
	}
};
int Object::count=0;

int main(){
	Design test;
	//Cube name(x,y,z,sidelength)
	Cube c(0,0,0,5);
	//Cylinder name(x,y,z,r,h,facet#)
	Cylinder cyl(2.5,2.5,2.5,2,7,500);
	test.add(c);
	test.add(cyl);
	test.write("cubeandcyl.stl");

	return 0;
}
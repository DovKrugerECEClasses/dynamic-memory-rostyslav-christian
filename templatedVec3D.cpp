/*
HW4: Create a Class for 3D vectors
Author: Christian Jensen
Cite: N/A

Pledge: I pledge my honor that I have abided by the Stevens Honor System
*/

#include <iostream>
#include <cmath>

using namespace std;
template <typename Precision>
class Vec3d {
private:
	Precision x,y,z;
public:
	Vec3d(Precision dx=0,Precision dy=0,Precision dz=0): x(dx), y(dy), z(dz){}
	
	Precision dot (Vec3d b) const{
		return x*b.x+y*b.y+z*b.z;
	}

	Precision mag () const{
		return sqrt(x*x+y*y+z*z);
	}

	Precision magSq () const{
		return x*x+y*y+z*z;
	}

	Precision dist (Vec3d b) const{
		return (x-b.x)*(x-b.x)+(y-b.y)*(y-b.y)+(z-b.z)*(z-b.z);
	}

	Vec3d operator -() const{
		return Vec3d(-x,-y,-z);
	}

	friend Vec3d operator +(Vec3d a, Vec3d b){
		return Vec3d(a.x+b.x,a.y+b.y,a.z+b.z);
	}

	friend Vec3d operator -(Vec3d a, Vec3d b){
		return Vec3d(a.x-b.x,a.y-b.y,a.z-b.z);
	}
	friend Vec3d operator *(Vec3d a, Vec3d b){
		return Vec3d(a.y*b.z-b.y*a.z,a.x*b.z-b.x*a.z,a.x*b.y-b.x*a.y);
	}
	friend ostream& operator <<(ostream&s, Vec3d a){
		s << "<"<< a.x << ", " << a.y << ", " << a.z << ">";
		return s;
	}

};
int main (){
	Vec3d<double> vec(1,0,0);
	Vec3d<double> vec2(0,1,0);
	cout << "v1: " << vec << endl << "v2: " << vec2 << endl;
	cout << "Sum: " << vec+vec2 << endl;
	cout << "Dif: " << vec-vec2 << endl;
	cout << "Neg: " << -vec << endl;
	cout << "Dot: " << vec.dot(vec2) << endl;
	cout << "XPro:" << vec * vec2 << endl;
	cout << "Mag: " << vec.mag() << endl;
	cout << "M^2: " << vec.magSq() << endl;
	cout << "Dis: " << vec.dist(vec2) << endl;
	Vec3d<int> vecint(1,2,4);
	Vec3d<float> vecfloat(1,2,7);
	cout << vecint << " " << vecfloat << endl;
	return 0;
}
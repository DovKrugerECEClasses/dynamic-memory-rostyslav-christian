/*
HW: Create a class for fractions
Author: Christian Jensen
Cite: RV

Pledge: I pledge my honor that I have abided by the Stevens Honor System
*/


#include<iostream>
#include "Fraction.hh"

using namespace std;

int main(){
	const Fraction a(1,2);
	const Fraction b(12);
	const Fraction c(3);
	const Fraction d(1,3);
	const Fraction e(1,6);
	Fraction s=a;

	cout << "a: " << a << '\t' << "s=a: "<< s <<'\n';
	s=s*(-b);
	cout << "b: " << b << '\t' << "s*(-b): "<< s <<'\n';
	s=s/c;
	cout << "c: " << c << '\t' << "s/c: "<< s <<'\n';
	s=s+d;
	cout << "d: " << d << '\t' << "s+d: "<< s <<'\n';
	s=s-e;
	cout << "e: " << e << '\t' << "s-e: "<< s <<'\n';
	s.setNum(400);
	cout << s.simplify();
	#if 0
	Fraction test;
	cin >> test;
	cout << test;
	#endif
	return 0;
}
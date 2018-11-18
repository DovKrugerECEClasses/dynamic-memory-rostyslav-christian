/*
HW: Create a class for fractions
Author: Christian Jensen
Cite: RV

Pledge: I pledge my honor that I have abided by the Stevens Honor System
*/

#include <iostream>
#include "Fraction.hh"
using namespace std;

Fraction::Fraction (int n=0,int d=1): num(n), den(d){}

Fraction Fraction::simplify() const{
	Fraction simple;
	if (num%den==0){
		simple.num=num/den;
		simple.den=1;
	}
	else if(den%num==0){
		simple.num =1;
		simple.den = den/num;
	}
	else {
		simple.num=num;
		simple.den=den;
	}

	int x=simple.num;
	int y=simple.den;
	int temp;

	while(y!=0){
		temp=x%y;
		x=y;
		y=temp;
	}
	simple.num = simple.num/x;
	simple.den = simple.den/x;

	if (simple.den <0){
		simple.num = (-simple.num);
		simple.den = (-simple.den);
	}
	return simple;
}

void Fraction::print() const{
	cout << num << "/" << den;
}

void Fraction::setNum(int n){
	num=n;
}

void Fraction::setDen(int d){
	den=d;
}

Fraction Fraction::operator - () const{
	Fraction neg;
	neg.num=num*(-1);
	neg.den=den;
	return neg;
}

Fraction operator +(const Fraction& a, const Fraction& b){
	Fraction c(a.num*b.den+b.num*a.den,a.den*b.den);
	return c.simplify();
}
Fraction operator -(const Fraction& a, const Fraction& b){
	Fraction c(a.num*b.den-b.num*a.den,a.den*b.den);
	return c.simplify();
}
Fraction operator *(const Fraction& a, const Fraction& b){
	Fraction c(a.num*b.num,a.den*b.den);
	return c.simplify();;
}
Fraction operator /(const Fraction& a, const Fraction& b){
	Fraction c(a.num*b.den,a.den*b.num);
	return c.simplify();;
}
ostream& operator << (ostream& s, const Fraction& a){
	s << a.num << "/" << a.den;
	return s;
}
istream& operator >>(istream& s, Fraction& a){
	int ntemp,dtemp;
	char ignore;
	s >> ntemp >>ignore>> dtemp;
	a.num=ntemp;
	a.den=dtemp;
	return s;
}

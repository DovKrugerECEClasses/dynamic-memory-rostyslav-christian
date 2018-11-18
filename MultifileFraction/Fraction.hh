#pragma once
#include <iostream>


class Fraction{
	private:
		int num;
		int den;
	public:

		Fraction (int n,int d);

		Fraction simplify() const;

		void print() const;
		
		void setNum(int n);

		void setDen(int d);

		Fraction operator - () const;

		friend Fraction operator +(const Fraction& a, const Fraction& b);

		friend Fraction operator -(const Fraction& a, const Fraction& b);

		friend Fraction operator *(const Fraction& a, const Fraction& b);

		friend Fraction operator /(const Fraction& a, const Fraction& b);

		friend std::ostream& operator << (std::ostream& s, const Fraction& a);

		friend std::istream& operator >>(std::istream& s, Fraction& a);
};

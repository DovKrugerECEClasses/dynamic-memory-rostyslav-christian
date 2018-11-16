/*
HW: Create a templated function for sorts
Author: Christian Jensen
Cite: RA

Pledge: I pledge my honor that I have abided by the Stevens Honor System
*/
#include <iostream>

using namespace std;

template <typename T>
void sort(T array[],int n){
	for (int j = 0; j < n-2; ++j)
	{
		for (int i = 0; i < n-1; ++i)
		{
			if (array[i]>array[i+1])
			{
				swap(array[i],array[i+1]);
			}
		}
	}

}

template <typename T>
void print(T array[],int n){
	for (int i = 0; i < n; ++i)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

template <typename T>
T sum(T array[],int n){
	T sum=0;
	for (int i = 0; i < n; ++i)
	{
		sum+= array[i];
	}
	return sum;
}

int main(){
	int a[]= {5,4,3,1,8,9,2,1};
	sort(a,sizeof(a)/sizeof(int));
	print(a,sizeof(a)/sizeof(int));
	cout << sum(a,sizeof(a)/sizeof(int)) << endl;

	double b[]={5.5,4.5,1.2,2.9,9.2,5.2};
	sort(b,sizeof(b)/sizeof(double));
	print(b,sizeof(b)/sizeof(double));
	cout <<sum(b,sizeof(a)/sizeof(int)) << endl;

	string c[]={"yo","ho","test","foo","bar"};
	sort(c,sizeof(c)/sizeof(string));
	print(c,sizeof(c)/sizeof(string));

	return 0;
}
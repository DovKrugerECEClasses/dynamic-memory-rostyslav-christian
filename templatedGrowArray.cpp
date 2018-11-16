/*
HW: Create a templated function for lists
Author: Christian Jensen
Cite: RA

Pledge: I pledge my honor that I have abided by the Stevens Honor System
*/
#include <iostream>
using namespace std;

template <typename T>
class GrowArray{
private:
	uint32_t capacity;
	uint32_t len;
	T* data;
	void grow(uint32_t addlen) {
		if(len+addlen>=capacity){
			T* old = data;
			data = new T[2*capacity];
			for (int i = 0; i < len; i++)
				data[i] = old[i];
			len++;
			delete [] old;
		}
	}
public:
	GrowArray(): capacity(1),len(0),data(nullptr){}
	GrowArray(const GrowArray& a): capacity(a.capacity),len(a.len), data(new T[capacity]){
		for (uint32_t i = 0; i < len; ++i)
		{
			data[i]=a.data[i];
		}
	}
	GrowArray& operator =(const GrowArray& a){
		GrowArray copy(a);
		capacity=a.capacity();
		len=a.len();
		swap(data,copy.data);
		return *this;
	}
	~GrowArray(){
		delete [] data;
	}

	void addEnd(const T& x){
		grow(1);
		data[len-1]=x;
	}

	T removeEnd(){
		len--;
		return data[len];
	}
	T operator [](int i) const {
		return data[i];
	}

	T& operator [](int i) {
		return data[i];
	}

	friend ostream& operator << (ostream& s, const GrowArray& a){
		for (uint32_t i = 0; i < a.len; ++i)
		{
			cout << a[i] << " ";
		}
		return s;
	}

};

int main(){
	GrowArray<double> a;
	a.addEnd(5.589);
	a.addEnd(6.7896);
	cout << a << endl;
	cout << "Removing: " << a.removeEnd() << endl;
	cout << a << endl;
	GrowArray<int> b;
	b.addEnd(100);
	b.addEnd(66);
	cout << b << endl;
	cout << "Removing: " << b.removeEnd() << endl;
	cout << b << endl;
	return 0;
}
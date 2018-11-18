/*
HW6: Create a class for fractions
Author: Christian Jensen
Cite: N/A

Pledge: I pledge my honor that I have abided by the Stevens Honor System
*/
#include <iostream>

using namespace std;

class String{
private:
	uint32_t cap;
	uint32_t len;
	char* s;

	uint32_t strlength(const char str[]) const{
		uint32_t len = 0;
		while(*str++ != '\0'){
			len++;
		}
		return len;
	}

	void grow(uint32_t addlen){
		newlen=len+addlen;
		if(newlen>cap){
			const char* old=s;
			cap=2*newlen;
			s= new char[cap];
			for (uint32_t i = 0; i < len; ++i)
			{
				s[i]=old[i];
			}
			delete [] old;
		}
	}
public:
	String(): cap(0),len(0), s(nullptr) {}
	String(const char str[]): cap(2*strlength(str)),len(cap/2), s(new char[cap]){
		for(uint32_t i=0;i<len;i++){
			s[i]=str[i];
		}
	}
	String(const String& orig) : cap(orig.cap),len(orig.len), s(new char[cap] ) {
		uint64_t* src = (uint64_t*)orig.s;
		uint64_t* dest = (uint64_t*)s;
		uint32_t count;
		for (count = len; count >= 8; count -= 8)
			*dest++ = *src++;
		char* pdest = (char*)dest;
		char* psrc = (char*)src;
		for ( ; count > 0; count--)
			*pdest++ = *psrc++;
	}
	String(const char str[], uint32_t mult): cap(strlength(str)*mult*2),len(cap/2), s(new char[cap]) {
		uint32_t count =0;
		for(uint32_t j=0; j<mult;j++){
			for(uint32_t i=0;i<len/mult;i++){
			s[count]=str[i];
			count++;
			}
		}
	}
	~String(){
		delete [] s;
	}
	String& operator =(const String& str){
		String temp(str);
		len=str.len;
		cap=str.cap;
		swap(s,temp.s);
		return *this;
	}
	
	String& operator +=(const char str[]){
		const uint32_t l=strlength(str);
		grow(l);
		for (uint32_t i = 0; i < l; ++i)
		{
			s[len+i]=str[i];
		}
		len+=l;
		return *this;
	}

	char& operator [](const uint32_t& pos){
		return s[pos];
	}
	char operator [](const uint32_t& pos) const{
		return s[pos];
	}
	uint32_t length() const {
		return len;
	}
	uint32_t capacity() const {
		return cap;
	}
	void replace(const char& in,const char& with){
		for(uint32_t i=0;i<len;i++){
			if(s[i]==in){
				s[i]=with;
			}
		}
	}
	void insert(const uint32_t pos, const String& str){
		char* old = s;
		grow(str.len);
		len+=str.len;
		for (uint32_t i = 0; i < pos; ++i)
		{
			s[i]=old[i];
		}
		for (uint32_t i = 0; i < str.len; ++i)
		{
			s[pos+i]=str.s[i];
		}
		for (uint32_t i = pos; i < len-str.len; ++i)
		{
			s[str.len+i]=old[i];
		}
		delete [] old;

	}
	String substring(const uint32_t& pos, const uint32_t& length){
		String temp;
		temp.cap=length*2;
		temp.len=length;
		temp.s=new char [cap];
		for (uint32_t i = 0; i < length; ++i)
		{
			temp.s[i]=s[pos+i];
		}
		return temp;
	}
	friend String operator +(const String& a, const String& b){
		String result;
		result.len=a.len+b.len;
		result.cap=2*result.len;
		result.s= new char[cap];
		for (uint32_t i=0;i<a.len;i++){
			result.s[i]=a.s[i];
		}
		for (uint32_t i=0;i<b.len;i++){
			result.s[a.len+i]=b.s[i];
		}
		return result;
	}
	friend ostream& operator <<(ostream& s, const String& a){
		for (uint32_t i=0;i<a.len;i++){
			s << a.s[i];
		}
		return s;
	}


};


int main(){
	String a="Oh, Me! Oh, Life! ";
	String b("Of the endless trains of the faithless,\n");
	a+= "Of the questions reccuring\n";
	a= a + b;
	String c("Of filled with the foolish,\n");
	String d("cities ");
	c.insert(3,d);
	a = a+c;
	a.replace('c','B');
	cout << a;
	return 0;
}
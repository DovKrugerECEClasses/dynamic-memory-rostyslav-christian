/*
HW6: Create a class for a simple ASCII bitmap
Author: Christian Jensen
Cite: RV

Pledge: I pledge my honor that I have abided by the Stevens Honor System
*/
#include <iostream>
#include <cmath>
//#include "Color.hh"
using namespace std;

class Color {
private:
  uint8_t r,g,b;
  double alpha;
public:
	Color(uint8_t r=1, uint8_t g=1, uint8_t b=1, double a =1.0): r(r),g(g),b(b), alpha(a) {}
	char getChar() const{
		if((r==255)&&(g==0)&&(b==0)){
			return 'R';
		}
		else if((r==0)&&(g==255)&&(b==0)){
			return 'G';
		}
		else if((r==0)&&(g==0)&&(b==255)){
			return 'B';
		}
		else if((r==255)&&(g==255)&&(b==255)){
			return 'W';
		}
		else if((r==0)&&(g==0)&&(b==0)){
			return 'b';
		}
		else{
			return '*';
		}
	}
	friend ostream& operator <<(ostream& s, const Color& c){
		s<< c.getChar();
		return s;
	}
};
class Bitmap{
private:
	uint32_t w,h;
	char *p;
public:
	Bitmap(uint32_t width,uint32_t height): w(width), h(height), p(new char[w*h]){
		for(uint64_t i=0;i<w*h;i++){
			p[i]='*';
		}
	}

	~Bitmap(){
		delete [] p;
	}
	friend ostream& operator <<(ostream& s, const Bitmap& b){
		for (uint32_t row = 0; row < b.h; ++row)
		{
			for (uint32_t col = 0; col < b.w; ++col)
			{
				s<< b.p[b.w*row+col] << ' ';
			}
			s<<row<<'\n';
		}
		return s;
	}
	void horizLine(uint32_t x1,uint32_t x2, uint32_t y, Color c){
		for (uint32_t col = x1; col < x2; ++col)
			{
				p[w*y+col] = c.getChar();
			}
		}
	void vertLine(uint32_t x,uint32_t y1, uint32_t y2, Color c){
		for (uint32_t row = y1; row < y2; ++row)
			{
				p[w*row+x] = c.getChar();
			}
		}
	void drawRect(uint32_t x,uint32_t y, uint32_t wid, uint32_t hi,Color c){
		horizLine(x,x+wid,y,c);
		horizLine(x,x+wid-1,y+hi-1,c);
		vertLine(x,y,y+hi,c);
		vertLine(x+wid-1,y,y+hi,c);

	}
	void fillRect(uint32_t x,uint32_t y, uint32_t wid, uint32_t hi,Color c){
		for (uint32_t row = y; row < y+hi; ++row)
		{
			for (uint32_t col = x; col < x+wid; ++col)
			{
				p[w*row+col]=c.getChar();
			}
		}
	}
	void line(uint32_t x0,uint32_t y0, uint32_t x1, uint32_t y1,Color c){
		int64_t dx = (int64_t)x1 - x0;
     	int64_t dy = (int64_t)y1 - y0;
     	double sm=double(dy)/double(dx);
     	double m = abs(sm);
     	double error = 0.0; // No error at start
     	if(m<=1){
     		uint32_t tempy = y0;
     		for (uint32_t x = x0; x <= x1; ++x)
     		{
     			p[w*tempy+x]=c.getChar();
     			error+=m;
     			if (error >= 0.5)
     			{
     				if(dy>0){
     					tempy+=1;
     				}
     				if(dy<0){
     					tempy-=1;
     				}
     				error-=1;
     			}
   	  		}
     	}
     	else if((m>1)&&(sm>0)) {
     		uint32_t tempx = x0;
     		for (uint32_t y = y0; y <= y1; ++y)
     		{
     			p[w*y+tempx]=c.getChar();
     			error+=1/m;
     			if (error >= 0.5)
     			{
     				if(dx>0){
     					tempx+=1;
     				}
     				if(dx<0){
     					tempx-=1;
     				}
     				error-=1;
     			}
   	  		}
     	}
     	else {
     		uint32_t tempx = x0;
     		for (uint32_t y = y0; y > y1; --y)
     		{
     			p[w*y+tempx]=c.getChar();
     			error+=1/m;
     			if (error >= 0.5)
     			{
     				if(dx>0){
     					tempx+=1;
     				}
     				if(dx<0){
     					tempx-=1;
     				}
     				error-=1;
     			}
   	  		}
     	}
     	
     }
};
int main() {
	Color RED(255,0,0); // all red, no green, no blue (fully opaque)
	Color GREEN(0,255,0);
	Color WHITE(255,255,255);
	Color BLACK(0,0,0);
	Color BLUE(0,0,255);

	Bitmap b(30,20); // 30 pixels across, 20 pixels high, each pixel RGBA
	for (int i = 0; i < 3; ++i)
	{
		for (int i = 0; i < 10; ++i)
		{
			cout << i << " ";
		}

	}
	cout << endl;
	b.horizLine(0, 20, 19, GREEN); // from x=0 to x=20 at y=19
	b.vertLine(5, 0,19, GREEN); // from y = 0 to y=19 at x = 5
	b.drawRect(0,0, 5, 8,WHITE); // x = 0, y =0 w=5, h=8
	b.fillRect(10,10, 4, 3,BLACK); // x = 10, y =10 w=4, h=3
	b.line(0,0, 19,5, RED);
	b.line(15,15,24,0,BLUE);
	cout << b;
	// top left pixel = (0,0)

	
	#if 0
	b.line(0,0,   19,19, RED);
	b.line(0,5,   29,10, BLUE); //Bresenham algorithm
	//https://en.wikipedia.org/wiki/Bresenham's_line_algorithm

	// https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
	//TODO: b.line(0,100, 100,50, BLUE); //Wu algorithm
	

  b.ellipse(15,0, 8, 5, RED);    // ellipse centered at (15,0) w= 8, h=5
	cout << b;
	/*
R
 R
  R
   R
    R
BBB
   BBBBB
        BBBBBB


	 */
#endif
	return 0;
}



	

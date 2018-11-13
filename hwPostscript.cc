/*
HW6: Create a program for writing to Ghost Script
Author: Christian Jensen
Cite: RV

Pledge: I pledge my honor that I have abided by the Stevens Honor System
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

long double const PI= 3.1415926535897;

class Shape{
private:
public:
  double x,y;
  Shape(double x=0.0, double y=0.0): x(x), y(y){}
  virtual ~Shape(){}
  friend ostream& operator <<(ostream& s, const Shape* p){
    s<< p->cmdline();
    return s;
  }
  virtual double area() const=0;
  virtual string cmdline() const=0;
};

class Line: public Shape{
private:
  double x2,y2;
public:
  Line(double x=0.0,double y=0.0,double x2=0.0,double y2=0.0): Shape(x,y), x2(x2), y2(y2){}
  double area () const{
    return 0;
  }
  friend ostream& operator <<(ostream& s, const Line& a){
    s << a.x << " " << a.y << " moveto " << a.x2 << " " << a.y2 << " lineto stroke "; 
    return s;
  }
  string cmdline() const{
    string s= to_string(x)+ " " +to_string(y)
        + " moveto " + to_string(x2) + " " + to_string(y2) + " lineto stroke ";
    return s;
  }
};

class Rect: public Shape{
protected:
  double h,w;
public:
  Rect(double x=0.0,double y=0.0,double h=0.0, double w=0.0): Shape(x,y), h(h), w(w){}
  double area () const{
    return h*w;
  }
  friend ostream& operator <<(ostream& s, const Rect& a){
    s   << a.x << " "<<a.y << " moveto "
      << a.x+a.w << " "<< a.y << " lineto "
      << a.x+a.w << " "<< a.y+a.h << " lineto "
      << a.x << " "<< a.y+a.h << " lineto "
      << a.x << " "<< a.y << " lineto "
      << "closepath stroke "; 
    return s;
  }
  string cmdline() const{
    string s = to_string(x)+" "+ to_string(y)+" moveto "+ to_string(x+w)
          + " " + to_string(y) + " lineto " + to_string(x+w) + " "
          + to_string(y+h)+ " lineto "+to_string(x)+" "+to_string(y+h)
          +" lineto "+to_string(x)+" "+ to_string(y)+ " lineto closepath stroke ";
    return s;
  }
};
class FRect: public Rect{
public:
  FRect(double x=0.0,double y=0.0,double h=0.0, double w=0.0): Rect(x,y,h,w){}
  friend ostream& operator <<(ostream& s, const FRect& a){
    s   << a.x << " "<<a.y << " moveto "
      << a.x+a.w << " "<< a.y << " lineto "
      << a.x+a.w << " "<< a.y+a.h << " lineto "
      << a.x << " "<< a.y+a.h << " lineto "
      << a.x << " "<< a.y << " lineto "
      << "closepath fill "; 
    return s;
  }
  string cmdline() const{
    string s = to_string(x)+" "+ to_string(y)+" moveto "+ to_string(x+w)
          + " " + to_string(y) + " lineto " + to_string(x+w) + " "
          + to_string(y+h)+ " lineto "+to_string(x)+" "+to_string(y+h)
          +" lineto "+to_string(x)+" "+ to_string(y)+ " lineto closepath fill ";
    return s;
  }
};

class Triangle: public Shape{
protected:
  double x2,y2,x3,y3;
public:
  Triangle(double x,double y,double x2,double y2,double x3,double y3):Shape(x,y),x2(x2),y2(y2),x3(x3),y3(y3){}
  double area() const{
    double ans=.5*(x*(y2-y3)+x2*(y3-y)+x3*(y-y2));
    return (ans*ans)/ans;
  }
  string cmdline() const{
    string s = to_string(x)+" "+ to_string(y)+" moveto "+ to_string(x2)
          + " " + to_string(y2) + " lineto " + to_string(x3) + " "
          + to_string(y3)+ " lineto "+to_string(x)+" "+to_string(y)
          + " lineto closepath stroke ";
    return s;
  }
};

class FTriangle: public Triangle{
public:
  FTriangle(double x,double y,double x2,double y2,double x3,double y3):Triangle(x,y,x2,y2,x3,y3){}
  string cmdline() const{
    string s = to_string(x)+" "+ to_string(y)+" moveto "+ to_string(x2)
          + " " + to_string(y2) + " lineto " + to_string(x3) + " "
          + to_string(y3)+ " lineto "+to_string(x)+" "+to_string(y)
          + " lineto closepath fill ";
    return s;
  }
};


class Circle: public Shape{
protected:
  double r;
public:
  Circle(double x=0.0,double y=0.0, double r=0.0): Shape(x,y), r(r) {}
  double area () const{
    return PI*r*r;
  }
  friend ostream& operator <<(ostream& s, const Circle& a){
    s   << a.x << " "<<a.y << " "
      << a.r << "0 360 arc stroke ";
    return s;
  }
  string cmdline() const{
    string s= to_string(x)+" "+to_string(y)+" "+to_string(r)+" 0 360 arc stroke ";
    return s;
  }
};

class FCircle: public Circle{
public:
  FCircle(double x=0.0,double y=0.0, double r=0.0): Circle(x,y,r) {}
  friend ostream& operator <<(ostream& s, const FCircle& a){
    s   << a.x << " "<<a.y << " "
      << a.r << "0 360 arc fill ";
    return s;
  }
  string cmdline() const{
    string s= to_string(x)+" "+to_string(y)+" "+to_string(r)+" 0 360 arc fill ";
    return s;
  }
};

class Color{
private:
  double r,g,b;
public:
  Color(uint8_t r=0, uint8_t g=0, uint8_t b=0):r(r),g(g),b(b){}
  string cmdline() const{
    string s=to_string(r/255.0)+" "+to_string(g/255.0)+" "+to_string(b/255.0)+" setrgbcolor ";
    return s;
  }
};

class Grid{
private:
  double x,xstep,x2,y,ystep,y2;
public:
  Grid(double x,double xstep,double x2,double y,double ystep,double y2):x(x),xstep(xstep),x2(x2),y(y),ystep(ystep),y2(y2){}
  string cmdline() const{
    string s;
    for (double i = x; i <= x2; i+=xstep)
    {
      s+=to_string(i)+" "+to_string(y)+" moveto "+to_string(i)+" "+to_string(y2)+" lineto stroke ";
    }
    for (double i = y; i <= y2; i+=ystep)
    {
      s+=to_string(x)+" "+to_string(i)+" moveto "+to_string(x2)+" "+to_string(i)+" lineto stroke ";
    }
    return s;
  }
};

class Postscript {
private:
vector<string> out;
string filename;
public:
Postscript(const string& f): filename(f){}
void setColor(uint8_t r,uint8_t g,uint8_t b){
  Color temp(r,g,b);
  out.push_back(temp.cmdline());
}
void drawRect(double x, double y, double h,double w){
  Rect temp(x,y,h,w);
  out.push_back(temp.cmdline());
}

void line(double x, double y, double x2,double y2){
  Line temp(x,y,x2,y2);
  out.push_back(temp.cmdline());
}
void fillRect(double x, double y, double h,double w){
  FRect temp(x,y,h,w);
  out.push_back(temp.cmdline());
}
void drawTriangle(double x, double y, double x2,double y2, double x3,double y3){
  Triangle temp(x,y,x2,y2,x3,y3);
  out.push_back(temp.cmdline());
}
void fillTriangle(double x, double y, double x2,double y2, double x3,double y3){
  FTriangle temp(x,y,x2,y2,x3,y3);
  out.push_back(temp.cmdline());
}
void drawCircle(double x, double y, double r){
  Circle temp(x,y,r);
  out.push_back(temp.cmdline());
}
void fillCircle(double x, double y, double r){
  FCircle temp(x,y,r);
  out.push_back(temp.cmdline());
}
void grid(double x,double xstep,double x2,double y,double ystep,double y2){
  Grid temp(x,xstep,x2,y,ystep,y2);
  out.push_back(temp.cmdline());
}
void setFont(string font,uint32_t size){
  string s=R"(/)"+font+" findfont "+ to_string(size)+" scalefont setfont ";
  out.push_back(s);
}
void text(double x,double y,string t){
  string s=to_string(x)+" "+to_string(y)+" moveto ("+t+") show ";
  out.push_back(s);
}
void write(){
  ofstream f(filename);
  f<< "erasepage ";
  for(vector<string>::iterator it = out.begin() ; it != out.end(); ++it){
    f << *it;
  }
  f<< "showpage";
  f.close();
}

};



int main(){
  Postscript p("test.ps");
  p.drawRect(50,50,100,200);
  p.setColor(200,100,50);
  p.fillRect(200,200,200,200);
  p.drawTriangle(400,5,500,5,450,300);
  p.setColor(0,100,255);
  p.fillTriangle(400,200,500,630,550,800);
  p.drawCircle(75,75,75);
  p.setColor(10,240,50);
  p.fillCircle(200,400,100);
  p.line(0,0,500,400);
  p.grid(0,50,500,0,50,400);
  p.setFont("Helvetica",32);
  p.text(200,200, "Yo Ho");
  p.write();
  return 0;
}
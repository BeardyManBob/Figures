#ifndef Figures_h
#define Figures_h
#include <vcclr.h> 
#include <fstream>
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
class Points
{
public:
	float x, y;
	Points()
	{
		x = 0;
		y = 0;
	}
};
class Figures
{
public:
	bool damaged = false;
	bool visible = true;
	float x, y;
	float elemx, elemy;
	float dx, dy;
	float radius;

	Figures() {

	}
	virtual void setParam(float, float) {};
	virtual float getx() { return 0; }
	virtual float gety() { return 0; }
	virtual int  num() { return 1; }
	virtual float getdx() { return 0; }
	virtual float getdy() { return 0; }
	virtual int getFigCount() { int f = 0; return f; }
	virtual void setFigCount(int) {}
	virtual void addToA(Figures*f) {}
	virtual Figures* Copies(){return 0;}
	virtual Figures** getFig() { return 0; };
	virtual void Change(bool f) {};
	virtual void SaveToFile(System::IO::StreamWriter ^file) {};
	virtual bool Collision(Figures* f)
	{
		int x1, x2, dx1, dx2, y1, y2, dy1, dy2,n;
		 
			x1 = this->getx();
			y1 = this->gety();
			dx1 = this->getdx() + this->getx();
			dy1 = this->getdy() + this->gety();
			x2 = f->getx();
			y2 = f->gety();
			dx2 = f->getdx() + f->getx();
			dy2 = f->getdy() + f->gety();

			if ((((dx1 >= x2) && (dx1 <= dx2) || (x1 <= dx2) && (x1 >= x2)) && (((y1 <= dy2) && (y1 >= y2)) || (dy1 <= dy2) && (dy1 >= y2))) || (((dy1 >= y2) && (dy1 <= dy2) || ((y1 <= dy2) && (y1 >= y2))) && ((x1 >= x2) && (x1 <= dx2))))
				return 1;
			return 0;
		 
		
	}
	virtual void Draw(Graphics^, float width, bool trace) {};
	virtual void Remove(Graphics^g) {};
	virtual void MLeft() {};
	virtual void MRight() {};
	virtual void MDown() {};
	virtual void MUp() {};
	virtual void StColor(Graphics^g) {};
};
class Rect: public Figures
{

	


public:
	 
	const float x1 = 10, y1 = 10, dx1 = 35, dy1 = 35;
	Rect() {
		x = 10;
		y = 10;
		dx = 35;
		dy = 35;
		elemx = x;
		elemy = y;
		 
	}
	Figures*Copies()
	{
		Figures*f = new Rect;
		*f = *this;
		f->elemx = this->x;
		f->elemy = this->y;
		return f;
	}
	  float getx() { return x; }
	  float gety() { return y; }
	  float getdx() { return dx; }
	  float getdy() { return dy; }
	void SaveToFile(System::IO::StreamWriter ^file)
	{
		 
			file->WriteLine("1"+ " "+ x + " " + y );
		   
		 
			 
			
		
	}
	void setParam(float xx, float yy)
	{
		
		x =x+xx;
		y =y+  yy;
	}
	void Draw( Graphics^g, float width, bool trace) ;
	void Change(bool f);
	void Remove(Graphics^g) ;
	 void MLeft( ) ;
	void MRight () ;
	void MDown( ) ;
	void MUp () ;
	void StColor(Graphics^g);
};
class Circle : public Figures
{

	
	
public:
 
	const float x1 = 10, y1 = 10, r1 = 35;
	Circle() {
		x = 10;
		y = 10;
		radius = 35;
		dx = radius;
		dy = radius;
		elemx = x;
		elemy = y;
	}
	Figures*Copies()
	{
		Figures*f = new Circle;
		*f = *this;
		f->elemx = this->x;
		f->elemy = this->y;
		return f;
	}
	float getx() { return x; }
	float gety() { return y; }
	float getdx() { return dx; }
	float getdy() { return dy; }
	void SaveToFile(System::IO::StreamWriter ^file)
	{
		
			file->WriteLine("2" + " " + x + " " + y);



			 
		
	}
	void setParam(float xx, float yy)
	{
		 
		 x=x+xx;
		 y=y+yy;
	}
	void Draw( Graphics^g, float width, bool trace);
	 void Remove(Graphics^g) ;
	 void MLeft();
	void MRight();
    void MDown() ;
	 void MUp() ;
	 void StColor(Graphics^g);
	 void Change(bool f);
};
class Agregate : public Figures
{
	public:
		
		Figures** figures=new Figures*[30];
		Figures** copy;
		int NumberOfFigures;
		Agregate()
		{
			NumberOfFigures = 0;
			 
		}
		int  num() { return NumberOfFigures; }
		void SaveToFile(System::IO::StreamWriter ^file)
		{
			file->WriteLine("3");
			for (int i = 1; i <= NumberOfFigures; i++)
			{
				figures[i]->SaveToFile(file);
			}
			file->WriteLine("0");
		}
		void setParam(float xx, float yy)
		{
			for (int i = 1; i <= NumberOfFigures; i++)
			{
				figures[i]->setParam(xx, yy);
				 
			}
			
		}
		void addToA(Figures*f) 
		{
			 
			NumberOfFigures++;
			 
			 
			figures[NumberOfFigures] = f->Copies();

		}
		Figures* Copies() 
		{		
			Figures* f = new Agregate;
			*f = *this;
			f->elemx = this->x;
			f->elemy = this->y;
			int a;
			a = this->getFigCount();
			f->setFigCount(a);
			for (int i = 1; i<=NumberOfFigures; i++)
			{
				f->getFig()[i] = getFig()[i]->Copies();
			}
			return f;
		}
		Figures** getFig() 
		{  
			return this->figures;
		}
		int getFigCount()
		{
			return this->NumberOfFigures;
		}
		void setFigCount(int fc)
		{
			this->NumberOfFigures = fc;
		}
		bool Collision(Figures* f)
		{
			int x1, x2, dx1, dx2, y1, y2, dy1, dy2;
			bool x;

			for (int i = 1; i <= NumberOfFigures; i++)
			{
				 
				x= f->Collision(figures[i]);
				if(x==0) x = figures[i]->Collision(f);
				return x;
					/*x2 = f->getx();
					y2 = f->gety();
					dx2 = f->getdx() + f->getx();
					dy2 = f->getdy() + f->gety();
				 
				
				x1 = figures[i]->getx();
				y1 = figures[i]->gety();
				dx1 = figures[i]->getdx() + figures[i]->getx();
				dy1 = figures[i]->getdy() + figures[i]->gety();
				
				if ((((dx1 >= x2) && (dx1 <= dx2) || (x1 <= dx2) && (x1 >= x2)) && (((y1 <= dy2) && (y1 >= y2)) || (dy1 <= dy2) && (dy1 >= y2))) || (((dy1 >= y2) && (dy1 <= dy2) || ((y1 <= dy2) && (y1 >= y2))) && ((x1 >= x2) && (x1 <= dx2))))
					return 1;
				return 0;*/
			}
			
		}
	 
		void Draw(Graphics^g,float width, bool trace)
		{
			for (int i = 1; i <= NumberOfFigures; i++)
			{
				figures[i]->Draw(g, width, trace);
			}
		
		}
		void Remove(Graphics^g)
		{
			for (int i = 1; i <= NumberOfFigures; i++)
			{
				figures[i]->Remove(g);
			}
		}
		void MLeft()
		{
			for (int i = 1; i <= NumberOfFigures; i++)
			{
				figures[i]->MLeft();
			}
		}
		void MRight()
		{

			for (int i = 1; i <= NumberOfFigures; i++)
			{
				figures[i]->MRight();
			}
		}
		void MDown()
		{

			for (int i = 1; i <= NumberOfFigures; i++)
			{
				figures[i]->MDown();
			}
		}
		void MUp()
		{

			for (int i = 1; i <= NumberOfFigures; i++)
			{
				figures[i]->MUp();
			}
		}
		void StColor(Graphics^g)
		{

			for (int i = 1; i <= NumberOfFigures; i++)
			{
				figures[i]->StColor(g);
			}
		}
		void Change(bool f)
		{

			for (int i = 1; i <= NumberOfFigures; i++)
			{
				figures[i]->Change(f);
			}
		}
};
#endif

#include "Figures.h"





void Rect::Draw(  Graphics^g, float width, bool trace)
{
 

	if(!damaged)
	{
		Pen^ p = gcnew Pen(Color::Black, width);

		if (trace)
		{
			Pen^ p = gcnew Pen(Color::Gray, width);
			g->DrawRectangle(p, x, y, dx, dy);
		}


		else 	g->DrawRectangle(p, x, y, dx, dy);
	}
	if (damaged)
	{
		Pen^ p = gcnew Pen(Color::Red, width);

		if (trace)
		{
			Pen^ p = gcnew Pen(Color::Gray, width);
			g->DrawRectangle(p, x, y, dx, dy);
		}


		else 	g->DrawRectangle(p, x, y, dx, dy);
	}
	 
	
	
}
void Rect::Remove(Graphics^g)
{
	 
		Pen^ p = gcnew Pen(Color::Black, 2.0f);
		//	g->FillRectangle(Brushes::White, x, y, dx, dy);
		x =elemx;
		y = elemy;
		g->DrawRectangle(p, elemx, elemy, dx1, dy1);
	 

	 
	

}
void Rect::MLeft()
{
	//Pen^ pp = gcnew Pen(Color::White, 2.0f);
	//if(!f)g->DrawRectangle(pp, x, y, dx, dy);
	
	x -=4;

	//Pen^ p = gcnew Pen(color, 2.0f);
	//g->FillRectangle(Brushes::Red, x, y, dx, dy);
	//g->DrawRectangle(p, x, y, dx, dy);

}
void Rect::MRight()
{
//	Pen^ pp = gcnew Pen(Color::White, 2.0f);
//	if (!f)g->DrawRectangle(pp, x, y, dx, dy);
	x +=4;

//	Pen^ p = gcnew Pen(color, 2.0f);
	//g->FillRectangle(Brushes::Red, x, y, dx, dy);
//	g->DrawRectangle(p, x, y, dx, dy);


}
void Rect::MDown()
{
//	Pen^ pp = gcnew Pen(Color::White, 2.0f);
//	if (!f)g->DrawRectangle(pp, x, y, dx, dy);
	y+=4;
	
	//Pen^ p = gcnew Pen(color, 2.0f);
	//g->FillRectangle(Brushes::Red, x, y, dx, dy);
	//g->DrawRectangle(p, x, y, dx, dy);

}
void Rect::MUp()
{
	//Pen^ pp = gcnew Pen(Color::White, 2.0f);
	//if (!f)g->DrawRectangle(pp, x, y, dx, dy);
	y -=4;

	//Pen^ p = gcnew Pen(color, 2.0f);
	//g->FillRectangle(Brushes::Red, x, y, dx, dy);
	//g->DrawRectangle(p, x, y, dx, dy);


}
void Rect::StColor(Graphics^g)
{
	Pen^ p = gcnew Pen(Color::White, 2.0f);
	//g->FillRectangle(Brushes::White, x, y, dx, dy);
	g->DrawRectangle(p, x, y, dx, dy);
}
 
void Rect::Change(bool f)
{

	dx = dx1;
	dy = dy1;
	if (f)
	{
		dx += 20;
		dy += 20;

		damaged = true;;
	}
	else
	{
		dx = dx1;
		dy = dy1;
		damaged = false;
	}
}
void Circle::Change(bool f)
{

	
	radius = r1;
	if (f)
	{
		radius += 20;
			dx = radius;
		dy = radius;
		damaged = true;
	}
	else
	{
		radius = r1;
		dx = radius;
		dy = radius;
		damaged = false;
	}
}
void Circle::Draw(  Graphics^g, float width, bool trace)
{
	 
	 
	if (!damaged)
	{
		Pen^ p = gcnew Pen(Color::Black, width);

		if (trace)
		{
			Pen^ p = gcnew Pen(Color::Gray, width);
			g->DrawEllipse(p, x, y, radius, radius);
		}


		else g->DrawEllipse(p, x, y, radius, radius);
	}
	if (damaged)
	{
		Pen^ p = gcnew Pen(Color::Red, width);

		if (trace)
		{
			Pen^ p = gcnew Pen(Color::Gray, width);
			g->DrawEllipse(p, x, y, radius, radius);
		}


		else g->DrawEllipse(p, x, y, radius, radius);
	}


}
void Circle::Remove(Graphics^g)
{
	Pen^ p = gcnew Pen(Color::Black, 2.0f);
 
	x = elemx;
	y = elemy;
	g->DrawEllipse(p, elemx, elemy, r1, r1);
}
void Circle::MLeft()
{ 
	x -= 4;

	 

}
void Circle::MRight()
{
	 
	x += 4;
}
void Circle::MDown()
{ 
	y += 4;


}
void Circle::MUp()
{

	y -= 4;

}
void Circle::StColor(Graphics^g)
{
	Pen^ p = gcnew Pen(Color::White,2.0f);
	 
	 g->DrawEllipse(p, x, y, radius, radius);

}
 












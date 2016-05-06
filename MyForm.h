#pragma once
#include <vcclr.h> 
#include "Figures.h"
 

namespace Graphics_lab {



	using namespace System;
	using namespace std;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;
	using namespace System::Threading;

	 
	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::PictureBox^  pictureBox1;


	private: System::Windows::Forms::Timer^  timer1;
























	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(874, 557);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Interval = 35;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Gainsboro;
			this->ClientSize = System::Drawing::Size(898, 581);
			this->ControlBox = false;
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	 
		int NumberOfFigures = 0;
		int currentFigure = 0;
		int activeFigure = 0;
		int currentr = 0;
		int currentc = 0;
		float x , y;
		bool trace = false;
		int i;
		bool record = false;
		bool changing = false;
		bool agregation = false;
		Color rectcolor, elcolor;
		Figures** figures= new Figures*[NumberOfFigures];
		Figures** copies; 
		
		Points* points= new Points[10000000];
		unsigned long long int steps = 0;
 
 void update()
 {

	 if (NumberOfFigures > 0)
	 {
		 System::Drawing::Graphics^ g = pictureBox1->CreateGraphics();
		 bool back = true;
		 for (int i = 1; i <= NumberOfFigures; i++)
		 {
			 if (i == activeFigure) continue;
			 

				 if (figures[i]->visible)
				 {
					  if (figures[activeFigure]->Collision(figures[i]))  
					  {
						  figures[activeFigure]->StColor(g);

						 figures[activeFigure]->Change(true);
						 figures[activeFigure]->Draw(g, 2, 0);
						 back = false;
						 
					 }
					  if (figures[i]->Collision(figures[activeFigure]))
					  {
						  figures[activeFigure]->StColor(g);

						  figures[activeFigure]->Change(true);
						  figures[activeFigure]->Draw(g, 2, 0);
						  back = false;

					  }
					   
				 }
			 

		 }
		 if (back)
		 {
			 figures[activeFigure]->StColor(g);
			 figures[activeFigure]->Change(false);
			 figures[activeFigure]->Draw(g, 2, 0);
		 }



 
	 	 for (int i = 1; i <= NumberOfFigures; i++)
		 {
			  
				 if (figures[i]->visible)
				 {
					 figures[i]->StColor(g);
					 figures[i]->Draw(g, 1, 0);
				 }
			  
			

		 } 
	 }
 }
 Figures* CreateArg(ifstream&f,Figures*a)
 {
	 Figures** buff = new Figures*[NumberOfFigures];
	 int s=5;
	 int i = 1;
	 float xy;

	 
	 float yx;
	 while (s != 0)
	 {
		 f >> s;
		 if (s == 3) CreateArg(f, a);
		 else
		 {
			 if(s==2)
			 {
				 buff[i] = new Circle;
				 f >> xy;
				 f >> yx;
				 buff[i]->x = xy;
				 buff[i]->y = yx;
				 a->addToA(buff[i]);
				 i++;
			 }
			 if(s==1)
			 {
				buff[i] = new Rect; 
				 f >> xy;
				 f >> yx;
				 buff[i]->x = xy;
				 buff[i]->y = yx;
				 a->addToA(buff[i]);
				 i++;
			 }
		 }
	 }
	
	 return a;
 }
 void clear()
 {
	 System::Drawing::Graphics^ g = pictureBox1->CreateGraphics();
	 for (int i = 1; i <= NumberOfFigures; i++)
	 {
		 delete figures[i];
	 }
	
	 g->Clear(Color::White);
	 NumberOfFigures = 0;
 }

private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	System::Drawing::Graphics^ g = pictureBox1->CreateGraphics();

	if (e->KeyCode == Keys::R)
	{



		copies = new Figures*[NumberOfFigures];

		for (int i = 1; i <= NumberOfFigures; i++)
		{
			copies[i] = figures[i];
		}

		if ((NumberOfFigures > 0)&& figures[activeFigure]->visible)
		{
			figures[activeFigure]->StColor(g);
			figures[activeFigure]->Draw(g, 1, 0);
		}

		NumberOfFigures++;
		figures = new Figures*[NumberOfFigures];
		for (int i = 1; i <= NumberOfFigures - 1; i++)
		{


			figures[i] = copies[i];

		}


		figures[NumberOfFigures] = new Rect;
		activeFigure = NumberOfFigures;

		figures[activeFigure]->StColor(g);
		figures[activeFigure]->Draw(g, 2, 0);

		 
		//currentFigure++;


	}
	if (e->KeyCode == Keys::C)
	{

		copies = new Figures*[NumberOfFigures];

		for (int i = 1; i <= NumberOfFigures; i++)
		{
			copies[i] = figures[i];
		}

		if ((NumberOfFigures > 0) && figures[activeFigure]->visible)
		{
			figures[activeFigure]->StColor(g);
			figures[activeFigure]->Draw(g, 1, 0);
		}

		NumberOfFigures++;
		figures = new Figures*[NumberOfFigures];
		for (int i = 1; i <= NumberOfFigures - 1; i++)
		{


			figures[i] = copies[i];

		}


		figures[NumberOfFigures] = new Circle;
		activeFigure = NumberOfFigures;

		figures[activeFigure]->StColor(g);
		figures[activeFigure]->Draw(g, 2, 0);
	}
	if (e->KeyCode == Keys::F1)
	{
		MessageBox::Show("C - create a circle\n" +
			"R - create a rectangle\n" +
			"D - delete object\n" +
			"Tab - next object\n" +
			"Arrows - move object\n" +
			"V - visible/unvisible\n" +
			"S - recover position\n" +
			"T - trace\n" +
			"Q - start recording trajectory\n" +
			"W - motion path\n" +
			"A - start creating agregate\n" +
			"Y - add to agregae\n" +
			"F - save to file\n" +
			"L - load from file",
			"Help");
	}

	if (e->KeyCode == Keys::F)
	{

		System::IO::StreamWriter ^file = gcnew System::IO::StreamWriter("1.txt");
		file->WriteLine(NumberOfFigures);
		for (int i = 1; i <= NumberOfFigures; i++)
		{
			figures[i]->SaveToFile(file);
		}
	
		file->Close();



	}
	if (e->KeyCode == Keys::L)
	{
	if(NumberOfFigures>0)	clear();
	int s;
		float xy;
		float yx;
		int xxxx;
		bool doagr = false;
		
		ifstream f("1.txt");
		f >> xxxx;
		NumberOfFigures = xxxx;
		
		
		figures = new Figures*[NumberOfFigures];
		for (int i = 1; i <= NumberOfFigures;i++)
		{
			f >> s;
			if (s == 1)
			{
			 
 
				 
				figures[i] = new Rect;
				 

				figures[i]->StColor(g);
				f >> xy;
				f >> yx;
				figures[i]->x = xy;
				figures[i]->y = yx;
				figures[i]->Draw(g, 1, 0);
			}
			if (s == 2)
			{
				figures[i] = new Circle;


				figures[i]->StColor(g);
				f >> xy;
				f >> yx;
				figures[i]->x = xy;
				figures[i]->y = yx;
				figures[i]->Draw(g, 1, 0);
			}
			if (s == 3)
			{
			 
				figures[i] = new Agregate;
				CreateArg(f, figures[i]);
				figures[i]->StColor(g);
				figures[i]->Draw(g, 1, 0);
			}
		}
		activeFigure = NumberOfFigures;
		figures[activeFigure]->Draw(g, 2, 0);
	}


	if (NumberOfFigures > 0)
	{ 
		if (figures[activeFigure]->visible)
		{
			if (e->KeyCode == Keys::S)
			{
				figures[activeFigure]->StColor(g);
				figures[activeFigure]->Remove(g);
			}
			if (e->KeyCode == Keys::Up)
			{

				
			if(!trace)	figures[activeFigure]->StColor(g);
				if (record)
				{
					steps++;
					y =- 4;
					x = 0;
					points[steps].x = x;
					points[steps].y = y;
				}
				if (trace)
				{
					figures[activeFigure]->Draw(g, 2, 1);

				}
				figures[activeFigure]->MUp();
				
               


			   update();
				figures[activeFigure]->Draw(g, 2, 0);

			}
			if (e->KeyCode == Keys::Down)
			{

			

				if (!trace)	figures[activeFigure]->StColor(g);
				if (record)
				{
					steps++;
					y = 4;
					x = 0;
					points[steps].x = x;
					points[steps].y = y;
				}
				if (trace)
				{
					figures[activeFigure]->Draw(g, 2, 1);

				}
				figures[activeFigure]->MDown();

				
				update();
				figures[activeFigure]->Draw(g, 2, 0);
				
			}
			if (e->KeyCode == Keys::Right)
			{


				
				if (!trace)	figures[activeFigure]->StColor(g);
				if (record)
				{
					steps++;
					x = 4;
					y = 0;
					points[steps].x = x;
					points[steps].y = y;
				}
				if (trace)
				{
					figures[activeFigure]->Draw(g, 2, 1);

				}
				figures[activeFigure]->MRight();
				
				
				update();
				figures[activeFigure]->Draw(g, 2, 0);


			}
			if (e->KeyCode == Keys::Left)
			{


			
				if (!trace)	figures[activeFigure]->StColor(g);
				if (record)
				{
					steps++;
					x = -4;
					y = 0;
					points[steps].x = x;
					points[steps].y = y;
				}
				if (trace)
				{
					figures[activeFigure]->Draw(g, 2, 1);

				}
				figures[activeFigure]->MLeft();
				
				
				update();
				figures[activeFigure]->Draw(g, 2, 0);


			}
		}

		


		if (e->KeyCode == Keys::Tab)
		{
			
			
				figures[activeFigure]->StColor(g);
              if (figures[activeFigure]->visible)
			{
				figures[activeFigure]->Draw(g, 1, 0);
			}
			activeFigure--;
			if (activeFigure < 1)activeFigure = NumberOfFigures;
			
			
			figures[activeFigure]->Draw(g, 2, 0);
			
		}
		if (e->KeyCode == Keys::T)
		{

			trace = !trace;
		}
		if (e->KeyCode == Keys::W)
		{
			timer1->Enabled=!timer1->Enabled;
			i = 0;
			 

		}
		if (e->KeyCode == Keys::Q)
		{
			 
			 
			record = !record;

		}
		if (e->KeyCode == Keys::D)
		{
			figures[activeFigure]->StColor(g);
			delete figures[activeFigure];
			for (int i = activeFigure; i <= NumberOfFigures - 1; i++)
			{
				figures[i] = figures[i + 1];
			} 
			activeFigure=1;
			NumberOfFigures--;
		 
			if (NumberOfFigures > 0)
			{
				update();
				if (figures[activeFigure]->visible)figures[activeFigure]->Draw(g, 2, 0);
			}
		}
		if (e->KeyCode == Keys::V)
		{
			
			if (figures[activeFigure]->visible)
			{
				figures[activeFigure]->StColor(g);
				figures[activeFigure]->visible = false;
			}
			else
			{
				figures[activeFigure]->visible = true;
				figures[activeFigure]->Draw(g, 2, 0);
			}
		}
		if (e->KeyCode == Keys::A)
		{
			if (agregation)
			{
				NumberOfFigures++;
				activeFigure = NumberOfFigures;

				figures[activeFigure]->StColor(g);
				figures[activeFigure]->Draw(g, 2, 0);
			}
			else
			{
				int x = 0;
				x=NumberOfFigures;
				copies = new Figures*[x];

				for (int i = 1; i <= x; i++)
				{
					copies[i] = figures[i];
				}

			 

				x++;
				figures = new Figures*[x];
				for (int i = 1; i <= x - 1; i++)
				{


					figures[i] = copies[i];

				}


				figures[x] = new Agregate;
			}
			agregation = !agregation;
		}
		if (e->KeyCode == Keys::Y)
		{
			if (agregation)
			{
				NumberOfFigures++;
				figures[NumberOfFigures]->addToA(figures[activeFigure]);
				NumberOfFigures--;
			}
		}
		if (e->KeyCode == Keys::M)
		{
			figures[activeFigure]->StColor(g);
			figures[activeFigure]->Change(true);

			figures[activeFigure]->Draw(g, 2, 0);
			changing = !changing;
			//update();
		}
		



	}
	
}
 
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

}
 
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

	 
	i++;

	System::Drawing::Graphics^ g = pictureBox1->CreateGraphics();
	if(!trace)figures[activeFigure]->StColor(g);
	if (trace)figures[activeFigure]->Draw(g, 2, 1);

	

 	figures[activeFigure]->setParam(points[i].x, points[i].y);
		 
	 ;
	
	  
		figures[activeFigure]->Draw(g, 2, 0);
		if (i == steps)
		{
			steps = 0;
			timer1->Enabled = false;
			
		}
}
};
}

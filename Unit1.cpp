//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include <vector>
#include <string.h>
#include <cmath>
#include <gdiplus.h>
#include <string.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


class GraphicElement {
	virtual void create(int x1, int y1, TImage *Image1) = 0;
	virtual void create(TImage *Image1) = 0;
};

class Segment : public GraphicElement{
	private:
		int x,y; // ���������� ������ ����� �������
		int x1,y1; // ���������� ������ ����� �������
		TColor color;
		int bold;
		bool activ = false; // �������� �� ������
	public:
		Segment(TColor color, int bold, int x, int y, std::vector<int>&sequence){
		   this -> color = color;
		   this -> bold = bold;
		   this -> x = x;
		   this -> y = y;
		   this -> x1 = x;
		   this -> y1 = y;
		   sequence.emplace_back(1);
		}

        void setColor(TColor color){
			 this->color = color;
		}

		void setBold(int bold){
			 this->bold = bold;
		}

		void setActiv(bool activ){
			 this->activ = activ;
		}

		bool getActiv(){
			 return activ;
		}

		void create(int x1, int y1, TImage *Image1){
			this -> x1 = x1;
			this -> y1 = y1;
			this -> color = color;
			Form1->Image1->Canvas->Pen->Style = psSolid;
			Form1->Image1->Canvas->Pen->Color = color;
			Form1->Image1->Canvas->Pen->Width = bold;
			Image1->Canvas->MoveTo(x,y); // ����� �����
			Image1->Canvas->LineTo(x1,y1);
		}

		void create(TImage *Image1){
			Form1->Image1->Canvas->Pen->Style = psSolid;
			if(activ)
				Form1->Image1->Canvas->Pen->Color = clBlue;
			else
				Form1->Image1->Canvas->Pen->Color = color;
			Form1->Image1->Canvas->Pen->Width = bold;
			Image1->Canvas->MoveTo(x,y); // ����� �����
			Image1->Canvas->LineTo(x1,y1);
		}

        bool accessory_point_figure(int x, int y, int x1, int y1){   // ����������� �� ����� ������

			/*-----------------------------------------------------------------------
			 1. ������ ������� �������������� - �������
			 2. ������ ������ ����������� ���� �������� ��� ������� segment
				� ������ ������� ��������������
			 3. ���� ���� �� � ����� �������� ������������ - ������ ����� ��������
			 4. ���� �� ������������, �� ���������, ����� �� ��� ����� ������
				������ ������� �����
			 5. ���� �� - ������ ����� ��������, ���� ���, �� ���
			------------------------------------------------------------------------*/
			 int X = this -> x;    int Y = this -> y;
			 int X1 = this -> x1;  int Y1 = this -> y1;

			 //----������ ���� ��������----- ((X,Y),(X1,Y1)) and ((x,y),(x1,y))
			 double A1 = Y1 - Y;
			 double B1 = X - X1;
			 double C1 = - A1 * X - B1 * Y;

			 double A2 = y - y;
			 double B2 = x - x1;
			 double C2 = -A2 * x - B2 * y;

			 double f1 = A1 * x + B1 * y + C1;
			 double f2 = A1 * x1 + B1 * y + C1;
			 double f3 = A2 * X + B2 * Y + C2;
			 double f4 = A2 * X1 + B2 * Y1 + C2;

			 bool intersect1 = (f1 * f2 < 0 && f3 * f4 < 0); // ������� �����������
			 //----������ ���� ��������-----   ((X,Y),(X1,Y1)) and ((x,y),(x,y1))
			 A2 = y1 - y;
			 B2 = x - x;
			 C2 = -A2 * x - B2 * y;

			 f1 = A1 * x + B1 * y + C1;
			 f2 = A1 * x + B1 * y1 + C1;
			 f3 = A2 * X + B2 * Y + C2;
			 f4 = A2 * X1 + B2 * Y1 + C2;

			 bool intersect2 = (f1 * f2 < 0 && f3 * f4 < 0);
			 //----������ ���� ��������-----  ((X,Y),(X1,Y1)) and  ((x1,y1),(x,y1))
			 A2 = y1 - y1;
			 B2 = x1 - x;
			 C2 = -A2 * x1 - B2 * y1;

			 f1 = A1 * x1 + B1 * y1 + C1;
			 f2 = A1 * x + B1 * y1 + C1;
			 f3 = A2 * X + B2 * Y + C2;
			 f4 = A2 * X1 + B2 * Y1 + C2;

			 bool intersect3 = (f1 * f2 < 0 && f3 * f4 < 0);
			 //----��������� ���� ��������-----   ((X,Y),(X1,Y1)) and  ((x1,y1),(x1,y))
			 A2 = y - y1;
			 B2 = x1 - x1;
			 C2 = -A2 * x1 - B2 * y1;

			 f1 = A1 * x1 + B1 * y1 + C1;
			 f2 = A1 * x1 + B1 * y + C1;
			 f3 = A2 * X + B2 * Y + C2;
			 f4 = A2 * X1 + B2 * Y1 + C2;

			 bool intersect4 = (f1 * f2 < 0 && f3 * f4 < 0);
			 //--------------------------------

			 if(intersect1 || intersect2 || intersect3 || intersect4){
				return true;
			 }
			 else {
				if((((X < x && X > x1) || (X > x && X < x1)) &&
					((Y < y && Y > y1) || (Y > y && Y < y1)))&&
					((X1 < x && X1 > x1) || (X1 > x && X1 < x1)) &&
					((Y1 < y && Y1 > y1) || (Y1 > y && Y1 < y1)))
					return true;
				else
					return false;
			 }
		}

		void backlight_figure(int x, int y, int x1, int y1){ // ������� ������ ��������, ���� ������ ����������� ������������� �������
			if(this->accessory_point_figure(x, y, x1, y1) == true){
				activ = true;
			}
		}

};

class MyArc : public GraphicElement{
	private:
		TPoint points[3]; // ������ ����� ��� ���������� ������ �����
		TColor color;
		int bold;
		bool activ = false; // �������� �� ������

	public:
		MyArc(TColor color, int bold, int x, int y, std::vector<int>&sequence){
		   this -> color = color;
		   this -> bold = bold;
		   this -> points[0] = TPoint(x,y);
		   this -> points[1] = TPoint(x,y);
		   this -> points[2] = TPoint(x,y);
		   sequence.emplace_back(2);
		}

		MyArc(TColor color, int bold, int x, int y){
		   this -> color = color;
		   this -> bold = bold;
		   this -> points[0] = TPoint(x,y);
		   this -> points[1] = TPoint(x,y);
		   this -> points[2] = TPoint(x,y);
		}

		void create(int x1, int y1, TImage *Image1){
			this -> points[1] = TPoint(x1,y1);
			Form1->Image1->Canvas->Pen->Style = psSolid;
			Form1->Image1->Canvas->Pen->Color = color;
			Form1->Image1->Canvas->Pen->Width = bold;
			Image1->Canvas->MoveTo(points[0].x,points[0].y); //������� ��������� �����
			Image1->Canvas->PolyBezierTo(points,2);//��������� �����

		}

		void setColor(TColor color){
			 this->color = color;
		}

        void setBold(int bold){
			 this->bold = bold;
		}

		void setActiv(bool activ){
			 this->activ = activ;
		}

		bool getActiv(){
			 return activ;
		}

		void create(int x1, int y1){
			this -> points[2] = TPoint(x1,y1);
			this -> points[1] = TPoint(x1,y1);
		}

		void create(TImage *Image1){
			Form1->Image1->Canvas->Pen->Style = psSolid;
			if(activ)
				Form1->Image1->Canvas->Pen->Color = clBlue;
			else
				Form1->Image1->Canvas->Pen->Color = color;
			Form1->Image1->Canvas->Pen->Width = bold;
			Image1->Canvas->MoveTo(points[0].x,points[0].y); //������� ��������� �����
			Image1->Canvas->PolyBezierTo(points,2);//��������� �����
		}

		bool accessory_point_figure(int x, int y, int x1, int y1){   // ����������� �� ����� ������

			/*-----------------------------------------------------------------------
			 ���� 3 �����, ������������ ������ �����
			 ��������� �������� �� ������ ���� �� ��� � �����
			 ���� ��, �� ���� ����������
			 (� ���������, �������� �� ����� ������, ��� � ������ � ����������
			 ����� ����� ������ ����, �� �� ������ ���� �� �����. ����
			 �������� �� ������ ������ ��������)
			------------------------------------------------------------------------*/
			// ��������� ������ �����
			 int X = this -> points[0].x;
			 int Y = this -> points[0].y;
			 bool inside1 = false;
			 bool inside2 = false;
			 bool inside3 = false;

			 if(((X < x && X > x1) || (X > x && X < x1)) &&
					((Y < y && Y > y1) || (Y > y && Y < y1)))
				inside1 = true;

			 X = this -> points[1].x;
			 Y = this -> points[1].y;

			 if(((X < x && X > x1) || (X > x && X < x1)) &&
					((Y < y && Y > y1) || (Y > y && Y < y1)))
				inside2 = true;

			 X = this -> points[2].x;
			 Y = this -> points[2].y;

			 if(((X < x && X > x1) || (X > x && X < x1)) &&
					((Y < y && Y > y1) || (Y > y && Y < y1)))
				inside3 = true;

			 if(inside1 || inside2 || inside3)
				return true;
			 else
				return false;
		}

		void backlight_figure(int x, int y, int x1, int y1){ // ������� ������ ��������, ���� ������ ����������� ������������� �������
			if(this->accessory_point_figure(x, y, x1, y1) == true){
				activ = true;
			}
		}

};

class MyPolyline : public GraphicElement{
	 std::vector<MyArc> polyArcs;
	 TColor color;
	 int bold;
	 int a = -1; //������ ��� ������� ���������
	 //std::vector<int> sequenceP; // 1-�������, 2-����
	 bool activ = false; // �������� �� ������

     public:
		MyPolyline(TColor color, int bold, int x, int y){
			  polyArcs.emplace_back(MyArc(color, bold, x, y));
			  a++;
		}

		void myAdd(TColor color, int bold, int x, int y){
			  polyArcs.emplace_back(MyArc(color, bold, x, y));
			  a++;
		}

		void create(int x1, int y1, TImage *Image1){
			  polyArcs.at(a).create(x1, y1, Image1);
		}

		void setColor(TColor color){
			 polyArcs.at(a).setColor(color);
		}

        void setBold(int bold){
			 polyArcs.at(a).setBold(bold);
		}

		void setActiv(bool activ){
			 this->activ = activ;

			 for(int i=0; i< polyArcs.size(); i++) {
				 polyArcs.at(i).setActiv(activ);
			 }
		}

		bool getActiv(){
			 return activ;
		}

		void create(int x, int y){
				  polyArcs.at(a).create(x, y);
		}

		void create(TImage *Image1){
			 for(MyArc myarc : polyArcs){
					myarc.create(Image1);
			 }
		}

        bool accessory_point_figure(int x, int y, int x1, int y1){   // ����������� �� ����� ������
			 /* ------------------------------------------------
			 ��������� ���������� ������ ���, �������
			 �������������� ��������� ������������� ������
			 ������������ ��������� ������� backlight_figure ��
             ����. �������� �� �� �����.
			 --------------------------------------------------*/
			 for(int i=0; i< polyArcs.size(); i++) {
				 polyArcs.at(i).backlight_figure(x, y, x1, y1);
				 if(polyArcs.at(i).getActiv()){
					return true;
				 }
			 }
		}

		void backlight_figure(int x, int y, int x1, int y1){ // ������� ������ ��������, ���� ������ ����������� ������������� �������
			if(this->accessory_point_figure(x, y, x1, y1) == true){
				this -> setActiv(true);
			}
		}

};

class MyCircle : public GraphicElement{
	private:
		int x,y; // ���������� ������ ����������
		int x1,y1; // ���������� ����� �� ����������
		TColor color;
		int bold;
		bool activ = false; // �������� �� ������

	private:
		double radius(){
			return sqrt(pow((x1-x),2)+pow((y1-y),2));
		}

		double distance_between_points(int x, int y, int x1, int y1){
			return sqrt(pow((x1-x),2)+pow((y1-y),2));
		}

	public:
		MyCircle(TColor color, int bold, int x, int y, std::vector<int>&sequence){
		   this -> color = color;
		   this -> bold = bold;
		   this -> x = x;
		   this -> y = y;
		   this -> x1 = x;
		   this -> y1 = y;
		   sequence.emplace_back(4);
		}

		MyCircle(TColor color, int bold, int x, int y){
		   this -> color = color;
		   this -> bold = bold;
		   this -> x = x;
		   this -> y = y;
		   this -> x1 = x;
		   this -> y1 = y;
		}

		void setColor(TColor color){
			 this->color = color;
		}

		void setBold(int bold){
			 this->bold = bold;
		}

		void setActiv(bool activ){
			 this->activ = activ;
		}

		bool getActiv(){
			 return activ;
		}

		void create(int x1, int y1, TImage *Image1){
			this -> x1 = x1;
			this -> y1 = y1;
			this -> color = color;
			Form1->Image1->Canvas->Pen->Style = psSolid;
			Form1->Image1->Canvas->Pen->Color = color;
			Form1->Image1->Canvas->Pen->Width = bold;
			unsigned radius = sqrt(pow(abs((x1-x)),2) + pow(abs((y1-y)),2));
			Image1->Canvas->MoveTo(x+radius,y);
			Image1->Canvas->AngleArc(x, y, radius, 0, 360);
		}

		void create(TImage *Image1){
			Form1->Image1->Canvas->Pen->Style = psSolid;
			if(activ == true)
				Form1->Image1->Canvas->Pen->Color = clBlue;
			else if(activ == false)
				Form1->Image1->Canvas->Pen->Color = color;
			Form1->Image1->Canvas->Pen->Width = bold;
			unsigned radius = sqrt(pow(abs((x1-x)),2) + pow(abs((y1-y)),2));
			Image1->Canvas->MoveTo(x+radius,y);
			Image1->Canvas->AngleArc(x, y, radius, 0, 360);
		}

		bool accessory_point_figure(int x, int y, int x1, int y1){   // ����������� �� ����� ������

			/*-----------------------------------------------------------------------
			 ���� ���������� ����� ������� ���������� � ����� ���������
			 �������������� ������ ��� ������ ������� ���������� - ���������
			 ������������ �� ������� ���������� � ��������������,
			 ����� - ������������.
			------------------------------------------------------------------------*/
			/*----------------------------------------------------------------------
			 ���� ����� ���������� ��� ��� ���������� �������� � ������� �����,
			 �� ��� ����������,
			 ���� ����� ������ ����������, �� ���������� �� ����������
			 -----------------------------------------------------------------------*/
			// ������ ���������� ����� ������ �������� �������������� � ������� ����������
			double distance1 = this -> distance_between_points(this -> x, this -> y, x, y);
			double distance2 = this -> distance_between_points(this -> x, this -> y, x1, y1);
			double distance3 = this -> distance_between_points(this -> x, this -> y, x, y1);
			double distance4 = this -> distance_between_points(this -> x, this -> y, x1, y);
			// ������ ������ ����������
			double radius = this -> radius();
			if((distance1 > radius && distance2 > radius &&
				distance3 > radius && distance4 > radius) ||
			   (distance1 < radius && distance2 < radius &&
				distance3 < radius && distance4 < radius)) {
				   if((distance1 > radius && distance2 > radius &&
					   distance3 > radius && distance4 > radius)){
					if(((this->x < x && this->x > x1) || (this->x > x && this->x < x1)) &&
					   ((this->y < y && this->y > y1) || (this->y > y && this->y < y1)))
						return true;
				   }
					else
						return false;
				}
			else
				return true;
		}

		void backlight_figure(int x, int y, int x1, int y1){ // ������� ������ ��������, ���� ������ ����������� ������������� �������
			if(this->accessory_point_figure(x, y, x1, y1) == true){
				activ = true;
			}
		}

};


class MyText : public GraphicElement{
	private:
		String text;
		HFONT font;
		LOGFONT lf;
		int x, y; //����� ��������� bitmap �� image
		TColor color;

		bool activ = false; // �������� �� ������

	public:

		void createText(TImage *Image1, String s, TColor color,
						HFONT font, int x, int y , std::vector<int>&sequence, LOGFONT lf){

			sequence.emplace_back(5);
			this-> text = s;
			this-> x = x;
			this-> y = y;
			this-> color = color;
			this-> lf = lf;

			Image1->Canvas->Font->Handle = font;
			Image1->Canvas->Font->Color = color;
			Image1->Canvas->TextOut(x,y,s);
		}


		void create(TImage *Image1){
			font = CreateFontIndirect(&this->lf);
			Image1->Canvas->Font->Handle = font;
			if(activ)
				Image1->Canvas->Font->Color = clBlue;
			else
				Image1->Canvas->Font->Color = color;

			Image1->Canvas->TextOut(x,y,text);
		}

		void create(int x1, int y1, TImage *Image1){}

        void setActiv(bool activ){
			 this->activ = activ;
		}

		bool getActiv(){
			 return activ;
		}

        bool accessory_point_figure(int x, int y, int x1, int y1){   // ����������� �� ����� ������
             // ��������� ������ ����� ����� ��������� � �����
			 int X = this -> x;
			 int Y = this -> y;

			 if(((X < x && X > x1) || (X > x && X < x1)) &&
					((Y < y && Y > y1) || (Y > y && Y < y1)))
				return true;
			 else
				return false;
		}

		void backlight_figure(int x, int y, int x1, int y1){ // ������� ������ ��������, ���� ������ ����������� ������������� �������
			if(this->accessory_point_figure(x, y, x1, y1) == true){
				activ = true;
			}
		}


};


struct FRAME  // ��������� ������������� �����
{
	int x,y;
	int x1,y1;
};
//-------------------------------------------------
void redrawing(const std::vector<Segment>&segments,
			   const std::vector<MyArc>&arcs,
			   const std::vector<MyPolyline>&polylines,
			   const std::vector<MyCircle>&circles,
			   const std::vector<MyText>&strings,
			   const std::vector<int>&sequence,
			   TImage *Image1, String fileName){

	if(fileName != ""){
		Image1->Picture->LoadFromFile(fileName);
	}
	else{
		Form1->Image1->Canvas->Brush->Color=clWhite; // ������� ��� �����
		Form1->Image1->Canvas->Pen->Style=psSolid;
		Form1->Image1->Canvas->Pen->Width = 1;
		Form1->Image1->Canvas->Pen->Color = clWindowFrame;
		Form1->Image1->Canvas->Rectangle(0,0,Form1->Image1->Width, Form1->Image1->Height);
	}

	int i = 0, a = 0, p = 0, e = 0, s = 0;
	for(int t : sequence){
		 if(t==1){
			Segment segment = segments.at(i);
			segment.create(Image1);
			i++;
		 }
		 if(t==2) {
			MyArc myarc = arcs.at(a);
			myarc.create(Image1);
			a++;
		 }
		 if(t==3) {
			MyPolyline mypl = polylines.at(p);
			mypl.create(Image1);
			p++;
		 }
		 if(t==4) {
			MyCircle myel = circles.at(e);
			myel.create(Image1);
			e++;
		 }
		 if(t==5) {
			MyText mytxt = strings.at(s);
			mytxt.create(Image1);
			s++;
		 }
	}
}

void vectors_cleaning(std::vector<Segment>&segments,
					  std::vector<MyArc>&arcs,
					  std::vector<MyPolyline>&polylines,
					  std::vector<MyCircle>&circles,
					  std::vector<MyText>&strings,
					  std::vector<int>&sequence){
   segments.clear();
   arcs.clear();
   polylines.clear();
   circles.clear();
   strings.clear();
   sequence.clear();
}

void figures_choice(int x, int y, int x1, int y1,
			   std::vector<Segment>&segments,
			   std::vector<MyArc>&arcs,
			   std::vector<MyPolyline>&polylines,
			   std::vector<MyCircle>&circles,
			   std::vector<MyText>&strings,
			   std::vector<int>&sequence,
			   TImage *Image1, String fileName){

	if(fileName != ""){
		Image1->Picture->LoadFromFile(fileName);
	}
	else{
		Form1->Image1->Canvas->Brush->Color=clWhite; // ������� ��� �����
		Form1->Image1->Canvas->Pen->Style=psSolid;
		Form1->Image1->Canvas->Pen->Width = 1;
		Form1->Image1->Canvas->Pen->Color = clWindowFrame;
		Form1->Image1->Canvas->Rectangle(0,0,Form1->Image1->Width, Form1->Image1->Height);
	}

	int i = 0, a = 0, p = 0, e = 0, s = 0;
	for(int t : sequence){
		 if(t==1){
			segments.at(i).backlight_figure(x, y, x1, y1);
			i++;
		 }
		 if(t==2) {
			arcs.at(a).backlight_figure(x, y, x1, y1);
			a++;
		 }
		 if(t==3) {
			polylines.at(p).backlight_figure(x, y, x1, y1);
			p++;
		 }
		 if(t==4) {
			circles.at(e).backlight_figure(x, y, x1, y1);
			e++;
		 }
		 if(t==5) {
			strings.at(s).backlight_figure(x, y, x1, y1);
			s++;
		 }
	}
}

void remove_selection(
			   std::vector<Segment>&segments,
			   std::vector<MyArc>&arcs,
			   std::vector<MyPolyline>&polylines,
			   std::vector<MyCircle>&circles,
			   std::vector<MyText>&strings,
			   std::vector<int>&sequence,
			   TImage *Image1, String fileName){

	if(fileName != ""){
		Image1->Picture->LoadFromFile(fileName);
	}
	else{
		Form1->Image1->Canvas->Brush->Color=clWhite; // ������� ��� �����
		Form1->Image1->Canvas->Pen->Style=psSolid;
		Form1->Image1->Canvas->Pen->Width = 1;
		Form1->Image1->Canvas->Pen->Color = clWindowFrame;
		Form1->Image1->Canvas->Rectangle(0,0,Form1->Image1->Width, Form1->Image1->Height);
	}

	int i = 0, a = 0, p = 0, e = 0, s = 0;
	for(int t : sequence){
		 if(t==1){
			segments.at(i).setActiv(false);
			i++;
		 }
		 if(t==2) {
			arcs.at(a).setActiv(false);
			a++;
		 }
		 if(t==3) {
		   polylines.at(p).setActiv(false);
			p++;
		 }
		 if(t==4) {
			circles.at(e).setActiv(false);
			e++;
		 }
		 if(t==5) {
			strings.at(s).setActiv(false);
			s++;
		 }
	}
}

std::vector<Segment> segments;
std::vector<MyArc> arcs;
std::vector<MyPolyline> polylines;
std::vector<MyCircle> circles;
std::vector<MyText> strings; // ������ � �������
std::vector<int> sequence; // ������� ��������� 1 - �������� 2 -���� 3-��������� 4-���������� 5-�����
TColor color; // �������� ����
TColor color2 = clWhite; // ���� �������
int bold = 1; // �������� �������
int i = -1; // ������� ������ ��� ������� ��������
int a = -1; // ������� ������ ��� ������� ���
int p = -1; // ������� ������ ��� ������� ���������
int e = -1; // ������� ������ ��� ������� �����������
int s = -1; // ������� ������ ��� ������� ������
int point=0; // ������ ��� ������ ����� �������
int x,y; //��������� ����� �������
bool save = false; // ���������� �������� �� ��� ����
String fileName = "";
int seg_arc = 1;
int x2=0, y2=0; //����� ����������� �������� ��������� � ������ ������
int click=0;
int seg_arc_pr = 1;
//TFont *font;

HFONT hfont;   // ����� ������
TColor text_color; // ���� ������
String text; // ������ ������
CHOOSEFONT cf;            // ���� ���������
static LOGFONT lf;        // ���������, �������� ��������� ������
int angle; // ���� �������� ������

FRAME frame;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Form1->Image1->Width = 0;
	Form1->Image1->Height = 0;

	SpeedButton1 -> GroupIndex = 1;
	SpeedButton1 -> Down = true;
	SpeedButton2 -> GroupIndex = 1;
	SpeedButton2 -> Down = false;
	SpeedButton3 -> GroupIndex = 1;
	SpeedButton3 -> Down = false;
	SpeedButton4 -> GroupIndex = 1;
	SpeedButton4 -> Down = false;
	SpeedButton5 -> GroupIndex = 1;
	SpeedButton5 -> Down = false;
	SpeedButton6 -> GroupIndex = 1;
	SpeedButton6 -> Down = false;
	SpeedButton7 -> GroupIndex = 1;
	SpeedButton7 -> Down = false;
	ComboBox1->ItemIndex = 0;
	FlowPanel2-> Visible = false;
	FlowPanel3->Visible = false;
	Panel3->Visible = false;
	Panel4->Visible = false;
    Panel2->Visible = false;

    Edit1 -> Text = "0";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::New1Click(TObject *Sender)
{
  int k;
	if(Form1->Save1->Enabled == true ||
	   (i != -1 || a != -1 || p != -1 || e != -1 || s != -1)){
	   Application->NormalizeTopMosts();
	   #ifdef _DELPHI_STRING_UNICODE
	   k = Application->MessageBox(L"��������� ������� �����������?", L"PlyPaint ����������", MB_YESNOCANCEL);
	   #else
	   k = Application->MessageBox("��������� ������� �����������?", "PlyPaint ����������", MB_YESNOCANCEL);
	   #endif
	   Application->RestoreTopMosts();

		if(k == 6){
			SavePictureDialog1->DefaultExt=".bmp";
			SavePictureDialog1->Filter="Bitmaps (*.bmp)|*.bmp";
			if (SavePictureDialog1->Execute()){
				Image1->Picture->Bitmap->SaveToFile(SavePictureDialog1->FileName);
			}
			Form2->Show();
			Form1->Enabled = false;
            vectors_cleaning(segments, arcs, polylines, circles, strings,  sequence);
			i = -1; a = -1; p = -1; e = -1; s = -1; point=0;
		}
		if(k == 7) {
			Form2->Show();
			Form1->Enabled = false;
            vectors_cleaning(segments, arcs, polylines, circles, strings,  sequence);
		i = -1; a = -1; p = -1; e = -1; s = -1; point=0;
		}

	}
	else{
		Form2->Show();
		Form1->Enabled = false;
		vectors_cleaning(segments, arcs, polylines, circles, strings, sequence);
		i = -1; a = -1; p = -1; e = -1; s = -1; point=0;
	}

	save = false;
	fileName = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
	Form1-> ScrollBox1 -> Width = Form1 -> Width-55; //-20
	Form1-> ScrollBox1 -> Height = Form1 -> Height-80; //-80
	Form1-> FlowPanel1 -> Height = Form1 -> Height-81;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	Label3 -> Caption = X;
	Label4 -> Caption = Y;

	//----�������--------
	if(SpeedButton3 -> Down == true){
	 if(point == 1){
		redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName); // �������������� ��� ��������
		segments.at(i).setColor(color);
		segments.at(i).setBold(bold);
		segments.at(i).create(X,Y,Image1); // ������������ ����� �������
	 }
	}
	//----������� end----

    //----����--------
	if(SpeedButton6 -> Down == true){
		if(point == 1){
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
			arcs.at(a).setColor(color);
			arcs.at(a).setBold(bold);
			arcs.at(a).create(X,Y);
		}
		if(point == 2){
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
			arcs.at(a).setColor(color);
			arcs.at(a).setBold(bold);
			arcs.at(a).create(X,Y,Image1);
		}
	}
	//----������� end----

	//----���������--------

	if(SpeedButton4 -> Down == true){
		if(point == 1){
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
			polylines.at(p).setColor(color);
			polylines.at(p).setBold(bold);
			polylines.at(p).create(X,Y);
		}
		if(point == 2){
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
			polylines.at(p).setColor(color);
            polylines.at(p).setBold(bold);
			polylines.at(p).create(X,Y,Image1);
		}
	}

	//----��������� end----

	//----����������--------

	if(SpeedButton5 -> Down == true){

	 if(point == 1){
		redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName); // �������������� ��� ��������
		circles.at(e).setColor(color);
		circles.at(e).setBold(bold);
		circles.at(e).create(X,Y,Image1); //
	 }
	}
	//----���������� end----

    //----��������� ������-------
	if(SpeedButton2 -> Down == true){

		if(point == 1){
			frame.x1 = X;
			frame.y1 = Y;
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
			Form1->Image1->Canvas->Pen->Style = psDot;
			Form1->Image1->Canvas->Pen->Color = clBlue;
			Form1->Image1->Canvas->Brush->Style = bsClear;
			Form1->Image1->Canvas->Pen->Width = 1;
			Form1->Image1->Canvas->Rectangle(frame.x,frame.y,frame.x1,frame.y1);
		}

	}
	//----��������� ������ end---
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseLeave(TObject *Sender)
{
	Label3 -> Caption = "";
	Label4 -> Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveAs1Click(TObject *Sender)
{
	SavePictureDialog1->DefaultExt=".bmp";
	SavePictureDialog1->Filter="Bitmaps (*.bmp)|*.bmp";
	if (SavePictureDialog1->Execute()){
		Image1->Picture->Bitmap->SaveToFile(SavePictureDialog1->FileName);
	}
	Form1->Close1->Enabled = true;
	save = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Close1Click(TObject *Sender)
{
   int k;
	if(Form1->Save1->Enabled == true ||
	   (i != -1 || a != -1 || p != -1 || e != -1 || s != -1)){
	   Application->NormalizeTopMosts();
	   #ifdef _DELPHI_STRING_UNICODE
	   k = Application->MessageBox(L"��������� ������� �����������?", L"PlyPaint ����������", MB_YESNOCANCEL);
	   #else
	   k = Application->MessageBox("��������� ������� �����������?", "PlyPaint ����������", MB_YESNOCANCEL);
	   #endif
	   Application->RestoreTopMosts();

		if(k == 6){
			SavePictureDialog1->DefaultExt=".bmp";
			SavePictureDialog1->Filter="Bitmaps (*.bmp)|*.bmp";
			if (SavePictureDialog1->Execute()){
				Image1->Picture->Bitmap->SaveToFile(SavePictureDialog1->FileName);
			}
			Form1->Image1->Picture->Bitmap->FreeImage();
			Form1->Image1->Picture->Bitmap = NULL;
			Form1->Image1->Width = 0;
			Form1->Image1->Height = 0;
			Form1->Save1->Enabled = false;
			Form1->SaveAs1->Enabled = false;
			Form1->Close1->Enabled = false;
            vectors_cleaning(segments, arcs, polylines, circles, strings,  sequence);
			i = -1; a = -1; p = -1; e = -1; s = -1; point=0;
		}
		if(k == 7) {
			Form1->Image1->Picture->Bitmap->FreeImage();
			Form1->Image1->Picture->Bitmap = NULL;
			Form1->Image1->Width = 0;
			Form1->Image1->Height = 0;
			Form1->Save1->Enabled = false;
			Form1->SaveAs1->Enabled = false;
			Form1->Close1->Enabled = false;
            vectors_cleaning(segments, arcs, polylines, circles, strings,  sequence);
		i = -1; a = -1; p = -1; e = -1; s = -1; point=0;
		}

	}
	else{
		Form1->Image1->Picture->Bitmap->FreeImage();
		Form1->Image1->Picture->Bitmap = NULL;
		Form1->Image1->Width = 0;
		Form1->Image1->Height = 0;
		Form1->Save1->Enabled = false;
		Form1->SaveAs1->Enabled = false;
		Form1->Close1->Enabled = false;
		vectors_cleaning(segments, arcs, polylines, circles, strings, sequence);
		i = -1; a = -1; p = -1; e = -1; s = -1; point=0;
		save = false;
		fileName = "";
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Save1Click(TObject *Sender)
{
	Image1->Picture->Bitmap->SaveToFile(SavePictureDialog1->FileName);
	Form1->Save1->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Open1Click(TObject *Sender)
{
	int k;
	if(Form1->Save1->Enabled == true ||
	   (i != -1 || a != -1 || p != -1 || e != -1 || s != -1)){
	   Application->NormalizeTopMosts();
	   #ifdef _DELPHI_STRING_UNICODE
	   k = Application->MessageBox(L"��������� ������� �����������?", L"PlyPaint ����������", MB_YESNOCANCEL);
	   #else
	   k = Application->MessageBox("��������� ������� �����������?", "PlyPaint ����������", MB_YESNOCANCEL);
	   #endif
	   Application->RestoreTopMosts();

		if(k == 6){
			SavePictureDialog1->DefaultExt=".bmp";
			SavePictureDialog1->Filter="Bitmaps (*.bmp)|*.bmp";
			if (SavePictureDialog1->Execute()){
				Image1->Picture->Bitmap->SaveToFile(SavePictureDialog1->FileName);
			}
			if(OpenPictureDialog1->Execute()){
			   Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
			}
			Form1->Enabled = true;
			Form1->SaveAs1->Enabled = true;
			Form1->Close1->Enabled = true;
            vectors_cleaning(segments, arcs, polylines, circles, strings,  sequence);
			i = -1; a = -1; p = -1; e = -1; s = -1; point=0;
		}
		if(k == 7) {
			if(OpenPictureDialog1->Execute()){
				Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
			}
			Form1->Enabled = true;
			Form1->SaveAs1->Enabled = true;
			Form1->Close1->Enabled = true;
            vectors_cleaning(segments, arcs, polylines, circles, strings,  sequence);
			i = -1; a = -1; p = -1; e = -1; s = -1; point=0;
		}
	}
	else{
		if(OpenPictureDialog1->Execute()){
			fileName = OpenPictureDialog1->FileName;
			Image1->Picture->LoadFromFile(fileName);
		}
		Form1->Enabled = true;
		Form1->SaveAs1->Enabled = true;
		Form1->Close1->Enabled = true;
		vectors_cleaning(segments, arcs, polylines, circles, strings,  sequence);
		i = -1; a = -1; p = -1; e = -1; s = -1; point=0;
	}

}
//---------------------------------------------------------------------------




void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	//----�������--------
	if(SpeedButton3 -> Down == true){
		if(point == 0){
			point = 1;
			i++;
			segments.emplace_back(Segment(color, bold, X, Y,sequence));
		}

		else if(point == 1){
			point = 0;
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
		}

		if(save == true)
			Form1->Save1->Enabled = true;
	}
	//----������� end----

	//----����--------
	if(SpeedButton6 -> Down == true){
		if(point == 0){
			point = 1;
			a++;
			arcs.emplace_back(MyArc(color, bold, X, Y, sequence));
		}

		else if(point == 1){
			point = 2;
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
			arcs.at(a).create(X,Y);
		}

		else if(point == 2){
			point = 0;
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
		}

		if(save == true)
			Form1->Save1->Enabled = true;
	}
	//----���� end----

	//----���������--------

	if(SpeedButton4 -> Down == true){

        if(SpeedButton9 -> Down == true) seg_arc = 1;
		if(SpeedButton10 -> Down == true) seg_arc = 2;

		if(point == 0){
			point = 1;
			p++;
			polylines.emplace_back(MyPolyline(color, bold, X, Y));
			sequence.emplace_back(3);
		}

		else if(point == 1){
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
			polylines.at(p).create(X,Y);
			if(seg_arc == 2) point = 2;
			else {
			   polylines.at(p).myAdd(color, bold, X, Y);
			}
			x2 = X;
			y2 = Y;
		}

		else if(point == 2){
			point = 1;
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
			polylines.at(p).myAdd(color, bold, x2, y2);
		}

		if(save == true)
			Form1->Save1->Enabled = true;

        if ( Button == mbRight )
		{
			point = 0;
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
		}
	}

	//----��������� end----

	//----����������--------
	if(SpeedButton5 -> Down == true){

		if(point == 0){
			point = 1;
			e++;
			circles.emplace_back(MyCircle(color, bold, X, Y,sequence));
		}

		else if(point == 1){
			point = 0;
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
		}

		if(save == true)
			Form1->Save1->Enabled = true;

	}
	//----���������� end----

	//----�����--------
	if(SpeedButton7 -> Down == true){

		  if(Edit2->Text!=""){
			text = Edit2->Text;
			angle = StrToInt(Edit1 -> Text);

            cf.Flags = CF_EFFECTS|CF_INITTOLOGFONTSTRUCT|CF_SCREENFONTS;
			cf.lpLogFont = &lf; //��������� �� LOGFONT
			cf.lStructSize = sizeof(CHOOSEFONT); //������ ���������

			lf.lfEscapement = angle;
			lf.lfOrientation = angle;
			hfont = CreateFontIndirect(cf.lpLogFont);
			text_color = static_cast<TColor>(cf.rgbColors);

			s++;
			strings.emplace_back(MyText());
			strings.at(s).createText(Image1, text, text_color, hfont, X, Y, sequence, lf);
		  }
	}
	//----����� end----

	//----��������� ������-------
	if(SpeedButton2 -> Down == true){
		 if(point == 0){
			remove_selection(segments, arcs, polylines, circles,strings, sequence,Image1,fileName);
			frame.x = X;
			frame.y = Y;
            frame.x1 = X;
			frame.y1 = Y;
			point = 1;
		}

		else if(point == 1){
			frame.x1 = X;
			frame.y1 = Y;
			point = 0;
			figures_choice(frame.x,frame.y,frame.x1,frame.y1, segments,arcs,polylines,circles,strings,sequence, Image1,fileName);
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
		}
	}
	//----��������� ������ end---

	//----���� ��������-------
	if(SpeedButton1 -> Down == true){
		 remove_selection(segments, arcs, polylines, circles,strings, sequence,Image1,fileName);
		 redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
	}
	//----���� �������� end---
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel2Click(TObject *Sender)
{
	ColorDialog1->Execute();
	color = ColorDialog1->Color;
	Panel2 -> Color = color;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
	remove_selection(segments, arcs, polylines, circles,strings, sequence,Image1,fileName);
	redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
	FlowPanel2->Visible = true;
	FlowPanel3->Visible = false;
	Panel3->Visible = false;
	Panel2->Visible = true;
	Panel4->Visible = false;
	point = 0;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FlowPanel2MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	const int SC_DRAGMOVE=61458;

	ReleaseCapture();
	((TControl *)Sender)->Perform(WM_SYSCOMMAND,SC_DRAGMOVE,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
	if(ComboBox1->ItemIndex == 0) bold = 1;
	if(ComboBox1->ItemIndex == 1) bold = 3;
	if(ComboBox1->ItemIndex == 2) bold = 5;
	if(ComboBox1->ItemIndex == 3) bold = 7;
	if(ComboBox1->ItemIndex == 4) bold = 9;
	if(ComboBox1->ItemIndex == 5) bold = 11;
	if(ComboBox1->ItemIndex == 6) bold = 13;
	if(ComboBox1->ItemIndex == 7) bold = 15;
	if(ComboBox1->ItemIndex == 8) bold = 17;
	if(ComboBox1->ItemIndex == 9) bold = 20;
	if(ComboBox1->ItemIndex == 10) bold = 23;
	if(ComboBox1->ItemIndex == 11) bold = 25;
	if(ComboBox1->ItemIndex == 12) bold = 27;
	if(ComboBox1->ItemIndex == 13) bold = 30;
	if(ComboBox1->ItemIndex == 14) bold = 35;
	if(ComboBox1->ItemIndex == 15) bold = 40;
	if(ComboBox1->ItemIndex == 16) bold = 45;
	if(ComboBox1->ItemIndex == 17) bold = 50;
	if(ComboBox1->ItemIndex == 18) bold = 55;
	if(ComboBox1->ItemIndex == 19) bold = 60;
	if(ComboBox1->ItemIndex == 20) bold = 65;
	if(ComboBox1->ItemIndex == 21) bold = 70;
	if(ComboBox1->ItemIndex == 22) bold = 80;
	if(ComboBox1->ItemIndex == 23) bold = 90;
	if(ComboBox1->ItemIndex == 24) bold = 100;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
    point = 0;
	FlowPanel2->Visible = true;
	FlowPanel3->Visible = false;
	Panel3->Visible = false;
	Panel2->Visible = true;
	Panel4->Visible = false;
    remove_selection(segments, arcs, polylines, circles,strings, sequence,Image1,fileName);
	redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
    remove_selection(segments, arcs, polylines, circles,strings, sequence,Image1,fileName);
	redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
	point = 0;
	FlowPanel2->Visible = true;
	FlowPanel3->Visible = true;
	Panel3->Visible = false;
	Panel2->Visible = true;
	Panel4->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FlowPanel3MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	 const int SC_DRAGMOVE=61458;

	ReleaseCapture();
	((TControl *)Sender)->Perform(WM_SYSCOMMAND,SC_DRAGMOVE,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
	point = 0;
	FlowPanel2->Visible = true;
	FlowPanel3->Visible = false;
	Panel3->Visible = false;
	Panel2->Visible = true;
	Panel4->Visible = false;
    remove_selection(segments, arcs, polylines, circles,strings, sequence,Image1,fileName);
	redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
	point = 0;
	FlowPanel2->Visible = true;
	FlowPanel3->Visible = false;
	Panel3->Visible = true;
	Panel2->Visible = false;
	Panel4->Visible = false;
	FlowPanel2-> Visible = false;

    remove_selection(segments, arcs, polylines, circles,strings, sequence,Image1,fileName);
	redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
cf.Flags = CF_EFFECTS|CF_INITTOLOGFONTSTRUCT|CF_SCREENFONTS;
cf.lpLogFont = &lf; //��������� �� LOGFONT
cf.lStructSize = sizeof(CHOOSEFONT); //������ ���������
angle = StrToInt(Edit1 -> Text);
if (ChooseFont(&cf)== true) {

	lf.lfEscapement = angle;
	lf.lfOrientation = angle;
	hfont = CreateFontIndirect(cf.lpLogFont);
	text_color = static_cast<TColor>(cf.rgbColors);
}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Panel3MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	const int SC_DRAGMOVE=61458;

	ReleaseCapture();
	((TControl *)Sender)->Perform(WM_SYSCOMMAND,SC_DRAGMOVE,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
	Panel4->Visible = true;
    point = 0;
	FlowPanel2->Visible = false;
	FlowPanel3->Visible = false;
	Panel3->Visible = false;
	Panel2->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int I = -1, A = -1, P = -1, E = -1, S = -1;
	for(int j=0; j< sequence.size(); j++) {

		if(sequence.at(j) == 1 && i > -1){
			I++;
			if(segments.at(I).getActiv()){
				segments.erase(segments.begin() + I);
				sequence.erase(sequence.begin() + j);
				i--;
				j--;
				I--;
			}
		}

		else if(sequence.at(j) == 2 && a > -1){
			A++;
			if(arcs.at(A).getActiv()){
				arcs.erase(arcs.begin() + A);
				sequence.erase(sequence.begin() + j);
				a--;
				j--;
				A--;
			}
		}

		else if(sequence.at(j) == 3 && p > -1){
			P++;
			if(polylines.at(P).getActiv()){
				polylines.erase(polylines.begin() + P);
				sequence.erase(sequence.begin() + j);
				p--;
				j--;
				P--;
			}
		}

		else if(sequence.at(j) == 4 && e > -1){
			E++;
			if(circles.at(E).getActiv()){
				circles.erase(circles.begin() + E);
				sequence.erase(sequence.begin() + j);
				e--;
				j--;
				E--;
			}
		}

		else if(sequence.at(j) == 5 && s > -1){
			S++;
			if(strings.at(S).getActiv()){
				strings.erase(strings.begin() + S);
				sequence.erase(sequence.begin() + j);
				s--;
				j--;
				S--;
			}
		}
	}
	redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	Panel4->Visible = false;
    point = 0;
	FlowPanel2->Visible = false;
	FlowPanel3->Visible = false;
	Panel3->Visible = false;
	Panel2->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Panel4MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
   const int SC_DRAGMOVE=61458;

	ReleaseCapture();
	((TControl *)Sender)->Perform(WM_SYSCOMMAND,SC_DRAGMOVE,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
    if ((Key < '0') || (Key > '9')) Key = NULL;
}
//---------------------------------------------------------------------------




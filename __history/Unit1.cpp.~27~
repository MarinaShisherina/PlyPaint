//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include <vector>
#include <cmath>
//#include <gdiplus.h>
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
		int x,y; // координаты первой точки отрезка
		int x1,y1; // координаты второй точки отрезка
		TColor color;
		int bold;
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

		Segment(TColor color, int bold, int x, int y){
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

		void create(int x1, int y1, TImage *Image1){
			this -> x1 = x1;
			this -> y1 = y1;
			this -> color = color;
			Form1->Image1->Canvas->Pen->Style = psSolid;
			Form1->Image1->Canvas->Pen->Color = color;
			Form1->Image1->Canvas->Pen->Width = bold;
			Image1->Canvas->MoveTo(x,y); // рисую линию
			Image1->Canvas->LineTo(x1,y1);
		}

		void create(TImage *Image1){
			Form1->Image1->Canvas->Pen->Style = psSolid;
			Form1->Image1->Canvas->Pen->Color = color;
			Form1->Image1->Canvas->Pen->Width = bold;
			Image1->Canvas->MoveTo(x,y); // рисую линию
			Image1->Canvas->LineTo(x1,y1);
		}

};

class MyArc : public GraphicElement{
	private:
		TPoint points[3]; // массив точек для построения кривой Безье
		TColor color;
		int bold;

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
			Image1->Canvas->MoveTo(points[0].x,points[0].y); //задание начальной точки
			Image1->Canvas->PolyBezierTo(points,2);//отрисовка точек

		}

		void setColor(TColor color){
			 this->color = color;
		}

        void setBold(int bold){
			 this->bold = bold;
		}

		void create(int x1, int y1){
			this -> points[2] = TPoint(x1,y1);
			this -> points[1] = TPoint(x1,y1);
		}

		void create(TImage *Image1){
			Form1->Image1->Canvas->Pen->Style = psSolid;
			Form1->Image1->Canvas->Pen->Color = color;
			Form1->Image1->Canvas->Pen->Width = bold;
			Image1->Canvas->MoveTo(points[0].x,points[0].y); //задание начальной точки
			Image1->Canvas->PolyBezierTo(points,2);//отрисовка точек
		}

};

class MyPolyline : public GraphicElement{
	 std::vector<MyArc> polyArcs;
     TColor color;
	 int bold;
	 int a = -1; //индекс для вектора элементов
	 //std::vector<int> sequenceP; // 1-отрезок, 2-дуга

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

		void create(int x, int y){
				  polyArcs.at(a).create(x, y);
		}

        void create(TImage *Image1){
			 //arcs.at(a).create(Image1);
			 for(MyArc myarc : polyArcs){
					myarc.create(Image1);
			 }
		}

};

class MyCircle : public GraphicElement{
	private:
		int x,y; // координаты центра окружности
		int x1,y1; // координаты точки на окружности
		TColor color;
		int bold;

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
			Form1->Image1->Canvas->Pen->Color = color;
			Form1->Image1->Canvas->Pen->Width = bold;
			unsigned radius = sqrt(pow(abs((x1-x)),2) + pow(abs((y1-y)),2));
			Image1->Canvas->MoveTo(x+radius,y);
			Image1->Canvas->AngleArc(x, y, radius, 0, 360);
		}

};

//--------Demo-----------------

class MyText : public GraphicElement{
	private:
		String text;
		TFont *font;
		Graphics::TBitmap* gBitmap = new Graphics::TBitmap;
		int x, y; //точка отрисовки bitmap на image

		//Form1->Image1->Picture->Bitmap -> Width = Form2->Edit1->Text.ToInt();
		//Form1->Image1->Picture->Bitmap -> Height = Form2->Edit2->Text.ToInt();
	public:
		MyText(TFont *font, int x, int y, std::vector<int>&sequence){
		   this -> font = font;
		   this -> x = x;
		   this -> y = y;

		   sequence.emplace_back(5);
		}

		void setFont(TFont *font){
			 this->font = font;
		}
		/*
		void createMyBitmap(TImage *Image1){
			gBitmap->Width  = 60;
			gBitmap->Height = 20;

			// this -> text = "|";

			gBitmap->Canvas->Brush->Style=bsClear;
			gBitmap->Canvas->Font = font;
			gBitmap->Canvas->TextOut(2,2,text.c_str());

			//gBitmap->Canvas->Pen->Style = psDot;
			//gBitmap->Canvas->Pen->Width = 1;
		   //	gBitmap->Canvas->Pen->Color = clBlue;
			gBitmap->Canvas->Brush->Style = bsClear;
			gBitmap->Canvas->Pen->Style = psClear;
			//gBitmap->Canvas->Rectangle(0, 0, gBitmap->Width, gBitmap->Height);
			Image1->Canvas->Draw(x,y,gBitmap);
			//Form1->Image1->Picture->Bitmap->FreeImage();
		}  */

		void createText(TImage *Image1, String s){

			this->text = s;

			//gBitmap-> FreeImage();
			//gBitmap = NULL;

			gBitmap->Canvas->Font = font;
			gBitmap->Width  = gBitmap->Canvas->TextWidth(text+2);
			gBitmap->Height = gBitmap->Canvas->TextHeight(text);

			//gBitmap->Width  = 40;
			//gBitmap->Height = 40;
			gBitmap->Canvas->Brush->Color = clWhite;
			////gBitmap->Canvas->Rectangle(0, 0, gBitmap->Width, gBitmap->Height);
			gBitmap->Canvas->Brush->Style=bsClear;
			gBitmap->Canvas->Font = font;
			//TLogFont f = font;
			//f.lfEscapement=90; //Угол вывода
			//Bitmap->Canvas->Font->Handle = CreateFontIndirect(&f);
			//gBitmap->Canvas->Font->Handle = lfEscapement=90;
			//font.nOrientation = 90;
			//gBitmap->Canvas->Font->Handle = nOrientation = 90
			gBitmap->Canvas->TextOut(2,2,text.c_str());

			//TGraphics g = CreateGraphics();
			//g.RotateTransform(45); // поворот на 45 градусов
			//g.DrawImageUnscaled(gBitmap, 0, 0);
			//f.lfEscapement=0;
			//gBitmap->Canvas->Font->Handle = CreateFontIndirect(&f);
			//gBitmap->Canvas->Pen->Style = psDot;
			//gBitmap->Canvas->Pen->Width = 1;
			//gBitmap->Canvas->Pen->Color = clBlue;
			gBitmap->Canvas->Pen->Style = psClear;
			gBitmap->Canvas->Brush->Style = bsClear;
			Image1->Canvas->Brush->Style = bsClear;
			Image1->Canvas->Pen->Style = psClear;
			gBitmap->Transparent = true;  // разрешаем прозрачность
			gBitmap->TransparentMode = tmFixed; // для прозрачности будем использовать фиксированное значение цвета
			gBitmap->TransparentColor = clWhite;
			//gBitmap->Canvas->RotateTransform(45);
			//gBitmap->Canvas->Rectangle(0, 0, gBitmap->Width, gBitmap->Height);
			Image1->Canvas->Draw(x,y,gBitmap);
			//Form1->Image1->Picture->Bitmap->FreeImage();
		}

		void createRect(int x1, int y1, TImage *Image1){

		}

		void create(int x, int y, TImage *Image1){

		}

		void create(TImage *Image1){
            gBitmap->Canvas->Font = font;
			gBitmap->Width  = gBitmap->Canvas->TextWidth(text+2);
			gBitmap->Height = gBitmap->Canvas->TextHeight(text);

			gBitmap->Canvas->Brush->Color = clWhite;
			gBitmap->Canvas->Brush->Style=bsClear;
			gBitmap->Canvas->Font = font;
			gBitmap->Canvas->TextOut(2,2,text.c_str());

			gBitmap->Canvas->Pen->Style = psClear;
			gBitmap->Canvas->Brush->Style = bsClear;
			Image1->Canvas->Brush->Style = bsClear;
			Image1->Canvas->Pen->Style = psClear;
			gBitmap->Transparent = true;  // разрешаем прозрачность
			gBitmap->TransparentMode = tmFixed; // для прозрачности будем использовать фиксированное значение цвета
			gBitmap->TransparentColor = clWhite;
			Image1->Canvas->Draw(x,y,gBitmap);

		}

};
//----------Demo----------------

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
		Form1->Image1->Canvas->Brush->Color=clWhite; // заливаю все белым
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
	/*for(Segment n : segments) //перерисовка отрезков
		n.create(Image1);*/
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

  // for(auto i = segments.begin(); i != segments.end(); segments.erase(i));
}

std::vector<Segment> segments;
std::vector<MyArc> arcs;
std::vector<MyPolyline> polylines;
std::vector<MyCircle> circles;
std::vector<MyText> strings; // массив с текстом
std::vector<int> sequence; // порядок элементов 1 - отрезокб 2 -дуга 3-полилиния 4-окружность 5-текст
TColor color; // активный цвет
TColor color2 = clWhite; // цвет заливки
int bold = 1; // активная толщина
int i = -1; // текущий индекс для вектора отрезков
int a = -1; // текущий индекс для вектора дуг
int p = -1; // текущий индекс для вектора полилиний
int e = -1; // текущий индекс для вектора полилиний
int s = -1; // текущий индекс для вектора текста
int point=0; // первая или вторая точка отрезка
int x,y; //начальная точка отрезка
bool save = false; // показывает сохранен ли уже файл
String fileName = "";
int seg_arc = 1;
int x2=0, y2=0; //конец предыдущего сегмента полилинии и начало нового
int click=0;
int seg_arc_pr = 1;
TFont *font;
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
	SpeedButton8 -> GroupIndex = 1;
	SpeedButton8 -> Down = false;
	ComboBox1->ItemIndex = 0;
	FlowPanel2-> Visible = false;
	FlowPanel3->Visible = false;
	Panel3->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::New1Click(TObject *Sender)
{
  int k;
	if(Form1->Save1->Enabled == true){
	   Application->NormalizeTopMosts();
	   #ifdef _DELPHI_STRING_UNICODE
	   k = Application->MessageBox(L"Сохранить текущее изображение?", L"PlyPaint Сохранение", MB_YESNOCANCEL);
	   #else
	   k = Application->MessageBox("Сохранить текущее изображение?", "PlyPaint Сохранение", MB_YESNOCANCEL);
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
		}
		if(k == 7) {
			Form2->Show();
			Form1->Enabled = false;
		}
	}
	else{
		Form2->Show();
		Form1->Enabled = false;
		vectors_cleaning(segments, arcs, polylines, circles, strings, sequence);   i=-1;
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

	//----отрезок--------
	if(SpeedButton3 -> Down == true){
	 if(point == 1){
		redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName); // перерисовываем все элементы
		segments.at(i).setColor(color);
		segments.at(i).setBold(bold);
		segments.at(i).create(X,Y,Image1); // дорисовываем новый отрезок
	 }
	}
	//----отрезок end----

    //----дуга--------
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
	//----отрезок end----

	//----полилиния--------

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

	//----полилиния end----

	//----окружность--------

	if(SpeedButton5 -> Down == true){

	 if(point == 1){
		redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName); // перерисовываем все элементы
		circles.at(e).setColor(color);
		circles.at(e).setBold(bold);
		circles.at(e).create(X,Y,Image1); //
	 }
	}
	//----окружность end----

    //----текст--------
	if(SpeedButton7 -> Down == true){

		if(point == 1){
		  // strings.at(s).createMyBitmap(X, Y, Image1);
		}

	}
	//----текст end----
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
	//Form1->Save1->Enabled = true;
	Form1->Close1->Enabled = true;
	save = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Close1Click(TObject *Sender)
{
   int k;
	if(Form1->Save1->Enabled == true){
	   Application->NormalizeTopMosts();
	   #ifdef _DELPHI_STRING_UNICODE
	   k = Application->MessageBox(L"Сохранить текущее изображение?", L"PlyPaint Сохранение", MB_YESNOCANCEL);
	   #else
	   k = Application->MessageBox("Сохранить текущее изображение?", "PlyPaint Сохранение", MB_YESNOCANCEL);
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
		}
		if(k == 7) {
			Form1->Image1->Picture->Bitmap->FreeImage();
			Form1->Image1->Picture->Bitmap = NULL;
			Form1->Image1->Width = 0;
			Form1->Image1->Height = 0;
			Form1->Save1->Enabled = false;
			Form1->SaveAs1->Enabled = false;
			Form1->Close1->Enabled = false;
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
		vectors_cleaning(segments, arcs, polylines, circles, strings, sequence);   i=-1;
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
	if(Form1->Save1->Enabled == true){
	   Application->NormalizeTopMosts();
	   #ifdef _DELPHI_STRING_UNICODE
	   k = Application->MessageBox(L"Сохранить текущее изображение?", L"PlyPaint Сохранение", MB_YESNOCANCEL);
	   #else
	   k = Application->MessageBox("Сохранить текущее изображение?", "PlyPaint Сохранение", MB_YESNOCANCEL);
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
		}
		if(k == 7) {
			if(OpenPictureDialog1->Execute()){
				Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
			}
			Form1->Enabled = true;
			Form1->SaveAs1->Enabled = true;
			Form1->Close1->Enabled = true;
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
		vectors_cleaning(segments, arcs, polylines, circles, strings,  sequence);   i=-1;
	}

}
//---------------------------------------------------------------------------




void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	//----отрезок--------
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
	//----отрезок end----

	//----дуга--------
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
	//----отрезок end----

	//----полилиния--------

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
			//polylines.at(p).create(X,Y,2);
		}

		if(save == true)
			Form1->Save1->Enabled = true;

        if ( Button == mbRight )
		{
			point = 0;
			redrawing(segments,arcs,polylines,circles,strings,sequence,Image1,fileName);
		}
	}

	//----полилиния end----

	//----окружность--------
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
	//----окружность end----

	//----текст--------
	if(SpeedButton7 -> Down == true){
	  /*
		if(point == 0){
			point = 1;
			s++;
			strings.emplace_back(MyText(font, X, Y, sequence));
			strings.at(s).createText(Image1, Edit2->Text);
		}

		else if(point == 1){
			point = 0;

		}

		if(save == true)
			Form1->Save1->Enabled = true;
		  */
		  if(Edit2->Text!=""){
			s++;
			strings.emplace_back(MyText(font, X, Y, sequence));
			strings.at(s).createText(Image1, Edit2->Text);
		  }
	}
	//----текст end----
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
	FlowPanel2->Visible = true;
	FlowPanel3->Visible = false;
	Panel3->Visible = false;
	Panel2->Visible = true;

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
	FlowPanel2->Visible = true;
	FlowPanel3->Visible = false;
	Panel3->Visible = false;
	Panel2->Visible = true;
	//FlowPanel4->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
	point = 0;
	FlowPanel2->Visible = true;
	FlowPanel3->Visible = true;
	Panel3->Visible = false;
	Panel2->Visible = true;
	//FlowPanel4->Visible = false;
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
	//FlowPanel4->Visible = false;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
	point = 0;
	FlowPanel2->Visible = true;
	FlowPanel3->Visible = false;
	Panel3->Visible = true;
	Panel2->Visible = false;
	FlowPanel2-> Visible = false;
    FontDialog1->Execute();
	font = FontDialog1->Font;
	//FlowPanel4->Visible = true;
  /*
	//Form1->DoubleBuffered = true;
  Canvas->Rectangle(0,0,ClientWidth,ClientHeight);
  char *s1 = "Привет,";
// String s1 = "Hellow,";
  String s2 = "Win32 API!";
  Canvas->Brush->Style = bsClear;
  HDC hdc = Canvas->Handle;

  LOGFONT lf;
  ZeroMemory(&lf, sizeof(LOGFONT));
  lf.lfHeight = 20; // высота шрифта
  lf.lfWidth = 20; // ширина символов
  lf.lfWeight = 500; // толщина, "жирность" шрифта
  lf.lfItalic = 1; // если это поле не равно 0, шрифт будет курсивный
  lf.lfUnderline = 0; // если это поле не равно 0, шрифт будет подчёркнутый
  lf.lfEscapement = 0; // 0; //шрифт без поворота
  lf.lfCharSet = DEFAULT_CHARSET;
  lf.lfPitchAndFamily = FIXED_PITCH; // DEFAULT_PITCH;
  //wcscpy(lf.lfFaceName, _T("Courier New")); //    #include <tchar.h>
 //wcscpy(lf.lfFaceName, UnicodeString("Courier New").c_str()); // "Times New Roman"
// wcscpy(lf.lfFaceName, String("Courier New").c_str()); // "Times New Roman"
 //strcpy(lf.lfFaceName, "Times New Roman");
  Image1->Canvas->Font->Handle = CreateFontIndirect(&lf);
//  Canvas->Brush->Color = clBlue;
Image1->Canvas->Brush->Style=bsClear;
  Image1->Canvas->FillRect(Canvas->ClipRect);
//
  SetTextAlign(hdc, TA_LEFT); // |TA_BASELINE|TA_UPDATECP);
  int WidthOfString = Canvas->TextWidth(s1);
  int HeightOfString = Canvas->TextHeight(s1);
  int WidthOfString2 = Canvas->TextWidth(s2);
  int HeightOfString2 = Canvas->TextHeight(s2);
  SetTextColor(hdc, 0xff0000); //
//  SetBkColor(hdc, 0xff00ff); // RGB(255,0,255)); //второй параметр задаёт цвет
  SetBkMode(hdc, 0); // прозрачный фон
//
  Image1->Canvas->Brush->Style=bsClear;
  Image1->Canvas->Font = font;
  Image1->Canvas->TextOut(50,
		  50, // отступ строк
		  s2.c_str());

		  */

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
   //	FontDialog1->Execute();
	//font = FontDialog1->Font;
	//LOGFONT f;
   //	f = FontDialog1->ChooseFont();
   //LOGFONT f;
  // CHOOSEFONT ch;
   //FontDialog1->Execute();
  // ChooseFont();
  //CHOOSEFONT fch;
   HWND hwndParent; HFONT Font1; LOGFONT Logfont;
  static LOGFONT lfResult;
    ZeroMemory(&lfResult, sizeof(LOGFONT));
	lfResult=Logfont;

    CHOOSEFONT cf;
    ZeroMemory(&cf, sizeof(CHOOSEFONT));
    cf.lStructSize  = sizeof(CHOOSEFONT);
    cf.hDC          = GetDC(hwndParent);
    cf.Flags        = CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT;
	cf.lpLogFont    = Logfont;
    cf.nFontType    = SCREEN_FONTTYPE;
    cf.hwndOwner    = hwndParent;

    if(IDOK==ChooseFont(&cf) )
    {
		DeleteObject(Font1);
		Font1=CreateFontIndirect(Logfont);
		if(!Font1)
			lfResult=Logfont;
        if(hwndParent)
            InvalidateRect(hwndParent, NULL, TRUE);
    }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	 // s++;
	  //strings.emplace_back(MyText(font, X, Y, sequence));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
	 //strings.at(s).createText(Image1, Edit2->Text);
}
//---------------------------------------------------------------------------


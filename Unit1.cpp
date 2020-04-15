//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include <vector>
#include <cmath>
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
			Image1->Canvas->MoveTo(x,y); // ����� �����
			Image1->Canvas->LineTo(x1,y1);
		}

		void create(TImage *Image1){
			Form1->Image1->Canvas->Pen->Style = psSolid;
			Form1->Image1->Canvas->Pen->Color = color;
			Form1->Image1->Canvas->Pen->Width = bold;
			Image1->Canvas->MoveTo(x,y); // ����� �����
			Image1->Canvas->LineTo(x1,y1);
		}

};

class MyArc : public GraphicElement{
	private:
		TPoint points[3]; // ������ ����� ��� ���������� ������ �����
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
			Image1->Canvas->MoveTo(points[0].x,points[0].y); //������� ��������� �����
			Image1->Canvas->PolyBezierTo(points,2);//��������� �����

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
			Image1->Canvas->MoveTo(points[0].x,points[0].y); //������� ��������� �����
			Image1->Canvas->PolyBezierTo(points,2);//��������� �����
		}

};

class MyPolyline : public GraphicElement{
	 std::vector<MyArc> polyArcs;
     TColor color;
	 int bold;
	 int a = -1; //������ ��� ������� ���������
	 //std::vector<int> sequenceP; // 1-�������, 2-����

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
		int x,y; // ���������� ������ ����������
		int x1,y1; // ���������� ����� �� ����������
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
//-------------------------------------------------
void redrawing(const std::vector<Segment>&segments,
			   const std::vector<MyArc>&arcs,
			   const std::vector<MyPolyline>&polylines,
			   const std::vector<MyCircle>&circles,
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

	int i = 0, a = 0, p = 0, e = 0;
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
	}
	/*for(Segment n : segments) //����������� ��������
		n.create(Image1);*/
}

void vectors_cleaning(std::vector<Segment>&segments){
   segments.clear();

  // for(auto i = segments.begin(); i != segments.end(); segments.erase(i));
}

std::vector<Segment> segments;
std::vector<MyArc> arcs;
std::vector<MyPolyline> polylines;
std::vector<MyCircle> circles;
std::vector<int> sequence; // ������� ��������� 1 - �������� 2 -���� 3-���������
TColor color; // �������� ����
TColor color2 = clWhite; // ���� �������
int bold = 1; // �������� �������
int i = -1; // ������� ������ ��� ������� ��������
int a = -1; // ������� ������ ��� ������� ���
int p = -1; // ������� ������ ��� ������� ���������
int e = -1; // ������� ������ ��� ������� ���������
int point=0; // ������ ��� ������ ����� �������
int x,y; //��������� ����� �������
bool save = false; // ���������� �������� �� ��� ����
String fileName = "";
int seg_arc = 1;
int x2=0, y2=0; //����� ����������� �������� ��������� � ������ ������
int click=0;
int seg_arc_pr = 1;
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
}
//---------------------------------------------------------------------------
void __fastcall TForm1::New1Click(TObject *Sender)
{
  int k;
	if(Form1->Save1->Enabled == true){
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
		}
		if(k == 7) {
			Form2->Show();
			Form1->Enabled = false;
		}
	}
	else{
		Form2->Show();
		Form1->Enabled = false;
		vectors_cleaning(segments);   i=-1;
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
		redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName); // �������������� ��� ��������
		segments.at(i).setColor(color);
		segments.at(i).setBold(bold);
		segments.at(i).create(X,Y,Image1); // ������������ ����� �������
	 }
	}
	//----������� end----

    //----����--------
	if(SpeedButton6 -> Down == true){
		if(point == 1){
			redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName);
			arcs.at(a).setColor(color);
			arcs.at(a).setBold(bold);
			arcs.at(a).create(X,Y);
		}
		if(point == 2){
			redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName);
			arcs.at(a).setColor(color);
			arcs.at(a).setBold(bold);
			arcs.at(a).create(X,Y,Image1);
		}
	}
	//----������� end----

	//----���������--------

	if(SpeedButton4 -> Down == true){
		if(point == 1){
			redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName);
			polylines.at(p).setColor(color);
			polylines.at(p).setBold(bold);
			polylines.at(p).create(X,Y);
		}
		if(point == 2){
			redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName);
			polylines.at(p).setColor(color);
            polylines.at(p).setBold(bold);
			polylines.at(p).create(X,Y,Image1);
		}
	}

	//----��������� end----

	//----����������--------

	if(SpeedButton5 -> Down == true){

	 if(point == 1){
		redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName); // �������������� ��� ��������
		circles.at(e).setColor(color);
		circles.at(e).setBold(bold);
		circles.at(e).create(X,Y,Image1); //
	 }
	}
	//----���������� end----
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
		vectors_cleaning(segments);   i=-1;
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
		vectors_cleaning(segments);   i=-1;
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
			redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName);
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
			redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName);
			arcs.at(a).create(X,Y);
		}

		else if(point == 2){
			point = 0;
			redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName);
		}

		if(save == true)
			Form1->Save1->Enabled = true;
	}
	//----������� end----

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
			redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName);
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
			redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName);
			polylines.at(p).myAdd(color, bold, x2, y2);
			//polylines.at(p).create(X,Y,2);
		}

		if(save == true)
			Form1->Save1->Enabled = true;

        if ( Button == mbRight )
		{
			point = 0;
			redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName);
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
			redrawing(segments,arcs,polylines,circles,sequence,Image1,fileName);
		}

		if(save == true)
			Form1->Save1->Enabled = true;

	}
	//----���������� end----
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
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
	point = 0;
	FlowPanel2->Visible = true;
	FlowPanel3->Visible = true;
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
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
	Form2->Edit1->Text = 600;
	Form2->Edit2->Text = 600;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	 Form1->Enabled = true;
	 Form1->SaveAs1->Enabled = true;
	 Form1->Close1->Enabled = true;

	 //-- очистка image ---
	 Form1->Image1->Picture->Bitmap->FreeImage();
	 Form1->Image1->Picture->Bitmap = NULL;
	 //--------------------
	 Form1->Image1->Picture->Bitmap -> Width = Form2->Edit1->Text.ToInt();
	 Form1->Image1->Picture->Bitmap -> Height = Form2->Edit2->Text.ToInt();
	 Form1->Image1->Canvas->Pen->Style = psSolid;
	 Form1->Image1->Canvas->Pen->Width = 1;
	 Form1->Image1->Canvas->Pen->Color = clWindowFrame;
	 Form1->Image1->Canvas->Brush->Color=clWhite;
	 Form1->Image1->Canvas->Rectangle(0,0,Form2->Edit1->Text.ToInt(), Form2->Edit2->Text.ToInt());
	 Form1->Image1->Picture->Bitmap->FreeImage();
	 Form1-> ScrollBox1 -> Width = Form1 -> Width-55;
	 Form1-> ScrollBox1 -> Height = Form1 -> Height-80;
	 Form1->Label6->Caption = IntToStr(Form1->Image1->Width)+ "x" + IntToStr(Form1->Image1->Height);

	 Form2->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
		AnsiString Ts = "0123456789\b";
		char Tr[] = { '\0','0','1','2','3','4','5','6','7','8','9','\b' };
		Key = Tr[Ts.Pos(Key)];
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Edit2KeyPress(TObject *Sender, System::WideChar &Key)
{
     AnsiString Ts = "0123456789\b";
	 char Tr[] = { '\0','0','1','2','3','4','5','6','7','8','9','\b' };
	 Key = Tr[Ts.Pos(Key)];
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
	 Form1->Enabled = true;
}
//---------------------------------------------------------------------------

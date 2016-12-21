unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls;

type
  Tsmsdp = class(TForm)
    Label1: TLabel;
    Edit1: TEdit;
    Label2: TLabel;
    GroupBox1: TGroupBox;
    Label3: TLabel;
    Button1: TButton;
    Button2: TButton;
    GroupBox2: TGroupBox;
    Label4: TLabel;
    Edit3: TEdit;
    Label5: TLabel;
    Button3: TButton;
    GroupBox3: TGroupBox;
    Label8: TLabel;
    Button4: TButton;
    Button5: TButton;
    GroupBox4: TGroupBox;
    Button6: TButton;
    GroupBox5: TGroupBox;
    Label9: TLabel;
    Edit5: TEdit;
    Button7: TButton;
    Button8: TButton;
    Timer1: TTimer;
    Memo1: TMemo;
    Memo2: TMemo;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button8Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
  function Sms_Connection(CopyRight:pchar;Com_Port,Com_BaudRate:integer;var Mobile_Type,CopyRightToCOM:PChar):integer;stdcall;external 'sms.dll';
  function Sms_Send(Sms_TelNum:string;Sms_Text:string):integer;stdcall;external 'sms.dll';
  Function Sms_Receive(Sms_Type:string;var Sms_Text:PChar):integer;stdcall;external 'sms.dll';
  function Sms_Delete(Sms_Index:string):integer;stdcall;external 'sms.dll';
  function Sms_AutoFlag :integer;stdcall;external 'sms.dll';
  function Sms_NewFlag :integer;stdcall;external 'sms.dll';
  function Sms_Disconnection :integer;stdcall;external 'sms.dll';
var
  smsdp: Tsmsdp;

implementation

{$R *.dfm}

procedure Tsmsdp.Button1Click(Sender: TObject);
var
Mobile_Type:pchar;
CopyRight:pchar;
CopyRightToCOM:pchar;
begin
CopyRight:=PChar('//上海迅赛信息技术有限公司,网址www.xunsai.com//');
if Sms_Connection(CopyRight,StrToInt(Edit1.text),9600,Mobile_Type,CopyRightToCOM)<>0 then
   begin
     Label3.Caption:='连接成功,芯片为:'+Mobile_Type+'!';
   end
 else
   Label3.Caption:='连接失败!'
end;

procedure Tsmsdp.Button2Click(Sender: TObject);
var
DisReult:integer;
begin
Sms_Disconnection;
Label3.Caption:='已断开!';
end;

procedure Tsmsdp.Button3Click(Sender: TObject);
begin
if Sms_Send(edit3.Text,Memo1.lines.text)=1 then
   begin
     showmessage('发送成功!');
   end
 else
   showmessage('发送失败!')
end;

procedure Tsmsdp.Button6Click(Sender: TObject);
var
StrSmsReceive:pchar;
RecReult:integer;
begin
RecReult:=Sms_Receive('4',StrSmsReceive);
Memo2.lines.text:=StrSmsReceive;
end;

procedure Tsmsdp.Button7Click(Sender: TObject);
var
DelReult:integer;
begin
DelReult:=Sms_Delete(Edit5.text)
end;

procedure Tsmsdp.Button4Click(Sender: TObject);
begin
Timer1.enabled:=True;
end;

procedure Tsmsdp.Button5Click(Sender: TObject);
begin
Timer1.enabled:=False;
end;

procedure Tsmsdp.Timer1Timer(Sender: TObject);
begin
if Sms_NewFlag()=1 then
   begin
     Label8.Caption:='有新短信,请查收!';
   end
 else
   Label8.Caption:='无短信!';
end;
procedure Tsmsdp.Button8Click(Sender: TObject);
begin
close;
end;

end.





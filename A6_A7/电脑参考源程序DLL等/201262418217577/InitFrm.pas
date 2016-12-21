unit InitFrm;

interface

uses
  Classes, Controls, Forms, ExtCtrls, jpeg, LyComm, Variants, SysUtils;

type
  TfrmInit = class(TForm)
    imgLogo: TImage;
    tmRun: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure tmRunTimer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmInit: TfrmInit;
  IsOpen: Boolean;

implementation

uses MainFrm, MyFunction;

{$R *.dfm}

procedure TfrmInit.FormCreate(Sender: TObject);
begin
  tmRun.Enabled:= False;
  tmRun.Interval:= 0;
  imgLogo.AutoSize:= True;
  Width:= imgLogo.Width;
  Height:= imgLogo.Height;
  Left:= (Screen.Width - Width) div 2;
  Top:= (Screen.Height - Height)div 2;
  BorderStyle:= bsNone;
  tmRun.Enabled:= True;
  tmRun.Interval:= 300;
end;

procedure TfrmInit.tmRunTimer(Sender: TObject);
var
  nPort: Integer;
  hSerialPort: Integer;
begin
  tmRun.Enabled:= False;
  tmRun.Interval:= 0;
  nPort:= StrToIntDef(GetSetting('SMS', 'PORT', '3'), 3);
  hSerialPort:= OpenComm(nPort);
  IsOpen:= hSerialPort <> -1;
  if IsOpen then
  begin
    {这里仅供测试}
    CloseComm(hSerialPort);
    Hide;
    frmMain:= TfrmMain.Create(Application);
    frmMain.Show;
    Free;
  end
  else
  begin
    MsgBox('端口不能打开!');
    Application.Terminate;
    Halt;
  end;
end;

end.

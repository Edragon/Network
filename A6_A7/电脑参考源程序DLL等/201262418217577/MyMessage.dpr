program MyMessage;

uses
  Forms,
  MainFrm in 'MainFrm.pas' {frmMain},
  InitFrm in 'InitFrm.pas' {frmInit},
  MyFunction in 'MyFunction.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TfrmInit, frmInit);
  Application.Run;
end.

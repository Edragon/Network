program Project1;

{%File 'sms'}

uses
  Forms,
  Unit1 in 'Unit1.pas' {smsdp};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(Tsmsdp, smsdp);
  Application.Run;
end.

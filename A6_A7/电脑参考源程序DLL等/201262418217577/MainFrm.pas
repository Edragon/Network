unit MainFrm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, LyComm, StdCtrls, IdBaseComponent, IdComponent,
  IdTCPServer, IdCustomHTTPServer, IdHTTPServer, ComCtrls, jpeg, XPMan, ADODB, DB;

type
  MySms = class(TThread)
  protected
  public
    procedure Execute; Override;
    destructor Destroy; override;
  end;

  TfrmMain = class(TForm)
    tmRun: TTimer;
    Info: TMemo;
    tmServer: TTimer;
    StatusBar1: TStatusBar;
    imgTop: TImage;
    shaTop: TShape;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormCreate(Sender: TObject);
    procedure tmRunTimer(Sender: TObject);
    procedure tmServerTimer(Sender: TObject);
    procedure InfoChange(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
  function GetOneSms(nIndex: Integer): Boolean;
  function DelOneSms(nIndex: Integer): Boolean;
  function SendOneSms(UserTel, CenterTel, Msg: String):Boolean;
var
  frmMain: TfrmMain;
  hPort:   Integer;
  SmsCenterNO: WideString; {�������ĺ���}
  IsRunNextOnce: Boolean; {�Ƿ������һ�ε���ѯ}
  MyConn: TADOConnection;
implementation

uses MyFunction;

{$R *.dfm}

procedure TfrmMain.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  {�ر��豸}
  CloseComm(hPort);
  {�ͷ����ݿ�����}
  FreeAndNil(MyConn);
  {�˳�����}
  Application.Terminate;
  Halt;
end;

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  tmRun.Enabled:= False;
  tmRun.Interval:= 0;
  tmServer.Enabled:= False;
  tmServer.Interval:= 0;
  hPort:= -1;
  Color:= clWhite;
  imgTop.Left:= 1;
  imgTop.Top:= 1;
  shaTop.Left:= 0;
  shaTop.Top:= 0;
  shaTop.Height:= imgTop.Height + 2;
  HorzScrollBar.Visible:= False;
  VertScrollBar.Visible:= False;
  BorderStyle:= bsSizeable;
  Left:= (Screen.Width - Width) div 2;
  Top:= (Screen.Height - Height)div 2;
  tmRun.Enabled:= True;
  tmRun.Interval:= 500;
end;

procedure TfrmMain.tmRunTimer(Sender: TObject);
var
  nPort: Integer;
  strBuf, strIniTmp: String;
  nBegin, nEnd: Integer;
  strLink: String;{���ݿ������ַ���}
begin
  tmRun.Enabled:= False;
  tmRun.Interval:= 0;
  strLink:= GetSetting('SMS', 'MYLINK');
  strLink:= Trim(StringReplace(strLink, '{APP}', ExtractFilePath(ParamStr(0)), [rfReplaceAll]));
  if strLink = '' then
  begin
    Info.Lines.Add(VarToStr(Now) + '���ݿ��������ô���!');
    Exit;
  end;

  try
    MyConn:= TADOConnection.Create(nil);
    MyConn.ConnectionString:= strLink;
    MyConn.CursorLocation:= clUseClient;
    MyConn.ConnectionTimeout:= 30;
    MyConn.Open;
    Info.Lines.Add(VarToStr(Now) + vbTab + '���ݿ����ӳɹ�!');
  except
    on E: Exception do
    begin
      FreeAndNil(MyConn);
      Info.Lines.Add(VarToStr(Now) + vbTab + '���ݿ�����ʧ��!');
      Info.Lines.Add(VarToStr(Now) + vbTab + e.Message);
      Exit;
    end;
  end;
  nPort:= StrToIntDef(GetSetting('SMS', 'PORT', '3'), 3);
  hPort:= OpenComm(nPort);
  if hPort <> -1 then
  begin
    Info.Lines.Add(VarToStr(Now) + vbTab + '����è���ں�:COM' + VarToStr(nPort));
    Caption:= '���Ŷ˿ڴ�';
  end
  else
  begin
    Caption:= '���Ŷ˿ڹر�';
  end;
  strBuf:= SendComm(hPort, 'AT+CSCS="GSM"' + vbCr, 3000);
  if Pos('TIMEOUT', strBuf) > 0 then
  begin
    Info.Lines.Add(VarToStr(Now) + vbTab + '��ʼ��ʧ�ܣ�����SIM���Ƿ����!');
    Exit;
  end;
  if Pos('ERROR', strBuf) > 0 then
  begin
    Info.Lines.Add(VarToStr(Now) + vbTab + '��ʼ��ʧ�ܣ�����SIM���Ӵ��Ƿ�����!');
    Exit;
  end;
  if Pos('OK', strBuf) > 0 then
  begin
    strBuf:= SendComm(hPort, 'AT+CSCA?' + vbCr, 3000);
    nBegin:= Pos('"', strBuf);
    strBuf:= Copy(strBuf, nBegin + 2, 100);
    nEnd:=   Pos('"', strBuf);
    strBuf:= Copy(strBuf, 1, nEnd - 1);
  end;
  strIniTmp:= Trim(GetSetting('SMS', 'SMSCENTERNO'));
  if strIniTmp <> '' then
  begin
    SmsCenterNO:= strIniTmp;
  end
  else
  begin
    SmsCenterNO:= strBuf;
  end;
  Info.Lines.Add(VarToStr(Now) + vbTab + '�������ĺ���:' + SmsCenterNO);
  Info.Lines.Add(VarToStr(Now) + vbTab + '����è��ʼ���ɹ�!');
  tmServer.Interval:= 500;
  tmServer.Enabled:= True;
end;

procedure TfrmMain.tmServerTimer(Sender: TObject);
begin
  tmServer.Enabled:= False;
  tmServer.Interval:= 0;
  IsRunNextOnce:= False;
  StatusBar1.Panels[1].Text:= VarToStr(Now);
  MySms.Create(False);
end;


destructor MySms.Destroy;
begin
  inherited;
end;

procedure MySms.Execute;
  function GetMySms(): Boolean;
  var
    strBuf, strTmp:       WideString;
    nBegin, nEnd:         Integer;
    nNumShortMessage, I:  Integer;
  begin
    Result:= True;
    {���ն��ŵı���}
    strBuf:= SendComm(hPort, 'AT+CMGF=0' + vbCr, 3000);

    {��ȡ��������}
    strBuf:= SendComm(hPort, 'AT+CPMS="SM"' + vbCr, 3000);
    if Pos('OK', strBuf) > 0 then
    begin
      nBegin:= Pos('+CPMS:', strBuf) + 6;
      nEnd:=   Pos(',', strBuf);
      strTmp:= Trim(Copy(strBuf, nBegin, nEnd - nBegin));
      nNumShortMessage:= StrToIntDef(strTmp, 0);
    end
    else
    Begin
      nNumShortMessage:= 0;
    end;
    if nNumShortMessage = 0 then
    begin
      frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + 'SIM�����޶���!');
      Exit;
    end;
    I:= 0;
    while I <= nNumShortMessage do
    begin
      frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '��ȡ�豸������Ϊ[' + VarToStr(I) + ']����......');
      GetOneSms(I);
      Application.ProcessMessages;
      I:= I + 1;
    end;
  end;
//------------------------------------------------------------------------------
  function MySendSms(Conn: TADOConnection): Boolean;
  var
    strErrinfo: WideString;
    strMsg:     WideString;
    rsTmp:      TADOQuery;
    strTelNO:   WideString;
    nID:        Integer;
  begin
    Result:= False;
    rsTmp:= ExecuteQuery('SELECT TOP 5 * FROM [SEND] WHERE [SIGN]=0', Conn, strErrinfo);
    try
      if strErrinfo <> '' then
      begin
        frmMain.Info.Lines.Add(strErrinfo);
        Exit;
      end;
      if rsTmp = nil then
      begin
        Exit;
      end;
      while Not rsTmp.Eof do
      begin
        nID:= rsTmp.FieldByName('ID').AsInteger;
        strTelNO:= Trim(rsTmp.FieldByName('TELNO').AsString);
        strMsg:= Trim(rsTmp.FieldByName('MSG').AsString);
        if (nID <> 0) OR (strTelNO <> '') OR (strMsg <> '') then
        begin
          frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '���ڷ��Ͷ���......');
          SendOneSms(strTelNO, SmsCenterNO, strMsg);
          frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '���Ͷ������.');
          ExecuteSQL('UPDATE [SEND] SET [SIGN]=1 WHERE ID=:ID', [nID], Conn, strErrinfo);
          if strErrinfo <> '' then
          begin
            frmMain.Info.Lines.Add(strErrinfo);
          end;
        end;
        rsTmp.Next;
      end;
    finally
      rsTmp.Free;
    end;
  end;
begin
  { Place thread code here }
  FreeOnTerminate:= True;
  {GET}
  try
    if hPort = -1 then
    begin
      frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '����èδ��ʼ��!');
      Exit;
    end;
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '��ȡSIM���ڶ���......');
    GetMySms();
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '��ȡ��Ҫ���͵Ķ���......');
    MySendSms(MyConn);
  finally
    frmMain.tmServer.Enabled:= True;
    frmMain.tmServer.Interval:= 500;
  end;
end;

//*************************************************
//*
//*  ����һ������
//*
//*************************************************
function GetOneSms(nIndex: Integer): Boolean;
var
  strBuf, strTmp:   WideString;
  nBegin, nEnd:     Integer;
//------------------------------------------------------------------------------
  strSCA:           String;  {������������}
  scaLen:           Integer; {�������ĳ���}
  TelLen:           Integer; {���ͺ��볤��}
  MsgType:          String;  {��Ϣ����}
  SmsType:          String;  {}
  MsgTime:          String;  {���ŷ���ʱ��}
  TelNo:            String;  {�ֻ�����}
  MsgLen:           Integer; {��Ϣ����}
  MsgContent:       String;  {���ն�������}
//------------------------------------------------------------------------------
  strSQL: String;
label 100;
begin
  if hPort = -1 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '����èδ��ʼ��!');
    Result:= False;
    Exit;
  end;
  Result:= True;
  100:
  strBuf:= '';
  strBuf:= SendComm(hPort, 'AT+CMGR=' + IntToStr(nIndex) + vbCr, 3000);
  {���ſ��ܱ�ɾ��}
  if Pos('ERROR', strBuf) > 0 then
  begin
    Result:= False;
    Exit;
  end;
  if Pos('TIMEOUT', strBuf) > 0 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '���ն��ų�ʱ!');
    Result:= False;
    Exit;
  end;
  if Pos('CMGR:', strBuf) < 1 then
  begin
    goto 100;
  end
  else
  begin
    nBegin:=  Pos('08', strBuf);
    strBuf:=  Copy(strBuf, nBegin, 500);
    nEnd:=    Pos(vbCrLf, strBuf);
    if nEnd = 0 then
    begin
      strTmp:=  strBuf;
    end
    else
    begin
      strTmp:=  Copy(strBuf, 1, nEnd - 1);
    end;


    {���ĺų���}
    scaLen:= StrToIntDef('$' + Copy(strTmp, 1, 2), 0);
    strSCA:= Copy(strTmp, 5, (scaLen - 1) * 2);
    strSCA:= PDUToPhoneNumber(strSCA);

    {����ʱ��}
    MsgType:= Copy(strTmp, 19, 2);
    If (MsgType = '06') Or (MsgType = '02') Or (MsgType = '01')Then
    begin
      //״̬����
      MsgTime:= '';
    end
    Else
    begin
      {��ȡ��������֮��+2������}
      MsgTime:=  Copy(strTmp, 3 + scaLen * 2 + 2, Length(strTmp) - (scaLen * 2));
      {��ȡ���ͷ����볤��}
      TelLen:=  StrToIntDef('$' + Copy(MsgTime, 1, 2), 0);
      {�жϳ����Ƿ�ż��}
      If TelLen Mod 2 <> 0 Then
      begin
         TelLen:= TelLen + 1;
      end;
      MsgTime:= Copy(MsgTime, TelLen + 9, Length(MsgTime) - TelLen + 2);
      MsgTime:= Copy(MsgTime, 1, 14);
      MsgTime:= VarToStr(PDUToDate(MsgTime));

      {��ȡ�����˵��ֻ�����}
      TelNo:= Copy(strTmp, scaLen * 2 + 3, Length(strTmp) - (scaLen * 2 + 2));
      If (MsgType = '06') Or (MsgType = '02') or (MsgType = '01') Then
      begin
        TelNo:= Copy(TelNo, 5, Length(TelNo) - 2);
      end
      Else
      begin
        TelNo:= Copy(TelNo, 3, Length(TelNo) - 2);
      End;
      TelNo:= Copy(TelNo, 5, TelLen);
      TelNo:= PDUToPhoneNumber(TelNo);

      {��ȡ��������}
      If TelLen Mod 2 = 0 Then
      begin
        smsType:= Copy(strTmp, (scaLen + 6) * 2 + TelLen - 1, 2);
      end
      else
      begin
        smsType:= Copy(strTmp, (scaLen + 6) * 2 + TelLen, 2);
      end;

      {��Ϣ�������ݿ�ʼλ��}
      nBegin:= (scaLen + 6 + 7) * 2 + TelLen + 2;
      If nBegin Mod 2 = 0 Then
      begin
        nBegin:= nBegin - 1;
      end;
      MsgLen:= StrToIntDef('$' + Copy(strBuf, nBegin, 2), 0);
      MsgContent:= '';
      if SmsType = TP_DCS_UCS2 then //UCS2����
      begin
        MsgContent:= Copy(strBuf, nBegin + 2, MsgLen * 2);
        MsgContent:= DecodeUCS2(MsgContent);
      end;
      if SmsType = TP_DCS_7BIT then//7bit ����
      begin
        MsgLen:= MsgLen - (MsgLen div 8);
        MsgContent:= Copy(strBuf, nBegin + 2, MsgLen * 2);
        MsgContent:= Decode7bit(MsgContent);
      end;
      strSQL:= 'INSERT INTO [GET]([TELNO], [MSG], [INDEX])VALUES(:TELNO, :MSG, :INDEX)';
      if ExecuteSQL(strSQL, [TelNo, MsgContent, nIndex], MyConn, strTmp) then
      begin
        frmMain.Info.Lines.Add(vbCrLf + '-----------------------------------');
        //frmMain.Info.Lines.Add('�������ĺ���:' + strSCA);
        frmMain.Info.Lines.Add('���ŷ���ʱ��:' + MsgTime);
        frmMain.Info.Lines.Add('���ŷ��ͺ���:' + TelNo);
        frmMain.Info.Lines.Add('���ն�������:' + MsgContent + vbCrLf);
        {�������ɾ��}
        DelOneSms(nIndex);
      end;
    end;
  end;

end;

//*************************************************
//*
//*  ɾ��һ������
//*
//*************************************************
function DelOneSms(nIndex: Integer): Boolean;
var
  strBuf: String;
begin
  if hPort = -1 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '����èδ��ʼ��!');
    Result:= False;
    Exit;
  end;
  Result:= True;
  {ɾ����һ������}
  strBuf:= SendComm(hPort, 'AT+CMGD=' + VarToStr(nIndex) + vbCr, 3000);
  {���ſ��ܱ�ɾ��}
  if Pos('ERROR', strBuf) > 0 then
  begin
    Result:= False;
    Exit;
  end;
  if Pos('TIMEOUT', strBuf) > 0 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + 'ɾ�����ų�ʱ!');
    Result:= False;
    Exit;
  end;
end;

//*************************************************
//*
//*  ����һ������
//*
//*************************************************
function SendOneSms(UserTel, CenterTel, Msg: String):Boolean;
var
  strValue1: WideString;
  strValue2: WideString;
  strValue3: WideString;
  strValue4: WideString;
  strValue5: WideString;
  strBuf: WideString;
  nLen: Integer;
  leng: WideString;
begin
  if hPort = -1 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '����èδ��ʼ��!');
    Result:= False;
    Exit;
  end;
  Result:= True;
  {�������ĺ���}
  strValue1:= PhoneNumberToPDU(CenterTel);
  {���͵��ֻ�����}
  strValue2:= PhoneNumberToPDU(UserTel);
  strValue3:= Msg;
  strValue4:= EncodeUCS2(strValue3);
  nLen:= 2 * Length(strValue3);
  leng:= Format('%x', [nLen]);
  if nLen < 16 then
  begin
    leng:= '0' + leng;
  end;
  strValue5:= prex + strValue1 + midx + strValue2 + sufx + leng + strValue4;
  strBuf:= SendComm(hPort, 'AT+CMGF=0' + vbCr, 3000);
  strBuf:= SendComm(hPort, 'AT+CMGS=' + VarToStr(15 + nLen) + vbCr, 3000);
  if Pos('ERROR', strBuf) > 0 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '���ŷ���ʧ��, ����SIM���Ƿ�װ��ȷ!');
    Result:= False;
    Exit;
  end;
  if Pos('TIMEOUT', strBuf) > 0 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '���ŷ��ͳ�ʱ, ����SIM���Ƿ�װ��ȷ!');
    Result:= False;
    Exit;
  end;
  strBuf:= SendComm(hPort, strValue5 + #26, 3000);
  if Pos('ERROR', strBuf) > 0 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '���ŷ���ʧ��, ����SIM���Ƿ�װ��ȷ!');
    Result:= False;
    Exit;
  end;
  if Pos('TIMEOUT', strBuf) > 0 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '���ŷ��ͳ�ʱ, ����SIM���Ƿ�װ��ȷ!');
    Result:= False;
    Exit;
  end;
end;


{�Զ����������ʾ��Ϣ}
procedure TfrmMain.InfoChange(Sender: TObject);
begin
  if Info.Lines.Count > 15 then
  begin
    {ɾ���������ʾ��Ϣ}
    while Info.Lines.Count > 15 do
    begin
      Info.Lines.Delete(0);
    end;
  end
  else
  Begin
    SendMessage(Info.Handle, EM_SCROLL, SB_LINEDOWN, 0);
  end;
end;

end.

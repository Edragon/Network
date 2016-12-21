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
  SmsCenterNO: WideString; {短信中心号码}
  IsRunNextOnce: Boolean; {是否可以下一次的轮询}
  MyConn: TADOConnection;
implementation

uses MyFunction;

{$R *.dfm}

procedure TfrmMain.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  {关闭设备}
  CloseComm(hPort);
  {释放数据库连接}
  FreeAndNil(MyConn);
  {退出程序}
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
  strLink: String;{数据库链接字符串}
begin
  tmRun.Enabled:= False;
  tmRun.Interval:= 0;
  strLink:= GetSetting('SMS', 'MYLINK');
  strLink:= Trim(StringReplace(strLink, '{APP}', ExtractFilePath(ParamStr(0)), [rfReplaceAll]));
  if strLink = '' then
  begin
    Info.Lines.Add(VarToStr(Now) + '数据库连接配置错误!');
    Exit;
  end;

  try
    MyConn:= TADOConnection.Create(nil);
    MyConn.ConnectionString:= strLink;
    MyConn.CursorLocation:= clUseClient;
    MyConn.ConnectionTimeout:= 30;
    MyConn.Open;
    Info.Lines.Add(VarToStr(Now) + vbTab + '数据库连接成功!');
  except
    on E: Exception do
    begin
      FreeAndNil(MyConn);
      Info.Lines.Add(VarToStr(Now) + vbTab + '数据库连接失败!');
      Info.Lines.Add(VarToStr(Now) + vbTab + e.Message);
      Exit;
    end;
  end;
  nPort:= StrToIntDef(GetSetting('SMS', 'PORT', '3'), 3);
  hPort:= OpenComm(nPort);
  if hPort <> -1 then
  begin
    Info.Lines.Add(VarToStr(Now) + vbTab + '短信猫串口号:COM' + VarToStr(nPort));
    Caption:= '短信端口打开';
  end
  else
  begin
    Caption:= '短信端口关闭';
  end;
  strBuf:= SendComm(hPort, 'AT+CSCS="GSM"' + vbCr, 3000);
  if Pos('TIMEOUT', strBuf) > 0 then
  begin
    Info.Lines.Add(VarToStr(Now) + vbTab + '初始化失败，请检查SIM卡是否插入!');
    Exit;
  end;
  if Pos('ERROR', strBuf) > 0 then
  begin
    Info.Lines.Add(VarToStr(Now) + vbTab + '初始化失败，请检查SIM卡接触是否良好!');
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
  Info.Lines.Add(VarToStr(Now) + vbTab + '短信中心号码:' + SmsCenterNO);
  Info.Lines.Add(VarToStr(Now) + vbTab + '短信猫初始化成功!');
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
    {接收短信的编码}
    strBuf:= SendComm(hPort, 'AT+CMGF=0' + vbCr, 3000);

    {获取短信条数}
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
      frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + 'SIM卡内无短信!');
      Exit;
    end;
    I:= 0;
    while I <= nNumShortMessage do
    begin
      frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '获取设备索引号为[' + VarToStr(I) + ']短信......');
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
          frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '正在发送短信......');
          SendOneSms(strTelNO, SmsCenterNO, strMsg);
          frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '发送短信完毕.');
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
      frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '短信猫未初始化!');
      Exit;
    end;
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '获取SIM卡内短信......');
    GetMySms();
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '获取需要发送的短信......');
    MySendSms(MyConn);
  finally
    frmMain.tmServer.Enabled:= True;
    frmMain.tmServer.Interval:= 500;
  end;
end;

//*************************************************
//*
//*  接收一条短信
//*
//*************************************************
function GetOneSms(nIndex: Integer): Boolean;
var
  strBuf, strTmp:   WideString;
  nBegin, nEnd:     Integer;
//------------------------------------------------------------------------------
  strSCA:           String;  {短信中心数据}
  scaLen:           Integer; {短信中心长度}
  TelLen:           Integer; {发送号码长度}
  MsgType:          String;  {信息类型}
  SmsType:          String;  {}
  MsgTime:          String;  {短信发送时间}
  TelNo:            String;  {手机号码}
  MsgLen:           Integer; {消息长度}
  MsgContent:       String;  {接收短信内容}
//------------------------------------------------------------------------------
  strSQL: String;
label 100;
begin
  if hPort = -1 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '短信猫未初始化!');
    Result:= False;
    Exit;
  end;
  Result:= True;
  100:
  strBuf:= '';
  strBuf:= SendComm(hPort, 'AT+CMGR=' + IntToStr(nIndex) + vbCr, 3000);
  {短信可能被删除}
  if Pos('ERROR', strBuf) > 0 then
  begin
    Result:= False;
    Exit;
  end;
  if Pos('TIMEOUT', strBuf) > 0 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '接收短信超时!');
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


    {中心号长度}
    scaLen:= StrToIntDef('$' + Copy(strTmp, 1, 2), 0);
    strSCA:= Copy(strTmp, 5, (scaLen - 1) * 2);
    strSCA:= PDUToPhoneNumber(strSCA);

    {发送时间}
    MsgType:= Copy(strTmp, 19, 2);
    If (MsgType = '06') Or (MsgType = '02') Or (MsgType = '01')Then
    begin
      //状态报告
      MsgTime:= '';
    end
    Else
    begin
      {提取短信中心之后+2的数据}
      MsgTime:=  Copy(strTmp, 3 + scaLen * 2 + 2, Length(strTmp) - (scaLen * 2));
      {获取发送方号码长度}
      TelLen:=  StrToIntDef('$' + Copy(MsgTime, 1, 2), 0);
      {判断长度是否偶数}
      If TelLen Mod 2 <> 0 Then
      begin
         TelLen:= TelLen + 1;
      end;
      MsgTime:= Copy(MsgTime, TelLen + 9, Length(MsgTime) - TelLen + 2);
      MsgTime:= Copy(MsgTime, 1, 14);
      MsgTime:= VarToStr(PDUToDate(MsgTime));

      {提取发件人的手机号码}
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

      {提取短信内容}
      If TelLen Mod 2 = 0 Then
      begin
        smsType:= Copy(strTmp, (scaLen + 6) * 2 + TelLen - 1, 2);
      end
      else
      begin
        smsType:= Copy(strTmp, (scaLen + 6) * 2 + TelLen, 2);
      end;

      {信息长度数据开始位置}
      nBegin:= (scaLen + 6 + 7) * 2 + TelLen + 2;
      If nBegin Mod 2 = 0 Then
      begin
        nBegin:= nBegin - 1;
      end;
      MsgLen:= StrToIntDef('$' + Copy(strBuf, nBegin, 2), 0);
      MsgContent:= '';
      if SmsType = TP_DCS_UCS2 then //UCS2编码
      begin
        MsgContent:= Copy(strBuf, nBegin + 2, MsgLen * 2);
        MsgContent:= DecodeUCS2(MsgContent);
      end;
      if SmsType = TP_DCS_7BIT then//7bit 编码
      begin
        MsgLen:= MsgLen - (MsgLen div 8);
        MsgContent:= Copy(strBuf, nBegin + 2, MsgLen * 2);
        MsgContent:= Decode7bit(MsgContent);
      end;
      strSQL:= 'INSERT INTO [GET]([TELNO], [MSG], [INDEX])VALUES(:TELNO, :MSG, :INDEX)';
      if ExecuteSQL(strSQL, [TelNo, MsgContent, nIndex], MyConn, strTmp) then
      begin
        frmMain.Info.Lines.Add(vbCrLf + '-----------------------------------');
        //frmMain.Info.Lines.Add('短信中心号码:' + strSCA);
        frmMain.Info.Lines.Add('短信发送时间:' + MsgTime);
        frmMain.Info.Lines.Add('短信发送号码:' + TelNo);
        frmMain.Info.Lines.Add('接收短信内容:' + MsgContent + vbCrLf);
        {接收完毕删除}
        DelOneSms(nIndex);
      end;
    end;
  end;

end;

//*************************************************
//*
//*  删除一条短信
//*
//*************************************************
function DelOneSms(nIndex: Integer): Boolean;
var
  strBuf: String;
begin
  if hPort = -1 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '短信猫未初始化!');
    Result:= False;
    Exit;
  end;
  Result:= True;
  {删除第一条短信}
  strBuf:= SendComm(hPort, 'AT+CMGD=' + VarToStr(nIndex) + vbCr, 3000);
  {短信可能被删除}
  if Pos('ERROR', strBuf) > 0 then
  begin
    Result:= False;
    Exit;
  end;
  if Pos('TIMEOUT', strBuf) > 0 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '删除短信超时!');
    Result:= False;
    Exit;
  end;
end;

//*************************************************
//*
//*  发送一条短信
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
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '短信猫未初始化!');
    Result:= False;
    Exit;
  end;
  Result:= True;
  {短信中心号码}
  strValue1:= PhoneNumberToPDU(CenterTel);
  {发送的手机号码}
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
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '短信发送失败, 请检查SIM卡是否安装正确!');
    Result:= False;
    Exit;
  end;
  if Pos('TIMEOUT', strBuf) > 0 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '短信发送超时, 请检查SIM卡是否安装正确!');
    Result:= False;
    Exit;
  end;
  strBuf:= SendComm(hPort, strValue5 + #26, 3000);
  if Pos('ERROR', strBuf) > 0 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '短信发送失败, 请检查SIM卡是否安装正确!');
    Result:= False;
    Exit;
  end;
  if Pos('TIMEOUT', strBuf) > 0 then
  begin
    frmMain.Info.Lines.Add(VarToStr(Now) + vbTab + '短信发送超时, 请检查SIM卡是否安装正确!');
    Result:= False;
    Exit;
  end;
end;


{自动清理多余显示信息}
procedure TfrmMain.InfoChange(Sender: TObject);
begin
  if Info.Lines.Count > 15 then
  begin
    {删除多余的显示信息}
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

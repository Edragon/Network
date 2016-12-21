unit LyComm;
//****************************************************************************
//*
//*  模块功能:串口通讯函数
//*  程序设计:老廖
//*  QQ: 418464301
//*
//****************************************************************************
interface
  uses SysUtils, ComCtrls, Windows, Forms;
  
  function OpenComm(CommPort: Integer): Integer;
  function WriteComm(hSerialPort: Cardinal; strValue: String): Boolean;
  function ReadComm(hSerialPort: Cardinal): String;
  function CloseComm(hSerialPort: Cardinal): Boolean;
//------------------------------------------------------------------------------
  function SendComm(hSerialPort: Cardinal; strAtCommand: String; nDelayTime: Integer): String;
  function EncodeUCS2(src: WideString): String;
  function DecodeUCS2(src: String): String;
  function Encode7bit(s: String): String;
  function Decode7bit(pSrc:string):string;
  function PhoneNumberToPDU(src:String):String;
  function PDUToPhoneNumber(src:String):String;
  function DateToPDU(src:TDateTime):String;
  function PDUToDate(src:String):TDateTime;
//------------------------------------------------------------------------------
  function MsgBox(strPrompt: String; strTitle: String = '提示'; nButtons: UINT = 64): Integer;

  const
  vbCr:         String = #13;
  vbTab:         String = #9;
  vbCrLf:       String = #13#10;
  prex:         String = '0891';
  midx:         String = '11000D91';
  sufx:         String = '000800';
  TP_DCS_7BIT:  String = '00';
  TP_DCS_8BIT:  String = '04';
  TP_DCS_UCS2:  String = '08';

implementation

{打开串口端口}
function OpenComm(CommPort: Integer): Integer;
var
  Commcfg:      TCommConfig;
  hSerialPort:  Cardinal;
  strTmp:       String;
begin
  strTmp:='\\.\COM' + Format('%d', [CommPort]);
  hSerialPort:=CreateFile(PChar(strTmp), GENERIC_READ or GENERIC_WRITE, 0, nil, OPEN_EXISTING, 0, 0);
  if (hSerialPort = invalid_handle_value) then
  begin
    Result:= -1;
    Exit;
  end;
  GetCommState(hSerialPort, Commcfg.dcb);
  Commcfg.dcb.BaudRate:= CBR_9600;
  Commcfg.dcb.ByteSize:= 8;
  Commcfg.dcb.Parity:= NOPARITY;
  Commcfg.dcb.StopBits:= ONESTOPBIT;
  if not SetCommState(hSerialPort, Commcfg.dcb) then
  begin
      Result:= -1;
      CloseHandle(hSerialPort);
      Exit;
  end;
  Result:= hSerialPort;
end;

{关闭串口端口}
function CloseComm(hSerialPort: Cardinal): Boolean;
begin
  if hSerialPort <> 0 then
  begin
    CloseHandle(hSerialPort);
  end;
  Result:= True;
end;

{向串口写数据}
function WriteComm(hSerialPort: Cardinal; strValue: String): Boolean;
var
  lw:     LongWord;
  strTmp: String;
begin
  Result:= True;
  if hSerialPort = 0 then
  begin
    Exit;
  end;
  strTmp:= strValue;
  WriteFile(hSerialPort, PChar(strTmp)^, Length(strTmp), lw, nil);
end;

{向串口读数据}
function ReadComm(hSerialPort: Cardinal): String;
var
  strTmp:             String;
  inBuff:             array[0..2047]of Char;
  bytesRead, dwError: LongWord;
  Commstat:           TComStat;
begin
  ClearCommError(hSerialPort, dwError, @Commstat);
  if Commstat.cbInQue>SizeOf(inBuff)then
  begin
      PurgeComm(hSerialPort, PURGE_RXCLEAR);
      Exit;
  end;
  ReadFile(hSerialPort,inBuff,  Commstat.cbInQue, bytesRead, nil);
  strTmp:= Copy(inBuff, 1, Commstat.cbInQue);
  Result:= strTmp;
end;

{发送 AT 命令}
function SendComm(hSerialPort: Cardinal; strAtCommand: String; nDelayTime: Integer): String;
var
  strTmp: String;
  strBuf: String;
  IStart: Longint;
begin
  Result:= '';
  strTmp:= strAtCommand;
  //WriteLogFile(strAtCommand);
  WriteComm(hSerialPort, strTmp);
  Sleep(300);
  strBuf:= ReadComm(hSerialPort);
  Sleep(300);
  IStart:= GetTickCount();
  while strBuf = '' do
  begin
    strBuf:= strBuf + ReadComm(hSerialPort);
    if ((Longint(GetTickCount()) - IStart) >= nDelayTime) then
    begin
      strBuf:= UpperCase('TIMEOUT');
      Break;
    end;
    Sleep(300);
  end;
  FlushFileBuffers(hSerialPort);
  Result:= strBuf;
end;

//***************************************
// Function/Procedure : ResumeOrder
// Purpose            : ChangeOrder反向操作
// Inputs             : 字符串
// Return             : 字符串
//***************************************
function ResumeOrder(OriStr:String):String;
var
  I:    Integer;
  sStr: String;
begin
  sStr:= '';
  for i:=1 to (Length(OriStr) Div 2) do
  begin
      sStr:= sStr+OriStr[I*2]+OriStr[I*2-1];
  end;
  Result:= sStr;
end;


//***************************************
// Function/Procedure : EncodeUCS2
// Purpose            : 中文编码转PDU格式
// Inputs             : 中文 字符串
// Return             : PDU格式字符串
//***************************************
function EncodeUCS2(src: WideString): String;
var
 i,len:Integer;
 cur:Integer;
 t:String;
begin
 Result:='';
 len:= Length(src);
 i:=1;
 while i <= len do
 begin
    cur:= ord(src[i]);
    FmtStr(t, '%4.4X', [cur]); //BCD转换
    Result:= Result+t;
    inc(i);
 end;
end;


//***************************************
// Function/Procedure : DecodeUCS2
// Purpose            : PDU格式转中文编码
// Inputs             : PDU格式 字符串
// Return             : 中文字符串
//***************************************
  function DecodeUCS2(src: String): String;
  var
     i:Integer;
     S:String;
     D:WideChar;
     ResultW:WideString;
  begin
     for i:=1 to Round(Length(Src)/4) do
     begin
         S:= Copy(Src, (i - 1) * 4 + 1, 4);
         D:= WideChar(StrToInt('$' + s));
         ResultW:= ResultW + D;
     end;
     Result:= ResultW;
  end;

//***************************************
// Function/Procedure : PhoneNumberToPDU
// Purpose            : 电话号码转化为PDU格式
// Inputs             : 电话号码 字符串
// Return             : PDU格式 字符串
//***************************************
function PhoneNumberToPdu(src:String):String;
begin
 src:=  StringReplace(src, '+', '', [rfReplaceAll]);
 if ((length(src) mod 2) = 1) then
 begin
    src:= src + 'F';
 end;
 Result:= ResumeOrder(src);
end;

//***************************************
// Function/Procedure : PhoneNumberToPDU
// Purpose            : PDU格式串转化为电话号码
// Inputs             : PDU格式串 字符串
// Return             : 电话号码 字符串
//***************************************
function PduToPhoneNumber(src:String):String;
begin
 Result:= ResumeOrder(src);
 Result:= StringReplace(Result, 'F', '', [rfReplaceAll]);
end;

//***************************************
// Function/Procedure : DateToPDU
// Purpose            : 时间转化为PDU串
// Inputs             : 时间
// Return             : PDU串
//***************************************  
function DateToPdu(src:TDateTime):String;
var
  str:  String;
begin
  DateTimeToString(Str,'YYMMDDHHMMSS', src);
  Result:=  ResumeOrder(str);
end;

//***************************************
// Function/Procedure : PDUToDate
// Purpose            : PDU串转化为时间
// Inputs             : PDU串
// Return             : 时间
//***************************************   
function PduToDate(src:String):TDateTime;
var
str,tem:String;
begin
 //假如输入为:801192018533  则表示08-11-29 10:58:33
 str:= ResumeOrder(src);//倒叙，结果为081129105833
 tem:= copy(str,1,2)+'-'+  //格式化，结果为08-11-29 10:58:33
       copy(str,3,2)+'-'+
       copy(str,5,2)+' '+
       copy(str,7,2)+':'+
       copy(str,9,2)+':'+
       copy(str,11,2);
 Result:= StrToDateTimeDef(tem, 0);
end;


//***************************************
// Function/Procedure : Decode7bit
// Purpose            : 7 bit 解码 
// Inputs             : PDU串
// Return             : 时间
//***************************************    
function Decode7bit(pSrc:string):string;
var
  nSrcLength:Integer;
  nSrc:Integer; // 源字符串的计数值
  nByte:Integer; // 当前正在处理的组内字节的序号，范围是0-6
  nLeft:Byte; // 上一字节残余的数据
  tmpChar:Byte;
  pDst:string;
begin
  // 计数值初始化
  nSrc := 1;
  nSrcLength:=Length(pSrc);
  // 组内字节序号和残余数据初始化
  nByte := 0;
  nLeft := 0;
  pdst := ''; 
    // 将源数据每7个字节分为一组，解压缩成8个字节
    // 循环该处理过程，直至源数据被处理完
    // 如果分组不到7字节，也能正确处理
  while (nSrc < nSrcLength) do
  begin
      tmpChar := byte(StrToInt('$' + pSrc[nsrc] + pSrc[nsrc + 1]));
      // 将源字节右边部分与残余数据相加，去掉最高位，得到一个目标解码字节
      pDst := pDst + Char(((tmpchar shl nByte) or nLeft) and $7F);
      // 将该字节剩下的左边部分，作为残余数据保存起来
      nLeft := tmpChar shr (7 - nByte);

      // 修改字节计数值
      Inc(nByte);

      // 到了一组的最后一个字节
      if (nByte = 7) then
      begin
          // 额外得到一个目标解码字节
          pdst := pDst + Char(nLeft);

          // 组内字节序号和残余数据初始化
          nByte := 0;
          nLeft := 0;
      end; //end if

      // 修改源串的指针和计数值

      nSrc:= nSrc + 2;
  end; //end while
  // 返回目标串长度
  Result:= pdst;
end;


//***************************************
// Function/Procedure : Encode7bit
// Purpose            : 7 bit 编码
// Inputs             :  
// Return             :  PDU串
//***************************************
function Encode7bit(s: String): String; 
var
  i,j,len: Integer;
  cur: Integer;
  t: String;
begin
  Result := '';
  len := Length(s);
  //j 用于移位计数
  i := 1;
  j := 0;
  while i <= len do
  begin
    if i < len then
    begin
       //数据变换
      cur := (Ord(s[i]) shr j) or ((Ord(s[i+1]) shl (7-j)) and $ff);
    end
    else
    begin
      cur := (Ord(s[i]) shr j) and $7f;
    end;
    FmtStr(t, '%2.2X', [cur]);
    Result := Result+t;
    inc(i);
    //移位计数达到7位的特别处理
    j := (j+1) mod 7;
    if j = 0 then inc(i);
  end; //end while
end;

//****************************************************
//*  函数功能：消息框函数
//*  函数名称: MsgBox
//****************************************************
function MsgBox(strPrompt: String; strTitle: String = '提示'; nButtons: UINT = 64): Integer;
begin
  Result:= MessageBox(Application.Handle, PChar(strPrompt), PChar(strTitle), nButtons);
end;
end.
 
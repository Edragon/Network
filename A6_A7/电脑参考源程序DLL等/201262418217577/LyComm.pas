unit LyComm;
//****************************************************************************
//*
//*  ģ�鹦��:����ͨѶ����
//*  �������:����
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
  function MsgBox(strPrompt: String; strTitle: String = '��ʾ'; nButtons: UINT = 64): Integer;

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

{�򿪴��ڶ˿�}
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

{�رմ��ڶ˿�}
function CloseComm(hSerialPort: Cardinal): Boolean;
begin
  if hSerialPort <> 0 then
  begin
    CloseHandle(hSerialPort);
  end;
  Result:= True;
end;

{�򴮿�д����}
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

{�򴮿ڶ�����}
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

{���� AT ����}
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
// Purpose            : ChangeOrder�������
// Inputs             : �ַ���
// Return             : �ַ���
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
// Purpose            : ���ı���תPDU��ʽ
// Inputs             : ���� �ַ���
// Return             : PDU��ʽ�ַ���
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
    FmtStr(t, '%4.4X', [cur]); //BCDת��
    Result:= Result+t;
    inc(i);
 end;
end;


//***************************************
// Function/Procedure : DecodeUCS2
// Purpose            : PDU��ʽת���ı���
// Inputs             : PDU��ʽ �ַ���
// Return             : �����ַ���
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
// Purpose            : �绰����ת��ΪPDU��ʽ
// Inputs             : �绰���� �ַ���
// Return             : PDU��ʽ �ַ���
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
// Purpose            : PDU��ʽ��ת��Ϊ�绰����
// Inputs             : PDU��ʽ�� �ַ���
// Return             : �绰���� �ַ���
//***************************************
function PduToPhoneNumber(src:String):String;
begin
 Result:= ResumeOrder(src);
 Result:= StringReplace(Result, 'F', '', [rfReplaceAll]);
end;

//***************************************
// Function/Procedure : DateToPDU
// Purpose            : ʱ��ת��ΪPDU��
// Inputs             : ʱ��
// Return             : PDU��
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
// Purpose            : PDU��ת��Ϊʱ��
// Inputs             : PDU��
// Return             : ʱ��
//***************************************   
function PduToDate(src:String):TDateTime;
var
str,tem:String;
begin
 //��������Ϊ:801192018533  ���ʾ08-11-29 10:58:33
 str:= ResumeOrder(src);//���𣬽��Ϊ081129105833
 tem:= copy(str,1,2)+'-'+  //��ʽ�������Ϊ08-11-29 10:58:33
       copy(str,3,2)+'-'+
       copy(str,5,2)+' '+
       copy(str,7,2)+':'+
       copy(str,9,2)+':'+
       copy(str,11,2);
 Result:= StrToDateTimeDef(tem, 0);
end;


//***************************************
// Function/Procedure : Decode7bit
// Purpose            : 7 bit ���� 
// Inputs             : PDU��
// Return             : ʱ��
//***************************************    
function Decode7bit(pSrc:string):string;
var
  nSrcLength:Integer;
  nSrc:Integer; // Դ�ַ����ļ���ֵ
  nByte:Integer; // ��ǰ���ڴ���������ֽڵ���ţ���Χ��0-6
  nLeft:Byte; // ��һ�ֽڲ��������
  tmpChar:Byte;
  pDst:string;
begin
  // ����ֵ��ʼ��
  nSrc := 1;
  nSrcLength:=Length(pSrc);
  // �����ֽ���źͲ������ݳ�ʼ��
  nByte := 0;
  nLeft := 0;
  pdst := ''; 
    // ��Դ����ÿ7���ֽڷ�Ϊһ�飬��ѹ����8���ֽ�
    // ѭ���ô�����̣�ֱ��Դ���ݱ�������
    // ������鲻��7�ֽڣ�Ҳ����ȷ����
  while (nSrc < nSrcLength) do
  begin
      tmpChar := byte(StrToInt('$' + pSrc[nsrc] + pSrc[nsrc + 1]));
      // ��Դ�ֽ��ұ߲��������������ӣ�ȥ�����λ���õ�һ��Ŀ������ֽ�
      pDst := pDst + Char(((tmpchar shl nByte) or nLeft) and $7F);
      // �����ֽ�ʣ�µ���߲��֣���Ϊ�������ݱ�������
      nLeft := tmpChar shr (7 - nByte);

      // �޸��ֽڼ���ֵ
      Inc(nByte);

      // ����һ������һ���ֽ�
      if (nByte = 7) then
      begin
          // ����õ�һ��Ŀ������ֽ�
          pdst := pDst + Char(nLeft);

          // �����ֽ���źͲ������ݳ�ʼ��
          nByte := 0;
          nLeft := 0;
      end; //end if

      // �޸�Դ����ָ��ͼ���ֵ

      nSrc:= nSrc + 2;
  end; //end while
  // ����Ŀ�괮����
  Result:= pdst;
end;


//***************************************
// Function/Procedure : Encode7bit
// Purpose            : 7 bit ����
// Inputs             :  
// Return             :  PDU��
//***************************************
function Encode7bit(s: String): String; 
var
  i,j,len: Integer;
  cur: Integer;
  t: String;
begin
  Result := '';
  len := Length(s);
  //j ������λ����
  i := 1;
  j := 0;
  while i <= len do
  begin
    if i < len then
    begin
       //���ݱ任
      cur := (Ord(s[i]) shr j) or ((Ord(s[i+1]) shl (7-j)) and $ff);
    end
    else
    begin
      cur := (Ord(s[i]) shr j) and $7f;
    end;
    FmtStr(t, '%2.2X', [cur]);
    Result := Result+t;
    inc(i);
    //��λ�����ﵽ7λ���ر���
    j := (j+1) mod 7;
    if j = 0 then inc(i);
  end; //end while
end;

//****************************************************
//*  �������ܣ���Ϣ����
//*  ��������: MsgBox
//****************************************************
function MsgBox(strPrompt: String; strTitle: String = '��ʾ'; nButtons: UINT = 64): Integer;
begin
  Result:= MessageBox(Application.Handle, PChar(strPrompt), PChar(strTitle), nButtons);
end;
end.
 
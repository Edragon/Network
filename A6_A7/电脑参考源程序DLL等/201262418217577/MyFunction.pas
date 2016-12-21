unit MyFunction;

interface
  uses SysUtils, Windows, Variants, Forms, ADODB, Classes;

  function SaveSetting(strHead, strSet: String; vValue: Variant; strIniFile: String = ''): Boolean;
  function GetSetting(strHead, strSet: String; DefaultValue: String = ''; strIniFile: String = ''): string;
  function DelayTime(nSeconds: Integer = 100): Integer;
  function ExecuteSQL(strSql: string; ParamValues: array of Variant; Conn :TADOConnection; out ErrDescription: WideString; nExecuteTime: Integer = 50): Boolean;
  function ExecuteQuery(strSql: String; Conn: TADOConnection; out ErrDescription: WideString; nExecuteTime: Integer = 50): TADOQuery; overload;

implementation

  //****************************************************
  //*  函数功能：保存程序设置信息
  //*  函数名称: SaveSetting
  //****************************************************
  function SaveSetting(strHead, strSet: String; vValue: Variant; strIniFile: String = ''): Boolean;
  var
    strIni: String;
  begin
    Result:= True;
    if Trim(strIniFile) = '' then
    begin
      strIni:= ExtractFilePath(ParamStr(0)) + 'Config.ini';
    end
    else
    begin
      strIni:= strIniFile;
    end;
    if not WritePrivateProfileString(PChar(strHead), PChar(strSet), PChar(VarToStr(vValue)), PChar(strIni)) then
    begin
      Result:= False;
    end;
  end;

  //****************************************************
  //*  函数功能：取得程序设置信息
  //*  函数名称: GetSetting
  //****************************************************
  function GetSetting(strHead, strSet: String; DefaultValue: String = ''; strIniFile: String = ''): string;
  var
    strIni: String;
    Buffer: array[0..2047] of Char;
  begin
    if Trim(strIniFile) = '' then
    begin
      strIni:= ExtractFilePath(ParamStr(0)) + 'Config.ini';
    end
    else
    begin
      strIni:= strIniFile;
    end;
    SetString(Result, Buffer, GetPrivateProfileString(PChar(strHead), PChar(strSet), PChar(''), Buffer, SizeOf(Buffer), PChar(strIni)));
    if Result = '' then
    begin
      Result:= DefaultValue;
    end;
  end;

  //****************************************************
  //*  函数功能：时间延时程序
  //*  函数名称: DelayTime
  //****************************************************
  function DelayTime(nSeconds: Integer = 100): Integer;
  var
    IStart: Longint;
  begin
    IStart := GetTickCount();
    while ((Longint(GetTickCount()) - IStart) <= nSeconds) do
    begin
      Application.ProcessMessages; //100为毫秒
    end;
    Result:= 0;
  end;

  //'************************************************************
  //' 函数功能：执行SQL命令
  //' 函数名称：ExecuteQuery
  //'************************************************************
  function ExecuteQuery(strSql: String; Conn: TADOConnection; out ErrDescription: WideString; nExecuteTime: Integer = 50): TADOQuery; overload;
  begin
    ErrDescription:= '';
    Result:= TADOQuery.Create(nil);
    Result.CommandTimeout:= nExecuteTime;
    Result.SQL.Clear;
    Result.Parameters.Clear;
    Result.Connection := Conn;
    Result.SQL.Text := strSql;
    try
      Result.Open;
    except
      on E: Exception do
      begin
        ErrDescription:= e.Message;
        Result:= nil;
      end;
    end;
  End;

  //'************************************************************
  //' 函数功能：执行SQL命令
  //' 函数名称：ExecuteSQL
  //'************************************************************
  function ExecuteSQL(strSql: string; ParamValues: array of Variant; Conn :TADOConnection; out ErrDescription: WideString; nExecuteTime: Integer = 50): Boolean;
  var
    rsTmp:      TADOQuery;
    I:          Integer;
    ParamNames: TStrings;
  begin
    Result:= True;
    ErrDescription:= '';
    if SizeOf(ParamValues)>0 then
    begin
      ParamNames := TStringList.Create;
    end;
    rsTmp:= TADOQuery.Create(nil);
    rsTmp.CommandTimeout:= nExecuteTime;
    rsTmp.CursorLocation:= clUseClient;
    rsTmp.SQL.Clear;
    rsTmp.Parameters.Clear;
    rsTmp.Connection := Conn;
    rsTmp.SQL.Text := strSql;
    for I:= Low(ParamValues) to High(ParamValues) do
    begin
      rsTmp.Parameters.Items[I].Value:= ParamValues[I];
    end;
    try
      try
        rsTmp.ExecSQL;
      except
        on e: Exception do
        begin
          Result:= False;
          ErrDescription:= e.Message;
        end;
      end;
    finally
      FreeAndNil(rsTmp);
      FreeAndNil(ParamNames);
    end;
  end;

end.
 
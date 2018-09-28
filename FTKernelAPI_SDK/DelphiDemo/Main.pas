unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, FTKernelAPI, StdCtrls, ComCtrls, WinSock, ExtCtrls, Files,
  MakeTorrent, InputPwd, StrUtils;

type
  TMainFrm = class(TForm)
    GroupBox1: TGroupBox;
    Edit1: TEdit;
    Button1: TButton;
    OpenDialog1: TOpenDialog;
    GroupBox2: TGroupBox;
    ProgressBar1: TProgressBar;
    Button2: TButton;
    Button3: TButton;
    Memo1: TMemo;
    Timer1: TTimer;
    Memo2: TMemo;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
  private
    { Private declarations }

    sStartupPath: string;
    sTorrentFile: string;
    nTotalFileSize: QWORD;
    nPieceCount: DWord;
    hDownloader: HDownloader;
    sHexHashKey: string;
    bSetSeq: Boolean;

    function StartContext(): boolean;
    function StopContext(): boolean;
    function StartDownload(): boolean;
    function StopDownload(): boolean;

  public
    { Public declarations }
  end;

var
  MainFrm: TMainFrm;
  WSAData: TWSAData;

function IFormatByte(nSize: Int64): string;
function FFormatByte(fSize: Double): string;

implementation

function Startup(): boolean;
var
  ErrorCode: Integer;
begin
  ErrorCode := WSAStartup($0202, WSAData);
  if ErrorCode <> 0 then
    result := False;
end;

function Cleanup: boolean;
var
  ErrorCode: Integer;
begin
  ErrorCode := WSACleanup;
  if ErrorCode <> 0 then
    Result := False;
end;

function TMainFrm.StartContext(): boolean;
var
  sConfigFileName: string;
  xhConfigIni: HConfigIni;
  sLicenseKey: string;
begin

  Result := False;

  sLicenseKey := '851554BEA3F29D1EC3658672F131E48837C15A1F567E5C7CCC9E8EA94C023E';
  sLicenseKey := sLicenseKey + '9C0B0FF2FFA4BA74303AF02CCC217FB83F9129D8A8883ECDCB2AF2B6236F33BDC0E8E05901635351D9ADBCA17774A8E112DB94941F0F74A7E6C8C6F60C78FA54C64BE134A41D863AFB8C13F027B3C44243AD9E8E926B68C09B95FFCC42DBC13BF1';
  FTK_License_Set(PChar(sLicenseKey));

  if FTK_Context_IsInit() then
  begin
    Memo1.lines.Add('FTK_Context_IsInit:: success!');
    Exit;
  end;

  sConfigFileName := sStartupPath;
  sConfigFileName := sConfigFileName + 'Config.ini';

  Memo1.lines.Add('Config File: ' + sConfigFileName);
  //if not FTK_Context_Init( PChar(sConfigFileName), True ) then
  //如果想不使用配置文件更改绑定的端口
  xhConfigIni := FTK_Config_Open();
  FTK_Config_SetInt(xhConfigIni, PChar('fix_port'), 1);
  FTK_Config_SetInt(xhConfigIni, PChar('port'), 27800);

  if not FTK_Context_Init2(xhConfigIni, True) then
  begin
    Memo1.lines.Add('FTK_Context_Init:: failed!');
    FTK_Config_Close(xhConfigIni);
    Exit;
  end;

  FTK_Config_Close(xhConfigIni);

  if FTK_Context_IsRunning() then
  begin
    Memo1.lines.Add('FTK_Context_IsRunning:: success!');
    Exit;
  end;

  FTK_Context_Run();
  Result := FTK_Context_IsRunning();

end;

function TMainFrm.StopContext(): boolean;
begin
  result := true;

  if FTK_Context_IsInit() then
  begin
    FTK_Context_Release();
  end;

end;

function TMainFrm.StartDownload(): boolean;
var
  sValue: string;
  xhTorrentFile: HTorrentFile;
  aPreAllocFile: ArrayByte;
  aPrePrioFile: array of char;
  nFilesCount: Integer;
  sTorrentPath: string;
  sDestFileName: string;
  i: Integer;
  bRet: Boolean;
  bCipher: Boolean;
  nlengthStr: Integer;
begin
  if FTK_Torrent_IsCipherTorrent(PAnsiChar(sTorrentFile)) then
  begin
    PwdForm := TPwdForm.Create(self);
    if mrOK = PwdForm.ShowModal() then
    begin
      bCipher := True;
      xhTorrentFile := FTK_Torrent_Open(PAnsiChar(sTorrentFile), CP_ACP, PChar(PwdForm.Edit1.Text));
    end;
  end
  else
  begin
    xhTorrentFile := FTK_Torrent_Open(PAnsiChar(sTorrentFile));
  end;

  if not assigned(xhTorrentFile) then
  begin
    Memo1.lines.Add('StartDownload::Failed to open torrent file: !' + sTorrentFile);
    Exit;
  end;

  Memo1.lines.Add('StartDownload::Success to open torrent file: !' + sTorrentFile);

  nFilesCount := FTK_Torrent_GetFilesCount(xhTorrentFile);
  SetLength(aPreAllocFile, nFilesCount);

  for i := 0 to nFilesCount - 1 do
  begin
    aPreAllocFile[i] := 0;
  end;

  sTorrentPath := ExtractFilePath(sTorrentFile);
  sDestFileName := sTorrentPath + FTK_Torrent_GetTorrentName(xhTorrentFile);
  Memo1.lines.Add('StartDownload::Destination file: !' + sDestFileName);
  sValue := FTK_Torrent_GetHexInfoHash(xhTorrentFile);

  {    nLengthStr := length( sValue );
      sHexHashKey := '';
      for i := 1 to nlengthStr do
      begin
        if sValue[ i ] <> '%' then
        begin
          sHexHashKey := sHexHashKey + sValue[ i ];
        end;
      end; }

  sHexHashkey := AnsiReplaceStr(sValue, '%', '');

  hDownloader := FTK_Downloader_Open();

  //SetLength(aPrePrioFile, nFilesCount);
  //for i := 0 to nFilesCount - 1 do
  //begin
  //  aPrePrioFile[i] := #254;
  //end;

  //aPrePrioFile[nFilesCount -1] := #0;
  //FTK_Downloader_PreInitFilePriority(hDownloader, PChar(aPrePrioFile), nFilesCount);

  if bCipher = True then
  begin

    bRet := FTK_Downloader_Init(
      hDownloader,
      PAnsiChar(sTorrentFile),
      PByte(aPreAllocFile), //*****
      nFilesCount,
      False,
      PChar(sDestFileName),
      PChar(sStartupPath + 'Config.ini'),

      //If you want to don't output log file and status file ,input nil
      //Ohterwise input a absolute log filename and status filename.
      nil, //PChar( sStartupPath + 'Log\Downloader.log' ),
      nil, //PChar( sStartupPath + sHexHashKey + '.status' ),
      false, //如果想快速做种子，将这里设置为True，但是指向的目的路径一定要正确，后果自负
      PChar(PwdForm.Edit1.Text), //password
      CP_ACP);
  end
  else
  begin
    bRet := FTK_Downloader_Init(
      hDownloader,
      PAnsiChar(sTorrentFile),
      PByte(aPreAllocFile), //*****
      nFilesCount,
      False,
      PChar(sDestFileName),
      PChar(sStartupPath + 'Config.ini'),

      //If you want to don't output log file and status file ,input nil
      //Ohterwise input a absolute log filename and status filename.
      PChar(sStartupPath + 'Log\Downloader.log'),
      PChar(sStartupPath + sHexHashKey + '.status'),
      false, //如果想快速做种子，将这里设置为True，但是指向的目的路径一定要正确，后果自负
      nil, //password
      CP_ACP);
  end;

  if not bRet then
  begin
    Memo1.lines.Add('StartDownload::FTK_Downloader_Init failed!');
    Exit;
  end;

  bRet := FTK_Downloader_Execute(hDownloader);
  if not bRet then
  begin
    Memo1.lines.Add('StartDownload::FTK_Downloader_Execute failed!');
    FTK_Downloader_Close(hDownloader);
    hDownloader := nil;
    Exit;
  end;

  FTK_GlobalVar_AddTorrentSHA1(PChar(sHexHashKey), hDownloader);

  nTotalFileSize := FTK_Torrent_GetFileSize(xhTorrentFile);
  nPieceCount := FTK_Torrent_GetPieceCount(xhTorrentFile);

  FTK_Torrent_Close(xhTorrentFile);
  xhTorrentFile := nil;

  Result := True;

end;

function TMainFrm.StopDownload(): boolean;
begin
  result := False;

  if not assigned(hDownloader) then
  begin
    Exit;
  end;

  FTK_GlobalVar_RemoveTorrentSHA1(PAnsiChar(sHexHashKey));

  FTK_Downloader_Release(hDownloader);
  FTK_Downloader_Close(hDownloader);
  hDownloader := nil;

  Result := True;

end;

function IFormatByte(nSize: Int64): string;
begin
  if nSize > 1073741824 then
    Result := FormatFloat('###,##0.00G', nSize / 1073741824)
  else if nSize > 1048576 then
    Result := FormatFloat('###,##0.00M', nSize / 1048576)
  else if nSize > 1024 then
    Result := FormatFloat('###,##00K', nSize / 1024)
  else
    Result := FormatFloat('###,#0', nSize);
end;

function FFormatByte(fSize: Double): string;
begin
  if fSize > 1073741824.0 then
    Result := FormatFloat('###,##0.00G', fSize / 1073741824.0)
  else if fSize > 1048576.0 then
    Result := FormatFloat('###,##0.00M', fSize / 1048576.0)
  else if fSize > 1024.0 then
    Result := FormatFloat('###,##00K', fSize / 1024.0)
  else
    Result := FormatFloat('###,#0', fSize);
end;

{$R *.dfm}

procedure TMainFrm.Button1Click(Sender: TObject);
begin
  OpenDialog1.Filter := 'Torrent files (*.torrent)|*.TORRENT';
  if OpenDialog1.Execute() then
  begin
    Edit1.Text := OpenDialog1.FileName;
    sTorrentFile := Edit1.Text;
  end;
end;

procedure TMainFrm.Button2Click(Sender: TObject);
var
  bRet: boolean;
begin
  if not StartDownload then
  begin
    Memo1.lines.Add('StartDownload:: failed!');
  end;

  Memo1.lines.Add('StartDownload:: success!');
  Edit1.Enabled := False;
  Button1.Enabled := False;
  Button2.Enabled := False;
  Button6.Enabled := True;
end;

procedure TMainFrm.Button3Click(Sender: TObject);
begin
  Close();
end;

procedure TMainFrm.FormCreate(Sender: TObject);
var
  nVer: WORD;
  WSData: TWSAData;
begin

  bSetSeq := False;
  Memo1.Text := '';
  Memo2.Text := '';
  sStartupPath := ExtractFilePath(Application.ExeName);
  Memo1.Lines.Add('Startup Path: ' + sStartupPath);

  if not Startup() then
  begin
    Close();
  end;

  if StartContext() = false then
  begin
    Application.MessageBox('Warnning', 'StartContext:: failed!');
    Exit;
  end;
end;

procedure TMainFrm.FormDestroy(Sender: TObject);
begin
  StopDownload();
  StopContext();
  WSACleanup();
end;

procedure TMainFrm.Timer1Timer(Sender: TObject);
var
  sValue: string;
  nTotalFileHaveSize: QWORD;
  nSeqFileSize: QWORD;
  fLeftTime: Double;
  fValue: Double;
begin
  if not Assigned(hDownloader) then
  begin
    Exit;
  end;

  Memo2.Text := '';

  if FTK_Downloader_GetState(hDownloader) = DLSTATE_CHECKING then
  begin
    Memo2.Lines.Add('Status: checking file...');
  end
  else if FTK_Downloader_GetState(hDownloader) = DLSTATE_DOWNLOAD then
  begin
    Memo2.Lines.Add('Status: downloading...');

    {if bSetSeq = False then
    begin
      //如果想顺序下载，请调用此函数,参数为True，如果想恢复原来的下载模式，
      //也调用此函数，参数为False
      FTK_Downloader_SetSeqPicker(hDownloader, True);
      bSetSeq := True;
    end;}
  end
  else if FTK_Downloader_GetState(hDownloader) = DLSTATE_FETALERR then
  begin
    Memo2.Lines.Add('Status: downloading error...');
  end
  else if FTK_Downloader_GetState(hDownloader) = DLSTATE_TERMINATE then
  begin
    Memo2.Lines.Add('Status: stopping...');
  end;

  sValue := IFormatByte(nTotalFileSize);
  Memo2.Lines.Add('File size: ' + sValue);

  if (FTK_Downloader_GetState(hDownloader) = DLSTATE_CHECKING) and (nPieceCount > 0) then
  begin
    ProgressBar1.Position := FTK_Stat_GetCheckPieceCount(hDownloader) * 100 div nPieceCount;
  end;

  if FTK_Downloader_GetState(hDownloader) < DLSTATE_DOWNLOAD then
  begin
    Exit;
  end;

  if FTK_Downloader_GetState(hDownloader) >= DLSTATE_FETALERR then
  begin
    Exit;
  end;

  nTotalFileHaveSize := FTK_Stat_GetTotalFileHaveSize(hDownloader);
  ProgressBar1.Position := nTotalFileHaveSize * 100 div nTotalFileSize;
  GroupBox2.Caption := 'Downloaded progress: ' + IntToStr(ProgressBar1.Position) + '%';

  nSeqFileSize := FTK_Stat_GetStartSeqFileSize(hDownloader);
  nSeqFileSize := nSeqFileSize div (1024 * 1024);
  sValue := IntToStr(nSeqFileSize);
  Memo2.Lines.Add('Seqence Size: ' + sValue + ' MB');

  sValue := FFormatByte(Double(FTK_Stat_GetDownloadRate(hDownloader)));
  Memo2.Lines.Add('Down Speed: ' + sValue + '/s');

  sValue := FFormatByte(FTK_Stat_GetUploadRate(hDownloader));
  Memo2.Lines.Add('Up Speed: ' + sValue + '/s');

  fLeftTime := FTK_Stat_GetLeftTime(hDownloader);

  fValue := fLeftTime / (60.0 * 60.0);
  sValue := Format('%fh : ', [fValue]);

  fValue := (fLeftTime - fValue) / 60.0;
  sValue := sValue + Format('%fm : ', [fValue]);

  fValue := fLeftTime - fValue;
  sValue := sValue + Format('%fs', [fValue]);

  Memo2.Lines.Add('Left time: ' + sValue);

  sValue := IFormatByte(nTotalFileHaveSize);
  Memo2.Lines.Add('Downloaded: ' + sValue);

  sValue := IFormatByte(FTK_Stat_GetUploaded(hDownloader));
  Memo2.Lines.Add('Uploaded: ' + sValue);

  sValue := 'Peers: ' + IntToStr(FTK_Stat_GetTotalPeerCount(hDownloader));
  sValue := sValue + '(' + IntToStr(FTK_Stat_GetActivePeerCount(hDownloader));
  sValue := sValue + '/' + IntToStr(FTK_Stat_GetPassivePeerCount(hDownloader)) + ')';

  Memo2.Lines.Add(sValue);

  sValue := 'Seeds: ' + IntToStr(FTK_Stat_GetSeedCount(hDownloader));

  Memo2.Lines.Add(sValue);

  sValue := 'Uploaded: ' + IntToStr(FTK_Stat_GetUploadPeerCount(hDownloader));
  sValue := sValue + '/Downloaded: ' + IntToStr(FTK_Stat_GetDownloadPeerCount(hDownloader));

  Memo2.Lines.Add(sValue);

  if ProgressBar1.Position >= 100 then
  begin
    Memo2.Lines.Add('Downloaded OK...');
  end;
end;

procedure TMainFrm.Button4Click(Sender: TObject);
var
  i: Integer;
begin

  if nil = hDownloader then
  begin
    Exit;
  end;

  try
    sTorrentFileName := sTorrentFile;
    FilesForm := TFilesForm.Create(self);
    if FilesForm.ShowModal() = mrOK then
    begin
      for i := 0 to nTotalFileCount - 1 do
      begin
        FTK_Downloader_SetFilePriority(hDownloader, i, aFilePriority[i], FALSE);
      end;
      FTK_Downloader_ForceFilePriority(hDownloader);

    end;
    FilesForm.Destroy();
  except
  end;
end;

procedure TMainFrm.Button5Click(Sender: TObject);
var
  form: TMTForm;
begin
  form := TMTForm.Create(Self);
  try
    form.ShowModal();
  except

  end;
end;

procedure TMainFrm.Button6Click(Sender: TObject);
begin
  StopDownload();
  Button2.Enabled := True;
  Button6.Enabled := False;
  Button1.Enabled := True;
end;

end.


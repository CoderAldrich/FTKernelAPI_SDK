unit MTThread;

interface
uses
  windows, Classes, MakeTorrent, MTProgress, FTKernelAPI, SysUtils;
type
  TMTThread = class(TThread)
  private
    { Private declarations }
  protected
    procedure Execute; override;
  end;
implementation
{ TMTThread }

procedure TMTThread.Execute;
var
  i: Integer;
  arryAList: array of LPCSTR;
  sVal: string;
  slTemp: TStrings;
  j: Integer;
begin
  { Place thread code here }

  FTK_MT_SetAnnounceUrl(g_hMakeTorrent, PChar(sMainAnnounce));

  {    SetLength( arryAList, slAnnounces.Count );
      for i := 0 to slAnnounces.Count - 1 do
      begin
         arryAList[ i ] := AllocMem( 1024 );
         //StrCopy( arryAList[ i ], PChar( slAnnounces[ i ] ) );
      end;

      FTK_MT_AddAnnounceList( g_hMakeTorrent, arryAList, slAnnounces.Count );
      for i := 0 to slAnnounces.Count - 1 do
      begin
          FreeMem( arryAList[ i ] );
      end;
      SetLength( arryAList, 0 ); }
  for i := 0 to slAnnounces.Count - 1 do
  begin
    sVal := sVal + slAnnounces[i];
    sVal := sVal + ';';
  end;

  FTK_MT_AddAnnounceList2(g_hMakeTorrent, PChar(sVal));
  sVal := '';

  FTK_MT_SetComments(g_hMakeTorrent, PChar(sNote));

  if bIsFile then
  begin
    FTK_MT_SetFile(g_hMakeTorrent, PChar(sSourceName));
  end
  else
  begin
    FTK_MT_SetPath(g_hMakeTorrent, PChar(sSourceName));
  end;

  FTK_MT_SetPieceSize(g_hMakeTorrent, dwPieceSize);
  FTK_MT_SetLangCodePage(g_hMakeTorrent, 936);

  FTK_MT_MakeTorrent(g_hMakeTorrent);

  if sPassword = '' then
  begin
    FTK_MT_SaveAsTorrentFile(g_hMakeTorrent, PChar(sDestFileName), nil);
  end
  else
  begin
    FTK_MT_SaveAsTorrentFile(g_hMakeTorrent, PChar(sDestFileName), PChar(sPassword));
  end;

end;

end.

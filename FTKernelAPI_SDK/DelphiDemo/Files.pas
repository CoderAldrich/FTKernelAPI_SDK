unit Files;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, CheckLst, ComCtrls, FTKernelAPI;

type
  TFilesForm = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Label1: TLabel;
    ListView1: TListView;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }

  end;

var
  FilesForm: TFilesForm;
  sTorrentFileName: string;
  aFilePriority: ArrayByte;
  nTotalFileCount: Integer;
implementation

uses
  Main;

{$R *.dfm}

procedure TFilesForm.FormCreate(Sender: TObject);
var
  xhTorrentFile: HTorrentFile;
  aFileInfo: ArrayFileInfo;
  nFilesCount: Integer;
  nTotalFileSize: QWord;
  i: Integer;
  ListItem: TListItem;
begin
  xhTorrentFile := FTK_Torrent_Open(PAnsiChar(sTorrentFileName));
  if not assigned(xhTorrentFile) then
  begin
    Application.MessageBox(PChar('Failed to open torrent file!' + sTorrentFileName), 'error');
    Exit;
  end;

  if not FTK_Torrent_IsFile(xhTorrentFile) then
  begin
    nFilesCount := FTK_Torrent_GetFilesCount(xhTorrentFile);
    SetLength(aFileInfo, nFilesCount);

    FTK_Torrent_GetFiles(xhTorrentFile, aFileInfo);
    nTotalFileSize := FTK_Torrent_GetFileSize(xhTorrentFile);
    for i := 0 to nFilesCount - 1 do
    begin
      ListItem := ListView1.Items.Add();
      ListItem.Checked := True;
      ListItem.Caption := aFileInfo[i].m_szFileName;
      ListItem.SubItems.Add(IFormatByte(aFileInfo[i].m_qwFileSize));
      ListItem.SubItems.Add(Format('%f', [aFileInfo[i].m_qwFileSize * 100 / nTotalFileSize]));
    end;

    {
        // insert the item.
        m_wndFiles.InsertItem( i, pFileInfo[ i ].m_szFileName, 0 );

        CString strSize = AfxFormatBytes( ( INT64 ) pFileInfo[ i ].m_qwFileSize );
        CString strPercent;
        strPercent.Format( _T( "%lf" ), PERCENT( ( INT64 ) pFileInfo[ i ].m_qwFileSize, ( INT64 ) FTK_Torrent_GetFileSize( hTorrentFile ) ) );
        m_wndFiles.SetItemText( i, 1, strSize );
        m_wndFiles.SetItemText( i, 2, strPercent );
    }

  end
  else
  begin
    ListItem := ListView1.Items.Add();
    ListItem.Caption := FTK_Torrent_GetTorrentName(xhTorrentFile);
    ListItem.SubItems.Add(IFormatByte(FTK_Torrent_GetFileSize(xhTorrentFile)));
    ListItem.SubItems.Add('100');
    ListItem.Checked := True;
  end;
end;

procedure TFilesForm.Button1Click(Sender: TObject);
var
  i: Integer;
begin
  for i := 0 to ListView1.Items.Count - 1 do
  begin
    ListView1.Items.Item[i].Checked := True;
  end;
end;

procedure TFilesForm.Button3Click(Sender: TObject);
var
  i: Integer;
begin
  for i := 0 to ListView1.Items.Count - 1 do
  begin
    ListView1.Items.Item[i].Checked := not ListView1.Items.Item[i].Checked;
  end;
end;

procedure TFilesForm.Button2Click(Sender: TObject);
var
  i: Integer;
begin
  for i := 0 to ListView1.Items.Count - 1 do
  begin
    ListView1.Items.Item[i].Checked := False;
  end;
end;

procedure TFilesForm.Button4Click(Sender: TObject);
var
  i: Integer;
begin
  SetLength(aFilePriority, ListView1.Items.Count);
  for i := 0 to ListView1.Items.Count - 1 do
  begin
    if ListView1.Items.Item[i].Checked = True then
    begin
      aFilePriority[i] := 0;
    end
    else
    begin
      aFilePriority[i] := BYTE(-2);
    end;
  end;

  nTotalFileCount := ListView1.Items.Count;
end;

end.

unit MTProgress;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, FTKernelAPI, ExtCtrls;

type
  TMTPForm = class(TForm)
    OK: TButton;
    Cancel: TButton;
    ProgressBar1: TProgressBar;
    Timer1: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure OKClick(Sender: TObject);
    procedure CancelClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }


  end;

var
  MTPForm: TMTPForm;
  g_hMakeTorrent: HMakeTorrent;
implementation

uses
  MTThread;

var
  MTThread: TMTThread;

{$R *.dfm}

procedure TMTPForm.FormCreate(Sender: TObject);
begin
  g_hMakeTorrent := FTK_MT_Open();
  if nil = g_hMakeTorrent then
  begin
    Application.MessageBox('Failed to open handle!', 'Warning');
    Exit;
  end;

  MTThread := TMTThread.Create(False);
  Ok.Enabled := False;
  Cancel.Enabled := True;

end;

procedure TMTPForm.Timer1Timer(Sender: TObject);
begin

  if nil = g_hMakeTorrent then
  begin
    Timer1.Enabled := False;
    exit;
  end;

  ProgressBar1.Position := Round(FTK_MT_GetMTProgress(g_hMakeTorrent));

  if ProgressBar1.Position >= 100 then
  begin
    Sleep(10);
    Ok.Enabled := True;
    Cancel.Enabled := False;

    Timer1.Enabled := False;

    MessageBeep(MB_ICONEXCLAMATION);
  end;
end;

procedure TMTPForm.OKClick(Sender: TObject);
begin
  MTThread.WaitFor();
  FTK_MT_Close(g_hMakeTorrent);
  g_hMakeTorrent := nil;
  Self.Close();
end;

procedure TMTPForm.CancelClick(Sender: TObject);
begin
  if nil <> g_hMakeTorrent then
  begin
    FTK_MT_StopMake(g_hMakeTorrent);
  end;

  MTThread.WaitFor();
  Sleep(100);
  FTK_MT_Close(g_hMakeTorrent);
  g_hMakeTorrent := nil;
  Self.Close();
end;

end.

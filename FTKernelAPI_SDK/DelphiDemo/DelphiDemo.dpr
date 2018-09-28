program DelphiDemo;

uses
  Forms,
  Main in 'Main.pas' {MainFrm},
  FTKernelAPI in 'FTKernelAPI.pas',
  Files in 'Files.pas' {FilesForm},
  MakeTorrent in 'MakeTorrent.pas' {MTForm},
  MTProgress in 'MTProgress.pas' {MTPForm},
  MTThread in 'MTThread.pas',
  InputPwd in 'InputPwd.pas' {PwdForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainFrm, MainFrm);
  Application.Run;
end.


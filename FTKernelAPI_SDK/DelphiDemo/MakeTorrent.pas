unit MakeTorrent;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, FileCtrl;

type
  TMTForm = class(TForm)
    Label1: TLabel;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    Edit1: TEdit;
    Button1: TButton;
    OpenDialog1: TOpenDialog;
    DirectoryListBox1: TDirectoryListBox;
    DriveComboBox1: TDriveComboBox;
    Label2: TLabel;
    Edit2: TEdit;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Edit3: TEdit;
    Button2: TButton;
    SaveDialog1: TSaveDialog;
    Label6: TLabel;
    ComboBox1: TComboBox;
    CheckBox1: TCheckBox;
    Label7: TLabel;
    Edit4: TEdit;
    Button3: TButton;
    Button4: TButton;
    Memo1: TMemo;
    Memo2: TMemo;
    procedure Button1Click(Sender: TObject);
    procedure RadioButton2Click(Sender: TObject);
    procedure DirectoryListBox1Change(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }

    function GetPieceSize(i: Integer): DWord;
  public
    { Public declarations }
  end;

var
  MTForm: TMTForm;

  dwPieceSize: DWord;
  sSourceName: string;
  bIsFile: Boolean;
  sMainAnnounce: string;
  slAnnounces: TStrings;
  sNote: string;
  sDestFileName: string;
  sPassword: string;

implementation

uses MTProgress;

{$R *.dfm}

procedure TMTForm.Button1Click(Sender: TObject);
begin
  if RadioButton1.Checked then
  begin
    if OpenDialog1.Execute() then
    begin
      Edit1.Text := OpenDialog1.FileName;
      Edit3.Text := Edit1.Text + '.Torrent';
    end;

    exit;
  end;

  if RadioButton2.Checked then
  begin

  end;

end;

procedure TMTForm.RadioButton2Click(Sender: TObject);
begin

  DriveComboBox1.Enabled := RadioButton2.Checked;
  DirectoryListBox1.Enabled := RadioButton2.Checked;

end;

procedure TMTForm.DirectoryListBox1Change(Sender: TObject);
begin
  Edit1.Text := DirectoryListBox1.Directory;
end;

procedure TMTForm.Button4Click(Sender: TObject);
begin
  Self.Close();
end;

procedure TMTForm.Button3Click(Sender: TObject);
begin
  if Edit1.Text = '' then
  begin
    Application.MessageBox('Please select a file or directory!', 'Warning');
    exit;
  end;

  if Edit2.Text = '' then
  begin
    Application.MessageBox('Please input a main announce URL!', 'Warning');
    exit;
  end;

  if Edit3.Text = '' then
  begin
    Application.MessageBox('Please select out torrent name!', 'Warning');
    exit;
  end;

  dwPieceSize := GetPieceSize(ComboBox1.ItemIndex);
  sSourceName := Edit1.Text;
  bIsFile := RadioButton1.Checked;
  sMainAnnounce := Edit2.Text;
  slAnnounces := Memo1.Lines;
  sNote := Memo2.Lines.Text;
  sDestFileName := Edit3.Text;
  sPassword := Edit4.Text;

  MTPForm := TMTPForm.Create(Self);
  MTPForm.ShowModal();
end;

procedure TMTForm.CheckBox1Click(Sender: TObject);
begin
  Edit4.Enabled := CheckBox1.Checked;
end;

procedure TMTForm.Button2Click(Sender: TObject);
begin
  SaveDialog1.Filter := 'Torrent files (*.torrent)|*.torrent';
  if SaveDialog1.Execute() then
  begin
    Edit3.Text := SaveDialog1.FileName;
  end;
end;

function TMTForm.GetPieceSize(i: Integer): DWord;
begin
  Result := 1024 * 32;

  if i = 0 then
  begin
    Result := $FFFFFFFF;
  end
  else if i = 1 then
  begin
    Result := 1024 * 32;
  end
  else if i = 2 then
  begin
    Result := 1024 * 64;
  end
  else if i = 3 then
  begin
    Result := 1024 * 128;
  end
  else if i = 4 then
  begin
    Result := 1024 * 256;
  end
  else if i = 5 then
  begin
    Result := 1024 * 512;
  end
  else if i = 6 then
  begin
    Result := 1024 * 1024;
  end
  else if i = 7 then
  begin
    Result := 1024 * 1024 * 2;
  end
end;

end.

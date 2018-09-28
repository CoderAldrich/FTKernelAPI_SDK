object MTForm: TMTForm
  Left = 356
  Top = 88
  Width = 486
  Height = 501
  Caption = 'MTForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 73
    Height = 13
    Caption = 'File or Directory'
  end
  object Label2: TLabel
    Left = 8
    Top = 176
    Width = 78
    Height = 13
    Caption = 'Main Announce:'
  end
  object Label3: TLabel
    Left = 8
    Top = 208
    Width = 79
    Height = 13
    Caption = 'More Announce:'
  end
  object Label4: TLabel
    Left = 8
    Top = 288
    Width = 26
    Height = 13
    Caption = 'Note:'
  end
  object Label5: TLabel
    Left = 8
    Top = 344
    Width = 68
    Height = 13
    Caption = 'Torrent Name:'
  end
  object Label6: TLabel
    Left = 8
    Top = 376
    Width = 53
    Height = 13
    Caption = 'Piece Size:'
  end
  object Label7: TLabel
    Left = 272
    Top = 408
    Width = 49
    Height = 13
    Caption = 'Password:'
  end
  object RadioButton1: TRadioButton
    Left = 96
    Top = 8
    Width = 57
    Height = 17
    Caption = 'File'
    Checked = True
    TabOrder = 0
    TabStop = True
  end
  object RadioButton2: TRadioButton
    Left = 176
    Top = 8
    Width = 113
    Height = 17
    Caption = 'Directory'
    TabOrder = 1
    OnClick = RadioButton2Click
  end
  object Edit1: TEdit
    Left = 8
    Top = 24
    Width = 385
    Height = 21
    TabOrder = 2
  end
  object Button1: TButton
    Left = 400
    Top = 21
    Width = 75
    Height = 25
    Caption = '...'
    TabOrder = 3
    OnClick = Button1Click
  end
  object DirectoryListBox1: TDirectoryListBox
    Left = 8
    Top = 72
    Width = 457
    Height = 97
    Enabled = False
    ItemHeight = 16
    TabOrder = 4
    OnChange = DirectoryListBox1Change
  end
  object DriveComboBox1: TDriveComboBox
    Left = 8
    Top = 48
    Width = 145
    Height = 19
    DirList = DirectoryListBox1
    Enabled = False
    TabOrder = 5
  end
  object Edit2: TEdit
    Left = 96
    Top = 176
    Width = 369
    Height = 21
    TabOrder = 6
  end
  object Memo1: TMemo
    Left = 96
    Top = 208
    Width = 369
    Height = 73
    TabOrder = 7
  end
  object Memo2: TMemo
    Left = 40
    Top = 296
    Width = 425
    Height = 41
    TabOrder = 8
  end
  object Edit3: TEdit
    Left = 80
    Top = 344
    Width = 313
    Height = 21
    TabOrder = 9
  end
  object Button2: TButton
    Left = 400
    Top = 344
    Width = 75
    Height = 25
    Caption = '...'
    TabOrder = 10
    OnClick = Button2Click
  end
  object ComboBox1: TComboBox
    Left = 72
    Top = 376
    Width = 193
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 11
    Text = 'Automatic'
    Items.Strings = (
      'Automatic'
      '32 KB (1024 * 32)'
      '64 KB (1024 * 64)'
      '128 KB (1024 * 128)'
      '256 KB (1024 * 256)'
      '512 KB (1024 * 512)'
      '1 MB (1024 * 1024 * 1)'
      '2 MB (1024 * 1024 * 2)')
  end
  object CheckBox1: TCheckBox
    Left = 280
    Top = 376
    Width = 97
    Height = 17
    Caption = 'Encrypt Torrent'
    TabOrder = 12
    OnClick = CheckBox1Click
  end
  object Edit4: TEdit
    Left = 328
    Top = 407
    Width = 137
    Height = 21
    Enabled = False
    TabOrder = 13
  end
  object Button3: TButton
    Left = 136
    Top = 432
    Width = 75
    Height = 25
    Caption = 'Start'
    TabOrder = 14
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 232
    Top = 432
    Width = 75
    Height = 25
    Caption = 'Exit'
    TabOrder = 15
    OnClick = Button4Click
  end
  object OpenDialog1: TOpenDialog
    Left = 424
    Top = 16
  end
  object SaveDialog1: TSaveDialog
    Left = 424
    Top = 344
  end
end

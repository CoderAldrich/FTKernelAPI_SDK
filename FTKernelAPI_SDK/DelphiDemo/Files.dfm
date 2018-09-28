object FilesForm: TFilesForm
  Left = 295
  Top = 265
  Width = 462
  Height = 392
  Caption = 'Torrent Files'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 24
    Height = 13
    Caption = 'Files:'
  end
  object Button1: TButton
    Left = 16
    Top = 320
    Width = 75
    Height = 25
    Caption = '&Sel ALL'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 192
    Top = 320
    Width = 75
    Height = 25
    Caption = '&Desel ALL'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 104
    Top = 320
    Width = 75
    Height = 25
    Caption = '&Invert Select'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 280
    Top = 321
    Width = 75
    Height = 25
    Caption = '&OK'
    ModalResult = 1
    TabOrder = 3
    OnClick = Button4Click
  end
  object ListView1: TListView
    Left = 8
    Top = 32
    Width = 433
    Height = 281
    Checkboxes = True
    Columns = <
      item
        Caption = 'FileName'
        Width = 200
      end
      item
        Caption = 'FileSize'
      end
      item
        Caption = '%'
      end>
    TabOrder = 4
    ViewStyle = vsReport
  end
end

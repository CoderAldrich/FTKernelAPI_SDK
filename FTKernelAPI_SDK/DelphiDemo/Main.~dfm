object MainFrm: TMainFrm
  Left = 109
  Top = 238
  Width = 500
  Height = 497
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 449
    Height = 49
    Caption = '&Select a torrent file'
    TabOrder = 0
    object Edit1: TEdit
      Left = 8
      Top = 16
      Width = 353
      Height = 21
      TabOrder = 0
    end
    object Button1: TButton
      Left = 368
      Top = 13
      Width = 75
      Height = 25
      Caption = '...'
      TabOrder = 1
      OnClick = Button1Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 64
    Width = 449
    Height = 49
    Caption = '&Downloading progress'
    TabOrder = 1
    object ProgressBar1: TProgressBar
      Left = 8
      Top = 19
      Width = 433
      Height = 23
      TabOrder = 0
    end
  end
  object Memo1: TMemo
    Left = 8
    Top = 120
    Width = 449
    Height = 89
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object Button2: TButton
    Left = 0
    Top = 421
    Width = 75
    Height = 25
    Caption = '&Start'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 259
    Top = 421
    Width = 75
    Height = 25
    Caption = '&Exit'
    TabOrder = 4
    OnClick = Button3Click
  end
  object Memo2: TMemo
    Left = 8
    Top = 216
    Width = 449
    Height = 193
    BevelInner = bvLowered
    BevelOuter = bvRaised
    Lines.Strings = (
      'Memo1')
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 5
  end
  object Button4: TButton
    Left = 88
    Top = 421
    Width = 75
    Height = 25
    Caption = '&Files'
    TabOrder = 6
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 344
    Top = 421
    Width = 75
    Height = 25
    Caption = '&MakeTorrent'
    TabOrder = 7
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 171
    Top = 421
    Width = 75
    Height = 25
    Caption = '&Stop'
    TabOrder = 8
    OnClick = Button6Click
  end
  object OpenDialog1: TOpenDialog
    Left = 384
    Top = 16
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 432
    Top = 408
  end
end

object MTPForm: TMTPForm
  Left = 209
  Top = 224
  Width = 421
  Height = 129
  Caption = 'MTPForm'
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
  object OK: TButton
    Left = 72
    Top = 64
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 0
    OnClick = OKClick
  end
  object Cancel: TButton
    Left = 176
    Top = 64
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 1
    OnClick = CancelClick
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 24
    Width = 385
    Height = 17
    TabOrder = 2
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 320
    Top = 56
  end
end

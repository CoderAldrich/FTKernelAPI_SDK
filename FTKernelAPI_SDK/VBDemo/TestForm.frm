VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form TestForm 
   Caption         =   "TestFTKernelAPI"
   ClientHeight    =   3825
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8175
   LinkTopic       =   "Form1"
   ScaleHeight     =   3825
   ScaleWidth      =   8175
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   3600
      Top             =   3240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Torrent"
      Height          =   375
      Left            =   6720
      TabIndex        =   2
      Top             =   120
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   6495
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   4200
      Top             =   3240
   End
   Begin VB.CommandButton Command1 
      Caption         =   "StartDownload"
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   3240
      Width           =   1455
   End
   Begin VB.Label Label4 
      Height          =   495
      Left            =   0
      TabIndex        =   6
      Top             =   2520
      Width           =   6735
   End
   Begin VB.Label Label3 
      Caption         =   "Upload Speed:"
      Height          =   495
      Left            =   120
      TabIndex        =   5
      Top             =   1800
      Width           =   6615
   End
   Begin VB.Label Label2 
      Caption         =   "Download Speed:"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   1200
      Width           =   6495
   End
   Begin VB.Label Label1 
      Caption         =   "Progress:"
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   600
      Width           =   6495
   End
End
Attribute VB_Name = "TestForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private HDownloader As Long
Private sInfoKey As String
Private tlFileSize As TwoLong
Private nPieceCount As Long

Private Function TrimNull(Item As String)

    Dim pos As Integer
   
   'double check that there is a chr$  in the string
    pos = InStr(Item, Chr$(0))
    If pos Then
          TrimNull = Left$(Item, pos - 1)
    Else: TrimNull = Item
    End If
  
End Function

Private Sub Command3_Click()
  CommonDialog1.Filter = "(*.torrent)|*.torrent"
  CommonDialog1.FilterIndex = 1
  CommonDialog1.ShowOpen
  Text1.Text = CommonDialog1.FileName
End Sub

Private Sub Form_Load()
  
  HDownloader = 0
  
  Dim bRet As Boolean
  bRet = FTK_Context_Init(vbStringNull, 0)
  If bRet = 0 Then
    MsgBox ("Failed to initialize FTK_Context_Init")
    Exit Sub
  End If
  
  Call FTK_Context_Run
  If FTK_Context_IsRunning() = 0 Then
    MsgBox ("Failed to initialize FTK_Context_Run")
    Exit Sub
  End If

End Sub

Private Sub Form_Unload(Cancel As Integer)
  Timer1.Enabled = False
  If HDownloader <> 0 Then
    Call FTK_GlobalVar_RemoveTorrentSHA1(sInfoKey)
    Call FTK_Downloader_Release(HDownloader)
    Call FTK_Downloader_Close(HDownloader)
    HDownloader = 0
    
    Text1.Enabled = True
    Command3.Enabled = True
  End If
  
  Call FTK_Context_Stop
  Call FTK_Context_Release
End Sub

Private Sub Command1_Click()

    If HDownloader <> 0 Then
      Call FTK_GlobalVar_RemoveTorrentSHA1(sInfoKey)
      Call FTK_Downloader_Release(HDownloader)
      Call FTK_Downloader_Close(HDownloader)
      HDownloader = 0
    
      Text1.Enabled = True
      Command3.Enabled = True
    End If
    
    If Text1.Text = "" Then
        Call Text1.SetFocus
        MsgBox ("Please select a torrent file!")
        Exit Sub
    End If
    
    Dim hTorrentFile As Long
    hTorrentFile = FTK_Torrent_Open(Text1.Text, 0, 0, False, False)
    
    Dim lFilesCount As Long
    
    If hTorrentFile <= 0 Then
        MsgBox ("Failed to open torrent file!")
        Exit Sub
    End If
    
    lFilesCount = FTK_Torrent_GetFilesCount(hTorrentFile)
    
    Dim arryPreAlloc() As Byte
    ReDim arryPreAlloc(lFilesCount - 1) As Byte
    
    Dim incCount As Long
    
    For incCount = 0 To lFilesCount - 1
      arryPreAlloc(incCount) = 1
    Next
    
    tlFileSize = FTK_Torrent_GetFileSize(hTorrentFile)
    nPieceCount = FTK_Torrent_GetPieceCount(hTorrentFile)
    
    Dim bInit As Long
    
    HDownloader = FTK_Downloader_Open()
    bInit = FTK_Downloader_Init(HDownloader, Text1.Text, arryPreAlloc(0), lFilesCount, 0, "c:\", 0, 0, 0, 0, 0, 0)
    If bInit = 0 Then
      MsgBox ("FTK_Downloader_Init failed!")
      Call FTK_Downloader_Close(HDownloader)
      Exit Sub
    End If
    
    bInit = FTK_Downloader_Execute(HDownloader)
    If bInit = 0 Then
      MsgBox ("FTK_Downloader_Init failed!")
      Call FTK_Downloader_Close(HDownloader)
      Exit Sub
    End If
    
    sInfoKey = TrimNull(FTK_Torrent_GetHexInfoHash(hTorrentFile))
    sInfoKey = Replace(sInfoKey, "%", "")
    'MsgBox (sInfoKey)
    
    Call FTK_GlobalVar_AddTorrentSHA1(sInfoKey, HDownloader)
    Call FTK_Torrent_Close(hTorrentFile)
    
    Text1.Enabled = False
    Command3.Enabled = False
    Command1.Enabled = False
    Timer1.Enabled = True

End Sub

Private Sub Timer1_Timer()
  If HDownloader <= 0 Then
    Exit Sub
  End If
  
  If FTK_Downloader_GetState(HDownloader) = DLSTATE_CHECKING Then
    Label4.Caption = "Status: checking file..."
  ElseIf FTK_Downloader_GetState(HDownloader) = DLSTATE_DOWNLOAD Then
    Label4.Caption = "Status: downloading file..."
  ElseIf FTK_Downloader_GetState(HDownloader) = DLSTATE_FETALERR Then
    Label4.Caption = "Status: downloading error..."
  ElseIf FTK_Downloader_GetState(HDownloader) = DLSTATE_TERMINATE Then
    Label4.Caption = "Status: stopping..."
  End If

  Dim nPos As Long
  If FTK_Downloader_GetState(HDownloader) = DLSTATE_CHECKING Then
    nPos = FTK_Stat_GetCheckPieceCount(HDownloader)
    nPercent = nPos * 100 / nPieceCount
    Label1.Caption = "Checking progress: "
    Label1.Caption = Label1.Caption + Str(nPercent)
    Label1.Caption = Label1.Caption + "%"
  End If

  If FTK_Downloader_GetState(HDownloader) = DLSTATE_FETALERR Then
    Exit Sub
  End If
  
  If FTK_Downloader_GetState(HDownloader) <> DLSTATE_DOWNLOAD Then
    Exit Sub
  End If
  
  Dim tlFileHaveSize As TwoLong
  tlFileHaveSize = FTK_Stat_GetTotalFileHaveSize(HDownloader)
  nPos = CInt(GetDoubleFromTwoLong(tlFileHaveSize) * 100 / GetDoubleFromTwoLong(tlFileSize))
  Label1.Caption = "Downloading progress: "
  Label1.Caption = Label1.Caption + Str(nPos)
  Label1.Caption = Label1.Caption + "%"
  
  Dim dfSpeed As Double
  dfSpeed = FTK_Stat_GetDownloadRate(HDownloader)
  dfSpeed = dfSpeed / 1024#
  Label2.Caption = "Down Speed: "
  Label2.Caption = Label2.Caption + Str(dfSpeed) + " Kb/s"
    
  dfSpeed = FTK_Stat_GetUploadRate(HDownloader)
  dfSpeed = dfSpeed / 1024#
  Label3.Caption = "Up Speed: "
  Label3.Caption = Label2.Caption + Str(dfSpeed) + " Kb/s"
    
  If nPos >= 100 Then
    Label4.Caption = "Status: Downloaded OK..."
  End If

End Sub

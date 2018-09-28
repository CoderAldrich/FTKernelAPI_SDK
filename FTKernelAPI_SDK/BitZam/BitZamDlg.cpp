  // BitZamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BitZam.h"
#include "BitZamDlg.h"
#include "DlgProxySettings.h"
#include "DlgMakeTorrent.h"
#include "DlgOpenTorrentFile.h"
#include "DlgSelFiles.h"
#include "DlgAddExtAnnounce.h"
#include "DlgAddPeer.h"
#include "DlgLinkURL.h"

//内网穿透需要的两个辅助头文件
#include "FTKTCPxAPI.h"
#include "FTKUDPxAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////

//将给出的字符串以(%xx格式表示)
static CString AfxHexEncode( const BYTE *pData, int nLen )
{
    CString strResult = "";
    CString strTemp = "";

    for ( int i = 0; i < nLen; i++ )
    {
        strTemp.Format( "%.2X", pData[ i ] );
        strResult += strTemp;
    }

    return strResult;
}

//////////////////////////////////////////////////////////////////////////

static BOOL bTorrentDataMode = FALSE;
static CBitZamDlg *g_pBitZamDlg = NULL;

//内网穿透辅助服务器的地址
static CString g_strUDPServerIP = _T( "218.61.232.242" );

//通过链接下载时的链接地址
static CString g_strLinkURL = _T( "" );

//////////////////////////////////////////////////////////////////////////

//保留当前主动连接来的socket信息，注意如果是多任务下，此处要做针对每个任务保存一个列表
static unsigned int g_nSocket = 0;

//定义被动通知的回调函数
//Define callback function type
static BOOL BTAPI ftk_callback_func( unsigned int nSocket = 0, const unsigned char *pData = NULL )
{
	if ( NULL != g_pBitZamDlg )
	{
		g_nSocket = nSocket;
		g_pBitZamDlg ->PostMessage( WM_COMMAND, MAKEWPARAM( 1022, BN_CLICKED ), NULL );
	}

	return TRUE;
}

typedef struct _tagTunnelInfo
{
	char _szIP[ 64 ];
	USHORT _nPort;
	BYTE _pPeerID[ 20 ];
	BYTE _pInfoHash[ 20 ];
} CTunnelInfo;

//外部设置内网连接通知回调函数的指针
//Define callback function for Nat PEER notification
static BOOL BTAPI ftk_nat_peer_callback ( BYTE *pInfoHash, LPCTSTR lpszIP, unsigned short nPort, BYTE *pPeerID )
{
	//AfxMessageBox( lpszIP );
	CTunnelInfo *pTunnelInfo = new CTunnelInfo;
	ASSERT( NULL != pTunnelInfo );
	strcpy( pTunnelInfo ->_szIP, lpszIP );
	pTunnelInfo ->_nPort = nPort;
	memcpy( pTunnelInfo ->_pPeerID, pPeerID, 20 );
	memcpy( pTunnelInfo ->_pInfoHash, pInfoHash, 20 );
	g_pBitZamDlg ->PostMessage( WM_MSG_TUNNEL, ( WPARAM )pTunnelInfo, 0 );
	return TRUE;
}

//外部设置任务开始前通知回调函数的指针
static void BTAPI ftk_before_down_callback ( HDownloader hDownloader, HANDLE hEvent, BOOL bOnlyCheckFile )
{
	ASSERT( NULL != hDownloader );
	AfxMessageBox( _T( "Before download" ) );
	return;
}

//外部设置任务下载完毕后通知回调函数的指针
static void BTAPI ftk_on_complete_callback ( HDownloader hDownloader, HANDLE hEvent, BOOL bOnlyCheckFile )
{
	ASSERT( NULL != hDownloader );
	AfxMessageBox( _T( "On Complete" ) );
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_stdHwysoft;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, 1001, m_stdHwysoft);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitZamDlg dialog

CBitZamDlg::CBitZamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBitZamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBitZamDlg)
	m_strTorrentFile = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hDownloader	= NULL;
	m_bInitContext	= FALSE;
	m_qwTotalFileSize	= 0L;
	m_dwPieceCount	= 0L;

	g_pBitZamDlg = this;

	//内网穿透是否初始化
	m_bInitUDP = FALSE;
}

void CBitZamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBitZamDlg)
	DDX_Control(pDX, 1026, m_stdKernelLink);
	DDX_Control(pDX, 1013, m_pgrDownload);
	DDX_Text(pDX, 1010, m_strTorrentFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBitZamDlg, CDialog)
	//{{AFX_MSG_MAP(CBitZamDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(1001, OnExit)
	ON_WM_CLOSE()
	ON_BN_CLICKED(1011, OnSelTorrentFile)
	ON_BN_CLICKED(1022, OnStartDownload)
	ON_BN_CLICKED(1002, OnProxySettings)
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(1003, OnMakeTorrent)
	ON_BN_CLICKED(1004, OnSelFiles)
	ON_BN_CLICKED(1005, OnAddExtAnnounce)
	ON_BN_CLICKED(1006, OnAddPeer)
	ON_BN_CLICKED(1007, OnManualAnnounce)
	ON_BN_CLICKED(1029, OnTorrentData)
	ON_BN_CLICKED(1031, On1031)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(1034, On1034)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_MSG_TUNNEL, OnNatTunnel )
	ON_MESSAGE( WM_MSG_PEERCALL, OnPeerCall )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitZamDlg message handlers

BOOL CBitZamDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	int nSize = sizeof( _tagAnnounceData );

	m_stdKernelLink.SetColours( RGB( 0, 0, 255 ), RGB( 200, 0, 0 ), RGB( 0, 0, 180 ) );
 	m_stdKernelLink.SetURL( _T("http://wwww.hwysoft.com") );

    ( ( CSliderCtrl * ) GetDlgItem( 1015 ) ) ->SetRange( 20, 8192 );
    ( ( CSliderCtrl * ) GetDlgItem( 1015 ) ) ->SetPos( 8192 );
	SetDlgItemText( 1016, _T("Unlimited") );

    ( ( CSliderCtrl * ) GetDlgItem( 1027 ) ) ->SetRange( 10, 4096 );
    ( ( CSliderCtrl * ) GetDlgItem( 1028 ) ) ->SetPos( 4096 );
	SetDlgItemText( 1028, _T("Unlimited") );
	
	m_pgrDownload.SetShowText( TRUE );

	SetTimer( 2008, 1000, NULL );

	//内网穿透服务器的事件定时器
	SetTimer( 3000, 100, NULL );

	//内网穿透服务器的状态定时器
	SetTimer( 3100, 100, NULL );

	//int nSize = sizeof( _tagPeerData );

	if ( !StartContext() )
	{
        AfxMessageBox( _T("Failed to initialize context, Please visit http://www.hwysoft.com to get technical support!") );
		return FALSE;
	}

	//CString strVal = AfxHexEncode( FTK_Context_GetMyPeerID(), 20 );
	//AfxMessageBox( strVal );

	m_bInitContext	= TRUE;

	//内网穿透需要的初始化函数
	if ( !InitNatTunnel() )
	{
        AfxMessageBox( _T("初始化内网穿透失败!") );
	}

	//连接内网穿透服务器
	FTK_UDPX_Login( g_strUDPServerIP, 9999, FTK_Context_GetListenPort(), FTK_TCPX_GetPort(), ( char * )FTK_Context_GetMyPeerID() );
	FTK_Context_SetForceIP( FTK_UDPX_GetRealIP() );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBitZamDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBitZamDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBitZamDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBitZamDlg::OnOK() 
{
	// TODO: Add extra validation here	
}

void CBitZamDlg::OnCancel() 
{
	// TODO: Add extra cleanup here	
}

void CBitZamDlg::OnExit() 
{
	// TODO: Add your control notification handler code here

	if ( NULL != m_hDownloader )
	{
		StopDownload();
	}

	CDialog::OnOK();	
}

void CBitZamDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	OnExit();
}

void CBitZamDlg::OnSelTorrentFile() 
{
	// TODO: Add your control notification handler code here
	
	//通过链接下载时的链接地址
	g_strLinkURL = _T( "" );

    CString strFilter = _T( "Torrent File(*.Torrent)|*.torrent||" );
    CFileDialog OpenDlg( TRUE, _T( "torrent" ), _T( "*.Torrent" ),
                         OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_FILEMUSTEXIST,
                         strFilter );

    if ( IDOK != OpenDlg.DoModal() )
    {
        return ;
    }


	CDlgOpenTorrentFile DlgTorrent;

	DlgTorrent.SetEncrypt( FTK_Torrent_IsCipherTorrent( OpenDlg.GetPathName() ) );
	if ( IDOK != DlgTorrent.DoModal() )
	{
		return ;
	}   
	
	m_strDestPath = DlgTorrent.m_strDestPath;
	m_strDestPath.TrimRight( _T("\\") );
	m_strPassword = DlgTorrent.m_strPassword;
	SetDlgItemText( 1010, OpenDlg.GetPathName() );

	bTorrentDataMode = FALSE;
}

void CBitZamDlg::OnStartDownload() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	
	if ( m_strTorrentFile.IsEmpty() )
	{
		AfxMessageBox( _T("Please select the Torrent file!") );
		return;
	}

	AfxEnableDlgItem( this, 1010, FALSE );
	AfxEnableDlgItem( this, 1011, FALSE );

	BOOL bDownload = FALSE;
	if ( g_strLinkURL.IsEmpty() )
	{
		bDownload = StartDownload();
	}
	else
	{
		bDownload = StartDownload2();
	}

	if ( !bDownload )
	{
        AfxMessageBox( _T("Failed to sart download, Please visit http://www.hwysoft.com to get technical support!") );
		return;
	}

	AfxEnableDlgItem( this, 1022, FALSE );
}

void CBitZamDlg::OnProxySettings() 
{
	// TODO: Add your control notification handler code here
	
	CDlgProxySettings Dlg;
	if ( IDOK != Dlg.DoModal() )
	{
		return;
	}

    int nProxyType = Dlg.m_nProxyType;
    BOOL bAuthRequired = Dlg.m_bAuthRequired;
    CString strProxyServer = Dlg.m_strProxyServer;
    int nProxyPort = Dlg.m_nProxyPort;
    BOOL bUseOnlyHTTP = Dlg.m_bUseOnlyHTTP;
    CString strUserName = Dlg.m_strUserName;
    CString strPassword = Dlg.m_strPassword;

	if ( ( nProxyType > 0 && nProxyType <= 4 ) &&
		!strProxyServer.IsEmpty() &&
		( nProxyPort > 0 && nProxyPort <= 65535 ) )
	{
		bAuthRequired = bAuthRequired && ( nProxyType == PROXYTYPE_SOCKS5 || nProxyType == PROXYTYPE_HTTP11 );

		if ( bAuthRequired &&
			!strUserName.IsEmpty() &&
			!strPassword.IsEmpty() )
		{
			FTK_Proxy_SetAuthProxy( nProxyType, 
				strProxyServer, nProxyPort,
				strUserName, strPassword );
		}
		else
		{
			FTK_Proxy_SetProxy( nProxyType, 
				strProxyServer, nProxyPort );
		}

		FTK_Proxy_SetOnlyTracker( bUseOnlyHTTP );
	}
	else
	{
		FTK_Proxy_SetType( PROXYTYPE_NOPROXY );
	}
}

void CBitZamDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
    CSliderCtrl * pSliderCtrl = ( CSliderCtrl * ) pScrollBar;
    int nCurrentPos = pSliderCtrl->GetPos();
    CString strValue;
    strValue.Format( _T( "%ld KB/s" ), nCurrentPos );

    if ( 1015 == pSliderCtrl->GetDlgCtrlID() )
    {
        double fMaxDownloadRate = ( double ) nCurrentPos * 1024.0;
        if ( nCurrentPos >= 8192 )
        {
            fMaxDownloadRate = 0.0;
            strValue.Format( _T( "%s" ), _T("Unlimited") );
        }

        SetDlgItemText( 1016, strValue );

		if ( NULL != m_hDownloader )
		{
			FTK_Downloader_SetFixMaxDownloadRate( m_hDownloader, fMaxDownloadRate );
		}
    }

    if ( 1027 == pSliderCtrl->GetDlgCtrlID() )
    {
        double fMaxUploadRate = ( double ) nCurrentPos * 1024.0;
        if ( nCurrentPos >= 4096 )
        {
            fMaxUploadRate = 0.0;
            strValue.Format( _T( "%s" ), _T("Unlimited") );
        }

        SetDlgItemText( 1028, strValue );

		if ( NULL != m_hDownloader )
		{
			FTK_Downloader_SetFixMaxUploadRate( m_hDownloader, fMaxUploadRate );
		}
    }

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

CString GetNatType();
void CBitZamDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if ( nIDEvent == 2008 )
	{
		if ( NULL == m_hDownloader )
		{
			CDialog::OnTimer(nIDEvent);
			return;
		}
		
		CString strValue;
		
		if ( FTK_Downloader_GetState( m_hDownloader ) == DLSTATE_CHECKING )
		{
			strValue = _T("Status: checking file...");		
		}
		else if ( FTK_Downloader_GetState( m_hDownloader ) == DLSTATE_DOWNLOAD )
		{
			strValue = _T("Status: downloading...");		
		}
		else if ( FTK_Downloader_GetState( m_hDownloader ) == DLSTATE_FETALERR )
		{
			strValue = _T("Status: downloading error...");		
		}
		else if ( FTK_Downloader_GetState( m_hDownloader ) == DLSTATE_TERMINATE )
		{
			strValue = _T("Status: stopping...");		
		}
		
		SetDlgItemText( 1017, strValue );
		
		strValue = AfxFormatBytes( m_qwTotalFileSize );
		SetDlgItemText( 1019, _T("File size: ") + strValue );
		
		if ( FTK_Downloader_GetState( m_hDownloader ) == DLSTATE_CHECKING )
		{
			int nPos = PERCENT( (INT64)FTK_Stat_GetCheckPieceCount( m_hDownloader ), (INT64)m_dwPieceCount );
			
			strValue.Format( _T("%s %ld%%"), nPos < 100 ? _T("Checking") : _T("Checked") , nPos );
			
			m_pgrDownload.SetForeColour( ::GetSysColor( RGB( 200, 200, 255 ) ) );
			m_pgrDownload.SetBkColour( RGB( 50, 50, 255 ) );
			m_pgrDownload.SetTextForeColour( RGB( 255, 255, 255 ) );
			m_pgrDownload.SetTextBkColour( RGB( 255, 255, 255 ) );
			
			m_pgrDownload.SetWindowText( strValue );
			m_pgrDownload.SetPos( nPos );
		}
		
		if ( FTK_Downloader_GetState( m_hDownloader ) < DLSTATE_DOWNLOAD || 
			FTK_Downloader_GetState( m_hDownloader ) >= DLSTATE_FETALERR )
		{
			CDialog::OnTimer(nIDEvent);		
			return;
		}
		
		AfxEnableDlgItem( this, 1004, TRUE );
		AfxEnableDlgItem( this, 1005, TRUE );
		AfxEnableDlgItem( this, 1006, TRUE );
		AfxEnableDlgItem( this, 1007, TRUE );
		
		if ( g_nSocket > 0 )
		{
			FTK_Downloader_AddSourceExt( m_hDownloader, g_nSocket );
			g_nSocket = 0;
		}
		
		QWORD qwTotalFileHaveSize = FTK_Stat_GetTotalFileHaveSize( m_hDownloader );
		int nPos = PERCENT( (INT64)qwTotalFileHaveSize, (INT64)m_qwTotalFileSize );
		
		strValue.Format( _T("%s %ld%%"), nPos < 100 ? _T("Downloading") : _T("Downloaded") , nPos );
		
		m_pgrDownload.SetForeColour( ::GetSysColor( COLOR_HIGHLIGHT ) );
		m_pgrDownload.SetBkColour( ::GetSysColor( COLOR_WINDOW ) );
		m_pgrDownload.SetTextForeColour( ::GetSysColor( COLOR_HIGHLIGHT ) );
		m_pgrDownload.SetTextBkColour( ::GetSysColor( COLOR_WINDOW ) );
		
		m_pgrDownload.SetWindowText( strValue );
		m_pgrDownload.SetPos( nPos );
		
		strValue = AfxFormatBytes( FTK_Stat_GetDownloadRate( m_hDownloader ) );
		SetDlgItemText( 1018, _T("Down Speed: ") + strValue + _T("/s") );
		
		strValue = AfxFormatBytes( FTK_Stat_GetUploadRate( m_hDownloader ) );
		SetDlgItemText( 1025, _T("Up Speed: ") + strValue + _T("/s") );
		
		strValue.Format( _T( "%ld %s %ld %s %ld %s" ),
			( UINT32 ) FTK_Stat_GetLeftTime( m_hDownloader ) / ( 60 * 60 ),
			_T("h"),
			( ( UINT32 ) FTK_Stat_GetLeftTime( m_hDownloader ) % ( 60 * 60 ) ) / 60,
			_T("m"),
			( ( UINT32 ) FTK_Stat_GetLeftTime( m_hDownloader ) % ( 60 * 60 ) ) % 60,
			_T("s") );
		
		SetDlgItemText( 1020, _T("Left time: ") + strValue );	
		
		strValue = AfxFormatBytes( qwTotalFileHaveSize );
		SetDlgItemText( 1021, _T("Downloaded: ") + strValue );
		
		strValue = AfxFormatBytes( FTK_Stat_GetUploaded( m_hDownloader ) );
		SetDlgItemText( 1023, _T("Uploaded: ") + strValue );
		
		int nTotalPeerCnt = FTK_Stat_GetTotalPeerCount( m_hDownloader );
		int nSeedCnt = FTK_Stat_GetSeedCount( m_hDownloader );
		BOOL bTrackerOK = FTK_Stat_IsAnyTrackerOK( m_hDownloader );
		strValue.Format( _T( "BitZam, SeedCnt: %ld, PeerCnt: %ld" ), 
			nSeedCnt, nTotalPeerCnt );
		
		SetWindowText( strValue );
		
		if ( nPos >= 100 )
		{
			//		if ( NULL != m_hDownloader )
			//		{
			//			StopDownload();
			//		}
			//
			//		if ( m_bInitContext )
			//		{
			//			StopContext();
			//		}		
			//		
			// 		AfxEnableDlgItem( this, 1023, TRUE );
			
			strValue = _T("Status: Downloaded OK...");
			SetDlgItemText( 1017, strValue );
			
			//		AfxEnableDlgItem( this, 1022, TRUE );
			
			//		AfxEnableDlgItem( this, 1010, TRUE );
			// 		AfxEnableDlgItem( this, 1011, TRUE );		
		}
	}
	else if ( nIDEvent == 3000 )
	{
		//内网事件驱动
		DoUDPEvents();
	}
	else if ( nIDEvent == 3100 )
	{
		CString strVal;
		strVal.Format( _T( "内网状态: [%s], 本机地址: %s, 网络类型: %s, 在线用户: %lu" ),
			FTK_UDPX_IsLoginOK() ? _T( "登陆成功" ) : _T( "登陆失败" ),
			FTK_UDPX_GetRealIP(),
			GetNatType(),
			FTK_UDPX_GetOnlineUserCnt() );

		SetDlgItemText( IDC_UDP_STATUS, strVal );
	}

	CDialog::OnTimer(nIDEvent);
}

void CBitZamDlg::OnDestroy() 
{
	//与内网穿透服务器断开
	FTK_UDPX_Logout();
	
	//内网穿透需要的释放函数
	FreeNatTunnel();
	
	if ( m_bInitContext )
	{
		StopContext();
	}

	CDialog::OnDestroy();	
}

//////////////////////////////////////////////////////////////////////////

BOOL CBitZamDlg::StartContext()
{
#ifdef _DEBUG
	
	//BitZamd.exe 的授权码
	FTK_License_Set( "8C28DA880A0E66E969C709E70592D0835826F46CB13821AB1090EB2278B1D53B6CC42F4B223ECD2C4D6FD2ED5C68914087752ACD66C02D4BAD958D8904FB8D2DA709BE82E4CAA51565F55114852F2508A47AE490E0250D4A8E9803EB35CD7C10B1E7ACC0F074AB1F27C5D0B6A446EF9D82280FD42000CD5677BC35AD9504A9BE" );
	
#else
	
	//BitZam.exe 的授权码
	FTK_License_Set( "B38059711E93CD6C261E9F95317007D33C0FC1EFD25FA4848DD3B38476C6195B5D598BF5BE2FCDF3A87A553175F7E229871E72D44C3358EF149F08CE4A218E38B1656C356FA74C3E9A1D5895F7CE16CD7077DFBE5524923AB4E2C2DB8FB29A6D5E8BEF1FA32D96883ADE5B0DD99B0021AAD8F084F2A4EA5AE36E7B4E51F03F73" );	
	
#endif//_DEBUG
	
    ASSERT( !FTK_Context_IsInit() );
	
//	//FTK_Identifier_String10( "123456789xxx" );
//	//FTK_Http_UserAgent( _T("ppKiss") );
	
    CString strPath;
    ::GetModuleFileName( AfxGetInstanceHandle(),
		strPath.GetBuffer( _MAX_PATH ), _MAX_PATH );
    strPath.ReleaseBuffer();
	int nPos = strPath.ReverseFind( _T('\\') );
	ASSERT( -1 != nPos );
	strPath = strPath.Left( nPos + 1 );
	
	FTK_Context_NotifyCB( ftk_callback_func );
	
	//	HConfigIni hConfigIni;
	//	hConfigIni = FTK_Config_Open();
	//	FTK_Config_SetInt( hConfigIni, "listen_port", 0 );
	//	FTK_Config_SetInt( hConfigIni, "fix_port", 1 );
	//	FTK_Config_SetInt( hConfigIni, "port", 23333 );
	//	FTK_Config_SetInt( hConfigIni, "minport", 6881 );
	//	FTK_Config_SetInt( hConfigIni, "maxport", 6999 );
	//FTK_Config_SetStr( hConfigIni, "report_ip", "192.168.0.1" );
	
	//    if ( !FTK_Context_Init2( hConfigIni, TRUE ) )
	//    {
	//		FTK_Config_Close( hConfigIni );
	//		return FALSE;
	//    }
	
	//	FTK_Config_Close( hConfigIni );
	//	USHORT nPort = ::FTK_Context_GetListenPort();
	//ASSERT( 23333 == nPort );
	
	//初始化缓存大小设置
	FTK_Disk_SetCache( 6L, 20L, 20L );
	
    if ( !FTK_Context_Init( strPath + _T( "Config.ini" ), TRUE ) )
    {
		return FALSE;
	}
	
	USHORT nPort = ::FTK_Context_GetListenPort();
	
	if ( !FTK_Win_AddUPnPPortMapping( nPort ) )
	{
		AfxMessageBox( _T( "执行对于支持UPnP协议的Router进行自动的端口映射配置失败!" ) );
	}
	
//	BOOL bOpenFirewall = FALSE;
//	BOOL bPortMapping = FALSE;
//	FTK_Win_OpenWinXPICSF( nPort, bOpenFirewall, bPortMapping );
	
	FTK_Context_TorrentFile( FALSE, FALSE );
	
    ASSERT( FTK_Context_IsRunning() == FALSE );
    FTK_Context_Run();
    return FTK_Context_IsRunning() == TRUE;
}

BOOL CBitZamDlg::StopContext()
{
    if ( FTK_Context_IsInit() )
    {
        FTK_Context_Release();
    }

	return TRUE;
}

BOOL CBitZamDlg::StartDownload()
{
    ASSERT( NULL == m_hDownloader );

    CString strPath;
    ::GetModuleFileName( AfxGetInstanceHandle(),
                         strPath.GetBuffer( _MAX_PATH ), _MAX_PATH );
    strPath.ReleaseBuffer();
	int nPos = strPath.ReverseFind( _T('\\') );
	ASSERT( -1 != nPos );
	CString strStartupPath = strPath.Left( nPos + 1 );
	
	HTorrentFile hTorrentFile = FTK_Torrent_Open( m_strTorrentFile, CP_ACP, m_strPassword.IsEmpty() ? NULL : (LPCTSTR)m_strPassword, FALSE, FALSE );
	if ( NULL == hTorrentFile )
	{
		return FALSE;
	}

	CByteArray arryPreAllocFile;
	arryPreAllocFile.SetSize( FTK_Torrent_GetFilesCount( hTorrentFile ) );
	memset( arryPreAllocFile.GetData(), 0x01, arryPreAllocFile.GetSize() );

	nPos = m_strTorrentFile.ReverseFind( _T('\\') );
	ASSERT( -1 != nPos );
	CString strDestPath = m_strTorrentFile.Left( nPos + 1 );

	m_strKeyValue = FTK_Torrent_GetHexInfoHash( hTorrentFile );
	m_strKeyValue.Replace( _T("%"), _T("") );

	m_hDownloader = FTK_Downloader_Open();
//    BOOL bRet = FTK_Downloader_Init(
//					m_hDownloader,
//                    m_strTorrentFile,
//					arryPreAllocFile.GetData(),
//					arryPreAllocFile.GetSize(),
//					FALSE,
//                    m_strDestPath + _T("\\") + FTK_Torrent_GetTorrentName( hTorrentFile ),
//                    strStartupPath + _T( "Config.INI" ),
//                    strStartupPath + _T( "Log\\" ) + _T( "Downloader.log" ),
//                    strStartupPath + m_strKeyValue + _T( ".status" ),
//					TRUE,//如果想快速做种子，将此设置为TRUE
//					m_strPassword.IsEmpty() ? NULL : (LPCTSTR)m_strPassword,
//                      CP_ACP );


	//char szPrePrioFile[ 1024 ];
	//memset( szPrePrioFile, 254, 1024 );
	//FTK_Downloader_PreInitFilePriority( m_hDownloader, szPrePrioFile, FTK_Torrent_GetFilesCount( hTorrentFile ) );

	//FTK_Downloader_PreInitTrackers( m_hDownloader, _T( "http://127.0.0.1:6969/announce;http://127.0.0.1:8080/announce|http://127.0.0.1:8181/announce;http://127.0.0.1:8282/announce|http://127.0.0.1:9090/announce;http://127.0.0.1:9191/announce" ) );

	FTK_Downloader_SetNatPeerCB( m_hDownloader, ftk_nat_peer_callback );
	FTK_Downloader_SetBeforeDownCB( m_hDownloader, ftk_before_down_callback );
	FTK_Downloader_SetOnComleteCB( m_hDownloader, ftk_on_complete_callback );

	BOOL bRet = FALSE;
	if ( FALSE == bTorrentDataMode )
	{
//		HConfigIni hConfigIni;
//		hConfigIni = FTK_Config_Open();
//		FTK_Config_SetInt( hConfigIni, "prealloc_disk_space", 0 );
//		//FTK_Config_SetStr( hConfigIni, "report_ip", "192.168.0.1" );
//
//		bRet = FTK_Downloader_Init2(
//			m_hDownloader,
//			m_strTorrentFile,
//			arryPreAllocFile.GetData(),
//			arryPreAllocFile.GetSize(),
//			FALSE,
//			m_strDestPath + _T("\\") + FTK_Torrent_GetTorrentName( hTorrentFile ),
//			//strStartupPath + _T( "Config.INI" ),
//			hConfigIni,
//			strStartupPath + _T( "Log\\" ) + _T( "Downloader.log" ),
//			strStartupPath + m_strKeyValue + _T( ".status" ),
//			FALSE, //如果想快速做种子，将此设置为TRUE
//			m_strPassword.IsEmpty() ? NULL : (LPCTSTR)m_strPassword,
//			CP_ACP );
//
		//		FTK_Config_Close( hConfigIni );
		bRet = FTK_Downloader_Init(
			m_hDownloader,
			m_strTorrentFile,
			arryPreAllocFile.GetData(),
			arryPreAllocFile.GetSize(),
			FALSE,
			m_strDestPath + _T("\\") + FTK_Torrent_GetTorrentName( hTorrentFile ),
			strStartupPath + _T( "Config.INI" ),
			strStartupPath + _T( "Log\\" ) + _T( "Downloader.log" ),
			strStartupPath + m_strKeyValue + _T( ".status" ),
			FALSE,//如果想快速做种子，将此设置为TRUE
			m_strPassword.IsEmpty() ? NULL : (LPCTSTR)m_strPassword,
			CP_ACP );
	}
	else
	{
		char *pTorrentData = new char[ 1024 * 1024 * 2 ];
		CFile file;
		if ( !file.Open( m_strTorrentFile, CFile::modeRead | CFile::typeBinary ) )
		{
			delete [] pTorrentData;
			pTorrentData = NULL;

			FTK_Downloader_Close( m_hDownloader );
			m_hDownloader = NULL;

			return FALSE;
		}

		int nTorrentLength = file.GetLength();
		if ( nTorrentLength <= 0 )
		{
			delete [] pTorrentData;
			pTorrentData = NULL;

			FTK_Downloader_Close( m_hDownloader );
			m_hDownloader = NULL;

			return FALSE;
		}

		file.Read( pTorrentData, nTorrentLength );
		file.Close();

		bRet = FTK_Downloader_Init4(
			m_hDownloader,
			pTorrentData,
			nTorrentLength,
			arryPreAllocFile.GetData(),
			arryPreAllocFile.GetSize(),
			FALSE,
			m_strDestPath + _T("\\") + FTK_Torrent_GetTorrentName( hTorrentFile ),
			NULL,//strStartupPath + _T( "Config.INI" ),
			strStartupPath + _T( "Log\\" ) + _T( "Downloader.log" ),
			strStartupPath + m_strKeyValue + _T( ".status" ),
			FALSE, //如果想快速做种子，将此设置为TRUE
			m_strPassword.IsEmpty() ? NULL : (LPCTSTR)m_strPassword,
			CP_ACP );

		delete [] pTorrentData;
		pTorrentData = NULL;
	}

    if ( FALSE == bRet )
    {
        FTK_Downloader_Close( m_hDownloader );
        m_hDownloader = NULL;

        return FALSE;
    }

    bRet = FTK_Downloader_Execute( m_hDownloader );
    if ( FALSE == bRet )
    {
        FTK_Downloader_Close( m_hDownloader );
        m_hDownloader = NULL;

        return FALSE;
    }

	//主动要求限制给自己的下载速度
	FTK_Downloader_SetSeedMaxUPSpeed( m_hDownloader, 50 );

    FTK_GlobalVar_AddTorrentSHA1( m_strKeyValue, m_hDownloader );

	m_qwTotalFileSize	= FTK_Torrent_GetFileSize( hTorrentFile );

	m_dwPieceCount	= FTK_Torrent_GetPieceCount( hTorrentFile );

	//Close torrent file, release memory, It's important!
	FTK_Torrent_Close( hTorrentFile );
	hTorrentFile = NULL;

	return TRUE;
}

BOOL CBitZamDlg::StartDownload2()
{
    ASSERT( NULL == m_hDownloader );
	
    CString strPath;
    ::GetModuleFileName( AfxGetInstanceHandle(),
		strPath.GetBuffer( _MAX_PATH ), _MAX_PATH );
    strPath.ReleaseBuffer();
	int nPos = strPath.ReverseFind( _T('\\') );
	ASSERT( -1 != nPos );
	CString strStartupPath = strPath.Left( nPos + 1 );
	
	CByteArray arryPreAllocFile;
	arryPreAllocFile.SetSize( 1 );
	memset( arryPreAllocFile.GetData(), 0x01, arryPreAllocFile.GetSize() );
	
	char szInfoHashHex[ 64 ] = {0};
	char szFileName[ 1024 ] = {0};
	QWORD qwFileSize = 0L;
	DWORD dwPieceSize = 0L;
	if ( !FTK_Link_ParseLink( g_strLinkURL, szInfoHashHex, szFileName, qwFileSize, dwPieceSize ) )
	{
		return FALSE;
	}
	
	m_strKeyValue = szInfoHashHex;
	
	m_hDownloader = FTK_Downloader_Open();
	
	FTK_Downloader_PreInitTrackers( m_hDownloader, _T( "http://127.0.0.1:6969/announce" ) );
	
	FTK_Downloader_SetNatPeerCB( m_hDownloader, ftk_nat_peer_callback );
	FTK_Downloader_SetBeforeDownCB( m_hDownloader, ftk_before_down_callback );
	FTK_Downloader_SetOnComleteCB( m_hDownloader, ftk_on_complete_callback );
	
	BOOL bRet = FALSE;
	bRet = FTK_Downloader_Init5(
		m_hDownloader,
		g_strLinkURL,
		m_strTorrentFile,
		arryPreAllocFile.GetData(),
		arryPreAllocFile.GetSize(),
		FALSE,
		m_strDestPath + _T("\\") + szFileName,
		strStartupPath + _T( "Config.INI" ),
		strStartupPath + _T( "Log\\" ) + _T( "Downloader.log" ),
		strStartupPath + m_strKeyValue + _T( ".status" ),
		FALSE,//如果想快速做种子，将此设置为TRUE
		m_strPassword.IsEmpty() ? NULL : (LPCTSTR)m_strPassword,
		CP_ACP );
	
    if ( FALSE == bRet )
    {
        FTK_Downloader_Close( m_hDownloader );
        m_hDownloader = NULL;
		
        return FALSE;
    }
	
    bRet = FTK_Downloader_Execute( m_hDownloader );
    if ( FALSE == bRet )
    {
        FTK_Downloader_Close( m_hDownloader );
        m_hDownloader = NULL;
		
        return FALSE;
    }
	
	//主动要求限制给自己的下载速度
	FTK_Downloader_SetSeedMaxUPSpeed( m_hDownloader, 50 );
	
    FTK_GlobalVar_AddTorrentSHA1( m_strKeyValue, m_hDownloader );
	
	m_qwTotalFileSize	= qwFileSize;
	
	m_dwPieceCount	= ( ( qwFileSize - 1 ) / dwPieceSize ) + 1;
	return TRUE;
}

BOOL CBitZamDlg::StopDownload()
{
    ASSERT( NULL != m_hDownloader );

    FTK_GlobalVar_RemoveTorrentSHA1( m_strKeyValue );

	FTK_Downloader_Release( m_hDownloader );
    FTK_Downloader_Close( m_hDownloader );
    m_hDownloader = NULL;

	return TRUE;	
}

void CBitZamDlg::OnMakeTorrent() 
{
	// TODO: Add your control notification handler code here
	
	CDlgMakeTorrent dlg;
	dlg.DoModal();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_stdHwysoft.SetColours( RGB( 0, 0, 255 ), RGB( 200, 0, 0 ), RGB( 0, 0, 180 ) );
 	m_stdHwysoft.SetURL( _T("http://wwww.hwysoft.com") );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBitZamDlg::OnSelFiles() 
{
	// TODO: Add your control notification handler code here
	
	CDlgSelFiles dlg;
	dlg.SetInfo( m_strTorrentFile, m_strPassword.IsEmpty() ? NULL : (LPCTSTR)m_strPassword );
	if ( IDOK == dlg.DoModal() )
	{
		for ( register int i = 0; i < dlg.m_arryFilePriority.GetSize(); i++ )
		{
			FTK_Downloader_SetFilePriority( m_hDownloader, i, (char)dlg.m_arryFilePriority[ i ], FALSE );
		}

	    FTK_Downloader_ForceFilePriority( m_hDownloader );		
	}
}

void CBitZamDlg::OnAddExtAnnounce() 
{
	// TODO: Add your control notification handler code here

	CDlgAddExtAnnounce dlg;
	if ( IDOK == dlg.DoModal() )
	{
		FTK_Downloader_AddExtAnnounce( m_hDownloader, dlg.m_strExtAnnounce );
	}	
}

void CBitZamDlg::OnAddPeer() 
{
	// TODO: Add your control notification handler code here
	
	CDlgAddPeer dlg;
	if ( IDOK == dlg.DoModal() )
	{
		FTK_Downloader_AddSource( m_hDownloader, dlg.m_szIPAddress, dlg.m_nPort, NULL );
	}
}

void CBitZamDlg::OnManualAnnounce() 
{
	// TODO: Add your control notification handler code here
	
	FTK_Downloader_ReannounceAll( m_hDownloader );
}

void CBitZamDlg::OnTorrentData() 
{
	// TODO: Add your control notification handler code here
	
	//通过链接下载时的链接地址
	g_strLinkURL = _T( "" );

    CString strFilter = _T( "Torrent File(*.Torrent)|*.torrent||" );
    CFileDialog OpenDlg( TRUE, _T( "torrent" ), _T( "*.Torrent" ),
                         OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_FILEMUSTEXIST,
                         strFilter );

    if ( IDOK != OpenDlg.DoModal() )
    {
        return ;
    }


	CDlgOpenTorrentFile DlgTorrent;

	DlgTorrent.SetEncrypt( FTK_Torrent_IsCipherTorrent( OpenDlg.GetPathName() ) );
	if ( IDOK != DlgTorrent.DoModal() )
	{
		return ;
	}   
	
	m_strDestPath = DlgTorrent.m_strDestPath;
	m_strDestPath.TrimRight( _T("\\") );
	m_strPassword = DlgTorrent.m_strPassword;
	SetDlgItemText( 1010, OpenDlg.GetPathName() );

	bTorrentDataMode = TRUE;
}

void CBitZamDlg::On1031() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	HTorrentFile hTorrentFile = FTK_Torrent_Open( m_strTorrentFile, CP_ACP, m_strPassword.IsEmpty() ? NULL : (LPCTSTR)m_strPassword, FALSE, FALSE );
	if ( NULL == hTorrentFile )
	{
		return;
	}

	CString strPath;
	strPath = m_strDestPath;
	strPath.TrimRight( _T( "\\" ) );
	strPath += _T( "\\" );

	_tagFileInfo FileInfo;
	FTK_Torrent_GetFileInfo( hTorrentFile, 0, &FileInfo );
	CString strFileName = FileInfo.m_szFileName;

	if ( FTK_Torrent_IsFile( hTorrentFile ) )
	{
		strPath = strPath + FTK_Torrent_GetTorrentName( hTorrentFile );
	}
	else
	{
		strPath = strPath + FTK_Torrent_GetTorrentName( hTorrentFile );
		strPath = strPath + _T( "\\" ) + strFileName;
	}

	BYTE pSHA1FromTorrent[ 20 ] = {0};
	FTK_Torrent_GetFileSHA1( hTorrentFile, 0, pSHA1FromTorrent );

	FTK_Torrent_Close( hTorrentFile );
	hTorrentFile = NULL;

	BYTE pSHA1FromFile[ 20 ] = {0};
	if ( !FTK_Ext_GetFileSHA1( strPath, pSHA1FromFile ) )
	{
		return;
	}

	if ( memcmp( pSHA1FromFile, pSHA1FromTorrent, 20 ) == 0 )
	{
		AfxMessageBox( _T( "SHA1 is equal!" ) );
	}
}

//AfxHexEncode函数的反过程
static int AfxHexDecode( const BYTE *pHexData, int nHexLen, BYTE *szData, int &nLen )
{
    int i;
    const BYTE *cpos = pHexData;
    unsigned int nHexval = 0;
    int nNextchar = 0;
    for ( i = 0; i < nLen; i++ )
    {
        nHexval = 0;
        nNextchar = 0;
        if ( sscanf( ( char * ) cpos, "%%%02x%n", &nHexval, &nNextchar ) < 1 )
        {
            return -1; //解析错误
        }

        szData[ i ] = ( unsigned char ) nHexval;
        cpos += nNextchar;
    }

    nLen = i;

    if ( *cpos != 0 && *cpos != '\n' && *cpos != '\r' )
    {
        return -2; //没有解析完返回-2
    }

    return nLen;
}

void CBitZamDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
	if ( NULL != m_hDownloader )
	{
		//CString strVal = _T( "%2D%42%43%30%30%36%34%2D%FA%6F%D2%E3%F4%21%68%D9%7E%74%BC%DE" );
		CString strVal = _T( "%2D%42%43%30%30%36%34%2D%24%3C%80%1A%BA%8E%15%E2%96%DE%BD%A1" );
		
		BYTE pPeerID[ 20 ];
		int nPeerLen = 20;
		AfxHexDecode( ( const BYTE * )( LPCTSTR )strVal, strVal.GetLength(), pPeerID, nPeerLen );
		ASSERT( 20 == nPeerLen );
		
		FTK_Downloader_AddSource( m_hDownloader, "192.168.0.110", 8582, pPeerID, 0 );
	}
}


LRESULT CBitZamDlg::OnNatTunnel( WPARAM wParam, LPARAM lParam )
{
	CTunnelInfo *pTunnelInfo = ( CTunnelInfo * )wParam;
	ASSERT( NULL != pTunnelInfo );

	//通知内网穿透服务器，想连接某个用户
	FTK_UDPX_RemoteCallPeer( pTunnelInfo ->_pPeerID, pTunnelInfo ->_pInfoHash );

	delete pTunnelInfo;
	pTunnelInfo = NULL;
	
	return 0L;
}

//////////////////////////////////////////////////////////////////////////

//通讯回调函数
static void WINAPI ftk_udp_extprotocol_callback ( unsigned char nExtProtocol, const unsigned char *data, unsigned int length, unsigned int ip, unsigned short port )
{
	//处理接收到的UDP数据
	FTK_UDPX_ProcessUDPPacket(data, length, ip, port);
}

static LPTSTR lpszCmds[] = 
{
	_T( "应答" ),
		_T( "心跳" ),
		_T( "登陆" ),
		_T( "注销" ),
		_T( "UDP呼叫" ),
		_T( "路由检查" ),
		_T( "状态报告" ),
		_T( "未知命令" ) 
};

//通知外部自己失败的函数
void WINAPI ftk_udpx_error_callback ( unsigned char nCmd )
{
  CString strVal = _T( "" );
  strVal.Format( _T( "[%s]与服务器[%s:%lu]的连接断开, 重新登陆\r\n" ), 
		lpszCmds[nCmd],
		FTK_UDPX_GetServerIP(),
		FTK_UDPX_GetServerPort() );
  FTK_UDPX_WriteLog(4, strVal);
  FTK_UDPX_Relogin();
}

//通知外部在线人数的函数
void WINAPI ftk_udpx_usercnt_callback ()
{

}

//通知外部自己登陆成功的函数
void WINAPI ftk_udpx_login_callback ()
{
	CString strVal;
	strVal.Format( _T( "登陆服务器[%s:%lu]成功!\r\n" ), 
		FTK_UDPX_GetServerIP(),
		FTK_UDPX_GetServerPort() );
	FTK_UDPX_WriteLog(4, strVal);
}

//通知外部NAT类型发生了变化的函数
void WINAPI ftk_udpx_nattype_callback ()
{
	CString strRealIP = FTK_UDPX_GetRealIP();
	
	if ( FTK_UDPX_GetNatType() > 1 ) //如果处于Lan中..., 强制提交居于网IP地址
	{
		FTK_Context_SetForceIP(FTK_UDPX_GetRealIP());
	}
	else
	{
		FTK_Context_SetForceIP( _T( "" ) );
	}
}

CString GetNatType()
{
	CString strRet = _T( "未知" );
	unsigned char nType = FTK_UDPX_GetNatType();
	if (nType == 1)
	{
		strRet = _T( "公网" );
	}
	else if (nType == 2)
	{
		strRet = _T( "内网U" );
	}
	else if (nType == 3)
	{
		strRet = _T( "内网S" );
	}
	else if (nType == 4)
	{
		strRet = _T( "内网C" );
	}
	
	return strRet;
}

typedef struct _tagPeerCall
{
	char _szIP[ 32 ];
	unsigned short _nPort;
	BYTE _pPeerID[ 20 ];
	BYTE _pInfoHash[ 20 ];
	BYTE _nNetType;
	BYTE _nActive;
	char _szTransIP[ 32 ];
	unsigned short _nTransPort;
} CPeerCall;

//通知外部远程呼叫结果的函数的函数
static void WINAPI ftk_udpx_peercall_callback ( unsigned char nActive, const char *pPeerIP, unsigned short nTCPPort, const unsigned char *pPeerID, const unsigned char *pInfoHash, unsigned char nNetType, const char *pTransIP, unsigned short nTransPort )
{
	CPeerCall *pPeerCall = new CPeerCall;
	ASSERT( NULL != pPeerCall );
	strcpy( pPeerCall ->_szIP, pPeerIP );
	pPeerCall ->_nPort = nTCPPort;
	memcpy( pPeerCall ->_pPeerID, pPeerID, 20 );
	memcpy( pPeerCall ->_pInfoHash, pInfoHash, 20 );
	pPeerCall ->_nNetType = nNetType;
	pPeerCall ->_nActive = nActive;
	strcpy( pPeerCall -> _szTransIP, pTransIP );
	pPeerCall -> _nTransPort = nTransPort;
	g_pBitZamDlg ->PostMessage( WM_MSG_PEERCALL, ( WPARAM )pPeerCall, 0L );
}

//内网穿透需要的初始化函数
BOOL CBitZamDlg::InitNatTunnel()
{
	//内网穿透是否初始化
	if ( m_bInitUDP )
	{
		return TRUE;
	}

	//初始化TCP辅助库
	if ( !FTK_TCPX_Init( 9999 ) )
	{
		return FALSE;
	}

	FTK_Context_SetUDPTunnelInfo( "127.0.0.1", FTK_TCPX_GetPort() );

	//初始化UDPSocket 通讯接口
	//Initialize UDP Socket API interface
    if ( !FTK_UDPSocket_Init( 7590 ) )
	{
		//释放TCP辅助库
		FTK_TCPX_Release();
		return FALSE;
	}

	//挂接Socket通讯接口
	FTK_UDPX_SetUDPSocket(FTK_UDPSocket_GetUDPSocket());

	unsigned char nExt = FTK_UDPSocket_AddExtProtcol(ftk_udp_extprotocol_callback);
	FTK_UDPX_SetUDPExtProtocol(nExt);
	
	FTK_UDPX_SetCallback(ftk_udpx_error_callback, ftk_udpx_usercnt_callback, ftk_udpx_login_callback, ftk_udpx_nattype_callback, ftk_udpx_peercall_callback);
	FTK_UDPX_EnableLog(4, "UDPAPI.log");

	//内网穿透是否初始化
	m_bInitUDP = TRUE;

	return TRUE;
}

//内网穿透需要的释放函数
void CBitZamDlg::FreeNatTunnel()
{
	//内网穿透是否初始化
	if ( !m_bInitUDP )
	{
		return;
	}

	//释放TCP辅助库
	FTK_TCPX_Release();
}

//内网事件驱动
void CBitZamDlg::DoUDPEvents()
{
	if ( m_bInitUDP )
	{
		FTK_UDPSocket_DoSocketEvents();
		FTK_UDPX_ProcessEvents();

		BYTE nNetIdle = 0;
		if ( FTK_Context_GetTorrentCount() > 0 || FTK_TCPX_GetTransChannelCnt() > 0 )
		{
			nNetIdle = 1; //报告自己网络状态忙
		}
		else
		{
			nNetIdle = 0; //报告自己网络状态闲
		}

		FTK_UDPX_SetNetIdle(nNetIdle);
	}
}

LRESULT CBitZamDlg::OnPeerCall( WPARAM wParam, LPARAM lParam )
{
	CPeerCall *pPeerCall = ( CPeerCall * )wParam;

	//首先判断对方的网络类型
	if ( pPeerCall ->_nNetType == 1 ) //如果对方是公网
	{
		FTK_Downloader_AddSource( m_hDownloader, pPeerCall ->_szIP, pPeerCall ->_nPort, pPeerCall ->_pPeerID, 0 ); 	
	}
	else if ( pPeerCall ->_nNetType == 4 ) //如果对方属于可以穿透的内网
	{
		//如果自己也属于可以穿透的内网
		if ( 4 == FTK_UDPX_GetNatType() )
		{
			if ( NULL != m_hDownloader )
			{
				BYTE nTunnelType = 1;

				//是否是主动请求方
				if ( pPeerCall ->_nActive == 1 )
				{
					nTunnelType = TUNNEL_UDP_ACTIVE;
				}
				else
				{
					nTunnelType = TUNNEL_UDP_PASSIVE;
				}
				
				FTK_Downloader_AddSource( m_hDownloader, g_strUDPServerIP, 9911, pPeerCall ->_pPeerID, nTunnelType );
			}			
		}
	}
	else if ( pPeerCall ->_nNetType == 3 ) //如果对方属于无法穿透的内网?
	{
		//暂时不做处理
	}

	delete pPeerCall;
	pPeerCall = NULL;
	return 0L;
}
void CBitZamDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
	CString strVal;
	GetDlgItemText( 1010, strVal );
	if ( strVal.IsEmpty() )
	{
		return;
	}

	UINT nPeerCnt = 0L;
	UINT nSeedCnt = 0L;
	BOOL bNetworkErr = FALSE;
	char szErrInfo[ 1024 ] = {0};
	if ( FTK_Tracker_Http2( strVal, nPeerCnt, nSeedCnt, bNetworkErr, szErrInfo, 1024 ) )
	{
		strVal.Format( _T( "探测成功: PeerCnt:%lu, SeedCnt:%lu" ), nPeerCnt, nSeedCnt );
		AfxMessageBox( strVal );
	}
	else
	{
		strVal.Format( _T( "探测失败: %s" ), szErrInfo );
		AfxMessageBox( strVal );
	}
}

void CBitZamDlg::On1034() 
{
	// TODO: Add your control notification handler code here
	
	//通过链接下载时的链接地址
	g_strLinkURL = _T( "ftk://F7E647274BA40D0DEF8E03778E12BD75B22DE851|file|Ronaldo.rar|124494549|262144|D2E14D447C5D9DA09B9D46D3425FDD17A170D2F3" );

	m_strDestPath = _T( "F:\\TempData\\" );
	m_strPassword = _T( "" );

	bTorrentDataMode = FALSE;
	SetDlgItemText( 1010, _T( "F:\\TempData\\Ronaldo.rar.torrent" ) );
}

void CBitZamDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	
	CDlgLinkURL DlgLinkURL;
	DlgLinkURL.DoModal();
}

void CBitZamDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
}

void CBitZamDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	
	if ( NULL != m_hDownloader )
	{
		CString strVal = _T( "%2D%42%43%30%30%36%34%2D%BF%7B%C7%73%DC%FF%35%4C%60%71%4D%17" );
	
		BYTE pPeerID[ 20 ];
		int nPeerLen = 20;
		AfxHexDecode( ( const BYTE * )( LPCTSTR )strVal, strVal.GetLength(), pPeerID, nPeerLen );
		ASSERT( 20 == nPeerLen );

		FTK_Downloader_AddSource( m_hDownloader, "127.0.0.1", 9922, pPeerID, TUNNEL_TCP_ACTIVE );
	}
}

void CBitZamDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	
	if ( NULL != m_hDownloader )
	{
		CString strVal = _T( "%2D%42%43%30%30%36%34%2D%92%26%32%AA%F9%D7%05%2F%70%C8%85%D0" );
	
		BYTE pPeerID[ 20 ];
		int nPeerLen = 20;
		AfxHexDecode( ( const BYTE * )( LPCTSTR )strVal, strVal.GetLength(), pPeerID, nPeerLen );
		ASSERT( 20 == nPeerLen );

		FTK_Downloader_AddSource( m_hDownloader, "127.0.0.1", 9922, pPeerID, TUNNEL_TCP_PASSIVE );
	}
}

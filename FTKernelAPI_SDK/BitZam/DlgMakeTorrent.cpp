// DlgMakeTorrent.cpp : implementation file
//

#include "stdafx.h"
#include "BitZam.h"
#include "DlgMakeTorrent.h"
#include "SBDestination.h"
#include "DlgMTProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStringArray CDlgMakeTorrent::m_arryCodePages;

CString CDlgMakeTorrent::m_strMainAnnounce;
CString CDlgMakeTorrent::m_strOtherAnnounces;
CString CDlgMakeTorrent::m_strComments;
CString CDlgMakeTorrent::m_strDestTorrentName;
CString CDlgMakeTorrent::m_strEncryptPwd;
CString CDlgMakeTorrent::m_strSourceFilePath;
int CDlgMakeTorrent::m_nSelPieceSize = 0;
BOOL CDlgMakeTorrent::m_bIsFile	= 0;
UINT CDlgMakeTorrent::m_nCodePage	= CP_ACP;
BOOL CDlgMakeTorrent::m_bMakeSHA1 = FALSE;

/////////////////////////////////////////////////////////////////////////////
// CDlgMakeTorrent dialog


CDlgMakeTorrent::CDlgMakeTorrent(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMakeTorrent::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMakeTorrent)
	m_nFileOrDir = 0;
	m_strMainTracker = _T("");
	m_strOtherTracker = _T("");
	m_strNotes = _T("");
	m_strTorrentName = _T("");
	m_bEncrypt = FALSE;
	m_strPassword = _T("");
	m_strSrcPathFile = _T("");
	m_nPieceSize = 0;
	//}}AFX_DATA_INIT

	m_nCodePage = CP_ACP;
}


void CDlgMakeTorrent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMakeTorrent)
	DDX_Control(pDX, 1018, m_wndCodePage);
	DDX_Radio(pDX, 1006, m_nFileOrDir);
	DDX_Text(pDX, 1015, m_strMainTracker);
	DDX_Text(pDX, 1008, m_strOtherTracker);
	DDX_Text(pDX, 1009, m_strNotes);
	DDX_Text(pDX, 1010, m_strTorrentName);
	DDX_Check(pDX, 1012, m_bEncrypt);
	DDX_Text(pDX, 1013, m_strPassword);
	DDX_Text(pDX, 1004, m_strSrcPathFile);
	DDX_CBIndex(pDX, 1017, m_nPieceSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMakeTorrent, CDialog)
	//{{AFX_MSG_MAP(CDlgMakeTorrent)
	ON_BN_CLICKED(1005, OnSelFileOrDir)
	ON_WM_CLOSE()
	ON_BN_CLICKED(1011, OnSelTorrentFileName)
	ON_BN_CLICKED(1001, OnStartMakeTorrent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMakeTorrent message handlers

void CDlgMakeTorrent::OnCancel() 
{
	// TODO: Add extra cleanup here
	
}

void CDlgMakeTorrent::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDlgMakeTorrent::OnSelFileOrDir() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();

	if ( 0 == m_nFileOrDir )
	{
		CString strFilter = _T( "Any File(*.*)|*.*||" );
		CFileDialog OpenDlg( TRUE, _T( "*" ), _T( "*.*" ),
							 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_FILEMUSTEXIST,
							 strFilter );

		if ( IDOK != OpenDlg.DoModal() )
		{
			return ;
		}

		SetDlgItemText( 1004, OpenDlg.GetPathName() );
		SetDlgItemText( 1010, OpenDlg.GetPathName() + _T(".Torrent") );
	}
	else
	{
		CSBDestination SB;
		SB.SetTitle( _T("Select Folder") );
		SB.SetInitialSelection( _T("") );
		if ( TRUE == SB.SelectFolder() )
		{
			SetDlgItemText( 1004, SB.GetSelectedFolder() );
			SetDlgItemText( 1010, SB.GetSelectedFolder() + _T(".Torrent") );
		}
	}
}

BOOL CDlgMakeTorrent::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    EnumSystemCodePages( EnumCodePageProc, CP_INSTALLED );
	
    UINT nCodePage = CP_ACP;
    CPINFOEX CpinfoEX;
    int nIndex = -1;

    for ( register int i = 0; i < m_arryCodePages.GetSize(); i++ )
    {
        nCodePage = _ttoi( m_arryCodePages[ i ] );
        if ( GetCPInfoEx( nCodePage, 0, &CpinfoEX ) )
        {
            nIndex = m_wndCodePage.AddString( CpinfoEX.CodePageName );
            m_wndCodePage.SetItemData( nIndex, nCodePage );
        }
    }

    nIndex = SelectCodePage( m_wndCodePage, GetACP() );
    if ( -1 != nIndex )
    {
        m_wndCodePage.SetCurSel( nIndex );
    }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMakeTorrent::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnCancel();
}

void CDlgMakeTorrent::OnSelTorrentFileName() 
{
	// TODO: Add your control notification handler code here
	
    CString strFilter = _T( "Torrent File(*.torrent)|*.torrent||" );
    CFileDialog SaveDlg( FALSE, _T( "torrent" ), _T( "*.torrent" ),
                         OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER, strFilter );

    if ( IDOK != SaveDlg.DoModal() )
    {
        return ;
    }

    SetDlgItemText( 1010, SaveDlg.GetPathName() );
}

void CDlgMakeTorrent::OnStartMakeTorrent() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	
	if ( m_strSrcPathFile.IsEmpty() )
	{
		AfxMessageBox( _T("Please select source file or directory") );
		return;
	}

	if ( m_strMainTracker.IsEmpty() )
	{
		AfxMessageBox( _T("Please input main tracker server") );
		return;
	}

	if ( m_strTorrentName.IsEmpty() )
	{
		AfxMessageBox( _T("Please input main tracker server") );
		return;
	}

	if ( m_bEncrypt && m_strPassword.IsEmpty() )
	{
		AfxMessageBox( _T("Please input your password") );
		return;
	}

	CDlgMakeTorrent::m_strMainAnnounce		= m_strMainTracker;
	CDlgMakeTorrent::m_strOtherAnnounces	= m_strOtherTracker;
	CDlgMakeTorrent::m_strComments	= m_strNotes;
	CDlgMakeTorrent::m_strDestTorrentName	= m_strTorrentName;
	CDlgMakeTorrent::m_strEncryptPwd	= m_strPassword;
	CDlgMakeTorrent::m_strSourceFilePath = m_strSrcPathFile;
	CDlgMakeTorrent::m_nSelPieceSize = m_nPieceSize;
	CDlgMakeTorrent::m_bIsFile	= m_nFileOrDir == 0;
	CDlgMakeTorrent::m_nCodePage = m_wndCodePage.GetItemData( m_wndCodePage.GetCurSel() );
	CDlgMakeTorrent::m_bMakeSHA1 = IsDlgButtonChecked( 1014 );

	CDlgMTProgress dlg;
	dlg.DoModal();
}

BOOL CALLBACK CDlgMakeTorrent::EnumCodePageProc( LPTSTR lpCodePageString )
{
    m_arryCodePages.Add( lpCodePageString );
    return TRUE;
}

int CDlgMakeTorrent::SelectCodePage( CComboBox &wndComboBox, UINT nCodePage )
{
    int nIndex = -1;
    for ( register int i = 0; i < wndComboBox.GetCount(); i++ )
    {
        if ( nCodePage == wndComboBox.GetItemData( i ) )
        {
            nIndex = i;
            break;
        }
    }

    return nIndex;
}

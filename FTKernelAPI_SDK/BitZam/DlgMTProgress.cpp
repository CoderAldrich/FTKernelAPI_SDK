// DlgMTProgress.cpp : implementation file
//

#include "stdafx.h"
#include "BitZam.h"
#include "DlgMTProgress.h"
#include "BitZamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE CDlgMTProgress::m_hThread = NULL;

/////////////////////////////////////////////////////////////////////////////
// CDlgMTProgress dialog


CDlgMTProgress::CDlgMTProgress( CWnd* pParent /*=NULL*/ )
        : CDialog( CDlgMTProgress::IDD, pParent )
{
    //{{AFX_DATA_INIT(CDlgMTProgress)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

	m_nProgress = 0;
	m_bCanceled = FALSE;
}


void CDlgMTProgress::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(CDlgMTProgress)
    DDX_Control( pDX, 1002, m_wndProgress );
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP( CDlgMTProgress, CDialog )
//{{AFX_MSG_MAP(CDlgMTProgress)
ON_BN_CLICKED( 1, OnOk )
ON_WM_TIMER()
ON_BN_CLICKED( 2, OnCancel )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMTProgress message handlers

HMakeTorrent g_hTorrent = NULL;

BOOL CDlgMTProgress::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here

    SetTimer( 1088, 250, NULL );

	g_hTorrent = FTK_MT_Open();
	if ( NULL == g_hTorrent )
	{
		return FALSE;
	}
	
	CWinThread *pThread = AfxBeginThread( WorkThreadProc, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL );
	if ( NULL ==  pThread )
	{
        return FALSE;
    }

	m_hThread = pThread ->m_hThread;
	pThread ->ResumeThread();

    AfxEnableDlgItem( this, 1, FALSE );
	AfxEnableDlgItem( this, 2, TRUE );

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMTProgress::OnOk()
{
    // TODO: Add your control notification handler code here

	WaitForSingleObject( m_hThread, INFINITE );
	FTK_MT_Close( g_hTorrent );
	g_hTorrent = NULL;
    CDialog::OnOK();
}

void CDlgMTProgress::OnCancel()
{
    // TODO: Add your control notification handler code here

	if ( NULL != g_hTorrent )
	{
		FTK_MT_StopMake( g_hTorrent );	
	}

	m_bCanceled = TRUE;
	WaitForSingleObject( m_hThread, INFINITE );
	FTK_MT_Close( g_hTorrent );
	g_hTorrent = NULL;

	CDialog::OnCancel();
}

void CDlgMTProgress::OnTimer( UINT nIDEvent )
{
    // TODO: Add your message handler code here and/or call default

	m_nProgress = (int)FTK_MT_GetMTProgress( g_hTorrent );
    int nPos = ( int ) m_nProgress;
    m_wndProgress.SetPos( nPos );

	if ( ( nPos >= 100 ) || m_hThread == NULL )
    {
		Sleep( 10 );
        AfxEnableDlgItem( this, 1 );
        AfxEnableDlgItem( this, 2, FALSE );

        KillTimer( 1088 );

        MessageBeep( MB_ICONEXCLAMATION );
    }

    CDialog::OnTimer( nIDEvent );
}

UINT CDlgMTProgress::WorkThreadProc( LPVOID lpParam )
{
    return ( ( CDlgMTProgress * ) lpParam ) ->WorkThreadProc();
}

UINT CDlgMTProgress::WorkThreadProc()
{
	if ( NULL == g_hTorrent )
	{
		return 0;
	}
	
    CString strText;
    FTK_MT_SetAnnounceUrl( g_hTorrent, CDlgMakeTorrent::m_strMainAnnounce );

    CStringArray arryAnnounces;
    CString strAnnounce;
    strText = CDlgMakeTorrent::m_strOtherAnnounces;
    strText += _T( "\r\n" );

    for ( register int j = 0; j < strText.GetLength(); j++ )
    {
        if ( strText[ j ] == _T( '\r' ) || strText[ j ] == _T( '\n' ) )
        {
            if ( strAnnounce.GetLength() > 0 )
            {
                arryAnnounces.Add( strAnnounce );
                strAnnounce = _T( "" );
            }

            if ( arryAnnounces.GetSize() > 0 )
            {
				CStrArray strArray( arryAnnounces );
				if ( NULL != strArray.GetArrayPtr() )
				{
					FTK_MT_AddAnnounceList( g_hTorrent, (LPCTSTR *)strArray.GetArrayPtr(), strArray.GetArraySize() );
				}

                arryAnnounces.RemoveAll();
            }

            continue;
        }

        if ( strText[ j ] != _T( ',' ) && strText[ j ] != _T( ' ' ) )
        {
            strAnnounce += strText[ j ];
        }
        else
        {
            if ( !strAnnounce.IsEmpty() )
            {
                arryAnnounces.Add( strAnnounce );
                strAnnounce = _T( "" );
            }
        }
    }

    //FTK_MT_SetRealName( g_hTorrent, "我们代理司金銮殿非建立撒.rar" );
    FTK_MT_SetComments( g_hTorrent, CDlgMakeTorrent::m_strComments );

    if ( CDlgMakeTorrent::m_bIsFile )
    {
        FTK_MT_SetFile( g_hTorrent, CDlgMakeTorrent::m_strSourceFilePath );
    }
    else
    {
        FTK_MT_SetPath( g_hTorrent, CDlgMakeTorrent::m_strSourceFilePath );
    }

    FTK_MT_SetPieceSize( g_hTorrent, GetPieceSize( CDlgMakeTorrent::m_strSourceFilePath, CDlgMakeTorrent::m_nSelPieceSize ) );
    FTK_MT_SetLangCodePage( g_hTorrent, CDlgMakeTorrent::m_nCodePage );
	FTK_MT_SetFileSHA1( g_hTorrent, CDlgMakeTorrent::m_bMakeSHA1 );

	BOOL bRet = FTK_MT_MakeTorrent( g_hTorrent );
	bRet &= FTK_MT_SaveAsTorrentFile( g_hTorrent, CDlgMakeTorrent::m_strDestTorrentName, CDlgMakeTorrent::m_strEncryptPwd.IsEmpty() ? NULL : (LPCTSTR)CDlgMakeTorrent::m_strEncryptPwd );

	if ( !bRet && !m_bCanceled )
	{
		AfxMessageBox( _T("Failed to create new torrent file!") );
 	}
	
    return 0;
}

DWORD CDlgMTProgress::GetPieceSize( LPCTSTR lpszFilePath, int nSelIndex )
{
    ASSERT( NULL != lpszFilePath );

    DWORD dwPieceSize = 1024 * 32;

    if ( nSelIndex == 0 )
    {
        return 0xFFFFFFFF;
    }
    else if ( nSelIndex == 1 )
    {
        dwPieceSize = 1024 * 32;
    }
    else if ( nSelIndex == 2 )
    {
        dwPieceSize = 1024 * 64;
    }
    else if ( nSelIndex == 3 )
    {
        dwPieceSize = 1024 * 128;
    }
    else if ( nSelIndex == 4 )
    {
        dwPieceSize = 1024 * 256;
    }
    else if ( nSelIndex == 5 )
    {
        dwPieceSize = 1024 * 512;
    }
    else if ( nSelIndex == 6 )
    {
        dwPieceSize = 1024 * 1024;
    }
    else if ( nSelIndex == 7 )
    {
        dwPieceSize = 1024 * 1024 * 2;
    }

    return dwPieceSize;
}

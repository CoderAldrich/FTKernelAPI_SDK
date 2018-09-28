// DlgSelFiles.cpp : implementation file
//

#include "stdafx.h"
#include "BitZam.h"
#include "DlgSelFiles.h"
#include "FTKernelAPI.h"
#include "BitZamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelFiles dialog


CDlgSelFiles::CDlgSelFiles(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelFiles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelFiles)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSelFiles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelFiles)
	DDX_Control(pDX, 1011, m_wndFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelFiles, CDialog)
	//{{AFX_MSG_MAP(CDlgSelFiles)
	ON_BN_CLICKED(1004, OnSelAll)
	ON_BN_CLICKED(1005, OnInvertSel)
	ON_BN_CLICKED(1006, OnDeSelAll)
	ON_NOTIFY(LVN_ITEMCHANGED, 1011, OnItemchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelFiles message handlers

void CDlgSelFiles::OnSelAll() 
{
	// TODO: Add your control notification handler code here
    int nCount = m_wndFiles.GetItemCount();

    for ( int i = 0; i < nCount; i++ )
    {
        m_wndFiles.SetCheck( i, TRUE );
    }	
}

void CDlgSelFiles::OnInvertSel() 
{
	// TODO: Add your control notification handler code here
	
    int nCount = m_wndFiles.GetItemCount();

    for ( int i = 0; i < nCount; i++ )
    {
        m_wndFiles.SetCheck( i, !m_wndFiles.GetCheck( i ) );
    }
}

void CDlgSelFiles::OnDeSelAll() 
{
	// TODO: Add your control notification handler code here
	
    int nCount = m_wndFiles.GetItemCount();

    for ( int i = 0; i < nCount; i++ )
    {
        m_wndFiles.SetCheck( i, FALSE );
    }
}

BOOL CDlgSelFiles::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    InitializeHeaderControl();
    InitializeListControl();

    for ( int i = 0; i < m_wndFiles.GetItemCount(); i++ )
    {
        m_wndFiles.SetCheck( i, FALSE );
    }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelFiles::InitializeHeaderControl()
{
    m_wndFiles.ModifyStyle( NULL, LVS_REPORT );

    m_wndFiles.SetExtendedStyle( LVS_EX_FULLROWSELECT |
                                 LVS_EX_GRIDLINES | LVS_EX_FLATSB | LVS_EX_CHECKBOXES );

    CRect rectHeader;
    m_wndFiles.GetDlgItem( 0 ) ->GetClientRect( rectHeader );

    LV_COLUMN lvc;
    lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH | LVCF_FMT;
    lvc.fmt = LVCFMT_LEFT;

    CString strColNames[ 3 ];
    strColNames[ 0 ] = _T( "File Name" );
    strColNames[ 1 ] = _T( "Size" );
    strColNames[ 2 ] = _T( "%" );

    int i = 0;

    lvc.cx = rectHeader.Width() / 3 * 2;
    lvc.iSubItem = i;

    lvc.pszText = ( LPTSTR ) ( LPCTSTR ) strColNames[ i ];
    m_wndFiles.InsertColumn( i++, &lvc );

    lvc.cx = rectHeader.Width() / 3 * 1 / 2 ;
    lvc.iSubItem = i;

    lvc.pszText = ( LPTSTR ) ( LPCTSTR ) strColNames[ i ];
    m_wndFiles.InsertColumn( i++, &lvc );

    lvc.cx = rectHeader.Width() / 3 * 1 / 2;
    lvc.iSubItem = i;

    lvc.pszText = ( LPTSTR ) ( LPCTSTR ) strColNames[ i ];
    m_wndFiles.InsertColumn( i++, &lvc );
}

void CDlgSelFiles::InitializeListControl()
{
    m_wndFiles.DeleteAllItems();

	HTorrentFile hTorrentFile = FTK_Torrent_Open( m_strTorrentName, CP_ACP, m_strPassword.IsEmpty() ? NULL : (LPCTSTR)m_strPassword, FALSE, FALSE );
	if ( NULL == hTorrentFile )
	{
		return;
	}

    if ( !FTK_Torrent_IsFile( hTorrentFile ) )
    {
        CString strSize;

        int nFileCount = FTK_Torrent_GetFilesCount( hTorrentFile );
		_tagFileInfo *pFileInfo = new _tagFileInfo[ nFileCount ];
		ASSERT( NULL != pFileInfo );
		FTK_Torrent_GetFiles( hTorrentFile, pFileInfo );
		
        for ( register int i = 0; i < nFileCount; i++ )
        {
            // insert the item.
            m_wndFiles.InsertItem( i, pFileInfo[ i ].m_szFileName, 0 );

            CString strSize = AfxFormatBytes( ( INT64 ) pFileInfo[ i ].m_qwFileSize );
            CString strPercent;
            strPercent.Format( _T( "%lf" ), PERCENT( ( INT64 ) pFileInfo[ i ].m_qwFileSize, ( INT64 ) FTK_Torrent_GetFileSize( hTorrentFile ) ) );
            m_wndFiles.SetItemText( i, 1, strSize );
            m_wndFiles.SetItemText( i, 2, strPercent );
        }

		delete [] pFileInfo;
		pFileInfo = NULL;
    }
    else
    {
        // insert the item.
        CString strName = FTK_Torrent_GetTorrentName( hTorrentFile );
        m_wndFiles.InsertItem( 0, strName, 0 );

        CString strSize = AfxFormatBytes( ( INT64 ) FTK_Torrent_GetFileSize( hTorrentFile ) );
        m_wndFiles.SetItemText( 0, 1, strSize );
        m_wndFiles.SetItemText( 0, 2, _T( "100" ) );
    }

    OnSelAll();
}

void CDlgSelFiles::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CDlgSelFiles::OnOK() 
{
	// TODO: Add extra validation here

	m_arryFilePriority.SetSize( m_wndFiles.GetItemCount() );
    for ( register int i = 0; i < m_wndFiles.GetItemCount(); i++ )
    {
        if ( m_wndFiles.GetCheck( i ) )
        {
            //if ( ( char ) m_arryFilePriority[ i ] < ( char ) - 1 )
            {
                m_arryFilePriority[ i ] = ( BYTE ) 0;
            }
        }
        else
        {
            //if ( m_arryFilePriority[ i ] >= ( char ) - 1 )
            {
                m_arryFilePriority[ i ] = ( BYTE ) - 2;
            }
        }
    }
	
	CDialog::OnOK();
}





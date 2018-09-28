 // DlgProxySettings.cpp : implementation file
//

#include "stdafx.h"
#include "BitZam.h"
#include "BitZamDlg.h"
#include "DlgProxySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProxySettings dialog


CDlgProxySettings::CDlgProxySettings(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProxySettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProxySettings)
    m_nProxyType = 0;
    m_bAuthRequired = FALSE;
    m_strProxyServer = _T( "" );
    m_nProxyPort = 0;
    m_bUseOnlyHTTP = FALSE;
    m_strUserName = _T( "" );
    m_strPassword = _T( "" );
	//}}AFX_DATA_INIT
}


void CDlgProxySettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProxySettings)
    DDX_CBIndex( pDX, 1003, m_nProxyType );
    DDX_Check( pDX, 1010, m_bAuthRequired );
    DDX_Text( pDX, 1005, m_strProxyServer );
    DDX_Text( pDX, 1007, m_nProxyPort );
    DDX_Check( pDX, 1008, m_bUseOnlyHTTP );
    DDX_Text( pDX, 1013, m_strUserName );
    DDX_Text( pDX, 1014, m_strPassword );
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProxySettings, CDialog)
	//{{AFX_MSG_MAP(CDlgProxySettings)
	ON_CBN_SELCHANGE(1003, OnSelchangeProxyType)
	ON_BN_CLICKED(1010, OnClickAuthRequired)
	ON_BN_CLICKED(1015, OnClickTestProxy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProxySettings message handlers

void CDlgProxySettings::OnSelchangeProxyType() 
{
	// TODO: Add your control notification handler code here

    UpdateData();

    AfxEnableDlgItem( this, 1005, m_nProxyType != 0 );
    AfxEnableDlgItem( this, 1007, m_nProxyType != 0 );
    AfxEnableDlgItem( this, 1008, m_nProxyType != 0 );

    AfxEnableDlgItem( this, 1010, m_nProxyType == 3 || m_nProxyType == 4 );
    AfxEnableDlgItem( this, 1013, m_nProxyType == 3 || m_nProxyType == 4 );
    AfxEnableDlgItem( this, 1014, m_nProxyType == 3 || m_nProxyType == 4 );

    AfxEnableDlgItem( this, 1015, m_nProxyType != 0 );		
}

void CDlgProxySettings::OnClickAuthRequired() 
{
	// TODO: Add your control notification handler code here

    UpdateData();

    AfxEnableDlgItem( this, 1013, m_bAuthRequired );
    AfxEnableDlgItem( this, 1014, m_bAuthRequired );	
}

void CDlgProxySettings::OnClickTestProxy() 
{
	// TODO: Add your control notification handler code here
}


BOOL CDlgProxySettings::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    ( ( CComboBox * ) GetDlgItem( 1003 ) ) ->ResetContent();

    TCHAR *szItems[] = {
                           _T( "No Proxy" ),
                           _T( "Socks4" ),
                           _T( "Socks4a" ),
                           _T( "Socks5" ),
                           _T( "HTTP1.1" )
                       };

    for ( register int i = 0; i < 5; i++ )
    {
        ( ( CComboBox * ) GetDlgItem( 1003 ) ) ->AddString( szItems[ i ] );
    }

    ( ( CComboBox * ) GetDlgItem( 1003 ) ) ->SetCurSel( m_nProxyType );

    OnSelchangeProxyType();
    OnClickAuthRequired();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

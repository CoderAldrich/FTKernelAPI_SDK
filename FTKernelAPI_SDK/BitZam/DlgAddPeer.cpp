// DlgAddPeer.cpp : implementation file
//

#include "stdafx.h"
#include "BitZam.h"
#include "DlgAddPeer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddPeer dialog


CDlgAddPeer::CDlgAddPeer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddPeer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddPeer)
	m_nPort = 0;
	//}}AFX_DATA_INIT
}


void CDlgAddPeer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddPeer)
	DDX_Text(pDX, 1002, m_nPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddPeer, CDialog)
	//{{AFX_MSG_MAP(CDlgAddPeer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddPeer message handlers

void CDlgAddPeer::OnOK() 
{
	// TODO: Add extra validation here

    DWORD dwIP = 0L;
    ( ( CIPAddressCtrl * ) GetDlgItem( 1001 ) ) ->GetAddress( dwIP );

    struct in_addr addr;
    addr.S_un.S_addr = ntohl( dwIP );

    if ( dwIP != 0L )
    {
        strcpy( m_szIPAddress, inet_ntoa( ( struct in_addr ) addr ) );
    }

    UpdateData( TRUE );	
	
	CDialog::OnOK();
}

// DlgLinkURL.cpp : implementation file
//

#include "stdafx.h"
#include "bitzam.h"
#include "DlgLinkURL.h"
#include "FTKernelAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkURL dialog


CDlgLinkURL::CDlgLinkURL(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLinkURL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLinkURL)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgLinkURL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLinkURL)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLinkURL, CDialog)
	//{{AFX_MSG_MAP(CDlgLinkURL)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkURL message handlers

void CDlgLinkURL::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
    CString strFilter = _T( "Torrent File(*.Torrent)|*.torrent||" );
    CFileDialog OpenDlg( TRUE, _T( "torrent" ), _T( "*.Torrent" ),
                         OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_FILEMUSTEXIST,
                         strFilter );

    if ( IDOK != OpenDlg.DoModal() )
    {
        return ;
    }

	char szURL[ 1024 ] = {0};
	FTK_Link_GetLink2( OpenDlg.GetPathName(), szURL, 1024 );
	SetDlgItemText( 1002, szURL );
}

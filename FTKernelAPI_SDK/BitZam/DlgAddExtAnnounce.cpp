// DlgAddExtAnnounce.cpp : implementation file
//

#include "stdafx.h"
#include "BitZam.h"
#include "DlgAddExtAnnounce.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddExtAnnounce dialog


CDlgAddExtAnnounce::CDlgAddExtAnnounce(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddExtAnnounce::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddExtAnnounce)
	m_strExtAnnounce = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAddExtAnnounce::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddExtAnnounce)
	DDX_Text(pDX, 1001, m_strExtAnnounce);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddExtAnnounce, CDialog)
	//{{AFX_MSG_MAP(CDlgAddExtAnnounce)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddExtAnnounce message handlers

void CDlgAddExtAnnounce::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData();
	if ( m_strExtAnnounce.IsEmpty() )
	{
		return;
	}
	
	CDialog::OnOK();
}

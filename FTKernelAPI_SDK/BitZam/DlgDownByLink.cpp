// DlgDownByLink.cpp : implementation file
//

#include "stdafx.h"
#include "bitzam.h"
#include "DlgDownByLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDownByLink dialog


CDlgDownByLink::CDlgDownByLink(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDownByLink::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDownByLink)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgDownByLink::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDownByLink)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDownByLink, CDialog)
	//{{AFX_MSG_MAP(CDlgDownByLink)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDownByLink message handlers

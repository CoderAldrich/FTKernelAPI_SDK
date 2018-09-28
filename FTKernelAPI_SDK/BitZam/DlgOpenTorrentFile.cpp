// DlgOpenTorrentFile.cpp : implementation file
//

#include "stdafx.h"
#include "BitZam.h"
#include "BitZamDlg.h"
#include "SBDestination.h"
#include "DlgOpenTorrentFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOpenTorrentFile dialog


CDlgOpenTorrentFile::CDlgOpenTorrentFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOpenTorrentFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOpenTorrentFile)
	m_strPassword = _T("");
	m_strDestPath = _T("");
	//}}AFX_DATA_INIT

	m_bEncrypt	= FALSE;
}


void CDlgOpenTorrentFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOpenTorrentFile)
	DDX_Text(pDX, 1002, m_strPassword);
	DDX_Text(pDX, 1003, m_strDestPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOpenTorrentFile, CDialog)
	//{{AFX_MSG_MAP(CDlgOpenTorrentFile)
	ON_BN_CLICKED(1001, OnSelDestPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOpenTorrentFile message handlers

void CDlgOpenTorrentFile::OnSelDestPath() 
{
	// TODO: Add your control notification handler code here

	CSBDestination SB;
	SB.SetTitle( _T("Select Folder") );
	SB.SetInitialSelection( _T("") );
	if ( TRUE == SB.SelectFolder() )
	{
		SetDlgItemText( 1003, SB.GetSelectedFolder() );
	}	
}

BOOL CDlgOpenTorrentFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	AfxEnableDlgItem( this, 1002, m_bEncrypt );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgOpenTorrentFile::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData();

	if ( m_bEncrypt && m_strPassword.IsEmpty() )
	{
		AfxMessageBox( _T("Please input password for the torrent!") );
		return;
	}

	if ( m_strDestPath.IsEmpty() )
	{
		AfxMessageBox( _T("Please select or input destination directory!") );
		return;
	}

	if ( m_strDestPath[ m_strDestPath.GetLength() - 1 ] != _T('\\') )
	{
		m_strDestPath += _T("\\");
	}
	
	CDialog::OnOK();
}

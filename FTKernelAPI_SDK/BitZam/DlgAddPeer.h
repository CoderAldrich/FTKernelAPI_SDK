#if !defined(AFX_DLGADDPEER_H__6F480861_90FE_4CC8_B301_DE1A7399B1CD__INCLUDED_)
#define AFX_DLGADDPEER_H__6F480861_90FE_4CC8_B301_DE1A7399B1CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddPeer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddPeer dialog

class CDlgAddPeer : public CDialog
{
// Construction
public:
	CDlgAddPeer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddPeer)
	enum { IDD = IDD_DLG_ADD_PEER };
	UINT	m_nPort;
	//}}AFX_DATA

    char m_szIPAddress[ 16 ];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddPeer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddPeer)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDPEER_H__6F480861_90FE_4CC8_B301_DE1A7399B1CD__INCLUDED_)

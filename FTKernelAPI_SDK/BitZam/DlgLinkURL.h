#if !defined(AFX_DLGLINKURL_H__EBB8CF2E_DD1D_4DBB_8F10_B3995CE988CF__INCLUDED_)
#define AFX_DLGLINKURL_H__EBB8CF2E_DD1D_4DBB_8F10_B3995CE988CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLinkURL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkURL dialog

class CDlgLinkURL : public CDialog
{
// Construction
public:
	CDlgLinkURL(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLinkURL)
	enum { IDD = IDD_DLG_DWON_LINKURL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLinkURL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLinkURL)
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLINKURL_H__EBB8CF2E_DD1D_4DBB_8F10_B3995CE988CF__INCLUDED_)

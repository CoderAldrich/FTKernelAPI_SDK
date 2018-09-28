#if !defined(AFX_DLGDOWNBYLINK_H__9304DAD5_44EB_481A_BF5E_9DB6B6DCF09D__INCLUDED_)
#define AFX_DLGDOWNBYLINK_H__9304DAD5_44EB_481A_BF5E_9DB6B6DCF09D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDownByLink.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDownByLink dialog

class CDlgDownByLink : public CDialog
{
// Construction
public:
	CDlgDownByLink(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDownByLink)
	enum { IDD = IDD_DLG_ADD_DOWNBYLINK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDownByLink)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDownByLink)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDOWNBYLINK_H__9304DAD5_44EB_481A_BF5E_9DB6B6DCF09D__INCLUDED_)

#if !defined(AFX_DLGPROXYSETTINGS_H__CDD249E2_4FFF_47F8_B134_671D75917F98__INCLUDED_)
#define AFX_DLGPROXYSETTINGS_H__CDD249E2_4FFF_47F8_B134_671D75917F98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProxySettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProxySettings dialog

class CDlgProxySettings : public CDialog
{
// Construction
public:
	CDlgProxySettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProxySettings)
	enum { IDD = IDD_PROXYSETTINGS };
    int	m_nProxyType;
    BOOL	m_bAuthRequired;
    CString	m_strProxyServer;
    UINT	m_nProxyPort;
    BOOL	m_bUseOnlyHTTP;
    CString	m_strUserName;
    CString	m_strPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProxySettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProxySettings)
	afx_msg void OnSelchangeProxyType();
	afx_msg void OnClickAuthRequired();
	afx_msg void OnClickTestProxy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXYSETTINGS_H__CDD249E2_4FFF_47F8_B134_671D75917F98__INCLUDED_)

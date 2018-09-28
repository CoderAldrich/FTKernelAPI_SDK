#if !defined(AFX_DLGMTPROGRESS_H__BB3040B7_95AA_4D4D_9FC8_19F3D6202FF0__INCLUDED_)
#define AFX_DLGMTPROGRESS_H__BB3040B7_95AA_4D4D_9FC8_19F3D6202FF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000 
// DlgMTProgress.h : header file
//

#include "DlgMakeTorrent.h"
#include "TextProgressCtrl.h"

class CStrArray
{
public:
	CStrArray( CStringArray &strArray )
	{
		m_pStrArray = NULL;
		if ( 0 == strArray.GetSize() )
		{
			return;
		}

		m_nCount = strArray.GetSize();
		m_pStrArray = new LPTSTR[ m_nCount ];
		ASSERT( NULL != m_pStrArray );
		for ( register int i = 0; i < m_nCount; i++ )
		{
			m_pStrArray[ i ] = new TCHAR[ strArray[ i ].GetLength() + 1 ];
			strcpy( m_pStrArray[ i ], (LPCTSTR)strArray[ i ]);
		}
	};

	~CStrArray()
	{
		for ( register int i = 0; i < m_nCount; i++ )
		{
			delete [] m_pStrArray[ i ];
			m_pStrArray[ i ] = NULL;
		}

		delete [] m_pStrArray;
		m_pStrArray = NULL;
	};

	LPTSTR *GetArrayPtr()
	{
		return m_pStrArray;
	};

	int GetArraySize()
	{
		return m_nCount;
	};
	
protected:

	LPTSTR *m_pStrArray;
	int m_nCount;
};

/////////////////////////////////////////////////////////////////////////////
// CDlgMTProgress dialog

class CDlgMTProgress : public CDialog
{
    // Construction
public:
    CDlgMTProgress( CWnd* pParent = NULL );   // standard constructor

    // Dialog Data
    //{{AFX_DATA(CDlgMTProgress)
    enum { IDD = IDD_DLG_MTPOGRESS };
    CTextProgressCtrl	m_wndProgress;
    //}}AFX_DATA

	static HANDLE m_hThread;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgMTProgress)
protected:
    virtual void DoDataExchange( CDataExchange* pDX );    // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDlgMTProgress)
    virtual BOOL OnInitDialog();
    afx_msg void OnOk();
    afx_msg void OnCancel();
    afx_msg void OnTimer( UINT nIDEvent );
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:

    static UINT WorkThreadProc( LPVOID lpParam );
    UINT WorkThreadProc();

    DWORD GetPieceSize( LPCTSTR lpszFilePath, int nSelIndex );

protected:

	int m_nProgress;
	BOOL m_bCanceled;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMTPROGRESS_H__BB3040B7_95AA_4D4D_9FC8_19F3D6202FF0__INCLUDED_)

// BitZam.h : main header file for the BITZAM application
//

#if !defined(AFX_BITZAM_H__E5D72C41_E2BB_4F2A_B33B_06A8DC94638A__INCLUDED_)
#define AFX_BITZAM_H__E5D72C41_E2BB_4F2A_B33B_06A8DC94638A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBitZamApp:
// See BitZam.cpp for the implementation of this class
//

class CBitZamApp : public CWinApp
{
public:
	CBitZamApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitZamApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBitZamApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline CBitZamApp *AfxGetBZApp()
{
    return ( CBitZamApp * ) AfxGetApp();
}


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITZAM_H__E5D72C41_E2BB_4F2A_B33B_06A8DC94638A__INCLUDED_)

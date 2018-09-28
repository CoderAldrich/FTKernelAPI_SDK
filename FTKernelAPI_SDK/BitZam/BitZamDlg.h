// BitZamDlg.h : header file
//

#if !defined(AFX_BITZAMDLG_H__BD4EBBB3_3E53_4A9D_9A54_45E157A7B659__INCLUDED_)
#define AFX_BITZAMDLG_H__BD4EBBB3_3E53_4A9D_9A54_45E157A7B659__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FTKernelAPI.h"
#include "HyperLink.h"
#include "TextProgressCtrl.h"

#define WM_MSG_TUNNEL ( WM_USER + 102 )
#define WM_MSG_PEERCALL ( WM_USER + 103 )

inline void AfxEnableDlgItem( CWnd *pDlg, int nIDDlgItem, BOOL bEnabled = TRUE )
{
    HWND hDlgItem = ::GetDlgItem( pDlg->GetSafeHwnd(),
                                  nIDDlgItem );

    EnableWindow( hDlgItem, bEnabled );
}

inline CString AfxFormatBytes( INT64 nBytes )
{
    CString strResult;

    if ( nBytes >= ( INT64 ) 0x10000000000L )
    {
        strResult.Format( _T( "%-.2f TB" ), nBytes / 1099511627776.0f );
    }
    else if ( nBytes >= 0x40000000 )
    {
        strResult.Format( _T( "%-.2f GB" ), nBytes / 1073741824.0f );
    }
    else if ( nBytes >= 0x100000 )
    {
        strResult.Format( _T( "%-.2f MB" ), nBytes / 1048576.0f );
    }
    else if ( nBytes >= 0x400 )
    {
        strResult.Format( _T( "%-.2f KB" ), nBytes / 1024.0f );
    }
    else
    {
        strResult.Format( _T( "%ld Byte" ), nBytes );
    }

    return strResult;
}

#define PERCENT(n, d) ((100 * (double)(n)) / (double)(d))

/////////////////////////////////////////////////////////////////////////////
// CBitZamDlg dialog

class CBitZamDlg : public CDialog
{
// Construction
public:
	CBitZamDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBitZamDlg)
	enum { IDD = IDD_BITZAM_DIALOG };
	CHyperLink	m_stdKernelLink;
	CTextProgressCtrl	m_pgrDownload;
	CString	m_strTorrentFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitZamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBitZamDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnExit();
	afx_msg void OnClose();
	afx_msg void OnSelTorrentFile();
	afx_msg void OnStartDownload();
	afx_msg void OnProxySettings();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnMakeTorrent();
	afx_msg void OnSelFiles();
	afx_msg void OnAddExtAnnounce();
	afx_msg void OnAddPeer();
	afx_msg void OnManualAnnounce();
	afx_msg void OnTorrentData();
	afx_msg void On1031();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void On1034();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	//}}AFX_MSG
	afx_msg LRESULT OnNatTunnel( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnPeerCall( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

protected:

	BOOL StartContext();
	BOOL StopContext();
	BOOL StartDownload();
	BOOL StartDownload2();
	BOOL StopDownload();

	//内网穿透需要的初始化函数
	BOOL InitNatTunnel();

	//内网穿透需要的释放函数
	void FreeNatTunnel();

	//内网事件驱动
	void DoUDPEvents();

protected:

	HDownloader m_hDownloader;
	CString m_strKeyValue;
	BOOL m_bInitContext;
	QWORD m_qwTotalFileSize;
	DWORD m_dwPieceCount;
	CString m_strDestPath;
	CString m_strPassword;

	//内网穿透是否初始化
	BOOL m_bInitUDP;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITZAMDLG_H__BD4EBBB3_3E53_4A9D_9A54_45E157A7B659__INCLUDED_)

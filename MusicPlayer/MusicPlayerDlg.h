// MusicPlayerDlg.h : header file
//
//{{AFX_INCLUDES()
#include "wmpplayer4.h"
//}}AFX_INCLUDES

#if !defined(AFX_MUSICPLAYERDLG_H__4E48F485_4C23_4E0E_A7A3_94C651BDA187__INCLUDED_)
#define AFX_MUSICPLAYERDLG_H__4E48F485_4C23_4E0E_A7A3_94C651BDA187__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMusicPlayerDlg dialog

class CMusicPlayerDlg : public CDialog
{
// Construction
public:
	CMusicPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMusicPlayerDlg)
	enum { IDD = IDD_MUSICPLAYER_DIALOG };
	CString	m_edit;
	CWMPPlayer4	m_MediaPlayer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMusicPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	afx_msg void OnSelchangeList1();
	afx_msg void OnButtonPlay();
	afx_msg void OnDblclkList1();
	afx_msg void OnButtonLoadList();
	afx_msg void OnButtonSaveList();
	afx_msg void OnButtonRename();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonST();
	afx_msg void OnButtonS();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICPLAYERDLG_H__4E48F485_4C23_4E0E_A7A3_94C651BDA187__INCLUDED_)

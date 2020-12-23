// MusicPlayer.h : main header file for the MUSICPLAYER application
//

#if !defined(AFX_MUSICPLAYER_H__5E44E623_8995_4548_844E_CE670F821B59__INCLUDED_)
#define AFX_MUSICPLAYER_H__5E44E623_8995_4548_844E_CE670F821B59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMusicPlayerApp:
// See MusicPlayer.cpp for the implementation of this class
//

class CMusicPlayerApp : public CWinApp
{
public:
	CMusicPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMusicPlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICPLAYER_H__5E44E623_8995_4548_844E_CE670F821B59__INCLUDED_)

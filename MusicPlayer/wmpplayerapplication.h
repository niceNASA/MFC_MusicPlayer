#if !defined(AFX_WMPPLAYERAPPLICATION_H__918E60C4_2411_4B66_B020_D0FA11128012__INCLUDED_)
#define AFX_WMPPLAYERAPPLICATION_H__918E60C4_2411_4B66_B020_D0FA11128012__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CWMPPlayerApplication wrapper class

class CWMPPlayerApplication : public COleDispatchDriver
{
public:
	CWMPPlayerApplication() {}		// Calls COleDispatchDriver default constructor
	CWMPPlayerApplication(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPPlayerApplication(const CWMPPlayerApplication& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void switchToPlayerApplication();
	void switchToControl();
	BOOL GetPlayerDocked();
	BOOL GetHasDisplay();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMPPLAYERAPPLICATION_H__918E60C4_2411_4B66_B020_D0FA11128012__INCLUDED_)

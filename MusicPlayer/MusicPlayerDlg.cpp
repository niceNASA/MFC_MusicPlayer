// MusicPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "MusicPlayerDlg.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include "wmpcontrols.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicPlayerDlg dialog

CMusicPlayerDlg::CMusicPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMusicPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMusicPlayerDlg)
	m_edit = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusicPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMusicPlayerDlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_OCX1, m_MediaPlayer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMusicPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CMusicPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonOpen)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonPlay)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonLoadList)
	ON_BN_CLICKED(IDC_BUTTON4, OnButtonSaveList)
	ON_BN_CLICKED(IDC_BUTTON5, OnButtonRename)
	ON_BN_CLICKED(IDC_BUTTON6, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON7, OnButtonST)
	ON_BN_CLICKED(IDC_BUTTON8, OnButtonS)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicPlayerDlg message handlers

BOOL CMusicPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMusicPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMusicPlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMusicPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

using namespace std;
map<CString, CString> playList;		//播放列表缓存，曲名-路径

void CMusicPlayerDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	char szFileFilter[] = "mp3文件(*.mp3)|*.mp3|";//文件类型过滤  
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY, szFileFilter);
	
	CString fPath;
	CString fName;

	if (dlg.DoModal() == IDOK){
		fPath = dlg.GetPathName();
		fName = dlg.GetFileName();
	}
	CListBox *m_listbox;
	m_listbox = (CListBox*)GetDlgItem(IDC_LIST1);

	playList.insert(pair<CString,CString>(fName,fPath));	//将选择的歌曲文件添加到当前播放列表中
/*
	map<CString, CString>::iterator iter;
	iter = playList.find(fName);
	if(iter != playList.end())
		MessageBox(iter->second);
*/
	
	m_listbox->AddString(fName);
}

void CMusicPlayerDlg::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	
}

void CMusicPlayerDlg::OnButtonPlay() 
{
	// TODO: Add your control notification handler code here
	CListBox *m_listbox;
	m_listbox = (CListBox*)GetDlgItem(IDC_LIST1);
	int num = m_listbox->GetCurSel();	//获取选中的行号
	CString fName;
	CString fPath;
	m_listbox->GetText(num, fName);		//获取选中的内容
	
	map<CString, CString>::iterator iter;
	iter = playList.find(fName);
	if(iter != playList.end()){
		//MessageBox(iter->second);
		fPath = iter->second;
	}else{
		MessageBox("不存在");
	}
	
	m_MediaPlayer.SetUrl(fPath);
	/*
	CString t1 = "\"";
	CString t2 = "\"";
	fPath = t1 + fPath;
	fPath = fPath + t2;
	system(fPath);
	*/

}

void CMusicPlayerDlg::OnDblclkList1() //双击列表播放
{
	// TODO: Add your control notification handler code here
	OnButtonPlay();
}

void CMusicPlayerDlg::OnButtonLoadList() 
{
	// TODO: Add your control notification handler code here
	char szFileFilter[] = "文本文档(*.txt)|*.txt|";//文件类型过滤  
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY, szFileFilter);
	
	CString fPath;
	CString fName;

	if (dlg.DoModal() == IDOK){
		fPath = dlg.GetPathName();
		fName = dlg.GetFileName();
	}
	CListBox *m_listbox;
	m_listbox = (CListBox*)GetDlgItem(IDC_LIST1);
	
	fstream in;
	in.open(fPath, ios::in);
	playList.clear();
	m_listbox->ResetContent();
	while(!in.eof()){
		char temp1[256];
		in.getline(temp1,256);
		CString mName(temp1);
		char temp2[512];
		in.getline(temp2,512);
		CString mPath(temp2);
		playList.insert(pair<CString,CString>(mName,mPath));
		m_listbox->AddString(mName);
	}

	in.close();
	//playList.insert(pair<CString,CString>(fName,fPath));
}


void CMusicPlayerDlg::OnButtonSaveList() 
{
	// TODO: Add your control notification handler code here
	fstream out;
	out.open("PlayList.txt", ios::out);
	
	CListBox *m_listbox;
	m_listbox = (CListBox*)GetDlgItem(IDC_LIST1);
	int n = m_listbox->GetCount();

	for(int i=0; i<n; i++){
		CString fName;
		CString fPath;
		m_listbox->GetText(i, fName);		
		map<CString, CString>::iterator iter;
		iter = playList.find(fName);
		if(iter != playList.end()){
			string temp1 = LPCSTR(iter->first);
			string temp2 = LPCSTR(iter->second);
			out << temp1 << endl;
			out << temp2 << endl;
		}
	}
	
	/*
	map<CString, CString>::iterator it;
	for(it=playList.begin(); it!=playList.end(); it++){
		string temp1 = LPCSTR(it->first);
		string temp2 = LPCSTR(it->second);
		out << temp1 << endl;
		out << temp2 << endl;
	}
	*/


	out.close();
	
	MessageBox("保存成功！\nPlayList.txt保存在添加过的歌曲或本程序所在目录下");
}

void CMusicPlayerDlg::OnButtonRename() 
{
	// TODO: Add your control notification handler code here
	CListBox *m_listbox;
	m_listbox = (CListBox*)GetDlgItem(IDC_LIST1);
	int num = -1;
	try{
		num = m_listbox->GetCurSel();	//获取选中的行号
	}catch(CException e){
		MessageBox("未选择");
	}
	if(num!=-1){
		CString fName;
		CString fPath;
		m_listbox->GetText(num, fName);		//获取选中的内容
		
		map<CString, CString>::iterator iter;
		iter = playList.find(fName);
		if(iter != playList.end()){
			UpdateData();
			if(!m_edit.IsEmpty()){
				fPath = iter->second;
			playList.erase(fName);
			fName = m_edit;
			playList.insert(pair<CString,CString>(fName,fPath));
			m_listbox->DeleteString(num);
			m_listbox->InsertString(num,fName);
			m_edit.Empty();
			UpdateData();
			}else{
				MessageBox("请在重命名编辑框中输入新的名字");
			}
		}else{
			MessageBox("不存在");
		}
	}
}

void CMusicPlayerDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	CListBox *m_listbox;
	m_listbox = (CListBox*)GetDlgItem(IDC_LIST1);
	int num = -1;
	try{
		num = m_listbox->GetCurSel();	//获取选中的行号
	}catch(CException e){
		MessageBox("未选择");
	}
	if(num!=-1){
		CString fName;
		CString fPath;
		m_listbox->GetText(num, fName);		//获取选中的内容
		
		map<CString, CString>::iterator iter;
		iter = playList.find(fName);
		if(iter != playList.end()){
			//MessageBox(iter->second);
			playList.erase(fName);
			m_listbox->DeleteString(num);
		}else{
			MessageBox("不存在");
		}
	}
}

void CMusicPlayerDlg::OnButtonST() 
{
	// TODO: Add your control notification handler code here
	CWMPControls m_WMPControls;
	m_WMPControls = static_cast<CWMPControls>(m_MediaPlayer.GetControls());
	m_WMPControls.pause();
}

void CMusicPlayerDlg::OnButtonS() 
{
	// TODO: Add your control notification handler code here
	CWMPControls m_WMPControls;
	m_WMPControls = static_cast<CWMPControls>(m_MediaPlayer.GetControls());
	m_WMPControls.play();
}

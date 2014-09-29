
// SevenServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SevenServer.h"
#include "SevenServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
typedef struct
{
	CString	title;
	double		nWidth;
}COLUMNSTRUCT;
COLUMNSTRUCT m_Column_Data[] = 
{
	{_T("Wan"),					0.2		},
	{_T("Lan"),					0.2		},
	{_T("Hostname"),			0.2		},
	{_T("User"),				0.1		},
	{_T("Version"),				0.2		},
	{_T("Comment"),				0.1		},
};

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSevenServerDlg �Ի���




CSevenServerDlg::CSevenServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSevenServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSevenServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLIENT_LISTCTRL, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CSevenServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CSevenServerDlg ��Ϣ��������

BOOL CSevenServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ����Ӷ���ĳ�ʼ������
	m_Column_Count = 6;
	InitListCtrl();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSevenServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSevenServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSevenServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSevenServerDlg::InitListCtrl()
{
	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listCtrl.SetExtendedStyle(dwStyle); //������չ���
	
	CRect rect;
	this->GetClientRect(&rect);
	int width = rect.Width();
	for (int i=0;i<m_Column_Count;i++)
	{
		m_listCtrl.InsertColumn(i,m_Column_Data[i].title,LVCFMT_LEFT,(int)width*m_Column_Data[i].nWidth);
	}
}

void CSevenServerDlg::OnSize(UINT nType, int cx, int cy)
{
	//////////////////////////////////////////////////////////////////////////
	// move list ctrl
	//////////////////////////////////////////////////////////////////////////
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect;
	this->GetClientRect(&rect);
	m_listCtrl.MoveWindow(rect);
	int width = rect.Width();
	for (int i=0;i<m_Column_Count;i++)
	{
		m_listCtrl.SetColumnWidth(i,(int)width*m_Column_Data[i].nWidth);
	}
	// TODO: �ڴ˴�������Ϣ�����������
}


void CSevenServerDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: �ڴ˴�������Ϣ�����������
// 	if (m_listCtrl.GetSelectedCount() <= 0)
// 	{
// 		return;
// 	}
	//�������δ���, ��������Ӧ��ListCtrl
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_LIST_MENU);
	pPopup = menu.GetSubMenu(0);
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y,this);
}
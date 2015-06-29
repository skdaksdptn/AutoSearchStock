
// AutoSearchStockDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "AutoSearchStock.h"
#include "AutoSearchStockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CAutoSearchStockDlg ��ȭ ����



CAutoSearchStockDlg::CAutoSearchStockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutoSearchStockDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoSearchStockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editStatusBar);
	DDX_Control(pDX, IDC_EDIT2, m_editStockCount);
}

BEGIN_MESSAGE_MAP(CAutoSearchStockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1_CONNECT, &CAutoSearchStockDlg::OnBnClickedButton1Connect)
	ON_MESSAGE(WM_USER + XM_LOGIN, OnLogin)
	ON_MESSAGE(WM_USER + XM_DISCONNECT, OnDisConnect)
	ON_BN_CLICKED(IDC_BUTTON2_DISCONNECT, &CAutoSearchStockDlg::OnBnClickedButton2Disconnect)
END_MESSAGE_MAP()


// CAutoSearchStockDlg �޽��� ó����

BOOL CAutoSearchStockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	p_XingAPI = new IXingAPI;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CAutoSearchStockDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CAutoSearchStockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CAutoSearchStockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Test Connection 
void CAutoSearchStockDlg::OnBnClickedButton1Connect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strPath = "";

	// Dll init
	if (!(p_XingAPI->Init(NULL)))
	{
		int nLen = (int)GetModuleFileName(AfxGetInstanceHandle(), strPath.GetBuffer(MAX_PATH), MAX_PATH);
		strPath.ReleaseBuffer(nLen);
		int nFind = strPath.ReverseFind('\\');
		if (nFind > 0)
		{
			strPath = strPath.Left(nFind);

			if (!(p_XingAPI->Init(strPath)))
			{
				m_editStatusBar.SetWindowTextA("DLL �ε�����");
				return; // �ε����� ��ȯ.
			}
		}
	}
	else
	{
		m_editStatusBar.SetWindowTextA("DLL �ε�����");
	}

	// Connect Stock Server
	if (p_XingAPI->Connect(
				GetSafeHwnd(),
				"hts.etrade.co.kr",
				20001,
				WM_USER, -1, -1	))
	{
		// Success
		m_editStatusBar.SetWindowTextA("HTS �������� ����");

		// User Login
		if (p_XingAPI->Login(
				GetSafeHwnd(),
				"ID",
				"PW",
				"PW2",
				0, true))
		{
			// Success
			m_editStatusBar.SetWindowTextA("���� �α��� ����");
		}
		else
		{
			m_editStatusBar.SetWindowTextA("���� �α��� ����");
		}
	}
	else
	{
		m_editStatusBar.SetWindowTextA("HTS �������� ����");
	}

	//delete p_XingAPI;
}

LRESULT CAutoSearchStockDlg::OnLogin(WPARAM wParam, LPARAM lParam)
{
	LPCSTR pszCode = (LPCSTR)wParam;
	LPCSTR pszMsg = (LPCSTR)lParam;
	CString strMsg;
	CString cstAccount_Order;
	cstAccount_Order = "20063531601";
	strMsg.Format("[%s] %s", pszCode, pszMsg);
	int find_account = 0; 

	// wParam == 0000, login success
	if (atoi(pszCode) == 0)
	{
		// �α��� ����
		char szAccount[20];
		for (int i = 0; i<p_XingAPI->GetAccountListCount(); i++)
		{
			if (p_XingAPI->GetAccountList(i, szAccount, sizeof(szAccount)))
			{
				strMsg.Format("�������� %d : %s", i + 1, szAccount);
				m_editStockCount.SetWindowTextA(strMsg);
				
				if (cstAccount_Order.Compare(szAccount) == 0) // ������ ���� �߰ߵ�.
				{
					find_account = 1;
				}
			}
		}
		if (find_account == 0) // �Ÿſ� ����ϱ�� ������ ���°� ������ ���� �ƴ϶��, 
		{
			strMsg.Format("[�ֹ��Ұ� ����] : %s", cstAccount_Order);
			m_editStockCount.SetWindowTextA(strMsg);
		}
		else if (find_account == 1)
		{
			strMsg.Format("[�ֹ����� ����] : %s", cstAccount_Order);		
			m_editStockCount.SetWindowTextA(strMsg);
		}
	}
	else
	{
		m_editStatusBar.SetWindowTextA("�α��� ����");
	}
	return 0L;

}

LRESULT CAutoSearchStockDlg::OnDisConnect(WPARAM wParam, LPARAM lParam)
{
	OnBnClickedButton2Disconnect();
	return 0L;
}

void CAutoSearchStockDlg::OnBnClickedButton2Disconnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (p_XingAPI != NULL)
	{
		if (p_XingAPI->Logout(GetSafeHwnd()))
		{
			// Logout Success 
			p_XingAPI->Uninit();
		}
		delete p_XingAPI;
	}

	m_editStatusBar.SetWindowTextA("���� ����");
}

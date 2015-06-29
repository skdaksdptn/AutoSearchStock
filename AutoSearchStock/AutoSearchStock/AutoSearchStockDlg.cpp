
// AutoSearchStockDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "AutoSearchStock.h"
#include "AutoSearchStockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CAutoSearchStockDlg 대화 상자



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


// CAutoSearchStockDlg 메시지 처리기

BOOL CAutoSearchStockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	p_XingAPI = new IXingAPI;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAutoSearchStockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAutoSearchStockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Test Connection 
void CAutoSearchStockDlg::OnBnClickedButton1Connect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
				m_editStatusBar.SetWindowTextA("DLL 로딩실패");
				return; // 로딩실패 반환.
			}
		}
	}
	else
	{
		m_editStatusBar.SetWindowTextA("DLL 로딩성공");
	}

	// Connect Stock Server
	if (p_XingAPI->Connect(
				GetSafeHwnd(),
				"hts.etrade.co.kr",
				20001,
				WM_USER, -1, -1	))
	{
		// Success
		m_editStatusBar.SetWindowTextA("HTS 서버접속 성공");

		// User Login
		if (p_XingAPI->Login(
				GetSafeHwnd(),
				"ID",
				"PW",
				"PW2",
				0, true))
		{
			// Success
			m_editStatusBar.SetWindowTextA("유저 로그인 성공");
		}
		else
		{
			m_editStatusBar.SetWindowTextA("유저 로그인 실패");
		}
	}
	else
	{
		m_editStatusBar.SetWindowTextA("HTS 서버접속 실패");
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
		// 로그인 성공
		char szAccount[20];
		for (int i = 0; i<p_XingAPI->GetAccountListCount(); i++)
		{
			if (p_XingAPI->GetAccountList(i, szAccount, sizeof(szAccount)))
			{
				strMsg.Format("보유계좌 %d : %s", i + 1, szAccount);
				m_editStockCount.SetWindowTextA(strMsg);
				
				if (cstAccount_Order.Compare(szAccount) == 0) // 동일한 계좌 발견됨.
				{
					find_account = 1;
				}
			}
		}
		if (find_account == 0) // 매매에 사용하기로 지정된 계좌가 보유한 것이 아니라면, 
		{
			strMsg.Format("[주문불가 계좌] : %s", cstAccount_Order);
			m_editStockCount.SetWindowTextA(strMsg);
		}
		else if (find_account == 1)
		{
			strMsg.Format("[주문가능 계좌] : %s", cstAccount_Order);		
			m_editStockCount.SetWindowTextA(strMsg);
		}
	}
	else
	{
		m_editStatusBar.SetWindowTextA("로그인 실패");
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (p_XingAPI != NULL)
	{
		if (p_XingAPI->Logout(GetSafeHwnd()))
		{
			// Logout Success 
			p_XingAPI->Uninit();
		}
		delete p_XingAPI;
	}

	m_editStatusBar.SetWindowTextA("해제 성공");
}

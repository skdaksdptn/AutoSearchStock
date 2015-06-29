
// AutoSearchStockDlg.h : 헤더 파일
//

#pragma once

#include	"IXingAPI.h"
#include "afxwin.h"

// CAutoSearchStockDlg 대화 상자
class CAutoSearchStockDlg : public CDialogEx
{
// 생성입니다.
public:
	CAutoSearchStockDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_AUTOSEARCHSTOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	IXingAPI *p_XingAPI;


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	LRESULT	OnLogin(WPARAM wParam, LPARAM lParam);
	LRESULT OnDisConnect(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButton1Connect();
	// Status Bar
	CEdit m_editStatusBar;
	// 주식 계좌
	CEdit m_editStockCount;
	afx_msg void OnBnClickedButton2Disconnect();
};

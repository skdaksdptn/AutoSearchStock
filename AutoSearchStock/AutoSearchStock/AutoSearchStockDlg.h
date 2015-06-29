
// AutoSearchStockDlg.h : ��� ����
//

#pragma once

#include	"IXingAPI.h"
#include "afxwin.h"

// CAutoSearchStockDlg ��ȭ ����
class CAutoSearchStockDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CAutoSearchStockDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_AUTOSEARCHSTOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	IXingAPI *p_XingAPI;


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
	// �ֽ� ����
	CEdit m_editStockCount;
	afx_msg void OnBnClickedButton2Disconnect();
};

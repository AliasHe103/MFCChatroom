#pragma once
#include "afxdialogex.h"
#include "MFCChatroomCpp.h"

// CLOGIN 对话框

class CLOGIN : public CDialogEx
{
	DECLARE_DYNAMIC(CLOGIN)

public:
	CLOGIN(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLOGIN();

	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedLoginbt();
	CString name;
	void getinit();
};



// MFCChatroomCppDlg.h: 头文件
//

#pragma once
#include "zmq.hpp"
#include "CLOGIN.h"
// CMFCChatroomCppDlg 对话框
class CMFCChatroomCppDlg : public CDialogEx
{
// 构造
public:
	CMFCChatroomCppDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CString CTimeAndShow(CString msg) {// 重写
		CString str_show;//定义返回值
		CTime tm_now;//定义CTime获取时间，这个是MFC中的一个类
		//--------获取当前时间-----------------
		tm_now = CTime::GetCurrentTime();
		//-----------将时间与传进来的字符串进行拼接，其中时间以一定格式返回--------------
		str_show = tm_now.Format("%X");
		str_show += msg;
		return str_show;
	}
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATROOMCPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedConnectbutton();
//	CEdit m_Edit;
//	CEdit m_msg_list;
//	CString m_msg;
	afx_msg void OnCbnSelchangeCombo3();
	CComboBox m_msg;
//	CComboBox m_msg_list;
	afx_msg void OnBnClickedButton1();
	CString name;
	afx_msg void OnChangeNameedit();

	zmq::context_t context{ 1 };
	zmq::socket_t socket{ context, zmq::socket_type::req };
	bool ConnectStatus = false;
	CLOGIN login;
};

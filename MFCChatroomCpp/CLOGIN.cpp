// CLOGIN.cpp: 实现文件
//

#include "pch.h"
#include "MFCChatroomCpp.h"
#include "afxdialogex.h"
#include "CLOGIN.h"


// CLOGIN 对话框

IMPLEMENT_DYNAMIC(CLOGIN, CDialogEx)

CLOGIN::CLOGIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
{

}

CLOGIN::~CLOGIN()
{
}

void CLOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLOGIN, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLOGIN::OnBnClickedOk)
	ON_BN_CLICKED(IDC_LOGINBT, &CLOGIN::OnBnClickedLoginbt)
END_MESSAGE_MAP()


// CLOGIN 消息处理程序


void CLOGIN::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CLOGIN::OnBnClickedLoginbt()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(name);
	if (name.GetLength() <= 0) {
		MessageBox(_T("请输入昵称！"));
		return;
	}
	else if (IDOK == AfxMessageBox(_T("确定要修改昵称？"), MB_OKCANCEL)) {
		TCHAR str_path[100] = { 0 };
		CString str_file;
		GetCurrentDirectory(100, str_path);
		//将用户设置的昵称保存在本地配置文件，下次登录直接显示
		str_file.Format(L"%ls//userID.ini", str_path);
		WritePrivateProfileStringW(_T("CILENT"), _T("NAME"), name, str_file);
		EndDialog(0);
	}
}

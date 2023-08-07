
// MFCChatroomCppDlg.cpp: 实现文件

#include "pch.h"
#include "framework.h"
#include "MFCChatroomCpp.h"
#include "MFCChatroomCppDlg.h"
#include "afxdialogex.h"
#include <afxsock.h>

#include "zmq.hpp"
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatroomCppDlg 对话框



CMFCChatroomCppDlg::CMFCChatroomCppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATROOMCPP_DIALOG, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatroomCppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_PORT, m_Edit);

	DDX_Control(pDX, IDC_COMBO3, m_msg);
}

BEGIN_MESSAGE_MAP(CMFCChatroomCppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMFCChatroomCppDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCChatroomCppDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CONNECTBUTTON, &CMFCChatroomCppDlg::OnBnClickedConnectbutton)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMFCChatroomCppDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCChatroomCppDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_NAMEEDIT, &CMFCChatroomCppDlg::OnChangeNameedit)
END_MESSAGE_MAP()


// CMFCChatroomCppDlg 消息处理程序

BOOL CMFCChatroomCppDlg::OnInitDialog()
{
	ModifyStyle(0, WS_MINIMIZEBOX, TRUE);
	ModifyStyle(0, WS_POPUP, TRUE);
	ModifyStyle(0, WS_BORDER, TRUE);
	ModifyStyle(0, WS_SYSMENU, TRUE);
	ModifyStyle(0, WS_CAPTION, TRUE);
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	login.DoModal();
	WCHAR str_name[100];//定义保存名字的变量
	TCHAR str_path[100] = { 0 };//定义当前文件路径
	GetCurrentDirectory(100, str_path);//获取当前路径
	CString str_file;//定义文件名
	str_file.Format(L"%ls\\userID.ini", str_path);//拼接文件名和路径
	//从配置文件读取用户信息
	int ret = GetPrivateProfileString(_T("CILENT"), _T("NAME"), NULL , str_name, 100, str_file);
	if (ret > 0){//获取到信息则直接赋值给name，并将昵称显示在编辑框上
		name = str_name;
		GetDlgItem(IDC_NAMEEDIT)->SetWindowTextW(str_name);
	}
	else {//如果没有配置则显示空的昵称
		name = _T(" ");
		GetDlgItem(IDC_NAMEEDIT)->SetWindowTextW(name);
	}

	

	//创建连接
	//zmq::context_t context(1);
	//zmq::socket_t socket(context, ZMQ_REQ);//建立套接字
	////std::cout << "Connecting to hello world server..." << std::endl;//连接服务器
	//socket.connect("tcp://localhost:5555");
	//while (1) {
	//	char* send_str = new char;
	//	//std::cin >> send_str;
	//	//if (send_str == "end") break;
	//	s_send(socket, send_str);
	//	//std::cout << "Client Received: " << s_recv(socket) << std::endl;
	//	Sleep(1000);
	//}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatroomCppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatroomCppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatroomCppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatroomCppDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCChatroomCppDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_NAMEEDIT)->GetWindowTextW(name);
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
	}
}

//自定义类MySocket
class MySocket :public CAsyncSocket {
public:
	virtual ~MySocket() {};
	virtual void OnConnect(int n);
	virtual void OnReceive(int n);

};
MySocket* m_cilentSocket;
void CMFCChatroomCppDlg::OnBnClickedConnectbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	//定义两个保存串口和IP地址的变量
	
	//连接
	CString str_connect = CTimeAndShow(_T("正在连接... ..."));
	m_msg.AddString(str_connect);
	socket.connect("tcp://localhost:5555");
	Sleep(1000);
	ConnectStatus = true;
	str_connect = CTimeAndShow(_T("连接成功"));
	m_msg.AddString(str_connect);
	UpdateData(FALSE);
	//CString str_show = CTimeAndShow(_T("与服务器连接成功!"));
	//m_msg.AddString(str_show);
	//CMFCChatroomCppDlg* dlg = (CMFCChatroomCppDlg*)AfxGetApp()->GetMainWnd();//获取当前主窗口对象
	//CString str = dlg->CTimeAndShow(_T("与服务器连接成功!"));//str保存要上传的信息
	//dlg->m_msg.AddString(str);
	

	/*CString strPort, strIP;
	GetDlgItem(IDC_PORT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS1)->GetWindowText(strIP);
	USES_CONVERSION;
	char* szPort = (char*)T2A(strPort);
	char* szIP = (char*)T2A(strIP);
	int iPort = _ttoi(strPort);

	m_cilentSocket = new MySocket;
	m_cilentSocket->Create();
	m_cilentSocket->Connect(strIP, iPort);*/
}

void MySocket::OnConnect(int nErrorCode)
//connect成功连接后的回调函数
//相当于connect连接成功后返回的数据指令是这一整个函数
{
	CMFCChatroomCppDlg* dlg = (CMFCChatroomCppDlg*)AfxGetApp()->GetMainWnd();//获取当前主窗口对象
	CString str = dlg->CTimeAndShow(_T("与服务器连接成功!"));//str保存要上传的信息
	dlg->m_msg.AddString(str);
	CAsyncSocket::OnConnect(nErrorCode); //类内方法标准格式，可以忽略
}
void MySocket::OnReceive(int nErrorCode)
{

	CMFCChatroomCppDlg* dlg = (CMFCChatroomCppDlg*)AfxGetApp()->GetMainWnd();//获取窗口对象
	char recv_buff[1024] = { 0 }; // 定义字符串保存信息
	Receive(recv_buff, 1024, 0);  //从socket中接收信息
	CString str_show;
	CString str_msg;
	//str_msg保存我接受到的信息，str_show是将时间轴和信息拼接过后的显示内容
	str_msg += recv_buff;
	str_show = dlg->CTimeAndShow(str_msg);
	//对信息内容进行显示
	dlg->m_msg.AddString(str_show);
}
//重写完毕


void CMFCChatroomCppDlg::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCChatroomCppDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString send_buff = 0;
	CString send_all;
	if (ConnectStatus == false) {
		MessageBox(_T("消息发送失败，你还没有连接到服务器！"));
		return;
	}
	GetDlgItem(IDC_SENDEDIT)->GetWindowText(send_buff);
	std::string str = CW2A(send_buff);
	socket.send(zmq::buffer(str), zmq::send_flags::none);
	GetDlgItem(IDC_SENDEDIT)->SetWindowTextW(_T(""));
	zmq::message_t reply{};
	socket.recv(reply, zmq::recv_flags::none);
	std::string str_ret = reply.to_string();
	int ret = str_ret.compare(0,4,"RECV");
	if (ret != 0) {//如果ret不为0说明没有收到服务器的接收信号
		MessageBox(_T("消息发送失败，请检查与服务器的连接！"));
		return;
	}
	//如果服务器成功接受用户输入的消息，则展示在聊天室
	send_all = name + _T(":") + send_buff;
	CString str_show = CTimeAndShow(send_all);
	m_msg.AddString(str_show);
	UpdateData(FALSE);
}


void CMFCChatroomCppDlg::OnChangeNameedit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

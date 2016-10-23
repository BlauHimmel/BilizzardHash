
// 3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3.h"
#include "3Dlg.h"
#include "afxdialogex.h"
#include "FileGeneration.h"
#include <fstream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMy3Dlg 对话框



CMy3Dlg::CMy3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy3Dlg::IDD, pParent)
	, StringSize(0)
	, StringCount(0)
	, Key(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, StringSize);
	DDX_Text(pDX, IDC_EDIT3, StringCount);
	DDX_Text(pDX, IDC_EDIT4, Key);
}

BEGIN_MESSAGE_MAP(CMy3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy3Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy3Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMy3Dlg 消息处理程序

BOOL CMy3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy3Dlg::OnPaint()
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
HCURSOR CMy3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy3Dlg::OnBnClickedButton1()	//生成文件
{
	// TODO:  在此添加控件通知处理程序代码
	//UpdateData(true);
	//FILE* fStreamW = fopen("HashTestData.txt", "w");
	//FileGeneration(fStreamW, StringSize, StringCount);
	//fclose(fStreamW);
	//MessageBox(_T("已在程序根目录下成功生成测试数据文件！"), _T("提示"), MB_OK);
	//UpdateData(false);

	UpdateData(true);
	ofstream fStreamW("HashTestData.txt");
	FileGeneration(fStreamW, StringSize, StringCount);
	fStreamW.close();
	MessageBox(_T("已在程序根目录下成功生成测试数据文件！"), _T("提示"), MB_OK);
	UpdateData(false);
}


void CMy3Dlg::OnBnClickedButton2()	//搜索
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	int nLength = Key.GetLength();
	char* lpszKey = new char[nLength + 1];
	lpszKey[nLength] = '\0';
	for (int i = 0; i < nLength; i++)
	{
		lpszKey[i] = Key[i];
	}
	HashTable* pResult = Hash.GetFromHashTable(lpszKey, "APHash", "ELFHash", "JSHash");
	if (pResult != NULL)
	{
		MessageBox(_T("源文件中存在该关键字！"), _T("提示"), MB_OK);
	}
	else
	{
		MessageBox(_T("源文件中不存在该关键字！"), _T("提示"), MB_OK);
	}
	UpdateData(false);
}


void CMy3Dlg::OnBnClickedButton4()	//载入文件
{
	// TODO:  在此添加控件通知处理程序代码
	//UpdateData(true);
	//CFileDialog dlg(TRUE);
	//if (dlg.DoModal()!=IDOK)
	//	return;
	//CString cstrPath = dlg.GetPathName();
	//FILE* fStreamR = _tfopen(cstrPath, _T("r"));
	//fread(&nSize, sizeof(int), 1, fStreamR);
	//fseek(fStreamR, 2, SEEK_CUR);
	//fread(&nCount, sizeof(int), 1, fStreamR);
	//fseek(fStreamR, 2, SEEK_CUR);
	//char* lpszBuffer = new char[nSize + 1];
	//int nNonRepeatingCountTemp = 0;
	//while (fread(lpszBuffer, sizeof(char)*(nSize + 1), 1, fStreamR))
	//{
	//	fseek(fStreamR, 2, SEEK_CUR);
	//	if (Hash.InsertIntoHashTable(lpszBuffer, "APHash", "ELFHash", "JSHash"))
	//	{
	//		nNonRepeatingCountTemp++;
	//	}
	//}
	//nNonRepeatingCount = nNonRepeatingCountTemp;
	//fclose(fStreamR);
	//MessageBox(_T("文件载入成功！"), _T("提示"), MB_OK);
	//UpdateData(false);

	UpdateData(true);
	nCount = 0;
	CFileDialog dlg(TRUE);
	if (dlg.DoModal()!=IDOK)
		return;
	CString cstrPath = dlg.GetPathName();
	ifstream FIN(cstrPath);

	char* lpszBuffer = new char[MAX_KEY_LENGTH];
	int nNonRepeatingCountTemp = 0;

	while (!FIN.eof())
	{
		FIN >> lpszBuffer;
		nCount++;
		if (Hash.InsertIntoHashTable(lpszBuffer, "APHash", "ELFHash", "JSHash"))
		{
			nNonRepeatingCountTemp++;
		}
	}
	nNonRepeatingCount = nNonRepeatingCountTemp;
	
	FIN.close();

	MessageBox(_T("文件载入成功！"), _T("提示"), MB_OK);
	UpdateData(false);
}


void CMy3Dlg::OnBnClickedButton3()	//输出统计信息
{
	// TODO:  在此添加控件通知处理程序代码
	FILE* fStreamW = fopen("HashTableInfo.txt", "w");
	fprintf(fStreamW, "哈希表桶的个数 ");
	fprintf(fStreamW, "%u\n", Hash.GetHashTableLength());
	fprintf(fStreamW, "建立哈希表的字符串的个数 ");
	fprintf(fStreamW, "%d\n", nCount);
	fprintf(fStreamW, "建立哈希表的不重复的元素个数 ");
	fprintf(fStreamW, "%d\n", nNonRepeatingCount);
	fprintf(fStreamW, "冲突的桶的个数 ");
	fprintf(fStreamW, "%d\n", Hash.GetSumOfCollisionalBuckets());
	fprintf(fStreamW, "最长的链的长度 ");
	fprintf(fStreamW, "%d\n", Hash.GetLongestLengthOfLinkList());
	fprintf(fStreamW, "链表的平均长度 ");
	fprintf(fStreamW, "%lf\n", Hash.GetAverageLengthOfLinkList());
	fprintf(fStreamW, "哈希表桶的使用率 ");
	fprintf(fStreamW, "%lf\n", Hash.GetUtilizationRateOfBuckets());
	fclose(fStreamW);
	MessageBox(_T("已在程序根目录下成功生成统计信息文件！"), _T("提示"), MB_OK);
}

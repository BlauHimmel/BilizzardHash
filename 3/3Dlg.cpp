
// 3Dlg.cpp : ʵ���ļ�
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


// CMy3Dlg �Ի���



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


// CMy3Dlg ��Ϣ�������

BOOL CMy3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy3Dlg::OnPaint()
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
HCURSOR CMy3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy3Dlg::OnBnClickedButton1()	//�����ļ�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//UpdateData(true);
	//FILE* fStreamW = fopen("HashTestData.txt", "w");
	//FileGeneration(fStreamW, StringSize, StringCount);
	//fclose(fStreamW);
	//MessageBox(_T("���ڳ����Ŀ¼�³ɹ����ɲ��������ļ���"), _T("��ʾ"), MB_OK);
	//UpdateData(false);

	UpdateData(true);
	ofstream fStreamW("HashTestData.txt");
	FileGeneration(fStreamW, StringSize, StringCount);
	fStreamW.close();
	MessageBox(_T("���ڳ����Ŀ¼�³ɹ����ɲ��������ļ���"), _T("��ʾ"), MB_OK);
	UpdateData(false);
}


void CMy3Dlg::OnBnClickedButton2()	//����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(_T("Դ�ļ��д��ڸùؼ��֣�"), _T("��ʾ"), MB_OK);
	}
	else
	{
		MessageBox(_T("Դ�ļ��в����ڸùؼ��֣�"), _T("��ʾ"), MB_OK);
	}
	UpdateData(false);
}


void CMy3Dlg::OnBnClickedButton4()	//�����ļ�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	//MessageBox(_T("�ļ�����ɹ���"), _T("��ʾ"), MB_OK);
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

	MessageBox(_T("�ļ�����ɹ���"), _T("��ʾ"), MB_OK);
	UpdateData(false);
}


void CMy3Dlg::OnBnClickedButton3()	//���ͳ����Ϣ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	FILE* fStreamW = fopen("HashTableInfo.txt", "w");
	fprintf(fStreamW, "��ϣ��Ͱ�ĸ��� ");
	fprintf(fStreamW, "%u\n", Hash.GetHashTableLength());
	fprintf(fStreamW, "������ϣ����ַ����ĸ��� ");
	fprintf(fStreamW, "%d\n", nCount);
	fprintf(fStreamW, "������ϣ��Ĳ��ظ���Ԫ�ظ��� ");
	fprintf(fStreamW, "%d\n", nNonRepeatingCount);
	fprintf(fStreamW, "��ͻ��Ͱ�ĸ��� ");
	fprintf(fStreamW, "%d\n", Hash.GetSumOfCollisionalBuckets());
	fprintf(fStreamW, "������ĳ��� ");
	fprintf(fStreamW, "%d\n", Hash.GetLongestLengthOfLinkList());
	fprintf(fStreamW, "�����ƽ������ ");
	fprintf(fStreamW, "%lf\n", Hash.GetAverageLengthOfLinkList());
	fprintf(fStreamW, "��ϣ��Ͱ��ʹ���� ");
	fprintf(fStreamW, "%lf\n", Hash.GetUtilizationRateOfBuckets());
	fclose(fStreamW);
	MessageBox(_T("���ڳ����Ŀ¼�³ɹ�����ͳ����Ϣ�ļ���"), _T("��ʾ"), MB_OK);
}

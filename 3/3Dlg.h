
// 3Dlg.h : ͷ�ļ�
//

#pragma once

// CMy3Dlg �Ի���
class CMy3Dlg : public CDialogEx
{
// ����
public:
	CMy3Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	// �ַ�������
	int StringSize;
	// �ַ�������
	int StringCount;
	// �ؼ���
	CString Key;
	int nSize;
	int nCount;
	int nNonRepeatingCount;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};

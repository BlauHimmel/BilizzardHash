
// 3Dlg.h : 头文件
//

#pragma once

// CMy3Dlg 对话框
class CMy3Dlg : public CDialogEx
{
// 构造
public:
	CMy3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY3_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	// 字符串长度
	int StringSize;
	// 字符串个数
	int StringCount;
	// 关键字
	CString Key;
	int nSize;
	int nCount;
	int nNonRepeatingCount;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};

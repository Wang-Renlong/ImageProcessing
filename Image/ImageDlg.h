
// ImageDlg.h : 头文件
//

#pragma once
#include "base\bmp.h"
#include "base\pixel.h"

#include "include\magic.h"
#include "include\filter.h"
#include "include\q_and_qu.h"
#include "include\stastics.h"
#include "include\img.h"
#include "include\window.h"


// CMainDlg 对话框
class CMainDlg : public CDialogEx
{
// 构造
public:
	CMainDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IMAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	int ShowPixel(Pixel* pixel);//在预览区显示
	int ShowPixelDownLeft(Pixel* pixel);//在预览区左下角显示
	double CStringToDouble(CString str);//CString转double
	int CStringToInt(CString str);//CString转int

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	CEdit *editFile;
	CEdit *edit31;
	CEdit *edit41, *edit42, *edit43, *edit44;
	CEdit *edit51;
	CEdit *edit61, *edit62;
	CWnd *picCtl, *colorCtl;
	CBitmap memBitMap;
	CDC memDC;
	CRect picWndRect, colorRect;

	Pixel src, dst, out1, grap;
	char srcIndex, hasGrap;
public:
	afx_msg void OnBnClickedBtnabout();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedButtonload();
	afx_msg void OnBnClickedBtnChnR();
	afx_msg void OnBnClickedBtnChnG();
	afx_msg void OnBnClickedBtnChnB();
	afx_msg void OnBnClickedBtnGray();
	afx_msg void OnBnClickedBtnAnti();
	afx_msg void OnBnClickedBtn21();
	afx_msg void OnBnClickedBtn22();
	afx_msg void OnBnClickedBtn31();
	afx_msg void OnBnClickedBtn32();
	afx_msg void OnBnClickedBtn41();
	afx_msg void OnBnClickedBtn41b();
	afx_msg void OnBnClickedBtn42();
	afx_msg void OnBnClickedBtn43();
	afx_msg void OnBnClickedBtn44();
	afx_msg void OnBnClickedBtn45();
	afx_msg void OnBnClickedBtn51();
	afx_msg void OnBnClickedBtn52();
	afx_msg void OnBnClickedBtn53();
	afx_msg void OnBnClickedBtn61();
	afx_msg void OnBnClickedBtn62();
	afx_msg void OnBnClickedBtn63();
	afx_msg void OnBnClickedBtn71();
	afx_msg void OnBnClickedBtn72();
	afx_msg void OnBnClickedBtn73();
	afx_msg void OnBnClickedBtn74();
	afx_msg void OnBnClickedBtn81();
	afx_msg void OnBnClickedBtn91();
	afx_msg void OnBnClickedBtn92();
	afx_msg void OnBnClickedBtnsave();
};

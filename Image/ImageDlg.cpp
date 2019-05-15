
// ImageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image.h"
#include "ImageDlg.h"
#include "afxdialogex.h"

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


// CMainDlg �Ի���



CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

int CMainDlg::ShowPixel(Pixel* pixel)
{
	int i, j;
	int width, height;
	CRect ctlRect;
	picCtl->GetClientRect(&ctlRect);
	width = pixel->Width();
	height = pixel->Height();
	CDC *cdc = picCtl->GetDC();
	//cdc->SetBkColor(RGB(0, 0, 0));
	//memDC.SetBkColor(RGB(0, 0, 0));
	memDC.FillSolidRect(0, 0, ctlRect.Width(), ctlRect.Height(), RGB(0, 0, 0));
	//m = ctlRect.Height() - height;
	for (i = 0; i < height && i < ctlRect.Height(); i++)
	{
		for (j = 0; j < width && j < ctlRect.Width(); j++)
		{
			memDC.SetPixel(j, i, 
				RGB((*pixel)[i*width + j].r, (*pixel)[i*width + j].g, (*pixel)[i*width + j].b));
			//cdc->SetPixel(j, i,
			//		RGB((*pixel)[i*width + j].r, (*pixel)[i*width + j].g, (*pixel)[i*width + j].b));
		}
	}
	cdc->BitBlt(0, 0, ctlRect.Width(), ctlRect.Height(), &memDC, 0, 0, SRCCOPY);
	ReleaseDC(cdc);
	return 0;
}

int CMainDlg::ShowPixelDownLeft(Pixel* pixel)
{
	int i, j, m;
	int width, height;
	CRect ctlRect;
	picCtl->GetClientRect(&ctlRect);
	width = pixel->Width();
	height = pixel->Height();
	CDC *cdc = picCtl->GetDC();
	cdc->SetBkColor(RGB(0, 0, 0));
	m = ctlRect.Height() - height;
	//cdc->Rectangle(0, m - 1, width, height+m);
	for (i = 0; i < height && i < ctlRect.Height(); i++)
	{
		for (j = 0; j < width && j < ctlRect.Width(); j++)
		{
			cdc->SetPixel(j, m + i,
				RGB((*pixel)[i*width + j].r, (*pixel)[i*width + j].g, (*pixel)[i*width + j].b));
		}
	}
	return 0;
}

double CMainDlg::CStringToDouble(CString str)
{
	int strLen, i, dot, k;
	double result, dk;
	strLen = str.GetLength();
	//scan
	k = 0;
	dot = strLen;
	if (strLen <= 0)
	{
		return 0.0;
	}
	for (i = strLen - 1; i >= 0; i--)
	{
		if (str[i] == '.')
		{
			k++;
			if (k <= 1)
				dot = i;
		}
		if ((str[i] < '0' || str[i]>'9') && str[i] != '.')
		{
			return 0.0;
		}
		if (k > 1)
		{
			return 0.0;
		}
	}
	result = 0;
	k = 1;
	for (i = dot - 1; i >= 0; i--)
	{
		result += (str[i] - '0') * k;
		k = k * 10;
	}
	dk = 0.1;
	for (i = dot + 1; i < strLen; i++)
	{
		result += (str[i] - '0') * dk;
		dk = dk * 0.1;
	}
	return result;
}

int CMainDlg::CStringToInt(CString str)
{
	int result, strLen, i, k;
	strLen = str.GetLength();
	if (strLen <= 0)
		return 0;
	result = 0;
	k = 1;
	for (i = strLen - 1; i > 0; i--)
	{
		if (str[i] < '0' || str[i] > '9')
			return 0;
		result += (str[i] - '0') * k;
		k = k * 10;
	}
	if (str[0] == '-')
		result = 0 - result;
	else
		result += (str[0] - '0') * k;
	return result;
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNABOUT, &CMainDlg::OnBnClickedBtnabout)
	ON_BN_CLICKED(IDC_BUTTONLOAD, &CMainDlg::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC1_BTN_CHN_R, &CMainDlg::OnBnClickedBtnChnR)
	ON_BN_CLICKED(IDC1_BTN_CHN_G, &CMainDlg::OnBnClickedBtnChnG)
	ON_BN_CLICKED(IDC1_BTN_CHN_B, &CMainDlg::OnBnClickedBtnChnB)
	ON_BN_CLICKED(IDC1_BTN_GRAY, &CMainDlg::OnBnClickedBtnGray)
	ON_BN_CLICKED(IDC1_BTN_ANTI, &CMainDlg::OnBnClickedBtnAnti)
	ON_BN_CLICKED(IDC2_BTN1, &CMainDlg::OnBnClickedBtn21)
	ON_BN_CLICKED(IDC2_BTN2, &CMainDlg::OnBnClickedBtn22)
	ON_BN_CLICKED(IDC3_BTN1, &CMainDlg::OnBnClickedBtn31)
	ON_BN_CLICKED(IDC3_BTN2, &CMainDlg::OnBnClickedBtn32)
	ON_BN_CLICKED(IDC4_BTN1, &CMainDlg::OnBnClickedBtn41)
	ON_BN_CLICKED(IDC4_BTN1B, &CMainDlg::OnBnClickedBtn41b)
	ON_BN_CLICKED(IDC4_BTN2, &CMainDlg::OnBnClickedBtn42)
	ON_BN_CLICKED(IDC4_BTN3, &CMainDlg::OnBnClickedBtn43)
	ON_BN_CLICKED(IDC4_BTN4, &CMainDlg::OnBnClickedBtn44)
	ON_BN_CLICKED(IDC4_BTN5, &CMainDlg::OnBnClickedBtn45)
	ON_BN_CLICKED(IDC5_BTN1, &CMainDlg::OnBnClickedBtn51)
	ON_BN_CLICKED(IDC5_BTN2, &CMainDlg::OnBnClickedBtn52)
	ON_BN_CLICKED(IDC5_BTN3, &CMainDlg::OnBnClickedBtn53)
	ON_BN_CLICKED(IDC6_BTN1, &CMainDlg::OnBnClickedBtn61)
	ON_BN_CLICKED(IDC6_BTN2, &CMainDlg::OnBnClickedBtn62)
	ON_BN_CLICKED(IDC6_BTN3, &CMainDlg::OnBnClickedBtn63)
	ON_BN_CLICKED(IDC7_BTN1, &CMainDlg::OnBnClickedBtn71)
	ON_BN_CLICKED(IDC7_BTN2, &CMainDlg::OnBnClickedBtn72)
	ON_BN_CLICKED(IDC7_BTN3, &CMainDlg::OnBnClickedBtn73)
	ON_BN_CLICKED(IDC7_BTN4, &CMainDlg::OnBnClickedBtn74)
	ON_BN_CLICKED(IDC8_BTN1, &CMainDlg::OnBnClickedBtn81)
	ON_BN_CLICKED(IDC9_BTN1, &CMainDlg::OnBnClickedBtn91)
	ON_BN_CLICKED(IDC9_BTN2, &CMainDlg::OnBnClickedBtn92)
	ON_BN_CLICKED(IDC_OPEN, &CMainDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_BTNSAVE, &CMainDlg::OnBnClickedBtnsave)
END_MESSAGE_MAP()


// CMainDlg ��Ϣ�������

BOOL CMainDlg::OnInitDialog()
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
	//��ȡ�ؼ�
	editFile = (CEdit*)GetDlgItem(IDC_EDIT1);
	edit31 = (CEdit*)GetDlgItem(IDC3_EDIT1);
	edit41 = (CEdit*)GetDlgItem(IDC4_EDIT1);
	edit42 = (CEdit*)GetDlgItem(IDC4_EDIT2);
	edit43 = (CEdit*)GetDlgItem(IDC4_EDIT3);
	edit44 = (CEdit*)GetDlgItem(IDC4_EDIT4);
	edit51 = (CEdit*)GetDlgItem(IDC5_EDIT1);
	edit61 = (CEdit*)GetDlgItem(IDC6_EDIT1);
	edit62 = (CEdit*)GetDlgItem(IDC6_EDIT2);
	picCtl = (CWnd*)GetDlgItem(IDC_STATIC);
	colorCtl = (CWnd*)GetDlgItem(IDC_COLOR);
	
	//��������ͼƬ����
	CRect picRect;
	CDC *cdc;
	picCtl->GetClientRect(picRect);
	picCtl->GetWindowRect(picWndRect);
	ScreenToClient(&picWndRect);
	colorCtl->GetClientRect(&colorRect);
	TRACE("picRect:(%d %d %d %d)\n", picRect.left, picRect.top, picRect.right, picRect.bottom);
	TRACE("picWndRect:(%d %d %d %d)\n", picWndRect.left, picWndRect.top, picWndRect.right, picWndRect.bottom);
	cdc = picCtl->GetDC();
	memBitMap.CreateCompatibleBitmap(cdc, picRect.Width(), picRect.Height());
	memDC.CreateCompatibleDC(cdc);
	memDC.SelectObject(&memBitMap);
	ReleaseDC(cdc);
	//��ʼ����־λ
	srcIndex = 0;
	hasGrap = 0;
	//�����ʾ��Ϣ
	SetDlgItemText(IDC_TEXTOUT, TEXT("δ����ͼ��!"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMainDlg::OnPaint()
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
	{   //ˢ��Ԥ��������
		picCtl->GetWindowRect(picWndRect);
		ScreenToClient(&picWndRect);
		//ˢ��Ԥ������ʾ
		if (srcIndex == 1)
			ShowPixel(&src);
		else if (srcIndex == 2)
			ShowPixel(&dst);
		else if (srcIndex == 3)
			ShowPixel(&out1);
		//��ʾֱ��ͼ
		if (hasGrap)
			ShowPixelDownLeft(&grap);
		CDialogEx::OnPaint();
	}
}


HBRUSH CMainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//������ʾ��������ɫ
	if (pWnd->GetDlgCtrlID() == IDC_TEXTOUT)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	static COLORREF color;
	static char text[28];
	// ��Color PictureControl����ɫ��Color Static������
	if (point.x > picWndRect.left && point.x < picWndRect.right &&
		point.y > picWndRect.top && point.y < picWndRect.bottom)
	{
		color = memDC.GetPixel(point.x - picWndRect.left, point.y - picWndRect.top);
		CDC *dc = colorCtl->GetWindowDC();
		//24��30��color pictureControl �ؼ��ߴ�
		dc->FillSolidRect(0, 0, colorRect.Width(), colorRect.Height(), color);
		sprintf_s(text, sizeof(text), "RGB(%3d, %3d, %3d)", (int)GetRValue(color), (int)GetGValue(color), (int)GetBValue(color));
		SetDlgItemText(IDC_COLORTEXT, CString(text));
		ReleaseDC(dc);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CMainDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	static char cx[8], cy[8];
	// ������ҪX Y��������������
	if (point.x >= picWndRect.left && point.x < picWndRect.right &&
		point.y >= picWndRect.top && point.y < picWndRect.bottom)
	{
		sprintf_s(cx, sizeof(cx), "%d", point.x - picWndRect.left);
		sprintf_s(cy, sizeof(cy), "%d", point.y - picWndRect.top);
		CString sx(cx);
		CString sy(cy);
		edit42->SetWindowTextW(sx);
		edit43->SetWindowTextW(sy);
		edit61->SetWindowTextW(sx);
		edit62->SetWindowTextW(sy);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMainDlg::OnBnClickedBtnabout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CMainDlg::OnBnClickedOpen()
{
	// TODO:  �ڴ���Ӵ��ļ�����
	const TCHAR *szFilter = TEXT("λͼ�ļ�(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||");
	CString filePath;
	CFileDialog fileDlg(TRUE, TEXT("bmp"), NULL, 0, szFilter, this);
	if (fileDlg.DoModal() == IDOK)
	{
		filePath = fileDlg.GetPathName();
		SetDlgItemTextW(IDC_EDIT1, filePath);
	}
}

void CMainDlg::OnBnClickedButtonload()
{
	// TODO:  �ڴ����Loadimage����
	Bmp bmp;
	CString str;
	char fileName[1024];
	int size, i;
	//�����ļ���
	editFile->GetWindowTextW(str);
	size = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	if (size <= 1 || size >= 1024)
	{
		MessageBox(TEXT("�ļ���������δ��д"));
		return;
	}
	WideCharToMultiByte(CP_ACP, 0, str, -1, fileName, size, NULL, NULL);
	TRACE("fileName=%s\n", fileName);
	size--;
	for (i = 0; i < size; i++)
	{
		if (fileName[i] == '\\')
			fileName[i] = '/';
		if (fileName[i] == '*' || fileName[i] == '?' || fileName[i] == '<' ||
			fileName[i] == '>' || fileName[i] == '|' || fileName[i] == '"')
		{
			MessageBox(TEXT("�Ƿ��ļ���"));
			return;
		}
	}
	//���ز���ʾ
	bmp.LoadBitMap(fileName, &src);
	ShowPixel(&src);
	srcIndex = 1;
	hasGrap = 0;
	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}

void CMainDlg::OnBnClickedBtnChnR()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ������ȡRͨ������
	if (!(src.Width() && src.Height()))
		return;
	img::copyRedChannel(&src, &dst);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtnChnG()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ������ȡGͨ������
	if (!(src.Width() && src.Height()))
		return;
	img::copyGreenChannel(&src, &dst);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtnChnB()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ������ȡBͨ������
	if (!(src.Width() && src.Height()))
		return;
	img::copyBlueChannel(&src, &dst);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtnGray()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ���ӻҶȻ�����
	if (!(src.Width() && src.Height()))
		return;
	//img::toGray(&src, &dst);
	src.ToGray();
	ShowPixel(&src);
	srcIndex = 1;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtnAnti()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ���ӻҶ�ͼ��ɫ����
	if (!(src.Width() && src.Height()))
		return;
	img::AntiColor(&src, &dst);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn21()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����ֱ��ͼ����
	if (!(src.Width() && src.Height()))
		return;
	stastics::countGray(&src, &grap);
	ShowPixel(&src);
	ShowPixelDownLeft(&grap);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn22()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����ֱ��ͼ���⻯����
	if (!(src.Width() && src.Height()))
		return;
	img::equalization(&src, &dst);
	stastics::countGray(&dst, &grap);
	ShowPixel(&dst);
	ShowPixelDownLeft(&grap);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn31()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ���Ӿ�ֵ�˲�����
	CString str;
	int size;
	edit31->GetWindowTextW(str);
	size = CStringToInt(str);
	//TRACE("str=%s, size=%d\n", str, size);
	if (!(src.Width() && src.Height()) || size <= 0)
	{
		SetDlgItemText(IDC_TEXTOUT, TEXT("��������ȷ"));
		return;
	}
	Window wnd(size, size, 1);
	int len = size*size;
	int *knl = wnd.Kernel();
	for (int i = 0; i < len; i++)
		knl[i] = 1;
	filter::avg(&src, &dst, wnd);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn32()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ������ֵ�˲�����
	CString str;
	int size;
	edit31->GetWindowTextW(str);
	size = CStringToInt(str);
	//TRACE("str=%s, size=%d\n", str, size);
	if (!(src.Width() && src.Height()) || size <= 0)
	{
		SetDlgItemText(IDC_TEXTOUT, TEXT("��������ȷ"));
		return;
	}
	Window wnd(size, size, 0);
	filter::midGRAY(&src, &dst, wnd);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}

void CMainDlg::OnBnClickedBtn41()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����ͼ�����Ŵ���
	CString str;
	double rate;
	edit41->GetWindowTextW(str);
	rate = CStringToDouble(str);
	TRACE("str=%s, rate=%lf\n", str, rate);
	if (!(src.Width() && src.Height()) || rate <= 0.01)
	{
		SetDlgItemText(IDC_TEXTOUT, TEXT("��������ȷ"));
		return;
	}
	magic::reSize_Upper(&src, &dst, src.Width()*rate, src.Height()*rate);
	ShowPixel(&dst);
	srcIndex = 2;
	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}

void CMainDlg::OnBnClickedBtn41b()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����ͼ���ֵ���Ŵ���
	CString str;
	double rate;
	edit41->GetWindowTextW(str);
	rate = CStringToDouble(str);
	TRACE("str=%s, rate=%lf\n", str, rate);
	if (!(src.Width() && src.Height()) || rate <= 0.01)
	{
		SetDlgItemText(IDC_TEXTOUT, TEXT("��������ȷ"));
		return;
	}
	magic::reSize_quadratic_linear(&src, &dst, src.Width()*rate, src.Height()*rate);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}

void CMainDlg::OnBnClickedBtn42()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����ͼ��ƽ�ƴ���
	CString strX, strY;
	int x, y, fx, fy;
	unsigned int w, h;
	edit42->GetWindowTextW(strX);
	edit43->GetWindowTextW(strY);
	x = CStringToInt(strX);
	y = CStringToInt(strY);
	//TRACE("strX=%s, stry=%s, x=%d, y=%d\n", strX, strY, x, y);
	if (!(src.Width() && src.Height()) || x >= src.Width() || y >= src.Height())
	{
		SetDlgItemText(IDC_TEXTOUT, TEXT("��������ȷ"));
		return;
	}
	fx = 0; 
	fy = 0;
	w = src.Width() - x;
	h = src.Height() - y;
	if (x < 0)
	{
		fx = 0 - x;
		x = 0;
		w = src.Width() - fx;
	}
	if (y < 0)
	{
		fy = 0 - y;
		y = 0;
		h = src.Height() - fy;
	}
	magic::moveTo(&src, &dst, fx, fy, x, y, w, h);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn43()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����X�������
	magic::imageX(&src, &dst);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn44()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����Y�������
	magic::imageY(&src, &dst);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn45()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ������ת����
	CString str;
	int si;
	double sipi;
	edit44->GetWindowTextW(str);
	si = CStringToInt(str);
	if (!(src.Width() && src.Height()) || (si < 0 || si > 360))
	{
		SetDlgItemText(IDC_TEXTOUT, TEXT("��������ȷ"));
		return;
	}
	//TRACE("str=%s, si=%d\n", str, si);
	sipi = 3.14159f*si / 180;
	magic::rotateImgAdvanced(&src, &dst, src.Width() / 2, src.Height() / 2, sin(sipi), cos(sipi));
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn51()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ������ֵ�ָ����
	CString str;
	int t;
	edit51->GetWindowTextW(str);
	t = CStringToInt(str);
	//TRACE("str=%s, t=%d\n", str, t);
	if (!(src.Width() && src.Height()) || t < 0 || t > 255)
	{
		SetDlgItemText(IDC_TEXTOUT, TEXT("��������ȷ"));
		return;
	}
	img::divide(&src, &dst, t, t);
	stastics::countGrayWinthT(&src, &grap, t, -1);
	ShowPixel(&dst);
	ShowPixelDownLeft(&grap);
	//hasGrap = 1;
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn52()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ���ӵ�����ֵ����
	CString str;
	char out[6];
	int t;
	edit51->GetWindowTextW(str);
	t = CStringToInt(str);
	//TRACE("str=%s, t=%d\n", str, t);
	if (!(src.Width() && src.Height()) || t < 0 || t > 255)
	{
		SetDlgItemText(IDC_TEXTOUT, TEXT("��������ȷ"));
		return;
	}
	t = img::t_devide_iterative(&src, t % 256, 2);
	sprintf_s(out,6, "%d", t);
	SetDlgItemText(IDC5_EDIT1, CString(out));

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn53()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����OTSU����
	char out[6];
	int t = img::t_devide_otsu(&src);
	sprintf_s(out, 6, "%d", t);
	SetDlgItemText(IDC5_EDIT1, CString(out));

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn61()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ�������ӵ���������
	CString strX, strY;
	int x, y;
	edit61->GetWindowTextW(strX);
	edit62->GetWindowTextW(strY);
	x = CStringToInt(strX);
	y = CStringToInt(strY);
	//TRACE("strX=%s, stry=%s, x=%d, y=%d\n", strX, strY, x, y);
	if (!(src.Width() && src.Height()) || x < 0 || x >= src.Width() || y < 0 || y >= src.Height())
	{
		SetDlgItemText(IDC_TEXTOUT, TEXT("��������ȷ"));
		return;
	}
	img::devide_seed(&src, &dst, x, y, 10);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn62()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ�����Ĳ����ָ����
	if (!(src.Width() && src.Height()))
	{
		SetDlgItemText(IDC_TEXTOUT, TEXT("��������ȷ"));
		return;
	}
	img::QandQU qaqu;
	PixelRGBA color = { 0, 0, 255, 0 };
	img::devide_nonseed(&src, &dst, &out1, 8, 5, qaqu);
	magic::paint(&src, &out1, &out1, color, 0);
	ShowPixel(&out1);
	srcIndex = 3;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn63()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ�����Ĳ����ϲ�����
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn71()
{
	static boolean count = false;
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����prewitt����
	if (count == false)
		filter::edge_detection(&src, &dst, Window::GetPrewittWindow(WINDOW_HORIZONTAL));
	else
		filter::edge_detection(&src, &dst, Window::GetPrewittWindow(WINDOW_VERTICAL));
	count = !count;
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn72()
{
	static boolean count = false;
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����Sobel����
	if (count == false)
		filter::edge_detection(&src, &dst, Window::GetSobelWindow(WINDOW_HORIZONTAL));
	else
		filter::edge_detection(&src, &dst, Window::GetSobelWindow(WINDOW_VERTICAL));
	count = !count;
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn73()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����LoG����
	filter::edge_detection(&src, &dst, Window::GetLoGWindow());
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn74()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����Canny����
	filter::avg(&src, &out1, Window::GetGaussianWindow(5, 50));
	filter::edge_detection_canny(&out1, &dst, 10, 30);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn81()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����Houghֱ�ߴ���
	img::hough_line(&src, &dst, 100, 66);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn91()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ������ͨ���Ǵ���
	img::mark_sequential(&src, &dst, 30);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}


void CMainDlg::OnBnClickedBtn92()
{
	SetDlgItemText(IDC_TEXTOUT, TEXT("������..."));
	// TODO:  �ڴ����������ȡ����
	img::contour_extraction(&src, &dst, 255);
	ShowPixel(&dst);
	srcIndex = 2;

	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}

void CMainDlg::OnBnClickedBtnsave()
{
	// TODO:  �ڴ���ӱ������
	//���Ϊ�Ի���
	const TCHAR *szFilter = TEXT("λͼ�ļ�(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||");
	int size;
	char fileName[1024];
	CString filePath;
	Bmp bmp;
	CFileDialog fileDlg(FALSE, TEXT("bmp"), NULL, 0, szFilter, this);
	if (fileDlg.DoModal() != IDOK)
	{
		return;
	}
	filePath = fileDlg.GetPathName();
	size = WideCharToMultiByte(CP_ACP, 0, filePath, -1, NULL, 0, NULL, NULL);
	if (size <= 1 || size >= 1024)
	{
		MessageBox(TEXT("�ļ���������δ��д"));
		return;
	}
	WideCharToMultiByte(CP_ACP, 0, filePath, -1, fileName, size, NULL, NULL);
	//SetDlgItemTextW(IDC_EDIT1, filePath);
	//�洢
	SetDlgItemText(IDC_TEXTOUT, TEXT("�洢��..."));
	switch (srcIndex)
	{
	case 1:
	{
			  bmp.SaveBitMap(fileName, &src);
			  break;
	}
	case 2:
	{
			  bmp.SaveBitMap(fileName, &dst);
			  break;
	}
	case 3:
	{
			  bmp.SaveBitMap(fileName, &out1);
			  break;
	}
	default:
		break;
	}
	SetDlgItemText(IDC_TEXTOUT, TEXT("����"));
}






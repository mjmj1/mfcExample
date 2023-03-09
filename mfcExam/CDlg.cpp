// CDlg.cpp: 구현 파일
//

#include "pch.h"
#include "mfcExam.h"
#include "afxdialogex.h"
#include "CDlg.h"
#include <iostream>
using namespace std;


// CDlg 대화 상자

IMPLEMENT_DYNAMIC(CDlg, CDialogEx)

CDlg::CDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlg, pParent)
{
	m_pParent = pParent;
}

CDlg::~CDlg()
{
}

void CDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CDlg::InitImage()
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}

void CDlg::drawData(int radius)
{
	cout << radius << endl;
	int nStartX = m_image.GetWidth() % rand();
	int nStartY = m_image.GetHeight() % rand();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, m_image.GetWidth() * m_image.GetHeight());

	CClientDC dc(this);
	dc.Ellipse(nStartX, nStartY, nStartX + radius, nStartY + radius);
}

BOOL CDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	MoveWindow(0, 0, 640, 480);
	InitImage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_image)
		m_image.Draw(dc, 0, 0);
}

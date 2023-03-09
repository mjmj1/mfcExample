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

void CDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
	Invalidate();
}

bool CDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius)
	{
		bRet = true;
	}

	return bRet;
}

void CDlg::drawData(CDC* pDC)
{
	CRect rect(m_nStartX, m_nStartY, m_nStartX + m_nRadius * 2, m_nStartY + m_nRadius * 2);

	pDC->MoveTo(m_nStartX + m_nRadius - 3, m_nStartY + m_nRadius);
	pDC->LineTo(m_nStartX + m_nRadius + 3, m_nStartY + m_nRadius);
	pDC->MoveTo(m_nStartX + m_nRadius, m_nStartY + m_nRadius - 3);
	pDC->LineTo(m_nStartX + m_nRadius, m_nStartY + m_nRadius + 3);

	CPen pen(PS_SOLID, 2, RGB(255, 255, 0));
	CPen* oldPen = pDC->SelectObject(&pen);
	pDC->Ellipse(rect);
	pDC->SelectObject(oldPen);
}

void CDlg::drawCircle(int nRadius)
{
	//cout << nRadius << endl;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	m_nRadius = nRadius;
	m_nStartX = rand() % nWidth;
	m_nStartY = rand() % nHeight;
	int nCenterX = m_nStartX + nRadius;
	int nCenterY = m_nStartY + nRadius;
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	CClientDC dc(this);

	for (int j = m_nStartY; j < m_nStartY + m_nRadius * 2; j++)
	{
		for (int i = m_nStartX; i < m_nStartX + m_nRadius * 2; i++)
		{
			if (isInCircle(i, j, nCenterX, nCenterY, m_nRadius))
			{
				fm[j * nPitch + i] = 0;
			}
		}
	}

	UpdateDisplay();

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
	CPaintDC dc(this);
	if (m_image)
		m_image.Draw(dc, 0, 0);

	drawData(&dc);
}

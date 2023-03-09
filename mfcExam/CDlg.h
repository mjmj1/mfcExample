#pragma once
#include "afxdialogex.h"


// CDlg 대화 상자

class CDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg)

public:
	CDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlg();

	CWnd* m_pParent;
	CImage m_image;
	CPoint m_ptData;
	int m_nStartX = 0;
	int m_nStartY = 0;
	int m_nRadius = 0;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	void InitImage();
	void UpdateDisplay();
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void drawData(CDC* pDC);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void drawCircle(int radius);
};

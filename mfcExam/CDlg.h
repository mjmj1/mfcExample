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


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	void InitImage();
	

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void drawData(int radius);
};

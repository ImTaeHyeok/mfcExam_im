﻿
// mfcCImageDlg.h: 헤더 파일
//

#pragma once


// CmfcCImageDlg 대화 상자
class CmfcCImageDlg : public CDialogEx
{
private: //외부 사용금지
	CImage m_image;
	BOOL validImgPos(int x, int y);


// 생성입니다.
public: //외부 사용가능
	CmfcCImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCIMAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnImage();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnLoad();
	void UpdateDisplay();
	void moveRect();
	void drawCircle(unsigned char*fm,int i,int j,int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	afx_msg void OnBnClickedBtnActtion();
	afx_msg void OnBnClickedBtnListopen();
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	//afx_msg void OnBnClickedBtnOpen();
	void LoadImageAndDisplayCoords(CString filePath);
	void DrawXOnImage(unsigned char* fm, int x, int y);

};

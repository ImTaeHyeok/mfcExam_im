// mfcCImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfcCImage.h"
#include "mfcCImageDlg.h"
#include "afxdialogex.h"
#include "iostream"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다..

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX); //기본 데이터 교환 호출
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfcCImageDlg 대화 상자



CmfcCImageDlg::CmfcCImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcCImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//(x1,y1)(x2,y2) 입력창
	//DDX_Text -> 데이터 교환방식, GUI 요소와 변수 간의 값을 동기화
	//ID인 IDC_EDIT_X1 값을 변수 m_x1으로 저장
	//UpdateData(TRUE)호출하면 입력된 값이 변수로 저장
	// ** (FALSE) 호출하면 변수의 값이 입력 창으로 반영
	DDX_Text(pDX, IDC_EDIT_X1, m_x1); //해당 ID의 입력창과 변수 m_x1을 동기화
	DDX_Text(pDX, IDC_EDIT_Y1, m_y1);
	DDX_Text(pDX, IDC_EDIT_X2, m_x2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_y2);

}

BEGIN_MESSAGE_MAP(CmfcCImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE, &CmfcCImageDlg::OnBnClickedBtnImage)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CmfcCImageDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CmfcCImageDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_ACTTION, &CmfcCImageDlg::OnBnClickedBtnActtion)
	ON_BN_CLICKED(IDC_BTN_LISTOPEN, &CmfcCImageDlg::OnBnClickedBtnListopen)
END_MESSAGE_MAP()


// CmfcCImageDlg 메시지 처리기

BOOL CmfcCImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog(); //기본 대화 상자 초기화

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE); //시스템 메뉴 포인터 가져오기
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid); //문자열 로드 성공 확인
		if (!strAboutMenu.IsEmpty()) //문자열이 비어있지 ㅇ낳은지 확인
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 좌표 입력 초기화
	m_x1 = 0;
	m_y1 = 0;
	m_x2 = 0;
	m_y2 = 0;

	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmfcCImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CmfcCImageDlg::OnPaint()
{
	if (IsIconic()) //창이 최소화되어 있는지 확인
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CmfcCImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfcCImageDlg::OnBnClickedBtnImage()
{

	UpdateData(TRUE); //입력된 좌표 값을 가져오기 

	int nWidth = 1000;
	int nHeight = 900;
	int nBpp = 8; //비트 퍼 픽셀 = 8비트

	m_image.Create(nWidth, -nHeight, nBpp); //m_image를 만들겠다(이런 크기로)
	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb); // SetColorTable -> 이미지의 색상 테이블 설정
	}

	int nPitch = m_image.GetPitch(); //GetPitch -> 이미지의 한 행에 대한 바이트 수를 가져오기
	unsigned char* fm = (unsigned char*)m_image.GetBits(); //이미지의 첫번째 포인트를 가져온다

	memset(fm, 0xff, nWidth * nHeight); //이미지 데이터 초기화

	//x1, y1 좌표에 원 그리기, 반지름20
	int nRadius = 20;
	drawCircle(fm, m_x1, m_y1, nRadius, 0);



	UpdateDisplay(); //화면에 표시
	//이걸 해줘야 화면에 나타내줌
	//CClientDC dc(this); //CClientDC -> 변수 / dc로 만들고, (this) -> 초기화를 this로.this는 현재 가지고있는 다이어로그.
	//m_image.Draw(dc, 0, 0); //m_image를 그릴거다.(dc에다가 거릴거고, left=0, top=0 에대가 그릴겨.)

	//m_image.Save(_T("c:\\image\\save.bmp")); //결과값을 컴퓨터에 저장
}


CString	g_strFileImage = _T("c:\\image\\save.bmp");
void CmfcCImageDlg::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_image.Save(g_strFileImage); //결과값을 컴퓨터에 저장
}


void CmfcCImageDlg::OnBnClickedBtnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_image != NULL) // ! -> 반전 / NULL -> 없다
	{
		m_image.Destroy(); //기존의 이미지를 삭제
	}
	m_image.Load(g_strFileImage); // 파일에서 이미지 로드

	UpdateDisplay();
}

void CmfcCImageDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

//사각형 움직이는 함수
void CmfcCImageDlg::moveRect()
{
	static int nSttX = 0; 
	static int nSttY = 0; 
	int nGray = 80;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nRadius = 20;
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	//memset(fm, 0xff, nWidth * nHeight); //이미지를 클리어하고
	drawCircle(fm, nSttX, nSttY, nRadius, 0xff);
	drawCircle(fm, ++nSttX, ++nSttY, nRadius, nGray); //이미지를 그리고


	UpdateDisplay();
}

//사각형 움직임
void CmfcCImageDlg::OnBnClickedBtnActtion()
{
	UpdateData(TRUE); // 입력된 좌표값을 가져오기

	int nFrames = 100; // 총 프레임 수! 100프레임에 걸쳐 이동 / 파일101개
	int nRadius = 20; //반지름ㅇ
	unsigned char* fm = (unsigned char*)m_image.GetBits(); //이미지 첫번째 픽셀 포인트 가져오기 
	int nPitch = m_image.GetPitch(); //피치값 가져오기

	//for(int i=0; i<=100; i++) //nFrames로 불러오는게 추후 유지보수 편할것 같음
	for (int i = 0; i <= nFrames; i++)
	{
		int x = m_x1 + (m_x2 - m_x1) * i / nFrames;
		int y = m_y1 + (m_y2 - m_y1) * i / nFrames;

		memset(fm, 0xff, m_image.GetWidth() * m_image.GetHeight()); // 이미지를 초기화/안걸어주면 강의 설명처럼 이미지 흔적이 남음.
		// 메모리셋 이미지의 모든 픽셀을 흰색(0xff)으로 초기화 and 이전 프레임의 원을 리셋
		drawCircle(fm, x, y, nRadius, 0); // (x, y) 좌표에 원을 그림, 


		//drawCircle(fm, x, y, nRadius, 0);
		if (validImgPos(x, y))
			fm[y * nPitch + x] = 0;
		x++;
		y++;

		UpdateDisplay();

		// 이미지 저장
		CString strFilePath;
		strFilePath.Format(_T("c:\\image\\frame_%03d.bmp"), i);
		m_image.Save(strFilePath);

		Sleep(10); // 딜레이 1000=1초
	}

}


//사각형이 범위 밖으로 나가도 되게하는것
BOOL CmfcCImageDlg::validImgPos(int x, int y)
{
	//이미지의 너비와 높이를 가져옴!
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight); //이미지의 범위를 정의하는 사각형 생성!

	return rect.PtInRect(CPoint(x, y)); //주어진 좌표가 사각형 범위 내에 있는지 확인!
}


//원그리기
void CmfcCImageDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();//이미지의 피치를 가져옴

	for (int j = y; j < y + nRadius * 2; j++)
	{
		for (int i = x; i < x + nRadius * 2; i++)
		{
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = nGray;
		}
	}
}

bool CmfcCImageDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false; //초기 반환 값을 false로 설정

	//원의 중심으로부터의 거리 제곱을 계산
	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius)
	{
		bRet = true;
	}

	return bRet; // 결과를 반환
}

//이미지 목록
void CmfcCImageDlg::OnBnClickedBtnListopen()
{
	//CFileDialog -> 파일 선택 상자를 열기
	CFileDialog fileDlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"));
	if (fileDlg.DoModal() == IDOK) //DoModal -> 파일 선택 상자를 모달로 열기
	{
		CString filePath = fileDlg.GetPathName(); //GetPathName -> 선택 파일의 경로 가져오기
		LoadImageAndDisplayCoords(filePath); // 이미지를 로드하고 좌표를 표시하는거 밑에 설명
	}
}

void CmfcCImageDlg::LoadImageAndDisplayCoords(CString filePath)
{
	if (m_image != NULL)
	{
		m_image.Destroy(); //기존 이미지가 있으면 제거!
	}
	m_image.Load(filePath); //새 이미지 로드!

	//높이, 너비, 피치를 가져옴
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits(); //이미지의 비트 배열을 가져옴

	//원의 반지름과 중심 좌포를 초기화!
	int nRadius = 20;
	int xCenter = 0, yCenter = 0;
	bool found = false;

	// 원 중심 좌표 찾기
	// 첫번째 픽셀을 기준으로 검색범위설정하여 원의 중심 찾기
	
	
	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i++)
		{
			if (fm[j * nPitch + i] == 0)
			{
				xCenter = i;
				yCenter = j;
				found = true;
				break;
			}
		}
		if (found) { break; }
	}

	CString str;
	str.Format(_T("Circle center: (%d, %d)"), xCenter, yCenter);

	// 콘솔창
	/*std::cout << _T("Circle center: (") << xCenter << _T(", ") << yCenter << _T(")") << std::endl;*/
	std::cout << "원의 중앙 좌표 : (" << xCenter << " , " << yCenter << ")" << std::endl;

	// X표시하기
	DrawXOnImage(fm, xCenter+nRadius, yCenter+nRadius);

	UpdateDisplay(); //디플!
}

//원의 중심 좌표에 X표시를 그리는 함수!
void CmfcCImageDlg::DrawXOnImage(unsigned char* fm, int x, int y)
{
	int nPitch = m_image.GetPitch(); //이미지 피치를 가져오고
	int size = 20; // X 크기 설정

	// 좌상단에서 우하단 방향의 대각선 X 그리기
	for (int i = -size; i <= size; i++)
	{
		int posX1 = x + i;
		int posY1 = y + i;
		//현재 좌표가 이미지 범위 내에 있는지 확인
		//확인되면 그레이 값을 설정
		if (validImgPos(posX1, posY1))
			fm[posY1 * nPitch + posX1] = 255;
	}

	// 우상단에서 좌하단 방향의 대각선 X 그리기
	for (int i = -size; i <= size; i++)
	{
		int posX2 = x + i;
		int posY2 = y - i;
		if (validImgPos(posX2, posY2))
			fm[posY2 * nPitch + posX2] = 255;
	}
}

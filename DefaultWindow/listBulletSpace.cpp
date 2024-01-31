// DefaultWindow.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "Define.h"
#include "Player.h"
#include "Bullet.h"

#pragma region 초기설정

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);	// 창 외관적인 스타일 지정 함수
BOOL                InitInstance(HINSTANCE, int);			// 창 생성과 관련된 함수
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	// 윈도우 메세지 처리 함수
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);		// 정보 창 출력 함수

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,				// 현재 프로그램의 고유 식별 번호 : 메모리 할당되는 실체, 즉 객체, api에서 현재 구동되고 있는 프로그램 인스턴스(현재 실행되고 있는 프로그램 메모리)
	_In_opt_ HINSTANCE hPrevInstance,		// 전에 실행되었던 인스턴스의 핸들, 없을 경우 NULL
	_In_ LPWSTR    lpCmdLine,				// 문자열(모름)
	_In_ int       nCmdShow)				// 실행한 창의 스타일(모양 / 최소화 또는 최대화 모양) 옵션
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

	MSG msg;
	msg.message = WM_NULL;

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		// TranslateAccelerator : 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			// TranslateMessage : 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 해주는 함수
			TranslateMessage(&msg);

			//DispatchMessage : 메세지 큐에서 꺼낸 메세지를 프로그램의 메세지 처리 함수(WndProc)로 전달하는 함수
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;		// 윈도우 창의 여러 특성을 정의하기 위한 구조체

	wcex.cbSize = sizeof(WNDCLASSEX);	// 창 사이즈를 저장

	wcex.style = CS_HREDRAW | CS_VREDRAW;	// 가로 | 세로를 다시 그리기(윈도우 창의 수직 또는 수평의 크기가 변할 경우 윈도우 창을 다시 그린다는 옵션)
	wcex.lpfnWndProc = WndProc;	// 저장해둔 함수차 호출되어 메시지를 처리하도록 함

	wcex.cbClsExtra = 0;	// 윈도우가 특수한 목적으로 사용하는 여분의 공간
	wcex.cbWndExtra = 0;	// 일종의 예약 영역이며 사용하지 않을 경우 0으로 지정

	wcex.hInstance = hInstance;	// 윈도우 클래스를 사용하는 프로그램의 번호를 설정

	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
	// 윈도우 창이 사용할 아이콘을 지정(시작 표시줄)

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	// 윈도우 창에서 사용할 마우스 커서의 모양을 지정

	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// 윈도우 작업 영역의 배경 색을 설정

	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
	// 창 상단에 있는 메뉴 설정

	wcex.lpszClassName = szWindowClass;
	// 실행파일의 이름을 저장, 가급적이면 프로젝트 이름과 일치

	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	// 창 상단에 있는 작은 아이콘 모양을 지정

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	// CreateWindowW : 등록해 놓은 정보들을 토대로 창을 생성하는 함수

	HWND hWnd = CreateWindowW(szWindowClass,		  // 앞서 정의한 윈도우 클래스 전달한 클래스 이름
		szTitle,			  // 윈도우 상단의 나타낼 문자열
		WS_OVERLAPPEDWINDOW, // 만들고자 하는 윈도우 스타일 지정 : 기본 값으로 사용하는 모양
		CW_USEDEFAULT, 0,	  // 생성하는 창의 X,Y 위치
		800, 600,	  // 생성하는 창의 가로, 세로 사이즈
		nullptr,	  // 부모 윈도우 핸들. 없을 경우 NULL
		nullptr,	  // 윈도우에서 사용할 메뉴 핸들, 레지스터에 등록된 메뉴 형태를 사용하려면 NULL
		hInstance,	  // 윈도우를 만드는 주체, 프로그램 핸들을 지정	
		nullptr);	  // 운영체제가 특수한 목적으로 사용

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// 라이브러리 : 바이너리로 번역(컴파일)된 함수들을 모아놓은 파일

// - 코드 재사용을 위한 초창기 방법 중 하나이며, 다른 프로그램에서 사용할 수 있도록 운영체제나 소프트웨어 개발자에 의해 제공

// - 라이브러리의 대다수 함수들은 함수의 정의 및 선언들을 필요로 하기 때문에 링크 되기 전, 전처리기에 의해 해당 헤더파일을
// 원시 프로그램에 포함시켜야 한다.

// - 라이브러리들은 사용자의 프로그램과 링크되어 실행이 가능한 완전한 프로그램을 이루게 된다.

// kernel : 메모리를 관리하고 프로그램을 실행시키는 도구
// user : 유저 인터페이스와 윈도우 관리 도구
// gdi : 화면 처리와 그래픽 담당

#pragma endregion

Player* player;
int g_FireNumber = 0;
void PlayerRender(const HDC& hdc)
{
	RECT* playerRECT = player->GetRECT();
	Vector2* centerVector = player->GetCenterPosition();
	Vector2* rotationVector = player->GetCurrentRotationPosition();

	if (playerRECT == nullptr)
		return;

	Rectangle(hdc, playerRECT->left, playerRECT->top, playerRECT->right, playerRECT->bottom);
	MoveToEx(hdc, centerVector->x, centerVector->y, NULL);
	LineTo(hdc, rotationVector->x, rotationVector->y);
}

void Collision()
{
	//발사한 총알리스트 가져오기
	list<Bullet*>& bulletList = player->GetBulletList();
	//발사된 총알 충돌 체크
	for (list<Bullet*> ::iterator iter = bulletList.begin(); iter != bulletList.end();)
	{
		//총알 위치값 받아오기
		RECT rect = (*iter)->GetBulletRECT();
		//조건 검사
		if (rect.left < 0 || rect.top < 0 || rect.right > 800 || rect.bottom > 600)
		{
			//다시 player가 가지고 있는 발사되지 않은 총알 리스트에 넣기
			player->SetVecRePut(*iter);
			auto tempIter = bulletList.erase(iter);
			iter = tempIter;
		}
		else
		{
			++iter;
		}
	}
}

void BulletRender(const HDC& hdc)
{
	list<Bullet*> bulletList = player->GetBulletList();

	for (Bullet* iter : bulletList)
	{
		RECT& bulletRECT = iter->GetBulletRECT();
		Direction direction = iter->GetDirection();

		switch (direction)
		{
		case LEFT:
			iter->SetPositionX(-10l);
			break;
		case TOP:
			iter->SetPositionY(-10l);
			break;
		case RIGHT:
			iter->SetPositionX(+10l);
			break;
		case BOTTOM:
			iter->SetPositionY(+10l);
			break;
		case LEFTTOP:
			iter->SetPositionX(-10l);
			iter->SetPositionY(-10l);
			break;
		case LEFTBOTTOM:
			iter->SetPositionX(-10l);
			iter->SetPositionY(+10l);
			break;
		case RIGHTBOTTOM:
			iter->SetPositionX(+10l);
			iter->SetPositionY(+10l);
			break;
		case RIGHTTOP:
			iter->SetPositionX(+10l);
			iter->SetPositionY(-10l);
			break;
		}

		Ellipse(hdc, bulletRECT.left, bulletRECT.top, bulletRECT.right, bulletRECT.bottom);
	}
}

void Start()
{
	if (player == nullptr)
		player = new Player;

	player->Initialize();
}

void Update()
{
	Collision();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	//Render
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		// HDC : 출력에 관한 정보를 갖고 있는 데이터 구조체
		// GDI가 관리하며 어떤 포인터, 선의 색상, 굵기, 무늬 등에 대한 정보를 가진다.
		HDC hdc = BeginPaint(hWnd, &ps);

		PlayerRender(hdc);
		BulletRender(hdc);
		EndPaint(hWnd, &ps);
	}
	break;

	//Start
	case WM_CREATE:
		SetTimer(hWnd, 0, 0, 0);
		Start();
		break;

		//Update
	case WM_TIMER:
		InvalidateRect(hWnd, 0, TRUE);
		Update();
		break;

		//Input, Event
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case VK_RIGHT:
			//player->SetPositionX(10l);
			player->SetRotation(TimeDirection::TIMEDIRECTION_RIGHT);

			break;

		case VK_LEFT:
			//player->SetPositionX(-10l);
			player->SetRotation(TimeDirection::TIMEDIRECTION_LEFT);
			break;

		case VK_UP:
			player->SetPositionY(-10l);
			break;

		case VK_DOWN:
			player->SetPositionY(+10l);
			break;

		case VK_SPACE:
			++g_FireNumber;
			switch (g_FireNumber % 4)
			{
			case 0:
				player->ShotBullet(LEFTTOP);
				break;
			case 1:
				player->ShotBullet(LEFTBOTTOM);
				break;
			case 2:
				player->ShotBullet(RIGHTBOTTOM);
				break;
			case 3:
				player->ShotBullet(RIGHTTOP);
				break;
			}
			break;

		case 'A':
			player->ShotBullet(LEFT);
			break;
		case 'W':
			player->ShotBullet(TOP);
			break;
		case 'D':
			player->ShotBullet(RIGHT);
			break;
		case 'S':
			player->ShotBullet(BOTTOM);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


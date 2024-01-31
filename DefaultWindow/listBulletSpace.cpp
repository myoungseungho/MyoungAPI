// DefaultWindow.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "Define.h"
#include "Player.h"
#include "Bullet.h"

#pragma region �ʱ⼳��

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.


// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);	// â �ܰ����� ��Ÿ�� ���� �Լ�
BOOL                InitInstance(HINSTANCE, int);			// â ������ ���õ� �Լ�
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	// ������ �޼��� ó�� �Լ�
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);		// ���� â ��� �Լ�

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,				// ���� ���α׷��� ���� �ĺ� ��ȣ : �޸� �Ҵ�Ǵ� ��ü, �� ��ü, api���� ���� �����ǰ� �ִ� ���α׷� �ν��Ͻ�(���� ����ǰ� �ִ� ���α׷� �޸�)
	_In_opt_ HINSTANCE hPrevInstance,		// ���� ����Ǿ��� �ν��Ͻ��� �ڵ�, ���� ��� NULL
	_In_ LPWSTR    lpCmdLine,				// ���ڿ�(��)
	_In_ int       nCmdShow)				// ������ â�� ��Ÿ��(��� / �ּ�ȭ �Ǵ� �ִ�ȭ ���) �ɼ�
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

	MSG msg;
	msg.message = WM_NULL;

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		// TranslateAccelerator : �޴� ����� ����Ű�� ����� �۵��ϵ��� �˻��ϴ� �Լ�
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			// TranslateMessage : Ű���� �޼����� �����Ͽ� ���α׷����� ���� ����� �� �ֵ��� ���ִ� �Լ�
			TranslateMessage(&msg);

			//DispatchMessage : �޼��� ť���� ���� �޼����� ���α׷��� �޼��� ó�� �Լ�(WndProc)�� �����ϴ� �Լ�
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;		// ������ â�� ���� Ư���� �����ϱ� ���� ����ü

	wcex.cbSize = sizeof(WNDCLASSEX);	// â ����� ����

	wcex.style = CS_HREDRAW | CS_VREDRAW;	// ���� | ���θ� �ٽ� �׸���(������ â�� ���� �Ǵ� ������ ũ�Ⱑ ���� ��� ������ â�� �ٽ� �׸��ٴ� �ɼ�)
	wcex.lpfnWndProc = WndProc;	// �����ص� �Լ��� ȣ��Ǿ� �޽����� ó���ϵ��� ��

	wcex.cbClsExtra = 0;	// �����찡 Ư���� �������� ����ϴ� ������ ����
	wcex.cbWndExtra = 0;	// ������ ���� �����̸� ������� ���� ��� 0���� ����

	wcex.hInstance = hInstance;	// ������ Ŭ������ ����ϴ� ���α׷��� ��ȣ�� ����

	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
	// ������ â�� ����� �������� ����(���� ǥ����)

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	// ������ â���� ����� ���콺 Ŀ���� ����� ����

	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// ������ �۾� ������ ��� ���� ����

	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
	// â ��ܿ� �ִ� �޴� ����

	wcex.lpszClassName = szWindowClass;
	// ���������� �̸��� ����, �������̸� ������Ʈ �̸��� ��ġ

	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	// â ��ܿ� �ִ� ���� ������ ����� ����

	return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	// CreateWindowW : ����� ���� �������� ���� â�� �����ϴ� �Լ�

	HWND hWnd = CreateWindowW(szWindowClass,		  // �ռ� ������ ������ Ŭ���� ������ Ŭ���� �̸�
		szTitle,			  // ������ ����� ��Ÿ�� ���ڿ�
		WS_OVERLAPPEDWINDOW, // ������� �ϴ� ������ ��Ÿ�� ���� : �⺻ ������ ����ϴ� ���
		CW_USEDEFAULT, 0,	  // �����ϴ� â�� X,Y ��ġ
		800, 600,	  // �����ϴ� â�� ����, ���� ������
		nullptr,	  // �θ� ������ �ڵ�. ���� ��� NULL
		nullptr,	  // �����쿡�� ����� �޴� �ڵ�, �������Ϳ� ��ϵ� �޴� ���¸� ����Ϸ��� NULL
		hInstance,	  // �����츦 ����� ��ü, ���α׷� �ڵ��� ����	
		nullptr);	  // �ü���� Ư���� �������� ���

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

// ���̺귯�� : ���̳ʸ��� ����(������)�� �Լ����� ��Ƴ��� ����

// - �ڵ� ������ ���� ��â�� ��� �� �ϳ��̸�, �ٸ� ���α׷����� ����� �� �ֵ��� �ü���� ����Ʈ���� �����ڿ� ���� ����

// - ���̺귯���� ��ټ� �Լ����� �Լ��� ���� �� ������� �ʿ�� �ϱ� ������ ��ũ �Ǳ� ��, ��ó���⿡ ���� �ش� ���������
// ���� ���α׷��� ���Խ��Ѿ� �Ѵ�.

// - ���̺귯������ ������� ���α׷��� ��ũ�Ǿ� ������ ������ ������ ���α׷��� �̷�� �ȴ�.

// kernel : �޸𸮸� �����ϰ� ���α׷��� �����Ű�� ����
// user : ���� �������̽��� ������ ���� ����
// gdi : ȭ�� ó���� �׷��� ���

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
	//�߻��� �Ѿ˸���Ʈ ��������
	list<Bullet*>& bulletList = player->GetBulletList();
	//�߻�� �Ѿ� �浹 üũ
	for (list<Bullet*> ::iterator iter = bulletList.begin(); iter != bulletList.end();)
	{
		//�Ѿ� ��ġ�� �޾ƿ���
		RECT rect = (*iter)->GetBulletRECT();
		//���� �˻�
		if (rect.left < 0 || rect.top < 0 || rect.right > 800 || rect.bottom > 600)
		{
			//�ٽ� player�� ������ �ִ� �߻���� ���� �Ѿ� ����Ʈ�� �ֱ�
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
		// �޴� ������ ���� �м��մϴ�.
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
		// HDC : ��¿� ���� ������ ���� �ִ� ������ ����ü
		// GDI�� �����ϸ� � ������, ���� ����, ����, ���� � ���� ������ ������.
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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


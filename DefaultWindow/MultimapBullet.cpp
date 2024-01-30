// DefaultWindow.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "DefaultWindow.h"

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


RECT			rc{ 100,100, 200,200 };
multimap<int, RECT> mapBullet;
enum DIRECT
{
	LEFT = 1,
	TOP,
	RIGHT,
	BOTTOM,
	LEFTTOP,
	LEFTBOTTOM,
	RIGHTTOP,
	RIGHTBOTTOM
};

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

	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		// HDC : ��¿� ���� ������ ���� �ִ� ������ ����ü
		// GDI�� �����ϸ� � ������, ���� ����, ����, ���� � ���� ������ ������.
		HDC hdc = BeginPaint(hWnd, &ps);

		//Ŀ���� �̵���Ű�� �Լ�(NULL : Ŀ���� �̵��ϱ� �� ��ġ�� OUTPUT���·� ��ȯ)
		//�÷��̾� ����
		Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);

		for (auto mapIter = mapBullet.begin(); mapIter != mapBullet.end(); mapIter++)
		{
			//��ǥ ������ �Ѿ�� ����
			if (mapIter->second.left < 0 || mapIter->second.top < 0 || mapIter->second.right > 800 || mapIter->second.bottom > 600)
			{
				mapBullet.erase(mapIter);
				break;
			}

			//��Ȯ���� ���� �����ϴ°ͺ��� ���� �׸��°���.
			Ellipse(hdc, mapIter->second.left, mapIter->second.top, mapIter->second.right, mapIter->second.bottom);

			switch (mapIter->first)
			{
			case LEFT:
				mapIter->second.left -= 10;
				mapIter->second.right -= 10;
				break;
			case TOP:
				mapIter->second.top -= 10;
				mapIter->second.bottom -= 10;
				break;
			case RIGHT:
				mapIter->second.left += 10;
				mapIter->second.right += 10;
				break;
			case BOTTOM:
				mapIter->second.top += 10;
				mapIter->second.bottom += 10;
				break;
			
			case LEFTTOP:
				mapIter->second.left -= 10;
				mapIter->second.right -= 10;
				mapIter->second.top -= 10;
				mapIter->second.bottom -= 10;
				break;
			case LEFTBOTTOM:
				mapIter->second.left -= 10;
				mapIter->second.right -= 10;
				mapIter->second.top += 10;
				mapIter->second.bottom += 10;
				break;
			case RIGHTBOTTOM:
				mapIter->second.left += 10;
				mapIter->second.right += 10;
				mapIter->second.top += 10;
				mapIter->second.bottom += 10;
				break;
			case RIGHTTOP:
				mapIter->second.left += 10;
				mapIter->second.right += 10;
				mapIter->second.top -= 10;
				mapIter->second.bottom -= 10;
				break;
			}
		}
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_CREATE:
		SetTimer(hWnd, 0, 0, 0);
		// 1. ������ �ڵ� ����
		// 2. Ÿ�̸��� ID��ȣ�̴�, �����쿡�� ���� ���� Ÿ�̸Ӱ� ������ �� �����Ƿ� Ÿ�̸� ��ȣ �ʿ�
		// 3. Ÿ�̸��� �ֱ�, 0�� ��� 1000�� 1��
		// 4. NULL�� ��� ������ �ֱ��� WM_TIMER �޼����� �߻�
		break;

	case WM_TIMER:
		//InvalidateRect : â ���� �Լ�, WM_PAINT �޼����� �߻�
		InvalidateRect(hWnd, 0, TRUE);

		// 1. ������ â�� �ڵ�
		// 2. �������� ������ ���� ����, null�� ��� â ��ü ����(RECT �ּҸ� �־��ָ� �� �κи� ����)
		// 3. TRUE : �׷��� ���� ���� �κе� ��� ����
		//	  FALSE : �׸��� �κи� ����	
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case VK_RIGHT:
			rc.left += 10;
			rc.right += 10;
			break;

		case VK_LEFT:
			rc.left -= 10;
			rc.right -= 10;
			break;

		case VK_UP:
			rc.top -= 10;
			rc.bottom -= 10;
			break;

		case VK_DOWN:
			rc.top += 10;
			rc.bottom += 10;
			break;

		case 'A':
			mapBullet.insert({ LEFT,rc });
			break;
		case 'W':
			mapBullet.insert({ TOP,rc });
			break;
		case 'D':
			mapBullet.insert({ RIGHT,rc });
			break;
		case 'S':
			mapBullet.insert({ BOTTOM,rc });
			break;

		case VK_SPACE:
			mapBullet.insert({ LEFTTOP,rc });
			mapBullet.insert({ LEFTBOTTOM,rc });
			mapBullet.insert({ RIGHTTOP,rc });
			mapBullet.insert({ RIGHTBOTTOM,rc });
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


// �Լ� ȣ�� �Ծ� 

// - �Լ��� ������ ����Ǹ� �Ҵ� �Ǿ��� stack�� �Ҹ���Ѿ� �ϴµ� �̶� �Լ��� ȣ���� ȣ������� ������ �� �ƴϸ� ȣ�� ���� �� ȣ���ڿ��� �� �������� ���� ���

// __cdecl : c / c++ ����� �⺻ ȣ�� �Ծ�, ȣ����� stack�� ����, �������� �Լ�(�Ű� ������ �󸶳� ��� ���� �� �𸥴�)

// __stdcall : win32 api�� �⺻ ȣ�� �Ծ�, ��ȣ���ڰ� stack�� ����, �������� �Լ�(�Ű� ������ �̹� ���� �Ǿ�����)

// __fastcall : �Լ� ȣ���� ������ ó���ϱ� ���� ȣ�� �Ծ�, ecx�� edx��� �������͸� ���� ����, �������͸� ����ϰ� �ִٴ� ������ �Լ� ȣ���� �������� �ٰŰ� ��

// __thiscall : this �����͸� �Ű� ������ ���� �� ����ϴ� ȣ�� �Ծ�


// 1. �׸��� �׷��Ͷ�
// 2. W,A,S,D Ű �������� �Ѿ��� �������� ������, SPACE ������ �� �������� �������� ����


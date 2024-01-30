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
list<RECT>		listBullet;


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
		Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);

		MoveToEx(hdc, 150, 200, NULL);
		LineTo(hdc, 100, 300);
		MoveToEx(hdc, 150, 200, NULL);
		LineTo(hdc, 200, 300);
		MoveToEx(hdc, 150, 200, NULL);
		LineTo(hdc, 150, 300);
		LineTo(hdc, 100, 500);
		MoveToEx(hdc, 150, 300, NULL);
		LineTo(hdc, 200, 500);

		MoveToEx(hdc, 190, 300, NULL);
		LineTo(hdc, 200, 290);
		LineTo(hdc, 210, 300);
		LineTo(hdc, 200, 310);
		LineTo(hdc, 190, 300);
		MoveToEx(hdc, 200, 290, NULL);
		LineTo(hdc, 250, 270);
		MoveToEx(hdc, 210, 300, NULL);
		LineTo(hdc, 250, 270);

		Ellipse(hdc, 350, 350, 450, 450);
		Rectangle(hdc, 450, 350, 700, 450);
		MoveToEx(hdc, 470, 450, NULL);
		LineTo(hdc, 470, 530);
		MoveToEx(hdc, 680, 450, NULL);
		LineTo(hdc, 680, 530);



		//for (auto& iter : BulletList)
		//{
		//	Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

		//	iter.top	-= 10;
		//	iter.bottom -= 10;
		//}

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_CREATE:
		//SetTimer(hWnd, 0, 0, 0);
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

		case VK_SPACE:
			listBullet.push_back(rc);
			break;

		case 'W':
			listBullet.push_back(rc);
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


#include <Windows.h>
#include "resource.h"
#include <stdio.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "My main Window";


INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdline, INT nCmdShow)
{

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH) COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpfnWndProc = (WNDPROC) WndProc;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));

	int screenWidth = GetSystemMetrics(SM_CXSCREEN); // ширина экрана
	int screenHeight = GetSystemMetrics(SM_CYSCREEN); // высота экрана
	int windowWidth = (int)(screenWidth * 0.75); // ширина окна 75% от ширины экрана
	int windowHeight = (int)(screenHeight * 0.75); // высота окна 75% от высоты экрана

	
	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}
	HCURSOR hCursor = LoadCursorFromFile("arrow.cur");
	if (hCursor == NULL)
	{
		MessageBox(NULL, "Failed to load cursor", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	HWND hwnd = CreateWindowEx
	(
		NULL,              //Ex.Style
		g_sz_WINDOW_CLASS, //Class name
		g_sz_WINDOW_CLASS, // Window Title
		
		WS_OVERLAPPEDWINDOW, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2,
		windowWidth, windowHeight,
		 // Size - размер создаваемого окна
		NULL,
		NULL,    //hMenu - для главного окна это ResourceID главного меню, для дочернего окна (элемента какого-то окна) это ResourceID 
		// соответствующего элемента
		// поэтому ResourceID нужный элемент всегда можно получить при помощи функции 
		hInstance,
		NULL
	);

	

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}


	SetCursor(hCursor);
	ShowWindow(hwnd, nCmdShow); // Задает режим отображения окна(развернуто на весь экран, свернуто в окно или на панель задач)
	UpdateWindow(hwnd); // Прорисовывает окно


	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	
	return msg.wParam;
		
	
}


INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)


{
	
	
	switch (uMsg)
	{
	case WM_SIZE:
	{
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);
		RECT rect;
		GetWindowRect(hwnd, &rect);
		int x = rect.left;
		int y = rect.top;

		char text[100];
		sprintf_s(text, "Ширина: %d Высота: %d Положение: X=%d, Y=%d", width, height, x, y);
		SetWindowText(hwnd, text);

		break;
	}


	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);

	}
	return 0;
}
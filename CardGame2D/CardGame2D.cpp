// CardGame2D.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CardGame2D.h"
#include "Framework.h"
#include "InputComponent.h"
#include "Game.h"

#define MAX_LOADSTRING 100

namespace
{
	static Framework* m_framework = nullptr;
}

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	m_framework = Framework::CreateFramework();


	Game game;

    // TODO: Place code here.

    // Initialize global strings
    MyRegisterClass(hInstance);



    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	InputComponent::m_input = new Input();
	RECT rect;
	GetWindowRect(m_framework->GetWindow(), &rect);
	InputComponent::m_input->SetReadingState(Input::DeviceReadingState::READ_KEYBOARDANDMOUSE);
	InputComponent::m_input->Initialize(hInstance, m_framework->GetWindow(), rect.right - rect.left, rect.bottom - rect.top);
	

	game.Initialize();

	UpdateWindow(m_framework->GetWindow());

    MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
    }

	if (m_framework)
		delete m_framework;
	if (InputComponent::m_input)
		delete InputComponent::m_input;

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
	wcex.hIcon = 0;
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = 0;
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = L"CardGame";
	wcex.hIconSm = 0;

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(L"CardGame", L"CardGame", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   m_framework->SetWindow(hWnd);

  

   ShowWindow(hWnd, nCmdShow);
   SetForegroundWindow(hWnd);
  // UpdateWindow(hWnd);

   return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		m_framework->Resize(width, height);
	}
	break;

	case WM_DISPLAYCHANGE:
	{
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;
	case WM_PAINT:
	{
		if (InputComponent::m_input)
		{
			InputComponent::m_input->Update();
			if (InputComponent::m_input->IsKeyHit(1))
			{
				PostQuitMessage(0);
			}
		}
		m_framework->Render();
		InvalidateRect(hWnd, NULL, FALSE);
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

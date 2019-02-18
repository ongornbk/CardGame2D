#pragma once
#include "Direct2D.h"
#include "WindowHandle.h"
#include "RenderTarget.h"

class Framework : WindowHandle
{
public:
	~Framework();
	static Framework* CreateFramework();
	void Render();
	void Resize(uint32_t width, uint32_t height);
	void SetWindow(HWND hwnd);
	HWND GetWindow();

	friend int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPWSTR    lpCmdLine,
		_In_ int       nCmdShow);

	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
	Direct2D* m_graphics;
	Framework();



};


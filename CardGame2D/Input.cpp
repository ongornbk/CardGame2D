#include "stdafx.h"
#include "Input.h"
#include <iostream>
#include "Types.h"

template <class T>
Boolean Unacquire(T t)
{
	Boolean result;
	if (t)
	{
		result = t->Unacquire();
		t = nullptr;
	}
	return result;
}

Input::DeviceReadingState Input::m_readingState = Input::DeviceReadingState::READ_KEYBOARDANDMOUSE;

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Input::Input(void)
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
	memset(m_keys, 0, sizeof(bool)*s_NumKeys);
	OutputDebugStringW(L"DirectInput Contructed \n");
}


Input::~Input(void)
{
	Unacquire(m_mouse);
	Unacquire(m_keyboard);
	if (m_directInput)
	{
		(void)m_directInput->Release();
		m_directInput = NULL;
	}
	OutputDebugStringW(L"DirectInput Destructed \n");
}

bool Input::Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_mouseX = 0;
	m_mouseY = 0;

	

	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		OutputDebugStringW(L"DirectInput DirectInput8Create FAILED \n");
		return false;
	}

	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		OutputDebugStringW(L"DirectInput CreateDevice keyboard FAILED \n");
		return false;
	}

	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		OutputDebugStringW(L"DirectInput SetDataFormat keyboard FAILED \n");
		return false;
	}

	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		OutputDebugStringW(L"DirectInput SetCooperativeLevel keyboard FAILED \n");
		return false;
	}

	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		OutputDebugStringW(L"DirectInput Acquire keyboard FAILED \n");
		return false;
	}

	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		OutputDebugStringW(L"DirectInput CreateDevice mouse FAILED \n");
		return false;
	}

	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		OutputDebugStringW(L"DirectInput SetDataFormat mouse FAILED \n");
		return false;
	}

	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		OutputDebugStringW(L"DirectInput SetCooperativeLevel mouse FAILED \n");
		return false;
	}

	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		OutputDebugStringW(L"DirectInput Acquire mouse FAILED \n");
		return false;
	}

	OutputDebugStringW(L"DirectInput Initialized \n");

	return true;
}

bool __cdecl Input::Update()
{
	memcpy(m_prevKeys, m_keys, sizeof(bool)*s_NumKeys);
	memcpy(m_prevMouseState, m_mouseState.rgbButtons, sizeof(BYTE) * 4);
	bool result;
	result = ReadKeyboard();
	if (!result)return false;
	result = ReadMouse();
	if (!result) return false;
	ProcessInput();
	return true;
}

bool Input::IsKeyDown(unsigned int key)
{
	switch (m_readingState)
	{
	case READ_KEYBOARDANDMOUSE:
	{
		return m_keys[key];
	}break;
	case READ_KEYBOARD:
	{
		return m_keys[key];
	}break;
	default: return false;
	}
	return false;
}



bool Input::IsKeyHit(unsigned int key)
{
	switch (m_readingState)
	{
	case READ_KEYBOARDANDMOUSE:
	{
		return m_keys[key] && !m_prevKeys[key];
	}break;
	case READ_KEYBOARD:
	{
		return m_keys[key] && !m_prevKeys[key];
	}break;
	default: return false;
	}
	return false;
}

void Input::GetMousePosition(int & x, int & y)
{
	switch (m_readingState)
	{
	case READ_KEYBOARDANDMOUSE:
	{
		x = m_mouseX;
		y = m_mouseY;
	}break;
	case READ_MOUSE:
	{
		x = m_mouseX;
		y = m_mouseY;
	}break;
	default:
	{
		x = 0;
		y = 0;
	}
	}
}

void Input::SetReadingState(DeviceReadingState readingState)
{
	m_readingState = readingState;
}

bool Input::ReadKeyboard()
{
	HRESULT result;
	result = m_keyboard->GetDeviceState(sizeof(m_keys), (LPVOID)&m_keys);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Input::ReadMouse()
{
	if (m_mouse == NULL)
	{
		(void)m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
		return false;
	}

	HRESULT result;

	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

void Input::ProcessInput()
{
	switch (m_readingState)
	{
	case READ_KEYBOARDANDMOUSE:
	{
		m_mouseX += m_mouseState.lX * 2;
		m_mouseY += m_mouseState.lY * 2;
		if (m_mouseX < 24)m_mouseX = 24;
		if (m_mouseY < 48)m_mouseY = 48;
		if (m_mouseX > m_screenWidth - 24)m_mouseX = m_screenWidth - 24;
		if (m_mouseY > m_screenHeight + 24)m_mouseY = m_screenHeight + 24;
	}break;
	case READ_KEYBOARD:
	{

	}break;
	case READ_MOUSE:
	{
		m_mouseX += m_mouseState.lX * 2;
		m_mouseY += m_mouseState.lY * 2;
		if (m_mouseX < 24)m_mouseX = 24;
		if (m_mouseY < 24)m_mouseY = 24;
		if (m_mouseX > m_screenWidth - 24)m_mouseX = m_screenWidth - 24;
		if (m_mouseY > m_screenHeight - 24)m_mouseY = m_screenHeight - 24;
	}break;
	case READ_NOTHING: break;
	default: break;
	}



}

BYTE Input::GetMouseState(int index)
{
	return m_mouseState.rgbButtons[index];
}

bool Input::GetMousePressed(int32_t index)
{
	return m_mouseState.rgbButtons[index] && !m_prevMouseState[index];
}

void Input::Release()
{
	delete(this);
}
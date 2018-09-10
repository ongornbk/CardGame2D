#include "stdafx.h"
#include "GameRenderer.h"
#include "Graphics.h"
#include <sstream>
#include <algorithm>
#include <locale>
#include <codecvt>

namespace
{
	GameRenderer* m_instance = nullptr;

	static void _stdcall renderFoo() noexcept
	{
		m_instance->Render();
	}

	static void _stdcall updateFoo() noexcept
	{
		m_instance->Update();
	}
}

GameRenderer::GameRenderer() : RendererManager(&updateFoo,&renderFoo)
{
	m_instance = this;
}


GameRenderer::~GameRenderer()
{
}

uint16_t yt = 0u;

void GameRenderer::Update()
{
	yt += 1u;
	float offx = m_cameraPosition.x / 50.0f;
	float offy = m_cameraPosition.y / 50.0f;
	m_borders[0] = offx - (m_renderTargetSize.x / 50.0f);
	m_borders[1] = offy - (m_renderTargetSize.y / 50.0f);
	m_borders[2] = offx + (m_renderTargetSize.x / 50.0f);
	m_borders[3] = offx + (m_renderTargetSize.y / 50.0f);
	if (m_borders[0] < 0)m_borders[0] = 0;
	if (m_borders[1] < 0)m_borders[1] = 0;
	if (m_borders[2] >127)m_borders[2] = 127;
	if (m_borders[3] < 19)m_borders[3] = 19;
}

std::wstring stringStream2wstring(std::stringstream& strs)
{
	std::string str = strs.str();
	typedef std::codecvt_utf8<wchar_t> convert_type;
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.from_bytes(str);
}

void GameRenderer::Render()
{
	SetStroke(1.0f);
	SetBrush(m_lightSlateGrayBrush);
	SetTextSize(50.0f);

	float xs = m_xSize / -2.0f;

	std::stringstream ss;
	ss << L"0 : " << m_borders[0] << L"1 : " << m_borders[1] << L"2 : " << m_borders[2] << L"3 : " << m_borders[3];
	std::wstring ws = stringStream2wstring(ss);
	DrawWideText(ws, { 0,0,m_renderTargetSize.x,m_renderTargetSize.y });

	//for (int32_t x = m_borders[0]; x < m_borders[2]; x++)
	//{
	//	for (int32_t y = m_borders[1]; y < m_borders[3]; y++)
	//	{
	//		if (m_gameMap[x][y])
	//		{
	//			SetStroke((x+y+yt)%50);
	//			DirectX::XMFLOAT2 pt = m_gameMap[x][y]->position;
	//			DrawRectangle({ 50.0f*(xs + x),50.0f*+y,50.0f*(xs+x+1),50.0f*(y+1) });
	//		}
	//	}
	//}
}

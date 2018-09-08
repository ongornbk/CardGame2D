#include "stdafx.h"
#include "Direct2D.h"
#include <cstdlib>

namespace
{
	RendererManager*       m_renderer;
}

Direct2D::Direct2D()
{
	m_hwnd = NULL;
	m_factory = nullptr;
	m_lightSlateGrayBrush = nullptr;
	m_cornflowerBlueBrush = nullptr;
}


Direct2D::~Direct2D()
{
	if (m_renderTarget.load())
	{
		m_renderTarget.load()->Release();
		m_renderTarget = nullptr;
	}
	if (m_factory)
	{
		m_factory->Release();
		m_factory = nullptr;
	}
	if (m_lightSlateGrayBrush)
	{
		m_lightSlateGrayBrush->Release();
		m_lightSlateGrayBrush = nullptr;
	}
	if (m_cornflowerBlueBrush)
	{
		m_cornflowerBlueBrush->Release();
		m_cornflowerBlueBrush = nullptr;
	}
}

Boolean Direct2D::CreateFactory()
{
	return D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);
}

Boolean Direct2D::InitializeResources()
{
	Boolean result;

	RECT rc;
	GetClientRect(m_hwnd, &rc);


	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left,rc.bottom - rc.top);

	ID2D1HwndRenderTarget* temp;
	result =  m_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),D2D1::HwndRenderTargetProperties(m_hwnd, size), &temp);
	m_renderTarget.store(temp, std::memory_order::memory_order_seq_cst);
	CheckBoolean(result);

	m_renderTarget.load()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &m_lightSlateGrayBrush);
	CheckBoolean(result);
	m_renderTarget.load()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &m_cornflowerBlueBrush);
	CheckBoolean(result);
	return result;
}



Boolean Direct2D::DiscardDeviceResources()
{
	Boolean result;
	if ((m_renderTarget.load()))
	{
		result = m_renderTarget.load()->Release();
		m_renderTarget = nullptr;
	}
	CheckBoolean(result);
	if (m_lightSlateGrayBrush)
	{
		result = m_lightSlateGrayBrush->Release();
		m_lightSlateGrayBrush = nullptr;
	}
	CheckBoolean(result);
	if (m_cornflowerBlueBrush)
	{
		result = m_cornflowerBlueBrush->Release();
		m_cornflowerBlueBrush = nullptr;
	}
	CheckBoolean(result);
	return result;
}

Boolean Direct2D::OnResize(uint32_t width, uint32_t height)
{
	Boolean result = -1;
	if (m_renderTarget.load())
		result = m_renderTarget.load()->Resize(D2D1::SizeU(width, height));
	CheckBoolean(result);
	return result;
}

void Direct2D::SetRendererManager(RendererManager* renderer)
{
	m_renderer = renderer;
	OutputDebugString(L"wewewewe");
}

void Direct2D::BeginDraw()
{
	m_renderer->Update();
	InitializeResources();
	m_renderTarget.load()->BeginDraw();

	m_renderTarget.load()->SetTransform(D2D1::Matrix3x2F::Identity());

	m_renderTarget.load()->Clear(D2D1::ColorF(D2D1::ColorF::White));

	m_renderTargetSize = { m_renderTarget.load()->GetSize().width,m_renderTarget.load()->GetSize().height };

	m_renderer->Render();
		

		
		//for (int x = 0; x < width; x += 10)
		//{
		//	((ID2D1HwndRenderTarget*)Global::m_renderTarget.load())->DrawLine(
		//		D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
		//		D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
		//		m_lightSlateGrayBrush,
		//		0.5f
		//	);
		//}
		//
		//for (int y = 0; y < height; y += 10)
		//{
		//	((ID2D1HwndRenderTarget*)Global::m_renderTarget.load())->DrawLine(
		//		D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
		//		D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
		//		m_lightSlateGrayBrush,
		//		0.5f
		//	);
		//}
		
		//D2D1_RECT_F rectangle1 = D2D1::RectF(
		//	rtSize.width / 2 - 50.0f,
		//	rtSize.height / 2 - 50.0f,
		//	rtSize.width / 2 + 50.0f,
		//	rtSize.height / 2 + 50.0f
		//);
		//
		//D2D1_RECT_F rectangle2 = D2D1::RectF(
		//	rtSize.width / 2 - 100.0f,
		//	rtSize.height / 2 - 100.0f,
		//	rtSize.width / 2 + 100.0f,
		//	rtSize.height / 2 + 100.0f
		//);
		//
		//((ID2D1HwndRenderTarget*)Global::m_renderTarget.load())->FillRectangle(&rectangle1, m_lightSlateGrayBrush);
		//
		//((ID2D1HwndRenderTarget*)Global::m_renderTarget.load())->DrawRectangle(&rectangle2, m_cornflowerBlueBrush);

	
}

void Direct2D::EndDraw()
{
	m_renderTarget.load()->EndDraw();
		
	DiscardDeviceResources();
}

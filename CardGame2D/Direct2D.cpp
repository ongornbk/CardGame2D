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
	m_writeFactory = nullptr;
	m_imageFactory = nullptr;
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
	if (m_writeFactory)
	{
		m_writeFactory->Release();
		m_writeFactory = nullptr;
	}
	if (m_imageFactory)
	{
		m_imageFactory->Release();
		m_imageFactory = nullptr;
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
	if (m_redBrush)
	{
		m_redBrush->Release();
		m_redBrush = nullptr;
	}
	if (m_orangeBrush)
	{
		m_orangeBrush->Release();
		m_orangeBrush = nullptr;
	}
	if (m_blackBrush)
	{
		m_blackBrush->Release();
		m_blackBrush = nullptr;
	}
	ReleaseTextures();
}

Boolean Direct2D::CreateFactory()
{
	Boolean result;
	result = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_factory);
	CheckBoolean(result);
	result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(m_writeFactory),reinterpret_cast<IUnknown **>(&m_writeFactory));
	CheckBoolean(result);
	//result = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&m_imageFactory);
	//CheckBoolean(result);



	return result;
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

	result = m_renderTarget.load()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &m_lightSlateGrayBrush);
	CheckBoolean(result);
	result = m_renderTarget.load()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &m_cornflowerBlueBrush);
	CheckBoolean(result);
	result = m_renderTarget.load()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &m_redBrush);
	CheckBoolean(result);
	result = m_renderTarget.load()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Orange), &m_orangeBrush);
	CheckBoolean(result);
	result = m_renderTarget.load()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_blackBrush);
	CheckBoolean(result);
	result = m_writeFactory->CreateTextFormat(L"Consolas",NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,m_textSize,L"", &m_textFormat);
	CheckBoolean(result);

	result = m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	CheckBoolean(result);
	result = m_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
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
	if (m_redBrush)
	{
		result = m_redBrush->Release();
		m_redBrush = nullptr;
	}
	CheckBoolean(result);
	if (m_orangeBrush)
	{
		result = m_orangeBrush->Release();
		m_orangeBrush = nullptr;
	}
	CheckBoolean(result);
	if (m_blackBrush)
	{
		result = m_blackBrush->Release();
		m_blackBrush = nullptr;
	}
	CheckBoolean(result);
	if (m_textFormat)
	{
		result = m_textFormat->Release();
		m_textFormat = nullptr;
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
		


	
}

void Direct2D::EndDraw()
{
	m_renderTarget.load()->EndDraw();
		
	DiscardDeviceResources();
}

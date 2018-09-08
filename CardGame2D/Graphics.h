#pragma once
#include "RenderTarget.h"
#include "Brushes.h"

class Graphics : public Brushes, RenderTarget
{
public:
	Graphics();
	~Graphics();

	void SetBrush(ID2D1SolidColorBrush* brush);
	void DrawLine(DirectX::XMFLOAT2 pointA, DirectX::XMFLOAT2 pointB);

private:

	ID2D1HwndRenderTarget* __f000__();

	ID2D1SolidColorBrush* m_activeBrush;

};


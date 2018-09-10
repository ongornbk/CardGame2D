#include "stdafx.h"
#include "GameRenderer.h"
#include "Graphics.h"

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

void GameRenderer::Update()
{
}

void GameRenderer::Render()
{
	SetStroke(2.0f);
	SetBrush(m_lightSlateGrayBrush);
	FillRectangle({1.0f,1.0f,m_renderTargetSize.x-1.0f,m_renderTargetSize.y-1.0f});
	SetBrush(m_cornflowerBlueBrush);
	FillRectangle({ 10.0f,10.0f,m_renderTargetSize.x - 10.0f,m_renderTargetSize.y - 10.0f });
	SetBrush(m_lightSlateGrayBrush);
	DrawWideText(L"znanych jako wahaj¹ce siê, takich jak Pensylwania, Karolina Pó³nocna, Ohio, Wisconsin czy Floryda[260][261]. Zgodnie z ostatecznymi wynikami wyborów na Donalda Trumpa zag³osowa³o 62 979 879 osób (45,95%), co by³o drugim rezultatem w g³osowaniu bezpoœrednim. Pierwszy przypad³ kandydatce Partii Demokratycznej Hillary Clinton, która zdoby³a g³osy 65 845 063 osób (48,03%). Trump wygra³ jednak g³osowanie w Kolegium Elektorów, otrzymuj¹c 304 g³osy w stosunku do 227 g³osów Clinton[262]. By³ to pi¹ty w historii Stanów Zjednoczonych przypadek, w którym zwyciêzca wyborów przegrywa w g³osowaniu powszechnym, ale wygrywa w g³osowaniu elektorskim. Wczeœniej byli to John Quincy Adams (1824, przegrany – Andrew Jackson), Rutherford Hayes (1876, przegrany – Samuel J. Tilden), Benjamin Harrison (1888, przegrany – Grover Cleveland) i George W. Bush (2000, przegrany – Al Gore)[263][264].W wyborach, które odby³y siê 8 listopada 2016 Donald Trump zwyciê¿y³, uzyskuj¹c wiêcej ni¿ wymagana do zwyciêstwa wiêkszoœæ 270 g³osów elektorskich[259]. Wygran¹ w skali kraju zapewni³o Trumpowi niespodziewane zwyciêstwo w stanach znanych jako wahaj¹ce siê, takich jak Pensylwania, Karolina Pó³nocna, Ohio, Wisconsin czy Floryda[260][261]. Zgodnie z ostatecznymi wynikami wyborów na Donalda Trumpa zag³osowa³o 62 979 879 osób (45,95%), co by³o drugim rezultatem w g³osowaniu bezpoœrednim. Pierwszy przypad³ kandydatce Partii Demokratycznej Hillary Clinton, która zdoby³a g³osy 65 845 063 osób (48,03%). Trump wygra³ jednak g³osowanie w Kolegium Elektorów, otrzymuj¹c 304 g³osy w stosunku do 227 g³osów Clinton[262]. By³ to pi¹ty w historii Stanów Zjednoczonych przypadek, w którym zwyciêzca wyborów przegrywa w g³osowaniu powszechnym, ale wygrywa w g³osowaniu elektorskim. Wczeœniej byli to John Quincy Adams (1824, przegrany – Andrew Jackson), Rutherford Hayes (1876, przegrany – Samuel J. Tilden), Benjamin Harrison (1888, przegrany – Grover Cleveland) i George W. Bush (2000, przegrany – Al Gore)[263][264].W wyborach, które odby³y siê 8 listopada 2016 Donald Trump zwyciê¿y³, uzyskuj¹c wiêcej ni¿ wymagana do zwyciêstwa wiêkszoœæ 270 g³osów elektorskich[259]. Wygran¹ w skali kraju zapewni³o Trumpowi niespodziewane zwyciêstwo w stanach znanych jako wahaj¹ce siê, takich jak Pensylwania, Karolina Pó³nocna, Ohio, Wisconsin czy Floryda[260][261]. Zgodnie z ostatecznymi wynikami wyborów na Donalda Trumpa zag³osowa³o 62 979 879 osób (45,95%), co by³o drugim rezultatem w g³osowaniu bezpoœrednim. Pierwszy przypad³ kandydatce Partii Demokratycznej Hillary Clinton, która zdoby³a g³osy 65 845 063 osób (48,03%). Trump wygra³ jednak g³osowanie w Kolegium Elektorów, otrzymuj¹c 304 g³osy w stosunku do 227 g³osów Clinton[262]. By³ to pi¹ty w historii Stanów Zjednoczonych przypadek, w którym zwyciêzca wyborów przegrywa w g³osowaniu powszechnym, ale wygrywa w g³osowaniu elektorskim. Wczeœniej byli to John Quincy Adams (1824, przegrany – Andrew Jackson), Rutherford Hayes (1876, przegrany – Samuel J. Tilden), Benjamin Harrison (1888, przegrany – Grover Cleveland) i George W. Bush (2000, przegrany – Al Gore)[263][264].", { 1.0f,1.0f,m_renderTargetSize.x - 1.0f,m_renderTargetSize.y - 1.0f });


}

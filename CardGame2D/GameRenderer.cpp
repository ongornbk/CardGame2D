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
	DrawWideText(L"znanych jako wahaj�ce si�, takich jak Pensylwania, Karolina P�nocna, Ohio, Wisconsin czy Floryda[260][261]. Zgodnie z ostatecznymi wynikami wybor�w na Donalda Trumpa zag�osowa�o 62 979 879 os�b (45,95%), co by�o drugim rezultatem w g�osowaniu bezpo�rednim. Pierwszy przypad� kandydatce Partii Demokratycznej Hillary Clinton, kt�ra zdoby�a g�osy 65 845 063 os�b (48,03%). Trump wygra� jednak g�osowanie w Kolegium Elektor�w, otrzymuj�c 304 g�osy w stosunku do 227 g�os�w Clinton[262]. By� to pi�ty w historii Stan�w Zjednoczonych przypadek, w kt�rym zwyci�zca wybor�w przegrywa w g�osowaniu powszechnym, ale wygrywa w g�osowaniu elektorskim. Wcze�niej byli to John Quincy Adams (1824, przegrany � Andrew Jackson), Rutherford Hayes (1876, przegrany � Samuel J. Tilden), Benjamin Harrison (1888, przegrany � Grover Cleveland) i George W. Bush (2000, przegrany � Al Gore)[263][264].W wyborach, kt�re odby�y si� 8 listopada 2016 Donald Trump zwyci�y�, uzyskuj�c wi�cej ni� wymagana do zwyci�stwa wi�kszo�� 270 g�os�w elektorskich[259]. Wygran� w skali kraju zapewni�o Trumpowi niespodziewane zwyci�stwo w stanach znanych jako wahaj�ce si�, takich jak Pensylwania, Karolina P�nocna, Ohio, Wisconsin czy Floryda[260][261]. Zgodnie z ostatecznymi wynikami wybor�w na Donalda Trumpa zag�osowa�o 62 979 879 os�b (45,95%), co by�o drugim rezultatem w g�osowaniu bezpo�rednim. Pierwszy przypad� kandydatce Partii Demokratycznej Hillary Clinton, kt�ra zdoby�a g�osy 65 845 063 os�b (48,03%). Trump wygra� jednak g�osowanie w Kolegium Elektor�w, otrzymuj�c 304 g�osy w stosunku do 227 g�os�w Clinton[262]. By� to pi�ty w historii Stan�w Zjednoczonych przypadek, w kt�rym zwyci�zca wybor�w przegrywa w g�osowaniu powszechnym, ale wygrywa w g�osowaniu elektorskim. Wcze�niej byli to John Quincy Adams (1824, przegrany � Andrew Jackson), Rutherford Hayes (1876, przegrany � Samuel J. Tilden), Benjamin Harrison (1888, przegrany � Grover Cleveland) i George W. Bush (2000, przegrany � Al Gore)[263][264].W wyborach, kt�re odby�y si� 8 listopada 2016 Donald Trump zwyci�y�, uzyskuj�c wi�cej ni� wymagana do zwyci�stwa wi�kszo�� 270 g�os�w elektorskich[259]. Wygran� w skali kraju zapewni�o Trumpowi niespodziewane zwyci�stwo w stanach znanych jako wahaj�ce si�, takich jak Pensylwania, Karolina P�nocna, Ohio, Wisconsin czy Floryda[260][261]. Zgodnie z ostatecznymi wynikami wybor�w na Donalda Trumpa zag�osowa�o 62 979 879 os�b (45,95%), co by�o drugim rezultatem w g�osowaniu bezpo�rednim. Pierwszy przypad� kandydatce Partii Demokratycznej Hillary Clinton, kt�ra zdoby�a g�osy 65 845 063 os�b (48,03%). Trump wygra� jednak g�osowanie w Kolegium Elektor�w, otrzymuj�c 304 g�osy w stosunku do 227 g�os�w Clinton[262]. By� to pi�ty w historii Stan�w Zjednoczonych przypadek, w kt�rym zwyci�zca wybor�w przegrywa w g�osowaniu powszechnym, ale wygrywa w g�osowaniu elektorskim. Wcze�niej byli to John Quincy Adams (1824, przegrany � Andrew Jackson), Rutherford Hayes (1876, przegrany � Samuel J. Tilden), Benjamin Harrison (1888, przegrany � Grover Cleveland) i George W. Bush (2000, przegrany � Al Gore)[263][264].", { 1.0f,1.0f,m_renderTargetSize.x - 1.0f,m_renderTargetSize.y - 1.0f });


}

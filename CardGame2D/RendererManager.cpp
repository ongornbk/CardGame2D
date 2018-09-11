#include "stdafx.h"
#include "RendererManager.h"
#include "Direct2D.h"

void(*m_update)(void) = nullptr;
void(*m_render)(void) = nullptr;

void RendererManager::Update()
{
	m_update();
}

void RendererManager::Render()
{
	m_render();
}

RendererManager::RendererManager(void(*Update)(void),void(*Render)(void))
{

	m_update = Update;
	m_render = Render;
}


RendererManager::~RendererManager()
{
}

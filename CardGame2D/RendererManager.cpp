#include "stdafx.h"
#include "RendererManager.h"
#include "Direct2D.h"

void(*m_render)(void) = nullptr;

void RendererManager::Update()
{
}

void RendererManager::Render()
{
	m_render();
}

RendererManager::RendererManager(void(*Render)(void))
{
	m_render = Render;
}


RendererManager::~RendererManager()
{
}

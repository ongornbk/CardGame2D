#pragma once
#include <atomic>

namespace Global
{
	static std::atomic<void*> m_renderTarget = nullptr;
}
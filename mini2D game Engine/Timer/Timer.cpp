#include "Timer.h"
#include<SDL.h>

Timer* Timer::s_Instance = nullptr;

void Timer::Tick()
{
	m_DeltaTime = (SDL_GetTicks64() - m_LastTime) * (TARGET_FPS / 1000.0f);

	//����deltatime��С
	if (m_DeltaTime > TARGET_DELTATIME) {
		m_DeltaTime = 1.5f;
	}

	m_LastTime = SDL_GetTicks64();
}

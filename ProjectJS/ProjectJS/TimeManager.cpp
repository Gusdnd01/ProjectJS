#include "pch.h"
#include "TimeManager.h"
#include "Core.h"

void TimeManager::Init()
{
	m_dT = 0;
	m_llPrevCount = {};
	m_llCurCount = {};
	m_llFrequency = {};
	m_frameCount = 0;
	m_fps = 0;
	m_accFrameTime = 0.f;
	//현재 카운트의 틱을 가져온다. (지난 시간)
	// 1초 2초 이런 초가 아니고, Frequency로 알아야함
	QueryPerformanceCounter(&m_llPrevCount);
	
	//초당 카운트 횟수를 반환한다.
	//현재 타이머가 동작하는 주파수를 반환한다.
	QueryPerformanceFrequency(&m_llFrequency);

	
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	//DeltaTime
	m_dT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)/
		m_llFrequency.QuadPart;

	//FPS: Frame per second
	m_llPrevCount = m_llCurCount;
	//1. / m_dT;
	m_frameCount++;//프레임 호출 누적
	m_accFrameTime += m_dT;// 시간 누적
	if (m_accFrameTime >=1.f) {
		m_fps = m_frameCount / m_accFrameTime;
		m_accFrameTime = 0;
		m_frameCount = 0;
		static wchar_t titleBuf[50] = {};
		swprintf_s(titleBuf,L"FPS: %d, DT: %f", m_fps, m_dT);
		//wsprintf();
		SetWindowText(Core::GetInst()->GetHWnd(), titleBuf);
	}
}

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
	//���� ī��Ʈ�� ƽ�� �����´�. (���� �ð�)
	// 1�� 2�� �̷� �ʰ� �ƴϰ�, Frequency�� �˾ƾ���
	QueryPerformanceCounter(&m_llPrevCount);
	
	//�ʴ� ī��Ʈ Ƚ���� ��ȯ�Ѵ�.
	//���� Ÿ�̸Ӱ� �����ϴ� ���ļ��� ��ȯ�Ѵ�.
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
	m_frameCount++;//������ ȣ�� ����
	m_accFrameTime += m_dT;// �ð� ����
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

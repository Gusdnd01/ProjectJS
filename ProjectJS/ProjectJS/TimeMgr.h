#pragma once
class TimeMgr
{
	SINGLE(TimeMgr);
public:
	void Init();
	void Update();

public:
	const float& GetDT() const { return m_dT; }

private:
	//FPS
	//DT(1�����Ӵ� �ð�: DeltaTime)
	LARGE_INTEGER m_llPrevCount; //�����ð�
	LARGE_INTEGER m_llCurCount; //����ð�
	LARGE_INTEGER m_llFrequency;
	
	float m_dT;

	UINT m_fps;
	UINT m_frameCount; //������ ȣ�� üũ
	float m_accFrameTime; //�ð� ����

};


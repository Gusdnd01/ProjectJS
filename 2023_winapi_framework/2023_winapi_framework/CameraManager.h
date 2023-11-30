#pragma once
class Object;
class CameraManager
{
	SINGLE(CameraManager);


public:
	void Update();
public:
	void CaculateDiff();

public:
	void SetLookPos(const Vec2& _value) { 
		m_vLookPos = _value; 
		m_vCurLookPos = _value;
		m_vPrevLookPos = _value;

	}
	void SetTarget(Object* _value) { m_pTarget = _value; }

public:
	const Vec2& GetLookPos() { return m_vLookPos; }
	Object* GetTarget() { return m_pTarget; }
	Vec2 GetRenderPos(const Vec2& _value);

private:
	//������ ���� ��ġ(��¥�� 2D�� �������� �ۿ� �Ⱥ���.)
	Vec2 m_vLookPos;
	Vec2 m_vCurLookPos = Vec2(0.0f);
	Vec2 m_vPrevLookPos = Vec2(0.0f);

	//Ÿ�� ������Ʈ
	Object* m_pTarget;

	//��ġ ����
	Vec2 m_vDiffPos;
};


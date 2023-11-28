#pragma once
class Object;
class CameraManager
{
	SINGLE(CameraManager);

private:
	//������ ���� ��ġ(��¥�� 2D�� �������� �ۿ� �Ⱥ���.)
	Vec2 m_vLookPos;

	//Ÿ�� ������Ʈ
	Object* m_pTarget;

public:
	void Update();

public:
	void SetLookPos(const Vec2& _value) { m_vLookPos = _value; }
	void SetTarget(Object* _value) { m_pTarget = _value; }

public:
	const Vec2& GetLookPos() { return m_vLookPos; }
	Object* GetTarget() { return m_pTarget; }
};


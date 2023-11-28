#pragma once
class Object;
class CameraManager
{
	SINGLE(CameraManager);

private:
	//실제로 보는 위치(어짜피 2D라서 전방으로 밖에 안본다.)
	Vec2 m_vLookPos;

	//타겟 오브젝트
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


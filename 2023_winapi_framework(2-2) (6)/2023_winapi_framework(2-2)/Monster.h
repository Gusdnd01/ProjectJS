#pragma once
#include "Object.h"
class Monster : public Object
{
public:
	Monster();
	~Monster();
public:
	void Update() override;
public:
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
	void SetMoveDis(float _f) { m_fMaxDis = _f; }
	const float& GetSpeed() const { return m_fSpeed; }
public:
	virtual void OnCollisionEnter(Collider* _pOther);
	virtual void OnCollisionStay(Collider* _pOther);
	virtual void OnCollisionExit(Collider* _pOther);
private:
	float m_fSpeed; // ���� ���ǵ�
	Vec2 m_vCenterPos; // �߽� ��ġ
	float m_fMaxDis; // �̵��� �� �ִ� �ִ� �Ÿ�
	float m_fDir; // ����(-1: ����, 1: ������)
	int   m_iHp; // ü��
};


#pragma once
class Object;

class Collider
{
public:
	Collider();
	Collider(const Collider& _origin);
	~Collider();
	Collider& operator = (Collider& _origin) = delete;
public:
	void FinalUpdate();
	void Render(HDC _dc);
public:
	void EnterCollision(Collider* _pOther);
	void ExitCollision(Collider* _pOther);
	void StayCollision(Collider* _pOther);

public:
	void CheckPosition(Collider* _pOther);
	void ReleaseCheck();
	void CheckLeft(Collider* _pOther);
	void CheckRight(Collider* _pOther);
	void CheckTop(Collider* _pOther);
	void CheckBottom(Collider* _pOther);

public:
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetOffSetPos(Vec2 _vOffsetPos) 
	{ m_vOffsetPos = _vOffsetPos; }
	void SetCheckBottom(bool _value) { m_bCheckBottom = _value; }

	const Vec2& GetScale() const { return m_vScale; }
	const Vec2& GetOffSetPos() const { return m_vOffsetPos; }
	const Vec2& GetFinalPos() const 
	{ return m_vFinalPos; }
	const UINT& GetID() const { return m_ID; }
	Object* GetObj() const { return m_pOwner; }

	const bool& GetCheckLeft() const { return m_bCheckLeft; }
	const bool& GetCheckRight() const { return m_bCheckRight; }
	const bool& GetCheckTop() const { return m_bCheckTop; }
	const bool& GetCheckBottom() const { return m_bCheckBottom; }

private:
	UINT m_check;
	Object* m_pOwner;
	Vec2 m_vOffsetPos; // 오프셋
	Vec2 m_vFinalPos; // 파이널 위치
	Vec2 m_vScale; // 크기
	friend class Object;
	UINT m_ID; // 충돌체 ID값
	static UINT m_sNextID;
	bool m_bCheckLeft;
	bool m_bCheckRight;
	bool m_bCheckTop;
	bool m_bCheckBottom;
};


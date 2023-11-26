#pragma once
class Collider;
class Animator;
class RigidBody;
class Gravity;
class Object
{
public:
	Object();
	virtual ~Object();
//public:	// 크기, 위치
	//POINT m_ptPos;
	//POINT m_ptScale;
public:
	virtual void Update();
	virtual void FinalUpdate() final;
	virtual void Render(HDC _dc);
	
	void Component_Render(HDC _dc);

#pragma region Collider
public:
	virtual void EnterCollision(Collider* _pOther);
	virtual void ExitCollision(Collider* _pOther);
	virtual void StayCollision(Collider* _pOther);

public:
	virtual void CheckLeft(Collider* _pOther);
	virtual void CheckRight(Collider* _pOther);
	virtual void CheckTop(Collider* _pOther);
	virtual void CheckBottom(Collider* _pOther);
#pragma endregion

public:
	//Set
	void SetPos(Vec2 _vPos)		{ m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetName(wstring _name) { m_strName = _name; }

public:
	//Status
	const Vec2&		GetPos()	const { return m_vPos; }
	const Vec2&		GetScale()	const { return m_vScale; }
	const wstring&	GetName()	const { return m_strName; }
	bool			GetIsDead() const { return !m_IsAlive; }

public:
	//Components
	Collider*	GetCollider()	{ return m_pCollider; }
	Animator*	GetAnimator()	{ return m_pAnimator; }
	RigidBody*	GetRigidBody()	{ return m_cRb; }
	Gravity*	GetGravity()	{ return m_cGravity; }

private:
	void SetDead() { m_IsAlive = false; }
	friend class EventMgr;

public:
	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();
private:
	Vec2 m_vPos; // 위치
	Vec2 m_vScale; // 크기
	
	wstring m_strName; // 이름.
	bool m_IsAlive;

	Collider*	m_pCollider;
	Animator*	m_pAnimator;
	RigidBody*	m_cRb;
	Gravity*	m_cGravity;
};


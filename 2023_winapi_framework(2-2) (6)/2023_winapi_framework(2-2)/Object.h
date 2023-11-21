#pragma once
class Collider;
class Animator;
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

public:
	virtual void OnCollisionEnter(Collider* _pOther);
	virtual void OnCollisionStay(Collider* _pOther);
	virtual void OnCollisionExit(Collider* _pOther);
	
public:
	void Component_Render(HDC _dc);

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetScale() const { return m_vScale; }
	Collider* GetCollider() const 
	{ return m_pCollider; }
	Animator* GetAnimator() const 
	{ return m_animator; }
	const wstring& GetName() const { return m_strName; }
	void SetName(wstring _name) { m_strName = _name; }
	const bool& GetIsDead() const { return m_isAlive; }

private:
	void SetDead() { m_isAlive = false; }
	friend class EventManager;

public:
	void CreateCollider();
	void CreateAnimator();
private:
	Vec2 m_vPos; // 위치
	Vec2 m_vScale; // 크기
	Collider* m_pCollider;
	wstring m_strName;
	bool m_isAlive;
	Animator* m_animator;
};


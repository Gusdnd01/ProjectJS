#pragma once
class Object;
class Gravity
{
public:
	Gravity();
	~Gravity();

public:
	void FinalUpdate();

public:
	void SetGravity(float _value) { m_fGravity = _value; }

public:
	void OnGround(bool _value);

private:
	Object* m_pOwner;
	bool m_bOnGround;
	float m_fGravity;
	friend class Object;
};


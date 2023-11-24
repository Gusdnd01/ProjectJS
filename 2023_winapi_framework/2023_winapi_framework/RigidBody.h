#pragma once

class Object;
class RigidBody
{
public:
	RigidBody();
	~RigidBody();

public:
	const bool& IsGround() const { return m_bIsGround; }

public:
	void SetMass(float _mass) { m_fMass = _mass; }
	void SetGravity(float _gravity) { m_fGravity = _gravity; }
	void SetUseGrav(bool _value) { m_UseGravity = _value; }
	void SetIsGround(bool _value) { m_bIsGround = _value; }
	

public:
	void Update();

private:
	Object* m_pOwner;
	float m_fMass;
	float m_fGravity;
	bool m_UseGravity;
	bool m_bIsGround;
	friend class Object;
};


#pragma once

class Object;
class RigidBody
{
public:
	RigidBody();
	~RigidBody();

public:
	void SetMass(float _mass) { m_fMass = _mass; }
	void SetGravity(float _gravity) { m_fGravity = _gravity; }

public:
	void Update();

private:
	Object* m_pOwner;
	float m_fMass;
	float m_fGravity;
	bool m_UseGravity;
	friend class Object;
};


#pragma once

class Object;
class RigidBody
{
public:
	RigidBody();
	~RigidBody();

public:
	void FinalUpdate();
	void Move();

public:
	void AddForce(Vec2 _force) { m_vForce = m_vForce + _force; }

	void StopImmediately() {
		m_vAccel.y = 0.0f;
		m_vForce.y = 0.0f;
		m_vVelocity.y = 0.0f;
	};

	//Set Function
public:
	void SetMass(float _value) { m_fMass = _value; }
	void SetFriction(float _value) { m_fFriction = _value; }
	void SetMaxVelocity(float _value) { m_fMaxVelocity = _value; }

private:
	Object* m_pOwner;
	Vec2 m_vForce;
	Vec2 m_vAccel;
	Vec2 m_vVelocity;
	float m_fMass;
	float m_fFriction;
	float m_fMaxVelocity;
	friend class Object;
};


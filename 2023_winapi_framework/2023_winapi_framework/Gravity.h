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
	void OnGround(bool _value);
	
public:
	const bool& GetOnGround() const { return m_bOnGround; }

private:
	Object* m_pOwner;
	bool m_bOnGround;
	friend class Object;
};


#pragma once

class Object;
class GravityManager
{
	SINGLE(GravityManager);

public:
	void Update();

public:
	const float& GetGravity() const { return m_fGravity; }

private:
	vector<Object*> m_vGravityObj;
	float m_fGravity;
};


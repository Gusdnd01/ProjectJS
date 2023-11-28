#pragma once

class Object;
class RigidBodyManager
{
	SINGLE(RigidBodyManager);

public:
	void Update();

public:
	void AddGravObj(Object* _obj);

private:
	vector<Object*> m_vGravityObj;
};


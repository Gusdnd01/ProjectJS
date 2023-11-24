#pragma once

class Object;
class GravityManager
{
	SINGLE(GravityManager);

public:
	void Update();

public:
	void AddGravObj(Object* _obj);

private:
	vector<Object*> m_vGravityObj;
};


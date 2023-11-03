#pragma once

class Object;
class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Init() abstract;
	virtual void Update();
	virtual void Render(HDC _dc);
	virtual void Release();

private:
	//Object*	m_obj;
	vector<Object*> m_vObj[(UINT)OBJECT_GROUP::END];

public:
	void AddObj(Object* obj, OBJECT_GROUP type) {
		m_vObj[(UINT)type].push_back(obj);
	}
};


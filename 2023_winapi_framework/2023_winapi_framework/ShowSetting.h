#pragma once
class Texture;
class Object;
class ShowSetting
{
	SINGLE(ShowSetting);
public:
	bool IsActive = false;
public:
	void Init();
	void Render(HDC _dc);
	void Update();
	void AddObject(Object* _pObj, OBJECT_GROUP _eType)
	{
		m_vecObj[(UINT)_eType].push_back(_pObj);
	}
private:
	int moveY;
	int yIncrease;
	int arrowY;
	float bgmVolume;
	float effectVolume;
private:
	Texture* m_pTex;
	vector<Object*> m_vecObj[(UINT)OBJECT_GROUP::END];
};
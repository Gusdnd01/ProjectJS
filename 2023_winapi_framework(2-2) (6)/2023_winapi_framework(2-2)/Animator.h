#pragma once
class Object;
class Animation;
class Texture;
class Animator
{
public:
	Animator();
	~Animator();

public:
	//애니메이션 생성함수
	void CreateAnimation(const wstring& _strName, Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _frameCount, float _fDuration);

	Animation* FindAnimation(const wstring& _strName);
	void PlayAnim(const wstring& _strName, bool _bRepeat);

public:
	void Update();
	void Render(HDC _dc);

public:
	Object* GetOwner() const { return m_pOwner; }

private:
	map<wstring, Animation*> m_mapAnim;
	Animation* m_curAnimation;
	Object* m_pOwner;
	bool m_IsRepeat;
	friend class Object;
};


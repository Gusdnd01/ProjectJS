#pragma once
class Texture;
class Animator;

struct tAnimFrame
{
	Vec2 vLT;
	Vec2 vSlice;
	float fDuration;
};

class Animation
{
	Animation();
	~Animation();

public:
	void Update();
	void Render(HDC _dc);

public:
	void Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _frameCount, float _fDuration);

public:
	const wstring& GetName() const{ return m_strName; }
	void SetName(const wstring& _name) { m_strName = _name; }

private:
	UINT m_curFrame;
	float m_fAccTime;
	int m_repeatCnt;
	Texture* m_pTex;
	vector<tAnimFrame> m_vecAnimFrame;
	wstring m_strName;
	Animator* m_animator;
	friend class Animator;
};


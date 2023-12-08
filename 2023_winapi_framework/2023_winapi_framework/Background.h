#pragma once
class Texture;
class Background
{
	SINGLE(Background);

public:
	void Update();
	void Render(HDC _dc);

public:
	void SetFollowPos(const Vec2& _value) { m_vFollowPos = _value; }
	void SetTexture(Texture* _value) { m_pTex = _value; }

private:
	Vec2 m_vPos;
	Vec2 m_vScale;
	Vec2 m_vFollowPos;
	Texture* m_pTex;
};


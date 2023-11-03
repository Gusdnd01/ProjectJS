#pragma once
class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void Update();
	virtual void Render(HDC _dc);
public:
	void SetPos(Vector2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vector2 _vScale) { m_vScale = _vScale; }
	const Vector2& GetPos() const { return m_vPos; }
	const Vector2& GetScale() const { return m_vScale; }
private:
	Vector2 m_vPos;
	Vector2 m_vScale;
};


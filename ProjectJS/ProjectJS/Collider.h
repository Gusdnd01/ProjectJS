#pragma once

class Object;
class Collider
{
public:
	Collider();
	~Collider();

public:
	void FinalUpdate();
	void Render(HDC _dc);

public:
	void SetScale(Vector2 _vScale) { scale = _vScale; }
	void SetOffsetPos(Vector2 _vOffsetPos) { pos = _vOffsetPos; }
	const Vector2& GetScale() const { return scale; }
	const Vector2& GetOffsetPos() const { return pos; }

private:
	Object* owner;
	Vector2 pos;
	Vector2 finalPos;
	Vector2 scale;
	friend class Object;
};


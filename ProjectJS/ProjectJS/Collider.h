#pragma once
class Object;
class Collider
{
private:
	Object* owner;
	Vector2 pos;
	Vector2 bounds;

public:
	Collider();
	~Collider();

public:
	void LateUpdate();
	void Gizmos(HDC _dc);

public:
	bool IsCollision();

public:
	void SetOwner(Object* _owner) { owner = _owner; }

	void SetPos(Vector2 _pos) { pos = _pos; }
	void SetBounds(Vector2 _bounds) { bounds = _bounds; }

	const Vector2& GetPos() const { return pos; }
	const Vector2& GetBounds() const { return bounds; }
};


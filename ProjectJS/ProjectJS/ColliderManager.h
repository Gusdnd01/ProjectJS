#pragma once

class Collider;
class ColliderManager
{
	SINGLE(ColliderManager);

public:
	void Update();

public:
	void CheckGroup(OBJECT_GROUP _left, OBJECT_GROUP _right);
	void ResetGroup() {
		memset(m_checkLayer, 0, sizeof(UINT) * static_cast<UINT>(OBJECT_GROUP::END));
	}

private:
	vector<UINT> m_checkLayer[static_cast<UINT>(OBJECT_GROUP::END)];
};


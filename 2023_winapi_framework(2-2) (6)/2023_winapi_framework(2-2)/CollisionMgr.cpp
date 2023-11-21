#include "pch.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Scene.h"
#include "Collider.h"
void CollisionMgr::Update()
{
	for (UINT Row = 0; Row < (UINT)OBJECT_GROUP::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)OBJECT_GROUP::END; ++Col)
		{
			if (m_arrCheck[Row] & (1 << Col))
			{
				CollisionGroupUpdate((OBJECT_GROUP)Row, (OBJECT_GROUP)Col);
			}
		}
	}
}
void CollisionMgr::CollisionGroupUpdate(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight)
{
	std::shared_ptr<Scene> pCurScene = SceneMgr::GetInst()->GetCurScene();
	const vector<Object*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<Object*>& vecRight = pCurScene->GetGroupObject(_eRight);
	// �浹 �˻縦 �غ���.
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü�� ���� ���
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (vecRight[j]->GetCollider() == nullptr ||
				vecLeft[i] == vecRight[j])
				continue;
			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[j]->GetCollider();
			COLLIDER_ID colID;
			colID.left_id = pLeftCol->GetID();
			colID.right_id = pRightCol->GetID();

			auto iter = m_mapColInfo.find(colID.id);
			if (iter == m_mapColInfo.end()) {
				m_mapColInfo.insert({ colID.id,false });
				iter = m_mapColInfo.find(colID.id);
			}

			if (IsCollision(pLeftCol, pRightCol)) {
				if (iter->second) {
					if (vecLeft[i]->GetIsDead() || vecRight[i]->GetIsDead()) {
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
					}
					else {
						pLeftCol->OnCollisionStay(pRightCol);
						pRightCol->OnCollisionStay(pLeftCol);
					}
				}
				else
				{
					//if()
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);
					iter->second = true;
				}
			}
			else {
				if (iter->second) {
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;	
				}
			}
		}
	}
}

bool CollisionMgr::IsCollision(Collider* _pLeft, Collider* _pRight)
{
	Vec2 vLeftPos = _pLeft->GetFinalPos();
	Vec2 vRightPos = _pRight->GetFinalPos();
	Vec2 vLeftScale = _pLeft->GetScale();
	Vec2 vRightScale = _pRight->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.0f && abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.0f) {
		return true;
	}
	return false;
}

void CollisionMgr::CheckGroup(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight)
{
	// �������� ������ ���ô�.
	UINT Row = (UINT)_eLeft;
	UINT Col = (UINT)_eRight;
	Row = min(Row, Col);

	//// ��Ʈ ����
	// üũ�� �Ǿ��ִٸ�
	if (m_arrCheck[Row] & (1 << Col))
	{
		m_arrCheck[Row] &= ~(1 << Col);
	}
	// üũ�� �ȵǾ��ִٸ�r
	else
	{
		m_arrCheck[Row] |= (1 << Col);
	}
}

void CollisionMgr::CheckReset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)(OBJECT_GROUP::END));
}


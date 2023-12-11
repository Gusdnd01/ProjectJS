#include "pch.h"
#include "Core.h"
#include "ResMgr.h"
#include "TileManager.h"
#include "CameraManager.h"

#include "Ground.h"
#include "Collider.h"
#include "Gravity.h"
#include "Animator.h"
#include "Texture.h"

Ground::Ground()
	: m_pTex(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(GetCollider()->GetScale().x * 1.5f, GetCollider()->GetScale().y));
}

Ground::~Ground()
{
}

void Ground::Render(HDC _dc)
{
	//�̰� �� ��!���� �ȉҤ� �ä����Ĥ���
	// �̰� ���� �׸����� ũ�Ⱑ ȭ���� �Ѿ�� ����������.
	//Object::Render(_dc);

	if (m_pTex) {
		Vec2 originScale = GetScale();//���� ũ��!
		Vec2 originPos = GetPos();//����!

		Vec2 vScale = Vec2(originScale.y);
		Vec2 vPos = originPos + (Vec2(-originScale.x/2.0f, -vScale.y/2.0f));
		Vec2 vRenderPos = CameraManager::GetInst()->GetRenderPos(vPos);
		
		//Ÿ���� ���簢���̰�, scalex�� scaley�� ������ �������ٴ� �����Ͽ� �ݺ��Ѵ�.
		HBITMAP _backbit = CreateCompatibleBitmap(_dc, Core::GetInst()->GetResolution().x, Core::GetInst()->GetResolution().y);
		HDC _backDC = CreateCompatibleDC(_dc);
		SelectObject(_backDC, _backbit);
		PatBlt(_backDC
			, 0
			, 0
			, Core::GetInst()->GetResolution().x
			, Core::GetInst()->GetResolution().y
			, WHITENESS
		);
		if (originScale.x >= originScale.y) {
			for (int i = 0; i < (int)(originScale.x / originScale.y); ++i) {
				//���簢�� ũ��! x�� y���� ũ�ٴ� �����Ͽ�
				//��ġ ���ϴ� ����!
				vPos = originPos + (Vec2((vScale.x * i), -vScale.y / 2.0f));
				//�׷����� ��ġ
				vRenderPos = CameraManager::GetInst()->GetRenderPos(vPos);
				StretchBlt(_backDC
					, 0
					, 0
					, vScale.x
					, vScale.y
					, m_pTex->GetDC()
					, (int)(m_tileSlices.vLT.x)
					, (int)(m_tileSlices.vLT.y)
					, (int)(m_tileSlices.vSlice.x)
					, (int)(m_tileSlices.vSlice.y)
					, SRCCOPY
				);
				BitBlt(_dc
					, (int)(vRenderPos.x - originScale.x / 2.0f)
					, (int)(vRenderPos.y)
					, vScale.x
					, vScale.y
					, _backDC
					, 0
					, 0
					, SRCCOPY
				);

			}
		}
		if (originScale.x < originScale.y) {
			vScale = Vec2(originScale.x);
			for (int i = 0; i < (int)(originScale.y / originScale.x); ++i) {
				vPos = originPos + (Vec2(-vScale.x /2.0f, (vScale.y * i)));
				vRenderPos = CameraManager::GetInst()->GetRenderPos(vPos);
				StretchBlt(_backDC
					, 0
					, 0
					, vScale.x
					, vScale.y
					, m_pTex->GetDC()
					, (int)(m_tileSlices.vLT.x)
					, (int)(m_tileSlices.vLT.y)
					, (int)(m_tileSlices.vSlice.x)
					, (int)(m_tileSlices.vSlice.y)
					, SRCCOPY
				);
				BitBlt(_dc
					, (int)(vRenderPos.x)
					, (int)(vRenderPos.y - originScale.y / 2.0f)
					, vScale.x
					, vScale.y
					, _backDC
					, 0
					, 0
					, SRCCOPY
				);

			}
		}
		DeleteObject(_backbit);
		DeleteDC(_backDC);
	}
	else {
		Object::Render(_dc);
	}
	//Component_Render(_dc);
	//StretchBlt(_dc, )
}

void Ground::EnterCollision(Collider* _other)
{
	Object* obj = _other->GetObj();

	if (obj->GetName() == L"Player" && !GetCollider()->CheckBottom(_other)) {
		obj->GetGravity()->OnGround(true);

		Vec2 objPos = obj->GetPos();
		Vec2 objScale = obj->GetCollider()->GetScale();

		Vec2 pos = GetPos();
		Vec2 scale = GetCollider()->GetScale();
		float len = 0;
		len = objPos.y - pos.y;
		len = len <= 0 ? -len : len;
		float value = (objScale.y / 2.0f + scale.y / 2.0f) - len;

		objPos.y -= (value - 0.1f);
		obj->SetPos(objPos);
	}
}

void Ground::ExitCollision(Collider* _other)
{
	Object* obj = _other->GetObj();

	if (obj->GetName() == L"Player") {
		obj->GetGravity()->OnGround(false);
	}
}

void Ground::SetTiles(int _middle)
{
	m_pTex = TileManager::GetInst()->GetTileTexture();

	m_tileSlices = TileManager::GetInst()->GetTileData(_middle);
}

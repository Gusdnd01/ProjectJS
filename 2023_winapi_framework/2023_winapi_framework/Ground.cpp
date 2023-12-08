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
}

Ground::~Ground()
{
}

void Ground::Render(HDC _dc)
{
	//이거 왜 랜!더링 안됑ㅁ ㅓㄹ래ㅔㅎㅁ
	// 이거 내가 그리려는 크기가 화면을 넘어가서 문제였던거.
	//Object::Render(_dc);

	if (m_pTex) {
		Vec2 originScale = GetScale();//본래 크기!
		Vec2 tempPos = GetPos();
		Vec2 originPos = tempPos - (originScale / 2.0f);//원점!

		Vec2 vScale = Vec2(originScale.y);
		Vec2 vPos = originPos + (Vec2(0.0f, vScale.y/2.0f));
		Vec2 vRenderPos = CameraManager::GetInst()->GetRenderPos(vPos);
#pragma region Draw
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

		StretchBlt(_backDC
			, 0
			, 0
			, vScale.x
			, vScale.y
			, m_pTex->GetDC()
			, (int)(m_tileSlices[0].vLT.x)
			, (int)(m_tileSlices[0].vLT.y)
			, (int)(m_tileSlices[0].vSlice.x)
			, (int)(m_tileSlices[0].vSlice.y)
			, SRCCOPY
		);

		BitBlt(_dc
			, (int)(vRenderPos.x - vScale.x / 2.0f)
			, (int)(vRenderPos.y - vScale.y / 2.0f)
			, vScale.x
			, vScale.y
			, _backDC
			, 0
			, 0
			, SRCCOPY
		);
#pragma endregion
		//타일이 정사각형이고, scalex가 scaley로 나누어 떨어진다는 가정하에 반복한다.
		for (int i = 1; i < (int)(originScale.x / originScale.y) ; ++i) {
			//정사각형 크기! x가 y보다 크다는 가정하에

			//위치 구하는 공식!
			vPos = originPos + (Vec2(vScale.x * i, vScale.y / 2.0f));
			//그려지는 위치
			vRenderPos = CameraManager::GetInst()->GetRenderPos(vPos);
#pragma region Draw
			PatBlt(_backDC
				, 0
				, 0
				, Core::GetInst()->GetResolution().x
				, Core::GetInst()->GetResolution().y
				, WHITENESS
			);

			StretchBlt(_backDC
				, 0
				, 0
				, vScale.x
				, vScale.y
				, m_pTex->GetDC()
				, (int)(m_tileSlices[1].vLT.x)
				, (int)(m_tileSlices[1].vLT.y)
				, (int)(m_tileSlices[1].vSlice.x)
				, (int)(m_tileSlices[1].vSlice.y)
				, SRCCOPY
			);

			BitBlt(_dc
				, (int)(vRenderPos.x - vScale.x / 2.0f)
				, (int)(vRenderPos.y - vScale.y / 2.0f)
				, vScale.x
				, vScale.y
				, _backDC
				, 0
				, 0
				, SRCCOPY
			);
#pragma endregion
		}

		vPos = originPos + Vec2(vScale.x * ((originScale.x / originScale.y)), vScale.y / 2.0f);
		vRenderPos = CameraManager::GetInst()->GetRenderPos(vPos);

#pragma region Draw

		StretchBlt(_backDC
			, 0
			, 0
			, vScale.x
			, vScale.y
			, m_pTex->GetDC()
			, (int)(m_tileSlices[2].vLT.x)
			, (int)(m_tileSlices[2].vLT.y)
			, (int)(m_tileSlices[2].vSlice.x)
			, (int)(m_tileSlices[2].vSlice.y)
			, SRCCOPY
		);

		BitBlt(_dc
			, (int)(vRenderPos.x - vScale.x / 2.0f)
			, (int)(vRenderPos.y - vScale.y / 2.0f)
			, vScale.x
			, vScale.y
			, _backDC
			, 0
			, 0
			, SRCCOPY
		);

		DeleteObject(_backbit);
		DeleteDC(_backDC);
#pragma endregion
	}
	else {
		Object::Render(_dc);
	}

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

void Ground::SetTiles(int _first, int _middle, int _last)
{
	m_pTex = TileManager::GetInst()->GetTileTexture();

	m_tileSlices.push_back(TileManager::GetInst()->GetTileData(_first));
	m_tileSlices.push_back(TileManager::GetInst()->GetTileData(_middle));
	m_tileSlices.push_back(TileManager::GetInst()->GetTileData(_last));
}

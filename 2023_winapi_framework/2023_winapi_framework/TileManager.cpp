#include "pch.h"
#include "TileManager.h"
#include "ResMgr.h"
#include "Texture.h"

void TileManager::Init()
{
	m_pTileTexture = ResMgr::GetInst()->TexLoad(L"main_tile", L"Texture\\maptile.bmp");

	int width = m_pTileTexture->GetWidth();
	int height = m_pTileTexture->GetHeight();
	int cnt = 1;

	for (int i = 0; i < width / 16; ++i) {
		for (int j = 0; j < height / 16; ++j) {
			tTileSlice t = { Vec2(16.0f * j, 16.0f * i), Vec2(16.0f, 16.0f) };
			m_tileData.insert(make_pair(cnt, t));
			cnt++;
		}
	}
}
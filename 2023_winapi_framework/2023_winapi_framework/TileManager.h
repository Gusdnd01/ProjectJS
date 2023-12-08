#pragma once


class Texture;
class TileManager
{
	SINGLE(TileManager);

public:
	void Init();

public:
	const tTileSlice& GetTileData(int index) { return m_tileData[index]; }
	Texture* GetTileTexture() { return m_pTileTexture; }

private:
	Texture* m_pTileTexture;
	map<int, tTileSlice> m_tileData;
};

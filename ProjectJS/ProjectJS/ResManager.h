#pragma once
class Texture;
class ResManager
{
	SINGLE(ResManager);
public:
	Texture* TexLoad(const wstring& key, const wstring& relativePath);
	Texture* TexFind(const wstring& key);

	void Release();

private:
	map<wstring, Texture*> mapTex;
};


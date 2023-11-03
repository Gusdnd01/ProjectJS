#include "pch.h"
#include "ResManager.h"
#include "PathManager.h"
#include "Texture.h"

Texture* ResManager::TexLoad(const wstring& key, const wstring& relativePath)
{
	Texture* ptex = TexFind(key);
	if (ptex != nullptr) {
		return ptex;
	}
	wstring strFilePath = PathManager::GetInst()->GetResPath();
	strFilePath += relativePath;
	ptex=new Texture;
	ptex->Load(strFilePath);
	ptex->SetKey(key);
	ptex->SetRelativeKey(relativePath);
	mapTex.insert({ key,ptex });

	return ptex;
}

Texture* ResManager::TexFind(const wstring& key)
{
	auto iter = mapTex.find(key);
	if (iter != mapTex.end()) {
		return iter->second;
	}
	return nullptr;
}

void ResManager::Release()
{
	for (auto iter = mapTex.begin(); iter != mapTex.end(); iter++) {
		delete iter->second;
	}
}

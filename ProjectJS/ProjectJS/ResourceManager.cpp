#include "pch.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include "Texture.h"

Texture* ResourceManager::TexLoad(const wstring& key, const wstring& relativePath)
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

Texture* ResourceManager::TexFind(const wstring& key)
{
	auto iter = mapTex.find(key);
	if (iter != mapTex.end()) {
		return iter->second;
	}
	return nullptr;
}

void ResourceManager::Release()
{
	for (auto iter = mapTex.begin(); iter != mapTex.end(); iter++) {
		delete iter->second;
	}
}

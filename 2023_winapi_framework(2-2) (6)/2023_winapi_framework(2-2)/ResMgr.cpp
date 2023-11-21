#include "pch.h"
#include "ResMgr.h"
#include "PathMgr.h"
#include "Texture.h"
Texture* ResMgr::TexLoad(const wstring& _StrKey, const wstring& _strRelativePath)
{
    // ��ã������ �ְ�
    Texture* pTex = TexFind(_StrKey);
    if (nullptr != pTex)
        return pTex;
    // ��� �ϼ�
    wstring strFilePath = PathMgr::GetInst()->GetResPath();
    strFilePath += _strRelativePath;
    // 
    pTex = new Texture;
    pTex->Load(strFilePath);
    pTex->SetKey(_StrKey);
    pTex->SetRelativePath(_strRelativePath);
    m_mapTex.insert({ _StrKey,pTex });
    return pTex;
}

Texture* ResMgr::TexFind(const wstring& _strKey)
{
    auto iter = m_mapTex.find(_strKey);
    if (iter != m_mapTex.end())
    {
        return iter->second;
    }
    return nullptr;
}

void ResMgr::Release()
{
    map<wstring, Texture*>::iterator iter;
    for (iter = m_mapTex.begin(); iter != m_mapTex.end(); ++iter)
        delete iter->second;
}

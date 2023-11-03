#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TestScene.h"

void SceneManager::Init()
{
	m_curScene = nullptr;
	//�� ���
	RegisterScene(L"TestScene", make_shared<TestScene>());

	//�� �ε�
	LoadScene(L"TestScene");
}

void SceneManager::Update()
{
	m_curScene->Update();
}

void SceneManager::Render(HDC _dc)
{
	m_curScene->Render(_dc);
}

void SceneManager::LoadScene(const wstring& _scenename)
{
	//���� ������
	if (m_curScene != nullptr) {
		m_curScene->Release();
		m_curScene = nullptr;
	}
	auto iter = m_mapScenes.find(_scenename);
	if (iter != m_mapScenes.end()) {
		m_curScene = iter->second;
		m_curScene->Init();
	}
}

void SceneManager::RegisterScene(const wstring& _scenename, const shared_ptr<Scene>& _scene)
{
	m_mapScenes.insert(m_mapScenes.end(), { _scenename, _scene });
}

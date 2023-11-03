#include "pch.h"
#include "Scene.h"
#include "Object.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i) {
		for (size_t j = 0; j < m_vObj[i].size(); ++j) {
			m_vObj[i][j]->Update();
		}
	}
}

void Scene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i) {
		for (size_t j = 0; j < m_vObj[i].size(); ++j) {
			m_vObj[i][j]->Render(_dc);
		}
	}
}

void Scene::Release()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i) {
		for (size_t j = 0; j < m_vObj[i].size(); ++j) {
			delete m_vObj[i][j];
		}
		m_vObj[i].clear();
	}
}

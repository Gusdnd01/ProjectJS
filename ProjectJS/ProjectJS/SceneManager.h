#pragma once

class Scene;
class SceneManager
{
	SINGLE(SceneManager);
public:
	void Init();
	void Update();
	void Render(HDC _dc);

public:
	void LoadScene(const wstring& _scenename);
	void RegisterScene(const wstring& _scenename, const shared_ptr<Scene>& _scene);

public:
	const shared_ptr<Scene>& GetCurScene() const {
		return m_curScene;
	}
	//�ٲٴ°�
	//������

private:
	shared_ptr<Scene> m_curScene; //���� ��

	//������ �����ϴ� ��
	map<wstring, shared_ptr<Scene>> m_mapScenes;
};


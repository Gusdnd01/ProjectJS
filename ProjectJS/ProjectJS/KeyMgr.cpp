#include "pch.h"
#include "KeyMgr.h"
#include "Core.h"

void KeyMgr::Init()
{
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i) {
		m_vKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}

	m_ptMouse = {};
}

void KeyMgr::Update()
{
	HWND hWnd = GetFocus();
	if (hWnd != nullptr) {
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i) {
			if (GetAsyncKeyState(m_arrVKKey[i])) {
				//������ ���Ⱦ�
				if (m_vKey[i].IsPrevCheck) {
					m_vKey[i].eState = KEY_STATE::PRESS;
				}
				else {
					m_vKey[i].eState = KEY_STATE::DOWN;
				}
				m_vKey[i].IsPrevCheck = true;
			}
			else {
				if (m_vKey[i].IsPrevCheck) {
					m_vKey[i].eState = KEY_STATE::UP;
				}
				else {
					m_vKey[i].eState = KEY_STATE::NONE;
				}
				m_vKey[i].IsPrevCheck = false;
			}
		}

		//Mouse
		GetCursorPos(&m_ptMouse); //���콺 Ŀ�� ��ǥ
		//�츮�� ���� ������ â �������� ��ǥ ����
		ScreenToClient(Core::GetInst()->GetHWnd(), &m_ptMouse);
	}
	//��Ŀ���� �����Ǿ��� ��
	else {
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i) {
			m_vKey[i].IsPrevCheck = false;
			if (m_vKey[i].eState == KEY_STATE::PRESS ||
				m_vKey[i].eState == KEY_STATE::DOWN)
				m_vKey[i].eState = KEY_STATE::UP;
			if (m_vKey[i].eState == KEY_STATE::UP)
				m_vKey[i].eState = KEY_STATE::NONE;
		}
	}
}


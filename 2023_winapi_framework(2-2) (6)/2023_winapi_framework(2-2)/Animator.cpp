#include "pch.h"
#include "Animator.h"
#include "Animation.h"
#include "Texture.h"

Animator::Animator()
	: m_mapAnim{}
	, m_pOwner(nullptr)
	, m_curAnimation(nullptr)
	, m_IsRepeat(false)

{
}

Animator::~Animator()
{
	map<wstring, Animation*>::iterator iter;
	for (iter = m_mapAnim.begin(); iter != m_mapAnim.end(); ++iter) {
		if (iter->second != nullptr) {
			delete iter->second;
		}
		m_mapAnim.clear();
	}
}

void Animator::CreateAnimation(const wstring& _strName, Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _frameCount, float _fDuration)
{
	Animation* pAnim = FindAnimation(_strName);

	if (pAnim != nullptr) {
		return;
	}
	
	pAnim = new Animation;
	pAnim->SetName(_strName);
	pAnim->m_animator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _frameCount, _fDuration);
	m_mapAnim.insert({ _strName, pAnim });

}

Animation* Animator::FindAnimation(const wstring& _strName)
{
	map<wstring, Animation*>::iterator iter = m_mapAnim.find(_strName);
	if (iter == m_mapAnim.end()) {
		return nullptr;
	}
	return iter->second;
}

void Animator::PlayAnim(const wstring& _strName, bool _bRepeat)
{
	m_curAnimation = FindAnimation(_strName);
	m_IsRepeat = _bRepeat;
}



void Animator::Update()
{
	if (m_curAnimation != nullptr)
		m_curAnimation->Update();
}

void Animator::Render(HDC _dc)
{
	if (m_curAnimation != nullptr)
		m_curAnimation->Render(_dc);
}

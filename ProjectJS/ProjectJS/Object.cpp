#include "pch.h"
#include "Object.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "Texture.h"

Object::Object()
: m_vPos{}
, m_vScale{}
{

}

Object::Object(Texture* _tex)
{
}

Object::~Object()
{

}

void Object::Update()
{
}

void Object::Render(HDC _dc)
{
	//Render
	RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
}

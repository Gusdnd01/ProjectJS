#include "pch.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

Object::Object()
: m_vPos{}
, m_vScale{}
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

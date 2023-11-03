#include "pch.h"
#include "Texture.h"
#include <assert.h>
#include "Core.h"

Texture::Texture() 
	: bit(0)
	, dc(0)
	, bitInfo{}
{
}

Texture::~Texture()
{
	DeleteDC(dc);
	DeleteObject(bit);
}

void Texture::Load(const wstring& strFile)
{
	bit = (HBITMAP)LoadImage(nullptr, strFile.c_str(), IMAGE_BITMAP, 0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	assert(bit);

	dc = CreateCompatibleDC(Core::GetInst()->GetMainDC());
	SelectObject(dc, bit);
	GetObject(bit, sizeof(BITMAP), &bitInfo);
}

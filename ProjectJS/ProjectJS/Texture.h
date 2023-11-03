#pragma once
#include "Res.h"
class Texture :
    public Res
{
public:
    Texture();
    ~Texture();

public:
    void Load(const wstring& strFile);
    const int& GetWidth() const { return bitInfo.bmWidth; }
    const int& GetHeight() const { return bitInfo.bmHeight; }
    const HDC& GetDC() const { return dc; }

private:
    HBITMAP bit;
    HDC     dc;
    BITMAP  bitInfo;
};


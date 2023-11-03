#pragma once
class Res
{
public:
	Res();
	~Res();

public:
	void SetKey(const wstring& key) { strKey = key; }
	void SetRelativeKey(const wstring& key) { strRelativePath = key; }
	const wstring& GetKey() const { return strKey; }
	const wstring& GetRelativeKey() const { return strRelativePath; }

private:
	wstring strKey;
	wstring strRelativePath;
};


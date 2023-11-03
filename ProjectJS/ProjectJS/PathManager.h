#pragma once
class PathManager
{
	SINGLE(PathManager)
public:
	void Init();
	const wchar_t* GetResPath() const {
		return strResPath;
	}
private:
	wchar_t strResPath[255];
};


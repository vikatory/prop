// -------------------------------------------------------------------------------
// @Author      : hejia
// @Created     : 2015-05-30 21:11
// @Desc        :
// -------------------------------------------------------------------------------

#pragma once
#include "sys.h"
#include "QFile.h"
#include <windows.h>

#define MAX_PATH          260

std::string getCurAppPath(void)  // ”≈ªØ
{
	TCHAR szAppDir[MAX_PATH] = { 0 };
	if (!GetModuleFileName(NULL, szAppDir, MAX_PATH))
		return "";
	int nEnd = 0;
	for (int i = 0; szAppDir[i]; i++)
	{
		if (szAppDir[i] == '\\')
			nEnd = i;
	}
	szAppDir[nEnd] = 0;
	int iLen = 2 * wcslen(szAppDir);
	char* chRtn = new char[iLen + 1];
	wcstombs(chRtn, szAppDir, iLen + 1);
	std::string strPath = chRtn;
	delete[] chRtn;
	chRtn = NULL;
	char fuldir[MAX_PATH] = { 0 };
	_fullpath(fuldir, strPath.c_str(), MAX_PATH);
	return fuldir;
}


std::string& replaceAll(std::string& str, const std::string& old_value, const std::string& new_value)
{
	size_t start = 0;
	while (true)
	{
		size_t pos = 0;
		if ((pos = str.find(old_value, start)) != std::string::npos) {
			str.replace(pos, old_value.length(), new_value);
			start = pos + new_value.length();
		}
		else break;
	}
	return str;
}

std::string getAppPath()
{
	std::string appPath = getCurAppPath();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	appPath.append("/../");
#endif
	appPath = replaceAll(appPath, "\\", "/");
	appPath = QFileInfo(appPath).absolutePath();
	appPath.append("prop/");
	return appPath;
}

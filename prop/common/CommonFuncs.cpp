// -------------------------------------------------------------------------------
// @Author      : hejia
// @Created     : 2015/2/12
// @Desc        :
// -------------------------------------------------------------------------------

#pragma once
#include "CommonFuncs.h"
#include <tchar.h>
#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include "QFile.h"
//#include "SimpleSymbolEngine.h"
using namespace std;


// 0 = ��ɫ    1 = ��ɫ     2 = ��ɫ    3 = ����ɫ
// 4 = ��ɫ    5 = ��ɫ     6 = ��ɫ    7 = ��ɫ
// 8 = ��ɫ    9 = ����ɫ   A = ����ɫ  B = ��ǳ��ɫ
// C = ����ɫ  D = ����ɫ   E = ����ɫ  F = ����ɫ
// FOREGROUND_BLUE      0x0001
// FOREGROUND_GREEN     0x0002
// FOREGROUND_RED       0x0004
// FOREGROUND_INTENSITY 0x0008 ��ɫ
// BACKGROUND_BLUE      0x0010
// BACKGROUND_GREEN     0x0020
// BACKGROUND_RED       0x0040
// BACKGROUND_INTENSITY 0x0080
struct ConsoleColor {
    string name;
    WORD color;
    bool isBackColor;
};

static ConsoleColor consoleColors[] = {
	{ "red", FOREGROUND_RED, false },
	{ "red_h", FOREGROUND_RED | FOREGROUND_INTENSITY, false },
	{ "green", FOREGROUND_GREEN, false },
	{ "green_h", FOREGROUND_GREEN | FOREGROUND_INTENSITY, false },
	{ "blue", FOREGROUND_BLUE, false },
	{ "blue_h", FOREGROUND_BLUE | FOREGROUND_INTENSITY, false },
	{ "yellow", FOREGROUND_RED | FOREGROUND_GREEN, false },
	{ "yellow_h", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, false },
	{ "cyan", FOREGROUND_GREEN | FOREGROUND_BLUE, false },
	{ "cyan_h", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, false },
	{ "magenta", FOREGROUND_BLUE | FOREGROUND_RED, false },
	{ "magenta_h", FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY, false },
	{ "white", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, false },
	{ "white_h", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, false },
	{ "red", BACKGROUND_RED, true },
	{ "red_h", BACKGROUND_RED | BACKGROUND_INTENSITY, true },
	{ "green", BACKGROUND_GREEN, true },
	{ "green_h", BACKGROUND_GREEN | BACKGROUND_INTENSITY, true },
	{ "blue", BACKGROUND_BLUE, true },
	{ "blue_h", BACKGROUND_BLUE | BACKGROUND_INTENSITY, true },
	{ "yellow", BACKGROUND_RED | BACKGROUND_GREEN, true },
	{ "yellow_h", BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY, true },
	{ "cyan", BACKGROUND_GREEN | BACKGROUND_BLUE, true },
	{ "cyan_h", BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY, true },
	{ "magenta", BACKGROUND_BLUE | BACKGROUND_RED, true },
	{ "magenta_h", BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY, true },
	{ "white", BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE, true },
	{ "white_h", BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY, true },
};

WORD getForeColor(char *foreColor)
{
	for (int i = 0; i < sizeof(consoleColors) / sizeof(consoleColors[0]); ++i)
	{
		if (!consoleColors[i].isBackColor)
		{
			if (consoleColors[i].name == string(foreColor))
				return consoleColors[i].color;
		}
	}
	return 0x0;

}

WORD getBackColor(char *backColor)
{
	for (int i = 0; i < sizeof(consoleColors) / sizeof(consoleColors[0]); ++i)
	{
		if (consoleColors[i].isBackColor)
		{
			if (consoleColors[i].name == string(backColor))
				return consoleColors[i].color;
		}
	}
	return 0x0;
}

void resetConsole() //�������ִ�й����в�Ҫ�������
{
    SetConsoleTitle(L"����̨");
    system("color 80 ");
    //system("mode con cols=120 lines=200 ");
}


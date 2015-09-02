#ifndef __COMMON_FUNC_H__
#define __COMMON_FUNC_H__
#include <windows.h>
#include <iostream>
#include <string>

void resetConsole();
WORD getForeColor(char *foreColor);
WORD getBackColor(char *backColor);


// 模板定义和实现要在一起？
template<typename AnyType>
void printc(AnyType text, char *textColor, char *backColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (handle == 0)
		return ;
	WORD fore = getForeColor(textColor);
	WORD back = getBackColor(backColor);

	CONSOLE_SCREEN_BUFFER_INFO console_info;
	//GetConsoleScreenBufferInfo(handle, &console_info);
	SetConsoleTextAttribute(handle, fore | back | 128 );
	std::cout << text;
	SetConsoleTextAttribute(handle, 128);
	//CloseHandle(handle);
}

#endif // __COMMON_FUNC_H__


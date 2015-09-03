#pragma once

#include <string>
#include "str.h"
#include "billcore.h"

class CBillApp
{
public:
	CBillApp();
	~CBillApp();
	void run();
	void exit();

private:
	void loop();
	std::string input();
	void processCmd(std::string cmd);

	

private:
	const size_t MENU_MAIN1  = 0x1;
	const size_t MENU_TRADE2 = 0x2;
	const size_t MENU_MODIFY = 0x2;

	bool isExit = false;
	size_t m_MenuState = 0;
	CBill * m_Bill = nullptr;
};



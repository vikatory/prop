#pragma once

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include "CommonFuncs.h"
#include "game.h"
#include "bill.h"

int _tmain(int argc, _TCHAR* argv[])
{
	resetConsole();

	//str�����

	//GameApp *pGameInstance = new GameApp();
	//pGameInstance->startup();
	//delete pGameInstance;

	CBillApp *pBillInstance = new CBillApp();
	pBillInstance->run();
	delete pBillInstance;

	return 0;
}


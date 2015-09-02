// -------------------------------------------------------------------------------
// @Author      : hejia
// @Created     : 2015-05-30 17:40
// @Desc        :
// -------------------------------------------------------------------------------

#pragma once
#include "singleton.h"
#include <iostream>
using namespace std;

Singleton* Singleton::_instance = 0;

Singleton::Singleton()
{
	cout << "Singleton...." << endl;
}

Singleton* Singleton::GetInstance()
{
	if (_instance == 0)
	{
		_instance = new Singleton();
	}
	return _instance;
}

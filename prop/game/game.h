#pragma once

#include <string>

class GameApp
{
public:
	GameApp();
	~GameApp();
	void startup();
	void loop();
	void exit();
private:


private:
	bool isExit = false;
	
};



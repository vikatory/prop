#include "game.h"

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

void GameApp::startup()
{
	loop();
}

void GameApp::loop()
{
	while (!isExit)
	{

	}
}

void GameApp::exit()
{
	isExit = true;
}
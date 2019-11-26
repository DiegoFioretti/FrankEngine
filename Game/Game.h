#ifndef GAME_H
#define GAME_H
#pragma once
#include <BaseGame.h>
class BASEGAMELIB Game : public BaseGame
{
public:
	Game();
	~Game();
	bool Start();
	bool Stop();
	bool Update();
	void Draw();
};
#endif
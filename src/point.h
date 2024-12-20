#pragma once
#include "Game.h"
#include <vector>
#include <iostream> 
#include <string>
using namespace std;
class Point : public Game {
public:
	Point();
	void Drawscore();
private:
	vector<int> highscores;
	Game hey;
};
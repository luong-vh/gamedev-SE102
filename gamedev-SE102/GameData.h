#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "debug.h"

#define FILE_PATH "GameData.txt"

using namespace std;
class CGameData
{
public:
	static int score;
	static int coin;
	static void SetScore(int _score);

	static void SetCoin(int _coin);
	static void AddScore(int _score);
	static void AddCoin(int _coin);
	static void InitData();
	static void SaveData();
	
	static void LoadData();
	
};


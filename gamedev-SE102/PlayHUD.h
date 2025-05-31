#pragma once
#include "Sprites.h"
#include "HUDTile.h"
#include "GameData.h"

#define ID_NUMBER_0		21000000
#define ID_NUMBER_1		21000001
#define ID_NUMBER_2		21000002
#define ID_NUMBER_3		21000003
#define ID_NUMBER_4		21000004
#define ID_NUMBER_5		21000005
#define ID_NUMBER_6		21000006
#define ID_NUMBER_7		21000007
#define ID_NUMBER_8		21000008
#define ID_NUMBER_9		21000009
#define ID_HUD_BACKGROUND	20000000
#define ID_HUD_PAUSE_TEXT 	20000001
#define ID_HUD_GAMEOVER_TEXT 20000002

#define ID_CARD_HUD_1 140000002
#define ID_CARD_HUD_2 140000003
#define ID_CARD_HUD_3 140000004

#define ID_HUD_POWERUP 20000003
#define ID_HUD_FULL_POWER 20000004
using namespace std;
class CPlayHUD
{
	static CPlayHUD* __instance;
	vector<CHUDTile*> coin;
	vector<CHUDTile*> score;
	vector<CHUDTile*> time;
	vector<CHUDTile*> powers;

	CHUDTile* background;
	CHUDTile* pauseText;
	CHUDTile* gameOverText;
	CHUDTile* card;
	CHUDTile* powerFull;
	float drawCardTime = 0;
	float drawPowerFullTime = 0;
	int power;
public:
	CPlayHUD();
	static CPlayHUD* GetInstance();
	void Render();
	void RenderWhilePaused();
	void RenderWhileGameOver();
	void SetCoin(int coin);
	void SetScore(int score);
	void SetTime(int time);
	void AddCard(int id);
	void Update(DWORD dt);
	void Clear() {
		delete __instance;
		__instance = NULL;
	}
	void SetPower(int p) {
		power = p;
		if (p != 6) drawPowerFullTime = 500;
	}
};


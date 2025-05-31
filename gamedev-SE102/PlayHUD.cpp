#include "PlayHUD.h"
#include <string>
CPlayHUD* CPlayHUD::__instance = NULL;
CPlayHUD::CPlayHUD()
{
	background = new CHUDTile(CSprites::GetInstance()->Get(ID_HUD_BACKGROUND), 128, 16);
	pauseText = new CHUDTile(CSprites::GetInstance()->Get(ID_HUD_PAUSE_TEXT), 128, 130);
	gameOverText = new CHUDTile(CSprites::GetInstance()->Get(ID_HUD_GAMEOVER_TEXT), 128, 130);

	for (int i = 0; i < 7; i++)
	{
		score.push_back(new CHUDTile(CSprites::GetInstance()->Get(ID_NUMBER_0), 66 + 8 * i, 11));
	}
	for (int i = 0; i < 2; i++)
	{
		coin.push_back(new CHUDTile(CSprites::GetInstance()->Get(ID_NUMBER_0), 146 + 8 * i, 19));
	}
	for (int i = 0; i < 3; i++)
	{
		time.push_back(new CHUDTile(CSprites::GetInstance()->Get(ID_NUMBER_0), 138 + 8 * i, 11));
	}
	for (int i = 0; i < 6; i++) {
		powers.push_back(new CHUDTile(CSprites::GetInstance()->Get(ID_HUD_POWERUP), 66 + 8 * i, 19));
	}
	powerFull = new CHUDTile(CSprites::GetInstance()->Get(ID_HUD_FULL_POWER), 120 , 19);
	CGameData::LoadData();
	SetCoin(CGameData::coin);
	SetScore(CGameData::score);
	card = NULL;
	power = 0;
}

CPlayHUD* CPlayHUD::GetInstance()
{
	if (__instance == NULL) __instance = new CPlayHUD();
	return __instance;
}

void CPlayHUD::Render()
{
	background->Draw();
	for (int i = 0; i < score.size(); i++)
	{
		score[i]->Draw();
	}
	for (int i = 0; i < coin.size(); i++)
	{
		coin[i]->Draw();
	}
	for (int i = 0; i < time.size(); i++)
	{
		time[i]->Draw();
	}
	for (int i = 0; i < power; i++) {
		powers[i]->Draw();
	}
	if (card && drawCardTime >0) card->Draw();
	if (power  == 6 && drawPowerFullTime>0) powerFull->Draw();
}

void CPlayHUD::RenderWhilePaused()
{
	Render();
	pauseText->Draw();
	
}

void CPlayHUD::RenderWhileGameOver()
{
	Render();
	gameOverText->Draw();
}

void CPlayHUD::SetCoin(int coinValue)
{
	string coinStr = to_string(coinValue);
	while (coinStr.length() < 2)
		coinStr = "0" + coinStr;
	if (coinStr.length() > 2)
		coinStr = coinStr.substr(coinStr.length() - 2, 2);
	for (int i = 0; i < 2; i++)
	{
		int digit = coinStr[i] - '0';
		int spriteId = ID_NUMBER_0 + digit;
		coin[i]->SetSprite(CSprites::GetInstance()->Get(spriteId));
	}
}

void CPlayHUD::SetScore(int scoreValue)
{
	string scoreStr = to_string(scoreValue);
	while (scoreStr.length() < 7)
		scoreStr = "0" + scoreStr;
	if (scoreStr.length() > 7)
		scoreStr = scoreStr.substr(scoreStr.length() - 7, 7);
	for (int i = 0; i < 7; i++)
	{
		int digit = scoreStr[i] - '0'; 
		int spriteId = ID_NUMBER_0 + digit;
		score[i]->SetSprite(CSprites::GetInstance()->Get(spriteId));
	}
}

void CPlayHUD::SetTime(int timeValue)
{
	string timeStr = to_string(timeValue);
	while (timeStr.length() < 3)
		timeStr = "0" + timeStr;
	if (timeStr.length() > 3)
		timeStr = timeStr.substr(timeStr.length() - 3, 3);
	for (int i = 0; i < 3; i++)
	{
		int digit = timeStr[i] - '0';
		int spriteId = ID_NUMBER_0 + digit;
		time[i]->SetSprite(CSprites::GetInstance()->Get(spriteId));
	}
}

void CPlayHUD::AddCard(int id)
{
	card = new CHUDTile(CSprites::GetInstance()->Get(ID_CARD_HUD_1 + id), 182, 16);
	this->drawCardTime = 500;

}

void CPlayHUD::Update(DWORD dt)
{
	drawCardTime -= dt;
	if (drawCardTime < -500) drawCardTime = 500;
	drawPowerFullTime -= dt;
	if (drawPowerFullTime < -500) drawPowerFullTime = 500;
}

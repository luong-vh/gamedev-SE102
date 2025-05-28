#include "GameManager.h"
#include "ScoreEffect.h"
#include "DamageEffect.h"
#include "GameData.h"
#include "PlayHUD.h"
#define ID_ANI_SCORE_100 100000100
#define ID_ANI_SCORE_200 100000200
#define ID_ANI_SCORE_400 100000400
#define ID_ANI_SCORE_800 100000800
#define ID_ANI_SCORE_1000 100001000
#define ID_ANI_SCORE_2000 100002000
#define ID_ANI_SCORE_4000 100004000
#define ID_ANI_SCORE_8000 100008000
#define ID_ANI_ONEUP_EFFECT 100010000

#define DOUBLE_SCORE_TIME_OUT 500
CGameManager* CGameManager::instance = nullptr;
CGameManager* CGameManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CGameManager();
	}
	return instance;
}

void CGameManager::AddScoreEffect(float x, float y, int value)
{
	objects.push_back(new CScoreEffect(x, y, GetIdAniScore(value)));
	AddScore(value);
}

void CGameManager::AddCoin(int value)
{
	CGameData::AddCoin(value);
	CPlayHUD::GetInstance()->SetCoin(CGameData::coin);

}

void CGameManager::AddScore(int value)
{
	CGameData::AddScore(value);
	CPlayHUD::GetInstance()->SetScore(CGameData::score);
}

void CGameManager::AddOneUpEffect(float x, float y)
{
	objects.push_back(new CScoreEffect(x, y, ID_ANI_ONEUP_EFFECT));
}

void CGameManager::AddDamageEffect(float x, float y)
{
	objects.push_back(new CDamageEffect(x, y));
}

void CGameManager::StomKoopa(float x, float y)
{
	ULONGLONG deltaTime = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetDeltaTime(lastTimeStomKoopa);
	if (deltaTime < DOUBLE_SCORE_TIME_OUT) {
		lastScoreKoopa *= 2;
	}
	else {
		lastScoreKoopa = 100;
	}
	switch (lastScoreKoopa)
	{
	case 16000:
		lastScoreKoopa = 8000;
		AddOneUpEffect(x, y);
		break;
	case 1600:
		lastScoreKoopa = 1000;
	default:
		AddScoreEffect(x, y, lastScoreKoopa);
		break;
	}
	
	lastTimeStomKoopa = GetTickCount64();
}

void CGameManager::StomGoomba(float x, float y)
{
	ULONGLONG deltaTime = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetDeltaTime(lastTimeStomGoomba);
	if (deltaTime < DOUBLE_SCORE_TIME_OUT) {
		lastScoreGoomba *= 2;
	}
	else {
		lastScoreGoomba = 100;
	}
	objects.push_back(new CScoreEffect(x, y, GetIdAniScore(lastScoreGoomba)));
	lastTimeStomGoomba = GetTickCount64();
}

void CGameManager::Update(DWORD dt)
{
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->Update(dt, NULL);
	}
	PurgeDeletedObjects();
}

void CGameManager::Render()
{
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->Render();
	}
}

int CGameManager::GetIdAniScore(int value)
{
	switch (value) {
	case 100:
		return ID_ANI_SCORE_100;
	case 200:
		return ID_ANI_SCORE_200;
	case 400:
		return ID_ANI_SCORE_400;
	case 800:
		return ID_ANI_SCORE_800;
	case 1000:
		return ID_ANI_SCORE_1000;
	case 2000:
		return ID_ANI_SCORE_2000;
	case 4000:
		return ID_ANI_SCORE_4000;
	case 8000:
		return ID_ANI_SCORE_8000;
	default:
		return 0;

	}
}

void CGameManager::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}

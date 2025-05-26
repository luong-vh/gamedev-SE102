#include "GameManager.h"
#include "ScoreEffect.h"

#define ID_ANI_SCORE_100 100000100
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
	objects.push_back(new CScoreEffect(x, y, ID_ANI_SCORE_100));
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

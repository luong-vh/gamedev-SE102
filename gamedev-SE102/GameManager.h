#pragma once
#include <vector>
#include "GameObject.h"
using namespace std;
class CGameManager
{
	static CGameManager* instance;
	vector<CGameObject*> objects;
public:
	static CGameManager* GetInstance();
	void AddScoreEffect(float x, float y, int value);
	void Update(DWORD dt);
	void Render();
	void PurgeDeletedObjects();
};


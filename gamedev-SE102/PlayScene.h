#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "BackgroundTile.h"
//#include "Koopas.h"
#define MAX_TIME_PLAYSCENE 300

class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;	
	ULONGLONG marioPause_start;
	float marioPause_time;
	float gamePause_time;
	float gameResume_time;
	bool isMarioPaused = false;
	bool isGamePaused = false;
	bool isGameOver = false;
	vector<LPGAMEOBJECT> objects;
	vector<CBackgroundTile*> tiles;
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_TILES(string line);
	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	float time = MAX_TIME_PLAYSCENE;
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void MarioPause(float time);
	virtual void GamePause();
	virtual void GameResume();
	virtual void GameOver();
	virtual bool IsPaused() { return isGamePaused; }
	virtual ULONGLONG GetDeltaTime(ULONGLONG start);

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();
	void AddObject(LPGAMEOBJECT obj) { objects.push_back(obj); }
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;


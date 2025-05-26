#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Block.h"
#include "Venus_Pipe.h"
#include "SampleKeyEventHandler.h"
#include "Piranha_Pipe.h"
#include "QuestionBrick.h"
#include "ParaGoomba.h"
#include "RedKoopa.h"
#include "PlayHUD.h"
#include "WoodenBlock.h"
#include "CloudBlock.h"
#include "GoldenBrick.h"
#include "ButtonBrick.h"
#include "InvisibleWall.h"
#include "KillZone.h"
#include "ParaKoopa.h"
#include "CGoalCard.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2
#define ASSETS_SECTION_TILES 3

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_TILES(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return; // skip invalid lines
	int ID = atoi(tokens[0].c_str());
	int x = atoi(tokens[1].c_str());
	int y = atoi(tokens[2].c_str());
	CBackgroundTile* tile = new CBackgroundTile(CSprites::GetInstance()->Get(ID), x, y);
	tiles.push_back(tile);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA:
		if (tokens.size() < 4) return;
		if (atoi(tokens[3].c_str()) == 0)
			obj = new CGoomba(x, y);
		else obj = new CParaGoomba(x, y);
		break;
	case OBJECT_TYPE_BRICK: 
	{
		if (tokens.size() < 4) return;
		int id = atoi(tokens[3].c_str());
		if (id == ID_WOODEN_BLOCK) obj = new CWoodenBlock(x, y);
		if (id == ID_CLOUD_BLOCK) obj = new CCloudBlock(x, y);
		if (id == ID_GOLDEN_BRICK) obj = new CGoldenBrick(x, y);
		if (id == ID_BUTTON_BRICK) obj = new CButtonBrick(x, y);
		if (id == ID_GOAL_CARD) obj = new CGoalCard(x, y);
		break;
	}
	case OBJECT_TYPE_COIN: 
		obj = new CCoin(x, y); break;

	case OBJECT_TYPE_PLATFORM:
	{
		if (tokens.size() < 13) return;
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int thick = atoi(tokens[6].c_str());
		int sprite_begin = atoi(tokens[7].c_str());
		int sprite_middle = atoi(tokens[8].c_str());
		int sprite_end = atoi(tokens[9].c_str());
		int sprite_begin2 = atoi(tokens[10].c_str());
		int sprite_middle2 = atoi(tokens[11].c_str());
		int sprite_end2 = atoi(tokens[12].c_str());
		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length, thick,
			sprite_begin, sprite_middle, sprite_end,
			sprite_begin2, sprite_middle2, sprite_end2
		);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		break;
	}
	case OBJECT_TYPE_BLOCK:
	{
		if (tokens.size() < 9) return;
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int width = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		int cell_id_1 = atoi(tokens[7].c_str());

		int shadow_cell_id = atoi(tokens[8].c_str());
		int has = atoi(tokens[8].c_str());


		obj = new CBlock(
			x, y,
			cell_width, cell_height, width, height,
			cell_id_1,
			shadow_cell_id, has == 1
		);
		break;
	}
	case OBJECT_TYPE_PIPE:
	{
		if (tokens.size() < 4) return;
		int height = atoi(tokens[3].c_str());


		obj = new CPipe(
			x, y, height
		);
		break;
	}
	case OBJECT_TYPE_RED_VENUS:
	{
		if (tokens.size() < 5) return;
		int height = atoi(tokens[3].c_str());
		int pipeHeight = atoi(tokens[4].c_str());
		LPVenusPipe pipe = new CVenus_Pipe(
			x, y + height * VENUS_CELL_HEIGHT / 2 + PIPE_CELL_HEIGHT / 2, pipeHeight, NULL
		);
		obj = new CVenusFireTrap(x, y, height, pipe, RED_VENUSFIRETRAP_ID);
		pipe->venusFireTrap = (LPVENUSFIRETRAP)obj;
		y += height * VENUS_CELL_HEIGHT;
		break;
	}
	case OBJECT_TYPE_GREEN_VENUS:
	{
		if (tokens.size() < 4) return;
		int height = atoi(tokens[3].c_str());
		int pipeHeight = atoi(tokens[4].c_str());
		int pipeHeadId = atoi(tokens[5].c_str());
		int pipeBodyId = atoi(tokens[6].c_str());
		LPVenusPipe pipe = new CVenus_Pipe(
			x, y + height * VENUS_CELL_HEIGHT / 2 + PIPE_CELL_HEIGHT / 2, pipeHeight, NULL
		);
		obj = new CVenusFireTrap(x, y, height, pipe, GREEN_VENUSFIRETRAP_ID);
		pipe->venusFireTrap = (LPVENUSFIRETRAP)obj;
		y += height * VENUS_CELL_HEIGHT;
		break;
	}
	case OBJECT_TYPE_PIRANHA:
	{
		if (tokens.size() < 5) return;
		int height = atoi(tokens[3].c_str());
		int pipeHeight = atoi(tokens[4].c_str());
		LPPIRANHAPIPE pipe = new CPiranha_Pipe(
			x, y + height * PIRANHA_CELL_HEIGHT / 2 + PIPE_CELL_HEIGHT / 2, pipeHeight, NULL
		);
		obj = new CPiranhaPlant(x, y, height, pipe);
		pipe->piranhaPlant = (LPPIRANHAPLANT)obj;
		y += height * PIRANHA_CELL_HEIGHT;
		break;
	}
	case OBJECT_TYPE_QUESTION_BRICK:
	{
		if (tokens.size() < 4) return;
		int item_type = atoi(tokens[3].c_str());
		obj = new CQuestionBrick(x, y, item_type);
		break;
	}
	case OBJECT_TYPE_KOOPAS:
	{
		if (tokens.size() < 4) return;
		int id = atoi(tokens[3].c_str());
		switch (id)
		{
		case ID_GREEN_KOOPA:
			obj = new CKoopa(x, y);
			break;
		case ID_RED_KOOPA:
			obj = new CRedKoopa(x, y);
			break;
		case ID_PARA_KOOPA:
			obj = new CParaKoopa(x, y);
		default:
			break;
		}
		break;
	}
	case OBJECT_TYPE_INVISIBLE_WALL:
	{
		obj = new CInvisibleWall(x, y);
		break;
	}

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	//obj->SetPosition(x, y);


	objects.push_back(obj);
	if (object_type == OBJECT_TYPE_RED_VENUS || object_type == OBJECT_TYPE_GREEN_VENUS)
	{
		objects.push_back(((LPVENUSFIRETRAP)obj)->pipe);
	}
	if (object_type == OBJECT_TYPE_PIRANHA)
	{
		objects.push_back(((LPPIRANHAPLANT)obj)->pipe);
	}
	
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line == "[TILES]") { section = ASSETS_SECTION_TILES; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case ASSETS_SECTION_TILES: _ParseSection_TILES(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;

		}
	}

	f.close();
	objects.push_back(new CKillZone());
	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	if (isGameOver || isGamePaused) return;
	if (isMarioPaused)
	{
		if  (GetDeltaTime(marioPause_start) > marioPause_time)
		{
			isMarioPaused = false;
			marioPause_start = 0;
			marioPause_time = 0;
		}
		return;
	}

	time -= dt * 1.0f / 1000;
	if (time <= 0)
	{
		GameOver();
		return;
	}
	CPlayHUD::GetInstance()->SetTime(floor(time));
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	if (cx < 0) cx = 0;
	if (cx > 2567) cx = 2564;
	if (cy > 100) cy = 236;
	CGame::GetInstance()->SetCamPos(cx, cy);
	CGameManager::GetInstance()->Update(dt);
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < tiles.size(); i++)
		tiles[i]->Draw();
	
	
	if (isGamePaused || isGameOver)
	{
		for (int i = 1; i < objects.size(); i++)
			objects[i]->RenderWhenGamePaused();
		if (isGameOver) CPlayHUD::GetInstance()->RenderWhileGameOver();
		else if (isGamePaused) CPlayHUD::GetInstance()->RenderWhilePaused();
		return;
	}

	if (isMarioPaused) {
		for (int i = 1; i < objects.size(); i++)
			objects[i]->RenderWhenMarioPaused();
		objects[0]->RenderWhenMarioPaused();
	}
	else {
		for (int i = 1; i < objects.size(); i++)
			objects[i]->Render();
		objects[0]->Render();
	}
	CPlayHUD::GetInstance()->Render();
	CGameManager::GetInstance()->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

void CPlayScene::MarioPause(float time)
{
	marioPause_start = GetTickCount64();
	marioPause_time = time;
	isMarioPaused = true;
}

void CPlayScene::GamePause()
{
	gamePause_time = GetTickCount64();
	isGamePaused = true;

}

void CPlayScene::GameResume()
{
	gameResume_time = GetTickCount64();
	isGamePaused = false;
}

void CPlayScene::GameOver()
{
	isGameOver = true;
}

ULONGLONG CPlayScene::GetDeltaTime(ULONGLONG start)
{
	ULONGLONG result = GetTickCount64()-start;
	if (start < marioPause_start) result -= marioPause_time;
	if (start < gameResume_time) {
		if (start > gamePause_time) result -= (gameResume_time - start);
		else result -= (gameResume_time - gamePause_time);;
	}
	return result;
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
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
#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	CPlayScene* playScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	switch (KeyCode)
	{
	case DIK_A:
		mario->ableToAttack = true;
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SlowFall();
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_F1:
		mario->SetPosition(1326, 106);
		break;
	case DIK_F2:
		mario->SetPosition(2047, 350);
		break;
	case DIK_F3:
		mario->SetPosition(2279, 80);
		break;
	case DIK_W:
		if (playScene->IsPaused()) playScene->GameResume();
		else playScene->GamePause();
		break;
		
	}

}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_A:
		mario->ableToAttack = false;
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	if (((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer() == NULL) return;
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (game->IsKeyDown(DIK_UP)) {
		mario->isAbleToRise = true;
	}
	else mario->isAbleToRise = false;
	if (game->IsKeyDown(DIK_DOWN)) {
		mario->isAbleToDive = true;
	}
	else mario->isAbleToDive = false;
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
	if (game->IsKeyDown(DIK_A)) mario->ableToHold = true;
	else mario->ableToHold = false;
	if(game->IsKeyDown(DIK_Z))
	{
		mario->ableToAttack = true;
	}
	if (game->IsKeyDown(DIK_X)) {
		mario->SlowFall();
	}
	
}
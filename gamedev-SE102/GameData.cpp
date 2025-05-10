#include "GameData.h"
int CGameData::score = 0;
int CGameData::coin = 0;
void CGameData::SetScore(int _score)
{
	CGameData::score = _score;
	SaveData();
}
void CGameData::SetCoin(int _coin)
{
	CGameData::coin = _coin;
	SaveData();
}
void CGameData::AddScore(int _score)
{
	CGameData::score += _score;
	SaveData();
}
void CGameData::AddCoin(int _coin)
{
	CGameData::coin += _coin;
	SaveData();
}
void CGameData::InitData()
{
	score = 0;
	coin = 0;
	SaveData();
}
void CGameData::SaveData()
{
	ofstream file(FILE_PATH);
	if (file.is_open())
	{
		file << "Score: " << score << endl;
		file << "Coin: " << coin << endl;
		file.close();
	}
	else
	{
		DebugOut(L"Unable to open file");
	}
}
void CGameData::LoadData()
{
	ifstream file(FILE_PATH);
	if (file.is_open())
	{
		string line;
		while (std::getline(file, line))
		{
			istringstream iss(line);
			string key;
			int value;
			if (iss >> key >> value)
			{
				if (key == "Score:")
					score = value;
				else if (key == "Coin:")
					coin = value;
			}
		}
		file.close();
	}
	else
	{
		InitData();
		DebugOut(L"Unable to open file, initializing data\n");
	}
}

#include "stdafx.h"
#include "SaveDataManager.h"


SaveDataManager::SaveDataManager()
{
	//テストしたかったらこれ呼ぶ。
	/*
	
	SaveDataManager SaveDataMng;
	SaveDataManager::SaveData data;

	SaveDataMng.Init(data);

	for (int i = 0; i < 11; i++) {
		data.score[i] = 1 * i;
	}


	data.score[2] = 5;
	data.score[3] = 5;

	data.score[4] = 7;

	int num = SaveDataMng.Sort(data, 6);
	SaveDataMng.SetPlayerName(data, m_inputName, num);

	for (int i = 0; i < 11; i++) {
		K2_LOG("\n%d\n", data.score[i]);
		K2_LOG("\n%ls\n", data.name[i]);
	}
	K2_LOG("\n%ls\n", data.name[num]);
	
	*/


	//スコアを初期化したいとき呼ぶ。
	/*
	
	for (int i = 0; i < 10 + 1; i++) {

		data.score[i] = 0;
	}

	*/

	//名前を初期化したいとき呼ぶ。
	/*
	
	for (int i = 0; i < 11; i++) {
		rankName[i * 5 + 0] = 'T';
		rankName[i * 5 + 1] = 'A';
		rankName[i * 5 + 2] = 'R';
		rankName[i * 5 + 3] = 'O';
		rankName[i * 5 + 4] = 'U';
	}
	
	*/
}

SaveDataManager::~SaveDataManager()
{

}
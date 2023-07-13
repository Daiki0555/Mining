#pragma once

namespace
{
	const int SCORE_MAX = 10;		//スコアの最大数。
	const int BUFFER_SIZE = 256;	//バッファーサイズ。
}

/// <summary>
/// セーブデータマネージャー。
/// </summary>
class SaveDataManager
{
public:
	/// <summary>
	/// セーブデータの構造体。
	/// </summary>
	struct SaveData
	{
		int			score[SCORE_MAX + 1];	//スコア。
	};

public:
	SaveDataManager();
	~SaveDataManager();

	/// <summary>
	/// 初期化処理。
	/// </summary>
	void Init(SaveData& data)
	{
		for (int i = 0; i < SCORE_MAX + 1; i++) {

			data.score[i] = 0;
		}
	}

	/// <summary>
	/// セーブ処理。
	/// </summary>
	/// <param name="data"></param>
	void Save(SaveData& data)
	{
		FILE* fp = fopen("saveData.dat", "wb");
		fwrite((void*)&data, sizeof(data), 1, fp);
		fclose(fp);
	}

	/// <summary>
	/// ロード処理。
	/// </summary>
	/// <param name="data"></param>
	void Load(SaveData& data)
	{
		FILE* fp = fopen("saveData.dat", "rb");
		if (fp != NULL) {
			fread((void*)&data, sizeof(data), 1, fp);
			fclose(fp);
		}
	}

	/// <summary>
	/// プレイヤー名をランキングに保存。
	/// </summary>
	/// <param name="name">プレイヤー名</param>
	/// <param name="num">順位</param>
	void SetPlayerName(char* name, int num)
	{
		FILE* fp = NULL;
		char rankName[BUFFER_SIZE];

		//ファイルを読み込む。
		fp = fopen("rankingName.txt", "r");

		K2_ASSERT(
			fp != NULL,
			"ファイルの読み込みに失敗しました。"
		);

		fread(rankName, sizeof(rankName), 1, fp);
		fgets(rankName, BUFFER_SIZE, fp);
		rankName[BUFFER_SIZE - 1] = '\0';
		fclose(fp);

		int j = 0;

		//順位の位置にある名前を上書き。
		for (int i = num * 5; i < num * 5 + 5; i++) {
			rankName[i] = name[j];
			j++;

			if (name[i] == '\0') {
				name[i] = 32;
			}
		}

		//ファイルに書き込む。
		fp = fopen("rankingName.txt", "w");
		
		//K2_ASSERT(
		//	fp != NULL,
		//	"ファイルの読み込みに失敗しました。"
		//);

		fwrite(rankName, sizeof(rankName), 1, fp);
		fclose(fp);

	}

	/// <summary>
	/// ランキングのソート処理。
	/// </summary>
	/// <param name="data">セーブデータ</param>
	/// <param name="newScore">新しいスコア</param>
	const int Sort(SaveData& data, int newScore)
	{
		int tmp = 0;
		data.score[SCORE_MAX] = newScore;

		//数値を降順にソート。
		for (int i = 0; i < SCORE_MAX + 1; i++)
		{
			for (int j = i + 1; j < SCORE_MAX + 1; j++)
			{
				if (data.score[i] < data.score[j]) {

					tmp = data.score[i];
					data.score[i] = data.score[j];
					data.score[j] = tmp;
				}
			}
		}

		for (int k = SCORE_MAX; k >= 0; k--) {

			if (newScore == data.score[k]) {

				//何位かを返す。
				return k;
			}
		}

		//エラー。
		return -1;
	}
};


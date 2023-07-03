#pragma once

namespace
{
	const int SCORE_MAX = 10;	//スコアの最大数
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
		float score[SCORE_MAX + 1];	//スコア。
	};

public:
	SaveDataManager();
	~SaveDataManager();

	/// <summary>
	/// セーブ処理。
	/// </summary>
	/// <param name="data"></param>
	void Save(SaveData& data)
	{
		FILE* fp = fopen("saveData.bin", "wb");
		fwrite((void*)&data, sizeof(data), 1, fp);
		fclose(fp);
	}

	/// <summary>
	/// ロード処理。
	/// </summary>
	/// <param name="data"></param>
	void Load(SaveData& data)
	{
		FILE* fp = fopen("saveData.bin", "rb");
		if (fp != NULL) {
			fread((void*)&data, sizeof(data), 1, fp);
			fclose(fp);
		}
	}

	/// <summary>
	/// ランキングのソート処理。
	/// </summary>
	/// <param name="data">セーブデータ</param>
	/// <param name="newScore">新しいスコア</param>
	void Sort(SaveData& data, float newScore)
	{
		float tmp = 0.0f;
		data.score[10] = newScore;

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
	}
};


#pragma once

namespace
{
	const int SCORE_MAX = 10;	//�X�R�A�̍ő吔
}

/// <summary>
/// �Z�[�u�f�[�^�}�l�[�W���[�B
/// </summary>
class SaveDataManager
{
public:
	/// <summary>
	/// �Z�[�u�f�[�^�̍\���́B
	/// </summary>
	struct SaveData
	{
		float score[SCORE_MAX + 1];	//�X�R�A�B
	};

public:
	SaveDataManager();
	~SaveDataManager();

	/// <summary>
	/// �Z�[�u�����B
	/// </summary>
	/// <param name="data"></param>
	void Save(SaveData& data)
	{
		FILE* fp = fopen("saveData.bin", "wb");
		fwrite((void*)&data, sizeof(data), 1, fp);
		fclose(fp);
	}

	/// <summary>
	/// ���[�h�����B
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
	/// �����L���O�̃\�[�g�����B
	/// </summary>
	/// <param name="data">�Z�[�u�f�[�^</param>
	/// <param name="newScore">�V�����X�R�A</param>
	void Sort(SaveData& data, float newScore)
	{
		float tmp = 0.0f;
		data.score[10] = newScore;

		//���l���~���Ƀ\�[�g�B
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


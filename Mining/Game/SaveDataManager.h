#pragma once

namespace
{
	const int SCORE_MAX = 10;		//�X�R�A�̍ő吔�B
	const int BUFFER_SIZE = 256;	//�o�b�t�@�[�T�C�Y�B
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
		int			score[SCORE_MAX + 1];	//�X�R�A�B
	};

public:
	SaveDataManager();
	~SaveDataManager();

	/// <summary>
	/// �����������B
	/// </summary>
	void Init(SaveData& data)
	{
		for (int i = 0; i < SCORE_MAX + 1; i++) {

			data.score[i] = 0;
		}
	}

	/// <summary>
	/// �Z�[�u�����B
	/// </summary>
	/// <param name="data"></param>
	void Save(SaveData& data)
	{
		FILE* fp = fopen("saveData.dat", "wb");
		fwrite((void*)&data, sizeof(data), 1, fp);
		fclose(fp);
	}

	/// <summary>
	/// ���[�h�����B
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
	/// �v���C���[���������L���O�ɕۑ��B
	/// </summary>
	/// <param name="name">�v���C���[��</param>
	/// <param name="num">����</param>
	void SetPlayerName(char* name, int num)
	{
		FILE* fp = NULL;
		char rankName[BUFFER_SIZE];

		//�t�@�C����ǂݍ��ށB
		fp = fopen("rankingName.txt", "r");

		K2_ASSERT(
			fp != NULL,
			"�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B"
		);

		fread(rankName, sizeof(rankName), 1, fp);
		fgets(rankName, BUFFER_SIZE, fp);
		rankName[BUFFER_SIZE - 1] = '\0';
		fclose(fp);

		int j = 0;

		//���ʂ̈ʒu�ɂ��閼�O���㏑���B
		for (int i = num * 5; i < num * 5 + 5; i++) {
			rankName[i] = name[j];
			j++;

			if (name[i] == '\0') {
				name[i] = 32;
			}
		}

		//�t�@�C���ɏ������ށB
		fp = fopen("rankingName.txt", "w");
		
		//K2_ASSERT(
		//	fp != NULL,
		//	"�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B"
		//);

		fwrite(rankName, sizeof(rankName), 1, fp);
		fclose(fp);

	}

	/// <summary>
	/// �����L���O�̃\�[�g�����B
	/// </summary>
	/// <param name="data">�Z�[�u�f�[�^</param>
	/// <param name="newScore">�V�����X�R�A</param>
	const int Sort(SaveData& data, int newScore)
	{
		int tmp = 0;
		data.score[SCORE_MAX] = newScore;

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

		for (int k = SCORE_MAX; k >= 0; k--) {

			if (newScore == data.score[k]) {

				//���ʂ���Ԃ��B
				return k;
			}
		}

		//�G���[�B
		return -1;
	}
};


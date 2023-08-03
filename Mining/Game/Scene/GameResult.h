#pragma once

class Fade;
class Sound;

namespace
{
	const int CRYSTAL_CATEGORY_MAX = 4;			// �N���X�^���̎�ސ�
}

class GameResult:public IGameObject
{
public:
	GameResult();
	~GameResult();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

public:
	/// <summary>
	/// �N���X�^���̎擾����ݒ肷��
	/// </summary>
	/// <param name="num">�z��̔ԍ�</param>
	/// <param name="sum">��</param>
	void SetCrystalSum(const int num, const int sum)
	{
		m_haveCristals[num] = sum;
	}

private:
	/// <summary>
	/// �X�R�A�̌v�Z�����B
	/// </summary>
	void CalcScore();

	/// <summary>
	/// �X�R�A��\������
	/// </summary>
	void DrawScore();

	/// <summary>
	/// �V�[���̑J�ڏ����B
	/// </summary>
	void TransitionScene();

private:
	Level2DRender*							m_level2DRender = nullptr;			// 2D�����_�[
	SpriteRender							m_backGroundSpriteRender;			//�w�i�摜�B
	SpriteRender							m_resultSpriteRender;				// ���U���g�����̉摜
	SpriteRender							m_scoreBoardSpriteRender;			// �X�R�A�{�[�h�̉摜
	FontRender								m_crystalFontRender;				//�z�΂̌������B
	FontRender								m_newRecordFontRender;				//�V�L�^���̕����B
	Fade*									m_fade = nullptr;					//�t�F�[�h�N���X�B
	Sound*									m_sound = nullptr;					// �T�E���h�N���X
	bool									m_isNewRecord = false;				//�V�L�^���ǂ����B
	bool									m_isWaitFadeOut = false;			//�t�F�[�h�A�E�g�̑ҋ@�����ǂ����B
	std::array<int, CRYSTAL_CATEGORY_MAX>	m_haveCristals = { 0,0,0,0 };		// player���擾�����N���X�^��
	int										m_newScore = 0;						// �X�R�A
	float									m_newRecordTimer = 0.0f;			//�V�L�^���̃^�C�}�[�B
};


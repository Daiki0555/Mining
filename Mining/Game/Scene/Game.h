#pragma once

class GameResult;
class Player;
class BackGround;
class GameCamera;
class PlayerStatusGauge;
class PressAndHoldGauge;
class Crystal;
class PhysicsGhost;
class EnemyBasic;

class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// �I�u�W�F�N�g�̍폜
	/// </summary>
	void Objct_DeleteGO();
	/// <summary>
	/// ���x���f�U�C��
	/// </summary>
	void LevelDesign();
	/// <summary>
	/// �Q�[�����̏���
	/// </summary>
	void PlayGame();
	/// <summary>
	/// �`��̗L�������肷��
	/// </summary>
	void CanDrawObject();
	/// <summary>
	/// �Q�[���̏I������
	/// </summary>
	void QuitGame();
	/// <summary>
	/// �N���A���̏���
	/// </summary>
	void GameClear();
	// �Q�[���I�[�o�[���̏���
	void GameOver();
	/// <summary>
	/// �X�R�A�v�Z
	/// </summary>
	void Score();

	/// <summary>
	/// �N���X�^���̃��X�g���擾����
	/// </summary>
	inline std::vector<Crystal*> GetCrystalList()
	{
		return m_crystalList;
	}

	/// <summary>
	/// �S�[�X�g�̃��X�g���擾����
	/// </summary>
	/// <returns></returns>
	inline std::vector<PhysicsGhost*> GetGhostList()
	{
		return m_ghostList;
	}

private:
	enum enGameState {
		m_enGameState_Play,												// �v���C��
		m_enGameState_GameClear,										// �Q�[���N���A
		m_enGameState_GameOver,											// �Q�[���I�[�o�[
	};
	enGameState					m_enGameState = m_enGameState_Play;		// �Q�[���X�e�[�g

	LevelRender					m_levelRender;							// ���x�������_�[

	GameResult*					m_gameResult = nullptr;					// ���U���g���
	Player*						m_player = nullptr;						// �v���C���[
	BackGround*					m_backGround = nullptr;					// �w�i
	GameCamera*					m_gameCamera = nullptr;					// �Q�[���J����
	PlayerStatusGauge*			m_playerStatusGauge = nullptr;			// �v���C���[�̃X�e�[�^�X�Q�[�W
	PressAndHoldGauge*			m_circleGauge = nullptr;				// �~�`�Q�[�W

	std::vector<Crystal*>		m_crystalList;							// �N���X�^���̑���
	std::vector<EnemyBasic*>	m_enemyList;							// �G�l�~�[�̑���
	std::vector<PhysicsGhost*>	m_ghostList;							// �S�[�X�g�̑���

	FontRender					m_fontRender;
};


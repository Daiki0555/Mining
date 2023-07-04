#pragma once

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
	/// �v���C���̏���
	/// </summary>
	void PlayGame();
	/// <summary>
	/// �N���A���̏���
	/// </summary>
	void ClearGame();
	/// <summary>
	/// ���S���̏���
	/// </summary>
	void OverGame();

	/// <summary>
	/// �N���X�^���̃��X�g���擾����
	/// </summary>
	inline std::vector<Crystal*> GetCrystalList()
	{
		return m_crystalList;
	}

private:
	enum enGameState {
		m_enGameState_Play,												// �v���C��
		m_enGameState_GameClear,										// �Q�[���N���A
		m_enGameState_GameOver,											// �Q�[���I�[�o�[
	};
	enGameState					m_enGameState = m_enGameState_Play;		// �Q�[���X�e�[�g

	LevelRender					m_levelRender;							// ���x�������_�[


	Player*						m_player = nullptr;						// �v���C���[
	BackGround*					m_backGround = nullptr;					// �w�i
	GameCamera*					m_gameCamera = nullptr;					// �Q�[���J����
	PlayerStatusGauge*			m_playerStatusGauge = nullptr;			// �v���C���[�̃X�e�[�^�X�Q�[�W
	PressAndHoldGauge*			m_circleGauge = nullptr;				// �~�`�Q�[�W
	PhysicsGhost*				m_physicsGhost = nullptr;				// �S�[�X�g�I�u�W�F�N�g

	std::vector<Crystal*>		m_crystalList;							// �N���X�^���̑���
	std::vector<EnemyBasic*>	m_enemyList;							// �G�l�~�[�̑���
	std::vector<PhysicsGhost*>	m_ghostList;							// �S�[�X�g�̑���

	FontRender m_fontRender;
};


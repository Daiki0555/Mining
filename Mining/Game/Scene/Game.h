#pragma once
class Player;
class BackGround;
class GameCamera;
class PlayerStatusGauge;
class PressAndHoldGauge;
class Crystal;
class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();

	void Objct_DeleteGO();											// �I�u�W�F�N�g�̍폜
	void LevelDesign();												// ���x���f�U�C��
	
private:
	enum enGameState {
		m_enGameState_Play,											// �v���C��
		m_enGameState_GameClear,									// �Q�[���N���A
		m_enGameState_GameOver,										// �Q�[���I�[�o�[
	};
	enGameState				m_enGameState = m_enGameState_Play;		// �Q�[���X�e�[�g

	LevelRender				m_levelRender;							// ���x�������_�[


	Player*					m_player = nullptr;						// �v���C���[
	BackGround*				m_backGround = nullptr;					// �w�i
	GameCamera*				m_gameCamera = nullptr;					// �Q�[���J����
	PlayerStatusGauge*		m_playerStatusGauge = nullptr;			// �v���C���[�̃X�e�[�^�X�Q�[�W
	PressAndHoldGauge*		m_circleGauge = nullptr;				// �~�`�Q�[�W

	std::list<Crystal*>		m_crystalList;							// �N���X�^���̑���
};


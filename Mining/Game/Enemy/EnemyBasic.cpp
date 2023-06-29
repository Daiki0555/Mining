#include "stdafx.h"
#include "EnemyBasic.h"
#include "Player.h"

namespace
{
	const float Y_POSITION = 25.0f;		// ���C�̍���
	const float ADD_LENGTH = 100.0f;	// ��Z����x�N�g���̒���
}

EnemyBasic::EnemyBasic()
{

}

EnemyBasic::~EnemyBasic()
{

}

bool EnemyBasic::Start(int attackPower, float moveSpeed, float radius, float height)
{
	// �C���X�^���X��T��
	m_player = FindGO<Player>("player");

	// �X�e�[�^�X��ݒ�
	m_enemyStatus.m_attackPower = attackPower;
	m_enemyStatus.m_basicSpeed = moveSpeed;
	// �L�����N�^�[�R���g���[���[���쐬
	m_characterController.Init(radius, height, m_position);

	// �X�t�B�A�R���C�_�[��ݒ�
	m_sphereCollider.Create(10.0f);

	return true;
}

void EnemyBasic::Move()
{
	// �v���C���[�֌������x�N�g�����쐬
	Vector3 moveSpeed = m_player->GetPosition() - m_position;
	moveSpeed.y = 0.0f;
	moveSpeed.Normalize();

	// �v���C���[�Ǝ��g�Ƃ̊Ԃɕǂ���������
	if (WallAndHit(m_position + (moveSpeed* ADD_LENGTH)) == false) {
		// �ړ����~����
		m_actionState = m_enActionState_Idle;
		return;
	}

	// �ړ�������
	m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime() * m_enemyStatus.m_basicSpeed);

	// ��]
	Rotation(moveSpeed);
}

void EnemyBasic::Idle()
{
	// �v���C���[�֌������x�N�g�����쐬
	Vector3 moveSpeed = m_player->GetPosition() - m_position;
	moveSpeed.y = 0.0f;
	moveSpeed.Normalize();

	if (WallAndHit(m_position + (moveSpeed * ADD_LENGTH)) == false) {
		return;
	}

	// �ړ����J�n����
	m_actionState = m_enActionState_Move;
}

struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;		// �Փ˃t���O

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		// �ǂƂԂ����Ă��Ȃ�������
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall) {
			// �Փ˂����͕̂ǂł͂Ȃ�
			return 0.0f;
		}

		// �ǂƂԂ�������
		// �t���O��true�ɂ���
		isHit = true;
		return 0.0f;
	}
};

bool EnemyBasic::WallAndHit(Vector3 targetPosition)
{
	btTransform start, end;

	start.setIdentity();
	end.setIdentity();

	// �n�_�̓G�l�~�[�̍��W
	start.setOrigin(btVector3(m_position.x, Y_POSITION, m_position.z));

	// �I�_�̓v���C���[�̍��W
	end.setOrigin(btVector3(targetPosition.x, Y_POSITION, targetPosition.z));

	SweepResultWall callback;

	// �R���C�_�[���n�_����I�_�܂œ������āA
	// �Փ˂��邩�ǂ������ׂ�
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(),start, end, callback);

	// �ǂƏՓ˂���
	if (callback.isHit == true) {
		return false;
	}

	// �ǂƏՓ˂��Ă��Ȃ�
	// �v���C���[��������
	return true;
}

void EnemyBasic::Attack()
{
	// �v���C���[�ɍU������
	m_player->Damage(m_enemyStatus.m_attackPower);

	m_actionState = m_enActionState_StopAction;
}

void EnemyBasic::Rotation(Vector3 rotation)
{
	// ��]
	m_rotation.SetRotationYFromDirectionXZ(rotation);
	m_modelRender.SetRotaition(m_rotation);
}

void EnemyBasic::Damege()
{
	if (m_modelRender.IsPlayingAnimation()) {
		return;
	}

	m_actionState = m_enActionState_StopAction;
}

void EnemyBasic::StopAction()
{
	m_StopTimer -= g_gameTime->GetFrameDeltaTime();

	// �^�C�}�[��0.0f�ȉ��ɂȂ�����ڍs����
	if (m_StopTimer >= 0.0f) {
		return;
	}

	m_actionState = m_enActionState_Move;
}
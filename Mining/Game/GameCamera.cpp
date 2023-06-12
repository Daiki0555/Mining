#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

namespace 
{
	float VALUE_Y = 150.0f;		// �����グ��l
	float VALUE_Z = 200.0f;		// ��O�Ɉړ�����l
}

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	// �ߕ��ʁE�����ʂ̐ݒ�
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);

	// �C���X�^���X��T��
	m_player = FindGO<Player>("player");
}

void GameCamera::UpDate()
{
	CameraSettings();							// �J�����ݒ�
}

void GameCamera::CameraSettings()
{
	// �����_
	Vector3 m_targetPosition = Vector3::Zero;
	m_targetPosition = m_player->GetPosition();	// �v���C���[�̍��W���Q��
	m_targetPosition.y += VALUE_Y;				// �����̏�����ɍ��W�������グ��

	g_camera3D->SetTarget(m_targetPosition);	// �����_��ݒ�


	// �n�_(���g�̍��W)
	Vector3 m_cameraPosition = Vector3::Zero;
	m_cameraPosition = m_player->GetPosition();	// �v���C���[�̍��W���Q��
	m_cameraPosition.z -= VALUE_Z;				// �����_�̎�O�Ɉړ�����

	g_camera3D->SetPosition(m_cameraPosition);	// �n�_��ݒ�

}
#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

namespace 
{
	const float		VALUE_Y = 150.0f;						// �����グ��l

	const Vector3	VECTOR = { 0.0f, 150.0f, -300.0f };		// �n�_���璍���_�֌������x�N�g��
}

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	// �C���X�^���X��T��
	m_player = FindGO<Player>("player");

	// �ߕ��ʁE�����ʂ̐ݒ�
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);

	// �n�_���璍���_�֌������x�N�g����ݒ�
	m_toCameraPosition.Set(VECTOR);

	return true;
}

void GameCamera::Update()
{
	CameraSettings();												// �J�����ݒ�
}

void GameCamera::CameraSettings()
{
	// �����_
	Vector3 targetPosition = m_player->GetPosition();				// �v���C���[�̍��W���Q��
	targetPosition.y += VALUE_Y;									// �����̏�����ɍ��W�������グ��

	// �n�_(���g�̍��W)
	Vector3 position = m_toCameraPosition + targetPosition;			// �����_�Ǝn�_���璍���_�֌������x�N�g�������Z

	g_camera3D->SetTarget(targetPosition);							// �����_��ݒ�
	g_camera3D->SetPosition(position);								// �n�_��ݒ�
	g_camera3D->Update();											// �X�V
}
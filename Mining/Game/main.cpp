#include "stdafx.h"
#include "system/system.h"
#include "Debug.h"
#include "Scene/Game.h"
#include "Scene/Title.h"
#include "SaveDataManager.h"
#include "NameEntry.h"
#include "Ranking.h"
#include "Scene/GameResult.h"
#include "UI/Fade.h"
#include "Scene/Guide.h"
#include "Scene/Logo.h"
#include "Sound.h"

// K2EngineLow�̃O���[�o���A�N�Z�X�|�C���g�B
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// �Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Mining!"));
	
	//����΂�́`


	// k2EngineLow�̏������B
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	g_camera3D->SetPosition({ 0.0f, 100.0f, -200.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });


	RenderingEngine::GetInstance()->Init();

	//NewGO<Debug>(0,"debug");
	//NewGO<Game>(0, "game");
	NewGO<Logo>(10, "logo");

	NewGO<Sound>(0, "sound");
	NewGO<Fade>(9, "fade");

	//NewGO<Title>(0, "title");
	//NewGO<Guide>(0, "guide");
	//NewGO<GameResult>(0, "gameResult");
	//NewGO<NameEntry>(0, "nameEntry");
	//NewGO<Ranking>(0, "ranking");


	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();
		// �t���[���̊J�n���ɌĂяo���K�v�����鏈������s
		g_k2EngineLow->BeginFrame();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V������Ăяo���B
		g_k2EngineLow->ExecuteUpdate();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̕`�揈����Ăяo���B
		g_k2EngineLow->ExecuteRender();

		// �f�o�b�O�`�揈������s����B
		g_k2EngineLow->DebubDrawWorld();

		RenderingEngine::GetInstance()->Execute(renderContext);

		// �t���[���̏I�����ɌĂяo���K�v�����鏈������s�B
		g_k2EngineLow->EndFrame();



	}

	delete g_k2EngineLow;

	return 0;
}


#pragma once

#include "EnemyBasic.h"

class Enemy_Mushroom:public EnemyBasic
{
public:
	Enemy_Mushroom();
	~Enemy_Mushroom()override;

	bool Start();
	void Update();
	/// <summary>
	/// �s������
	/// </summary>
	void Action();
	/// <summary>
	/// �A�j���[�V�����̃��[�h
	/// </summary>
	void LoadAnimation();
	/// <summary>
	/// �A�j���[�V�����̍Đ�����
	/// </summary>
	void PlayAnimation();
	void Render(RenderContext& rc);
};
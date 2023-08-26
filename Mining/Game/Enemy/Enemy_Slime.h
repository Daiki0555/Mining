#pragma once

#include "EnemyBasic.h"

class Enemy_Slime:public EnemyBasic
{
public:
	Enemy_Slime();
	~Enemy_Slime()override;

	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
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
};


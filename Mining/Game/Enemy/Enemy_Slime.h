#pragma once
#include "EnemyBasic.h"

class Enemy_Slime:public EnemyBasic
{
public:
	Enemy_Slime();
	~Enemy_Slime()override;

	bool Start();
	void Update();
	void LoadAnimation();
	void PlayAnimation();
	void Render(RenderContext& rc);
};


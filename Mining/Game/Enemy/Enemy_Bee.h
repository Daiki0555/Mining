#pragma once
#include "EnemyBasic.h"

class Enemy_Bee:public EnemyBasic
{
public:
	Enemy_Bee();
	~Enemy_Bee()override;

	bool Start();
	void Update();
	void LoadAnimation();
	void PlayAnimation();
	void Render(RenderContext& rc);
};


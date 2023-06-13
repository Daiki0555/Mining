#pragma once
#include "EnemyBasic.h"

class Enemy_Mushroom:public EnemyBasic
{
public:
	Enemy_Mushroom();
	~Enemy_Mushroom()override;

	bool Start();
	void Update();
	void LoadAnimation();
	void PlayAnimation();
	void Render(RenderContext& rc);
};
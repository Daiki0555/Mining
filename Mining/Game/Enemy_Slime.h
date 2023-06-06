#pragma once
#include "EnemyBasic.h"

class Enemy_Slime :public EnemyBasic
{
public:
	Enemy_Slime();
	~Enemy_Slime();

	bool Start();
	void Update();
	void RenderContext(RenderContext& rc);
};


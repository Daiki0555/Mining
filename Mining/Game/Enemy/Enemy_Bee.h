#pragma once
#include "EnemyBasic.h"

class Enemy_Bee:public EnemyBasic
{
public:
	Enemy_Bee();
	~Enemy_Bee()override;

	bool Start();
	void Update();
	/// <summary>
	/// 行動処理
	/// </summary>
	void Action();
	/// <summary>
	/// アニメーションのロード
	/// </summary>
	void LoadAnimation();
	/// <summary>
	/// アニメーションの再生処理
	/// </summary>
	void PlayAnimation();
	void Render(RenderContext& rc);
};


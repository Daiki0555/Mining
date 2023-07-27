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
};


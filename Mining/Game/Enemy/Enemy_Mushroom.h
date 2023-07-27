#pragma once

#include "EnemyBasic.h"

class Enemy_Mushroom:public EnemyBasic
{
public:
	Enemy_Mushroom();
	~Enemy_Mushroom()override;

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
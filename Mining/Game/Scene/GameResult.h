#pragma once

class Title;

namespace
{
	const int CRYSTAL_CATEGORY_MAX = 4;			// クリスタルの種類数
}

class GameResult:public IGameObject
{
public:
	GameResult();
	~GameResult();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// スコアを表示する
	/// </summary>
	void DrawScore();

	/// <summary>
	/// クリスタルの取得数を設定する
	/// </summary>
	/// <param name="num">配列の番号</param>
	/// <param name="sum">個数</param>
	void SetCrystalSum(const int num, const int sum) {
		m_haveCristals[num] = sum;
	}

private:
	SpriteRender							m_spriteRender;						// スプライトレンダー
	FontRender								m_fontRender;						// フォントレンダー

	Title*									m_title = nullptr;					// タイトル

	std::array<int, CRYSTAL_CATEGORY_MAX>	m_haveCristals = { 0,0,0,0 };		// playerが取得したクリスタル
	int										m_newScore = 0;						// スコア
};


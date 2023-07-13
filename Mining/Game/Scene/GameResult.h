#pragma once


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

public:
	/// <summary>
	/// クリスタルの取得数を設定する
	/// </summary>
	/// <param name="num">配列の番号</param>
	/// <param name="sum">個数</param>
	void SetCrystalSum(const int num, const int sum)
	{
		m_haveCristals[num] = sum;
	}

private:
	/// <summary>
	/// スコアの計算処理。
	/// </summary>
	void CalcScore();

	/// <summary>
	/// スコアを表示する
	/// </summary>
	void DrawScore();

	/// <summary>
	/// シーンの遷移処理。
	/// </summary>
	void TransitionScene();

private:
	SpriteRender							m_backGroundSpriteRender;			//背景画像。
	FontRender								m_crystalFontRender;				//鉱石の個数文字。
	FontRender								m_newRecordFontRender;				//新記録時の文字。

	std::array<int, CRYSTAL_CATEGORY_MAX>	m_haveCristals = { 0,0,0,0 };		// playerが取得したクリスタル
	bool									m_isNewRecord = false;				//新記録かどうか。
	int										m_newScore = 0;						// スコア
	float									m_newRecordTimer = 0.0f;			//新記録時のタイマー。
};


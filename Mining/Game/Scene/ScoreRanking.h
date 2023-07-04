#pragma once
class ScoreRanking : public IGameObject
{
public:
	ScoreRanking();
	~ScoreRanking();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
};


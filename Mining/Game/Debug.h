#pragma once

class Debug:public IGameObject
{
public:
	Debug();
	~Debug();
	void Update();
	void Render(RenderContext& rc);

private:
	Vector3 m_position=Vector3::Zero;
	Quaternion m_rotaition = Quaternion::Identity;
	Vector3 m_scale=Vector3(1.0f,1.0f,1.0f);
	ModelRender m_modelRender;

	//アニメーション
	enum EnAnimationClip {
		m_enAnimationClip_Idle,				//待機アニメーション
		m_enAnimationClip_Num,				//アニメーションの数
	};
	AnimationClip m_animationClips[m_enAnimationClip_Num];

};


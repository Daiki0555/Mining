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

	//�A�j���[�V����
	enum EnAnimationClip {
		m_enAnimationClip_Idle,				//�ҋ@�A�j���[�V����
		m_enAnimationClip_Num,				//�A�j���[�V�����̐�
	};
	AnimationClip m_animationClips[m_enAnimationClip_Num];

};


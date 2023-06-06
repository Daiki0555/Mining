#pragma once
class Player :public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void LoadAnimation();
	void PlayAnimation();

	void Rotation(Vector3 rotation);
	void Move();
	void Attack();
	void Damage(float attackPower);
	void Dig();
	void Death();
	void Clear();

private:
	enum m_ActionState {
		m_ActionState_Idle,			// 待機
		m_ActionState_Walk,			// 歩く
		m_ActionState_Run,			// 走る
		m_ActionState_Dig,			// 掘る
		m_ActionState_Damage,		// 被弾
		m_ActionState_Death,		// 死亡
		m_ActionState_Clear			// クリア
	};

	enum m_AnimationState {
		m_AnimationState_Idle,		// 待機
		m_AnimationState_Walk,		// 歩く
		m_AnimationState_Run,		// 走る
		m_AnimationState_Dig,		// 掘る
		m_AnimationState_Damage,	// 被弾
		m_AnimationState_Death,		// 死亡
		m_AnimationState_Clear		// クリア
	};

	enum EnAnimationClip {
		m_en_AnimationClips_Idle,		// 待機
		m_en_AnimationClips_Walk,		// 歩く
		m_en_AnimationClips_Run,		// 走る
		m_en_AnimationClips_Dig,		// 掘る
		m_en_AnimationClips_Damage,		// 被弾
		m_en_AnimationClips_Death,		// 死亡
		m_en_AnimationClips_Clear,		// クリア
		m_en_AnimationClips_Num
	};
	EnAnimationClip m_EnAnimationClips[m_en_AnimationClips_Num];

// --------------------------------------------------------
	ModelRender			m_ModelRender;						// モデルレンダー

	CharacterController m_CharacterController;				// キャラクターコントローラー

	Vector3				m_Position = Vector3::Zero;			// 自身の座標
	Vector3				m_Scale = Vector3::Zero;			// 自身のスケール
	Quaternion			m_Rotation= Quaternion::Identity;	// 自身の回転

	float				m_HitPoint = 150.0f;				// HP
	float				m_Stamina = 100.0f;					// スタミナ
	float				m_AttackPower = 50.0f;				// 攻撃力
	float				m_MoveSpeed = 10.0f;				// 移動速度
};


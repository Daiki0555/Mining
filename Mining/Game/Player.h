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

	void Rotation();
	void Move();
	void Attack();
	void Damage(int attackPower);
	void Dig();
	void Death();
	void Clear();

	/// <summary>
	/// 座標を参照する
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()const {
		return m_position;
	}

	/// <summary>
	/// 座標を設定する
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// スケールを設定する
	/// </summary>
	/// <param name="position"></param>
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// 回転を設定する
	/// </summary>
	/// <param name="position"></param>
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}

private:
	enum ActionState {
		m_ActionState_Idle,			// 待機
		m_ActionState_Walk,			// 歩く
		m_ActionState_Run,			// 走る
		m_ActionState_Dig,			// 掘る
		m_ActionState_Damage,		// 被弾
		m_ActionState_Death,		// 死亡
		m_ActionState_Clear			// クリア
	};
	ActionState m_actionState;

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
	AnimationClip m_EnAnimationClips[m_en_AnimationClips_Num];

// --------------------------------------------------------
	ModelRender			m_modelRender;						// モデルレンダー

	CharacterController m_characterController;				// キャラクターコントローラー

	Vector3				m_position = Vector3::Zero;			// 自身の座標
	Vector3				m_scale = Vector3::One;				// 自身のスケール
	Vector3				m_moveSpeed = Vector3::Zero;		// 移動速度

	Quaternion			m_rotation= Quaternion::Identity;	// 自身の回転

	struct PlayerStatus {
		int				m_hitPoint = 150;					// HP(150)
		int				m_attackPower = 25;					// 攻撃力(25)
		float			m_stamina = 100.0f;					// スタミナ(100.0f)
		float			m_basicSpeed = 100.0f;				// 基本速度(100.0f)
	};
	PlayerStatus		playerStatus;						// プレイヤーのステータス

	float				m_invincibleTimer = 5.0f;			// 無敵時間
	float				m_addSpped = 1.0f;					// 乗算速度

	bool				m_takeDamageflag = true;			// ダメージを受けるフラグ
};


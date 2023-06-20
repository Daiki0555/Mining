#pragma once
class Crystal;

namespace 
{
	const int	HIT_POINT = 150;			// HP
	const int	ATTACK_POWER = 25;			// 攻撃力
	const float	STAMINA = 100.0f;			// スタミナ
	const float BASIC_SPEED = 150.0f;		// 移動速度

	const float INVINCIBLE_TIMER = 5.0f;	// 無敵時間
}

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

	bool HitCrstal(Vector3 position);

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
	void SetPosition(const Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// スケールを設定する
	/// </summary>
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// 回転を設定する
	/// </summary>
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}

	/// <summary>
	/// クリスタルの総数を取得
	/// </summary>
	const int GetCrystalSum() const {
		return m_haveCrystals.size();
	}

	enum enActionState {
		m_enActionState_Idle,			// 待機
		m_enActionState_Walk,			// 歩く
		m_enActionState_Run,			// 走る
		m_enActionState_Dig,			// 掘る
		m_enActionState_Damage,		// 被弾
		m_enActionState_Death,		// 死亡
		m_enActionState_Clear			// クリア
	};

	/// <summary>
	/// 現在のステートを返す
	/// </summary>
	const enActionState GetActionState() const {
		return m_actionState;
	}

	/// <summary>
	/// プレイヤーのHPを参照する
	/// </summary>
	/// <returns></returns>
	const int GetHitPoint() const {
		return m_playerStatus.m_hitPoint;
	}

	/// <summary>
	/// プレイヤーのスタミナを参照する
	/// </summary>
	/// <returns></returns>
	const int GetStamina() const {
		return m_playerStatus.m_stamina;
	}

private:
	/// <summary>
	/// クリスタルの数を追加
	/// </summary>
	/// <param name="num">レア度</param>
	/// <returns></returns>
	void AddCrystalNum(const int& num){
		m_haveCrystals.push_back(num);
	}

	enActionState m_actionState;

	enum enAnimationClip {
		m_en_AnimationClips_Idle,		// 待機
		m_en_AnimationClips_Walk,		// 歩く
		m_en_AnimationClips_Run,		// 走る
		m_en_AnimationClips_Dig,		// 掘る
		m_en_AnimationClips_Damage,		// 被弾
		m_en_AnimationClips_Death,		// 死亡
		m_en_AnimationClips_Clear,		// クリア
		m_en_AnimationClips_Num
	};
	AnimationClip m_enAnimationClips[m_en_AnimationClips_Num];

// --------------------------------------------------------
	ModelRender			m_modelRender;							// モデルレンダー

	CharacterController m_characterController;					// キャラクターコントローラー
	SphereCollider		m_sphereCollider;						// スフィアコライダー


	Vector3				m_position = Vector3::Zero;				// 自身の座標
	Vector3				m_scale = Vector3::One;					// 自身のスケール
	Vector3				m_moveSpeed = Vector3::Zero;			// 移動速度

	Quaternion			m_rotation= Quaternion::Identity;		// 自身の回転

	Crystal*			m_crystal = nullptr;					// クリスタル

	struct PlayerStatus {
		int				m_hitPoint = HIT_POINT;					// HP
		int				m_attackPower = ATTACK_POWER;			// 攻撃力
		float			m_stamina = STAMINA;					// スタミナ
		float			m_basicSpeed = BASIC_SPEED;				// 基本速度
	};
	PlayerStatus		m_playerStatus;							// プレイヤーのステータス

	float				m_invincibleTimer = INVINCIBLE_TIMER;	// 無敵時間
	float				m_addSpped = 0.0f;						// 乗算速度

	bool				m_canDamageflag = true;					// ダメージを受けられるかどうか

	std::list<int>		m_haveCrystals;							// 所持しているクリスタル
};


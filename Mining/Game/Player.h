#pragma once
class Game;
class Crystal;
class PressAndHoldGauge;

namespace 
{
	const int	HIT_POINT = 150;			// HP
	const int	ATTACK_POWER = 25;			// 攻撃力
	const float	STAMINA = 100.0f;			// スタミナ
	const float BASIC_SPEED = 150.0f;		// 移動速度

	const float INVINCIBLE_TIMER = 5.0f;	// 無敵時間
	const float RECOVERY_TIMER = 2.0f;		// スタミナが回復するまでの時間

	const float ADDSPEED = 0.5f;			// ダッシュ時の加算速度
}

class Player :public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// アニメーションのロード
	/// </summary>
	void LoadAnimation();
	/// <summary>
	/// アニメーションの再生
	/// </summary>
	void PlayAnimation();
	/// <summary>
	/// 回転処理
	/// </summary>
	void Rotation();
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// 被弾処理
	/// </summary>
	/// <param name="attackPower">相手の攻撃力</param>
	void Damage(int attackPower);
	/// <summary>
	/// 採掘処理
	/// </summary>
	void Dig();
	/// <summary>
	/// 死亡処理
	/// </summary>
	void Death();
	/// <summary>
	/// クリアしているかどうかを判定
	/// </summary>
	void IsClear();
	/// <summary>
	/// クリア処理
	/// </summary>
	void Clear();
	/// <summary>
	/// クリスタルとの衝突判定
	/// </summary>
	/// <param name="targetPosition">目的の座標</param>
	/// <returns></returns>
	bool CrystalAndHit(Vector3 targetPosition);

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
	inline std::vector<Crystal*> GetCrystalList() const {
		return m_haveCrystals;
	}

	enum enActionState {
		m_enActionState_Idle,			// 待機
		m_enActionState_Walk,			// 歩く
		m_enActionState_Run,			// 走る
		m_enActionState_Dig,			// 掘る
		m_enActionState_Damage,			// 被弾
		m_enActionState_Death,			// 死亡
		m_enActionState_Clear			// クリア
	};

	/// <summary>
	/// ステートを設定する
	/// </summary>
	/// <param name="state"></param>
	void SetActionState(enActionState state) {
		m_actionState = state;
	}

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

	/// <summary>
	/// ダメージを受けられるかどうかのフラグを参照する
	/// </summary>
	/// <returns></returns>
	const bool GetCanDamege() const {
		return m_canAddDamage;
	}

private:
	enActionState			m_actionState = m_enActionState_Idle;

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
	AnimationClip			m_enAnimationClips[m_en_AnimationClips_Num];

// --------------------------------------------------------
	ModelRender				m_modelRender;									// モデルレンダー

	CharacterController		m_characterController;							// キャラクターコントローラー
	SphereCollider			m_sphereCollider;								// スフィアコライダー


	Vector3					m_position = Vector3::Zero;						// 自身の座標
	Vector3					m_scale = Vector3::One;							// 自身のスケール
	Vector3					m_basicSpeed = Vector3::Zero;					// 移動速度
	Vector3					m_crystalPosition = Vector3::Zero;				// 獲得するクリスタルの座標

	Quaternion				m_rotation= Quaternion::Identity;				// 自身の回転

	Game*					m_game = nullptr;								// ゲーム
	Crystal*				m_crystal = nullptr;							// クリスタル
	Crystal*				m_getCrystal = nullptr;							// 獲得したクリスタル
	PressAndHoldGauge*		m_pressAndHoldGauge = nullptr;					// 円形ゲージ

	std::vector<Crystal*>	m_haveCrystals;									// 所持しているクリスタル

	struct PlayerStatus {
		int					m_hitPoint = HIT_POINT;							// HP
		int					m_attackPower = ATTACK_POWER;					// 攻撃力
		float				m_stamina = STAMINA;							// スタミナ
		float				m_basicSpeed = BASIC_SPEED;						// 基本速度
	};
	PlayerStatus			m_playerStatus;									// プレイヤーのステータス

	float					m_recoveryTimer = RECOVERY_TIMER;				// スタミナが回復し始めるまでの時間
	float					m_invincibleTimer = INVINCIBLE_TIMER;			// 無敵時間
	float					m_addSpped = 0.0f;								// 乗算する移動速度
	float					m_addValue = ADDSPEED;							// 移動速度と比較するための変数

	bool					m_canAddDamage = true;							// ダメージを受けられるかどうか
	bool					m_isDig = false;								// 採掘しているかどうか
};


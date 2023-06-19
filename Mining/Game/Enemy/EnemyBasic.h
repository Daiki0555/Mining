#pragma once
class Player;
class EnemyBasic:public IGameObject
{
public:
	EnemyBasic();
	virtual ~EnemyBasic() = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="attackPower">攻撃力</param>
	/// <param name="moveSpeed">基本移動速度</param>
	/// <param name="radius">キャラクターコントローラーの半径</param>
	/// <param name="hight">キャラクターコントローラーの高さ</param>
	/// <returns></returns>
	bool Start(int attackPower, float moveSpeed, float radius, float height);

	void Rotation(Vector3 rotaion);
	void Move();
	void SearchPlayer();
	void Attack();
	void Damege();
	void Dizzy();

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// 座標を取得する
	/// </summary>
	/// <returns></returns>
	const Vector3 GetPosition() const {
		return m_position;
	}

	/// <summary>
	/// スケールを設定
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}

protected:
	enum ActionState {
		m_ActionState_Idle,					// 待機
		m_ActionState_Move,					// 移動
		m_ActionState_Attack,				// 攻撃
		m_ActionState_Damage,				// 被弾
	};
	ActionState m_actionState = m_ActionState_Idle;

	enum EnAnimationClip {
		m_en_AnimationClips_Idle,			// 待機
		m_en_AnimationClips_Move,			// 移動
		m_en_AnimationClips_Attack,			// 攻撃
		m_en_AnimationClips_Damage,			// 被弾
		m_en_AnimationClips_Num
	};
	AnimationClip m_EnanimationClips[m_en_AnimationClips_Num];

// -----------------------------------------------------------
	Player*				m_player = nullptr;						// プレイヤー

	CharacterController	m_characterController;					// キャラクターコントローラー

	ModelRender			m_modelRender;							// モデルレンダー

	Vector3				m_position = Vector3::Zero;				// 自身の座標
	Vector3				m_scale = Vector3::One;					// 自身のスケール
	Quaternion			m_rotation = Quaternion::Identity;		// 自身の回転

	struct EnemyStatus {
		int				m_attackPower = 0;						// 攻撃力
		float			m_moveSpeed = 0.0f;						// 移動速度
	};
	EnemyStatus			enemyStatus;							// エネミーのステータス
};


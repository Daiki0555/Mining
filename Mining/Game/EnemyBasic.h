#pragma once
class EnemyBasic:public IGameObject
{
public:
	EnemyBasic();
	~EnemyBasic();

	bool Start();

	void Rotation();
	void Move();
	void SearchPlayer();
	void Attack();
	void Damege();
	void Dizzy();

	/// <summary>
	/// ステータスを設定するs
	/// </summary>
	/// <param name="attackPower">攻撃力</param>
	/// <param name="moveSpeed">移動速度</param>
	void SetStatus(float attackPower, float moveSpeed) {
		m_AttackPower = attackPower;
		m_MoveSpeed = moveSpeed;
	}

	/// <summary>
	/// 攻撃力を参照する
	/// </summary>
	/// <returns></returns>
	float GetAttackPower() {
		return m_AttackPower;
	}

private:
	enum m_ActionState {
		m_ActionState_Idle,					// 待機
		m_ActionState_Move,					// 移動
		m_ActionState_Attack,				// 攻撃
		m_ActionState_Damege,				// 被弾
	};

	enum m_AnimationState {
		m_AnimationState_Idle,				// 待機
		m_AnimationState_Move,				// 移動
		m_AnimationState_Attack,			// 攻撃
		m_AnimationState_Damege,			// 被弾
	};

	enum EnAnimationClip {
		m_en_AnimationClips_Idle,				// 待機
		m_en_AnimationClips_Move,				// 移動
		m_en_AnimationClips_Attack,				// 攻撃
		m_en_AnimationClips_Damege,				// 被弾
		m_en_AnimationClips_Num
	};
	EnAnimationClip m_En_AnimationClips[m_en_AnimationClips_Num];

// -----------------------------------------------------------

	ModelRender		m_ModelRender;						// モデルレンダー

	Vector3			m_Position = Vector3::Zero;			// 自身の座標
	Vector3			m_Scale = Vector3::Zero;			// 自身のスケール
	Quaternion		m_Rotation = Quaternion::Identity;	// 自身の回転

	float			m_AttackPower = 0.0f;				// 攻撃力
	float			m_MoveSpeed = 0.0f;					// 移動速度
};


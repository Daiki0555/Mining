#pragma once

class Player;

namespace
{
	const float STOP_TIME = 5.0f;		// 行動を停止する時間
}

class EnemyBasic:public IGameObject
{
public:
	EnemyBasic();
	virtual ~EnemyBasic() = 0;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="attackPower">攻撃力</param>
	/// <param name="moveSpeed">基本移動速度</param>
	/// <param name="radius">キャラクターコントローラーの半径</param>
	/// <param name="hight">キャラクターコントローラーの高さ</param>
	/// <returns></returns>
	bool Start(int attackPower, float moveSpeed, float radius, float height);
	/// <summary>
	/// 回転処理
	/// </summary>
	void Rotation(Vector3 rotaion);
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// 待機時の処理
	/// </summary>
	void Idle();
	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack();
	/// <summary>
	/// 被弾処理
	/// </summary>
	void Damege();
	/// <summary>
	/// 行動を停止する
	/// </summary>
	void StopAction();
	/// <summary>
	/// 壁との衝突判定
	/// </summary>
	/// <param name="targetPosition">目的の座標</param>
	/// <returns></returns>
	bool WallAndHit(Vector3 targetPosition);

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

	/// <summary>
	/// 描画するかどうか決定する
	/// <param name="flag">trueなら描画する</param>
	void SetCanDrawFlag(bool flag) {
		m_canDraw = flag;
	}

	/// <summary>
	/// 描画しているかどうかを取得する
	/// </summary>
	bool GetCanDrawFlag() {
		return m_canDraw;
	}

protected:
	enum enActionState {
		m_enActionState_Idle,				// 待機
		m_enActionState_Move,				// 移動
		m_enActionState_Attack,				// 攻撃
		m_enActionState_Damage,				// 被弾
		m_enActionState_StopAction,			// 行動停止
	};
	enActionState		m_actionState = m_enActionState_Move;			// 行動ルーチン

	enum enAnimationClip {
		m_enAnimationClips_Idle,			// 待機
		m_enAnimationClips_Move,			// 移動
		m_enAnimationClips_Attack,			// 攻撃
		m_enAnimationClips_Damage,			// 被弾
		m_enAnimationClips_Num
	};
	AnimationClip		m_enAnimationClips[m_enAnimationClips_Num];		// アニメーションクリップ

// -----------------------------------------------------------
	Player*				m_player = nullptr;								// プレイヤー

	CharacterController	m_characterController;							// キャラクターコントローラー
	SphereCollider		m_sphereCollider;								// スフィアコライダー

	ModelRender			m_modelRender;									// モデルレンダー

	Vector3				m_position = Vector3::Zero;						// 自身の座標
	Vector3				m_scale = Vector3::One;							// 自身のスケール
	Quaternion			m_rotation = Quaternion::Identity;				// 自身の回転

	struct EnemyStatus {
		int				m_attackPower = 0;								// 攻撃力
		float			m_basicSpeed = 0.0f;							// 移動速度
	};

private:
	EnemyStatus			m_enemyStatus;									// エネミーのステータス

	float				m_StopTimer = STOP_TIME;						// 行動を停止するタイマー
	bool				m_canDraw = true;								// 描画できるかどうか
};


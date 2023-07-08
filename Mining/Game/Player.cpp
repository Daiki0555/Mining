#include "stdafx.h"
#include "Player.h"
#include "Scene/Game.h"
#include "Stage/Object/Crystal.h"
#include "UI/PressAndHoldGauge.h"

#define	DELTA_TIME 1.0f/60.0f						// Œo‰ßŠÔ

namespace
{
	const float RUN_SPEED = 2.5f;					// ƒ_ƒbƒVƒ…‚ÌˆÚ“®‘¬“x
	const float WALKING_SPEED = 1.0f;				// •à‚¢‚Ä‚¢‚é‚ÌˆÚ“®‘¬“x

	const float DECREASE_STAMINA_VALUE = 15.0f;		// ƒ_ƒbƒVƒ…‚ÌƒXƒ^ƒ~ƒiÁ”ï‘¬“x
	const float INCREASE_STAMINA_VALUE = 10.0f;		// ƒXƒ^ƒ~ƒi‰ñ•œ‘¬“x

	const float LINEAR_COMPLETION = 1.0f;			// üŒ`•âŠ®

	const float Y_POSITION = 25.0f;					// Õ“Ë”»’è‚ÌYÀ•W

	const float ADD_LENGTH = 0.7f;					// ‰ÁZ‚·‚é’·‚³
	const float NOT_DRAW_LENGTH = 100.0f;			// •`‰æ‚µ‚È‚¢’·‚³

	const int	STAMINA_MIN = 1;					// ƒXƒ^ƒ~ƒi‚ÌÅ’á’l
	const int	STAMINA_MAX = STAMINA;				// ƒXƒ^ƒ~ƒi‚ÌÅ‘å’l

	const int	HP_MIN = 0;							// HP‚ÌÅ’á’l
}

Player::Player() 
{
}

Player::~Player()
{
	m_haveCrystals.clear();

	for (int i = 0; i < m_haveCrystals.size(); i++) {
		DeleteGO(m_haveCrystals[i]);
	}
}

bool Player::Start()
{
	// ƒCƒ“ƒXƒ^ƒ“ƒX‚ğ’T‚·
	m_game = FindGO<Game>("game");
	m_crystal = FindGO<Crystal>("crystal");
	m_pressAndHoldGauge = FindGO<PressAndHoldGauge>("pressAndHoldGauge");

	LoadAnimation();

	m_modelRender.Init("Assets/modelData/player/unityChan.tkm", m_enAnimationClips, m_en_AnimationClips_Num, enModelUpAxisY, true);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_characterController.Init(25.0f, 75.0f, m_position);	// ƒLƒƒƒ‰ƒNƒ^[ƒRƒ“ƒgƒ[ƒ‰[‚ğ‰Šú‰»

	// ƒXƒtƒBƒAƒRƒ‰ƒCƒ_[‚ğİ’è
	m_sphereCollider.Create(10.0f);

	m_modelRender.Update();

	return true;
}

void Player::Update()
{
	// ‘Ì—Í‚ª0‚Ì‚Æ‚«
	if (m_playerStatus.m_hitPoint <= HP_MIN) {

		// •â³
		m_playerStatus.m_hitPoint = HP_MIN;

		Death();				// €–S‚·‚é
	}
	else {
		Move();					// ˆÚ“®
		Rotation();				// ‰ñ“]

		// Bƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½‚Æ‚«
		if (g_pad[0]->IsPress(enButtonB)) {
			// ÌŒ@‚·‚é
			Dig();
		}
		else {
			// Šp“x‚ğŒ¸‚ç‚·
			m_pressAndHoldGauge->SetChangeGaugeAngle(false);

			// ‰~Œ`ƒQ[ƒW‚ÌÀ•W(Bƒ{ƒ^ƒ“‚ğ‰Ÿ‚µ‚½‚Æ‚«‚Ì©g‚ÌÀ•W)‚ÖŒü‚©‚¤ƒxƒNƒgƒ‹‚ğì¬
			Vector3 diff = m_pressAndHoldGauge->Get3DPosition() - m_position;

			if (m_pressAndHoldGauge->GetNowStatus() == m_pressAndHoldGauge->enGaugeState_Max ||
				diff.Length() >= NOT_DRAW_LENGTH) {
				// ‰~Œ`ƒQ[ƒW‚ğƒŠƒZƒbƒg
				m_pressAndHoldGauge->ResetGaugeAngle();
			}
		}

		// ƒXƒ^ƒ~ƒi‚ªÅ‘å’l‚Å‚È‚¢@‚©‚Â@Aƒ{ƒ^ƒ“‚ª“ü—Í‚³‚ê‚Ä‚¢‚È‚¢‚Æ‚«
		if (m_playerStatus.m_stamina < STAMINA_MAX &&
			m_actionState != m_enActionState_Run) {

			m_recoveryTimer -= g_gameTime->GetFrameDeltaTime();

			if (m_recoveryTimer <= 0.0f) {
				// ƒXƒ^ƒ~ƒi‚ğ‘‚â‚·
				m_playerStatus.m_stamina += g_gameTime->GetFrameDeltaTime() * INCREASE_STAMINA_VALUE;
			}
		}
		else {
			m_recoveryTimer = RECOVERY_TIMER;		// ƒ^ƒCƒ}[‚ğƒŠƒZƒbƒg
		}

		if (m_actionState == m_enActionState_Invincible) {
			m_invincibleTimer -= g_gameTime->GetFrameDeltaTime();

			// ƒ^ƒCƒ}[‚ª0.0fˆÈ‰º‚Ì‚Æ‚«
			if (m_invincibleTimer < 0.0f) {
				m_canAddDamage = true;
				m_invincibleTimer = INVINCIBLE_TIMER;			// ƒ^ƒCƒ}[‚ğƒŠƒZƒbƒg
			}
		}
	}

	PlayAnimation();		// ƒAƒjƒ[ƒVƒ‡ƒ“

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_modelRender.Update();
}

void Player::LoadAnimation()
{
	m_enAnimationClips[m_en_AnimationClips_Idle].Load("Assets/animData/player/idle.tka");
	m_enAnimationClips[m_en_AnimationClips_Idle].SetLoopFlag(true);

	m_enAnimationClips[m_en_AnimationClips_Walk].Load("Assets/animData/player/walk.tka");
	m_enAnimationClips[m_en_AnimationClips_Walk].SetLoopFlag(true);

	m_enAnimationClips[m_en_AnimationClips_Run].Load("Assets/animData/player/run.tka");
	m_enAnimationClips[m_en_AnimationClips_Run].SetLoopFlag(true);

	//m_EnAnimationClips[m_en_AnimationClips_Dig].Load("Assets/animData/player/dig.tka");
	//m_EnAnimationClips[m_en_AnimationClips_Dig].SetLoopFlag(true);

	m_enAnimationClips[m_en_AnimationClips_Damage].Load("Assets/animData/player/damage.tka");
	m_enAnimationClips[m_en_AnimationClips_Damage].SetLoopFlag(false);

	m_enAnimationClips[m_en_AnimationClips_Death].Load("Assets/animData/player/KneelDown.tka");
	m_enAnimationClips[m_en_AnimationClips_Death].SetLoopFlag(false);

	m_enAnimationClips[m_en_AnimationClips_Clear].Load("Assets/animData/player/clear.tka");
	m_enAnimationClips[m_en_AnimationClips_Clear].SetLoopFlag(false);
}

void Player::PlayAnimation()
{
	switch (m_actionState) {
	case m_enActionState_Idle:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Idle, LINEAR_COMPLETION);
		break;
	case m_enActionState_Walk:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Walk, LINEAR_COMPLETION);
		break;
	case m_enActionState_Run:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Run, LINEAR_COMPLETION);
		break;
	case m_enActionState_Dig:
		//m_modelRender.PlayAnimation(m_en_AnimationClips_Dig, LINEAR_COMPLETION);
		break;
	case m_enActionState_Damage:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Damage, LINEAR_COMPLETION);
		break;
	case m_enActionState_Death:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Death, LINEAR_COMPLETION);
		break;
	case m_enActionState_Clear:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Clear, LINEAR_COMPLETION);
		break;
	}
}

void Player::Rotation()
{
	// ƒXƒeƒBƒbƒN‚Ì“ü—Í‚ª‚ ‚Á‚½‚ç
	if (fabsf(m_basicSpeed.x) >= 0.001 || fabsf(m_basicSpeed.z) >= 0.001) {
		// ƒLƒƒƒ‰ƒNƒ^[‚Ì•ûŒü‚ğ•Ï‚¦‚é
		m_rotation.SetRotationYFromDirectionXZ(m_basicSpeed);
		m_modelRender.SetRotaition(m_rotation);
	}
	else {
		// ‚È‚¢ê‡‚Í‘Ò‹@ó‘Ô‚É‚·‚é
		m_actionState = m_enActionState_Idle;
	}
}

void Player::Move()
{
	// ƒQ[ƒW‚ª“®‚¢‚Ä‚¢‚éŠÔ‚Í“®‚©‚³‚È‚¢
	if (m_pressAndHoldGauge->GetNowStatus() == m_pressAndHoldGauge->enGaugeState_Increase) {
		return;
	}

	m_basicSpeed.x = 0.0f;
	m_basicSpeed.z = 0.0f;

	// ƒQ[ƒ€ƒpƒbƒh‚Ì“ü—Í—Ê‚ğQÆ‚·‚é
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	// ƒJƒƒ‰‚Ì‘O•ûŒü‚Æ‰E•ûŒü‚ÌƒxƒNƒgƒ‹‚ğ‚Á‚Ä‚­‚é
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	// y•ûŒü‚É‚ÍˆÚ“®‚³‚¹‚È‚¢
	forward.y = 0.0f;
	right.y = 0.0f;

	if (g_pad[0]->IsPress(enButtonA) && m_playerStatus.m_stamina > STAMINA_MIN) {

		// ƒXƒeƒBƒbƒN‚Ì“ü—Í‚ª‚ ‚Á‚½‚Æ‚«
		if (fabsf(stickL.x) >= 0.001 || fabsf(stickL.y) >= 0.001) {
			// ƒ{ƒ^ƒ“‚ğ‰Ÿ‚µ‚Ä‚¢‚éŠÔƒ_ƒbƒVƒ…
			m_actionState = m_enActionState_Run;

			// ƒXƒ^ƒ~ƒi‚ğŒ¸‚ç‚·
			//m_playerStatus.m_stamina -= g_gameTime->GetFrameDeltaTime() * DECREASE_STAMINA_VALUE;

			m_addValue += ADDSPEED;
			m_addSpped = min(m_addValue, RUN_SPEED);
		}
	}
	else {
		// ‰Ÿ‚µ‚Ä‚¢‚È‚¢‚Æ‚«‚Í•à‚­
		m_actionState = m_enActionState_Walk;

		m_addSpped = WALKING_SPEED;
	}

	// ƒXƒeƒBƒbƒN‚Ì“ü—Í—Ê~ˆÚ“®‘¬“x~æZ‘¬“x‚ÅÅI“I‚ÈˆÚ“®‘¬“x‚ğŒvZ‚·‚é
	right *= stickL.x * m_playerStatus.m_basicSpeed * m_addSpped;
	forward *= stickL.y * m_playerStatus.m_basicSpeed * m_addSpped;

	// ˆÚ“®‘¬“x‚Éã‹L‚ÅŒvZ‚µ‚½ƒxƒNƒgƒ‹‚ğ‰ÁZ
	m_basicSpeed += right + forward;

	m_position = m_characterController.Execute(m_basicSpeed, DELTA_TIME);

	m_modelRender.SetPosition(m_position);
}

void Player::Attack()
{
}

void Player::Damage(int attackPower)
{
	if (m_actionState == m_enActionState_Invincible) {
		return;
	}

	m_actionState = m_enActionState_Damage;				// ”í’eƒ‚[ƒVƒ‡ƒ“‚ğÄ¶
	m_playerStatus.m_hitPoint -= attackPower;			// ƒ_ƒ[ƒW—Ê‚ğHP‚©‚çˆø‚­
	
	// ƒ_ƒ[ƒW‚ğó‚¯‚ç‚ê‚éó‘Ô‚Ì‚Æ‚«
	if (m_canAddDamage) {
		m_canAddDamage = false;							// ˜A‘±‚µ‚Äƒ_ƒ[ƒW‚ğó‚¯‚È‚¢
		m_actionState = m_enActionState_Invincible;		// –³“Gó‘Ô
	}
}

struct CrashedCrystal :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;		// Õ“Ëƒtƒ‰ƒO

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normallnWorldSpace) 
	{
		// Õ“Ë‚µ‚Ä‚¢‚È‚©‚Á‚½‚ç
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Crystal) {
			return 0.0f;
		}
		
		isHit = true;
		return 0.0f;
	}
};

bool Player::CrystalAndHit(Vector3 targetPosition)
{
	btTransform start, end;

	start.setIdentity();
	end.setIdentity();

	// n“_‚ÆI“_‚ğİ’è
	start.setOrigin(btVector3(m_position.x, Y_POSITION, m_position.z));
	end.setOrigin(btVector3(targetPosition.x, Y_POSITION, targetPosition.z));

	CrashedCrystal callback;

	// ƒRƒ‰ƒCƒ_[‚ğn“_‚©‚çI“_‚Ü‚Å“®‚©‚µ‚ÄÕ“Ë‚µ‚½‚©’²‚×‚é
	PhysicsWorld::GetInstance()->ConvexSweepTest(
		(const btConvexShape*)m_sphereCollider.GetBody(),
		start, 
		end, 
		callback);

	// Õ“Ë‚µ‚½‚È‚çfalse‚ğ•Ô‚·
	if (callback.isHit) {
		return false;
	}

	return true;
}

void Player::Dig()
{
	Vector3 diff = Vector3::Zero;

	if (!m_isDig) {
		// ƒNƒŠƒXƒ^ƒ‹‚Ì•ê”‚ğæ“¾
		int crystalNum = m_game->GetCrystalList().size();

		// ï¿½ÌŒ@ï¿½ï¿½ï¿½Ä‚ï¿½ï¿½ï¿½Æ‚ï¿½
		if (m_isDig) {
			m_isDig = false;
			return;
		}

		for (int i = 0; i < crystalNum; i++) {
			// À•W‚ğæ“¾
			Vector3 crystalPos = m_game->GetCrystalList()[i]->GetPosition();
			// ©g‚ÌÀ•W‚©‚çƒNƒŠƒXƒ^ƒ‹‚ÖŒü‚©‚¤ƒxƒNƒgƒ‹‚ğì¬
			diff = crystalPos - m_position;

			// Õ“Ë‚µ‚Ä‚¢‚é‚È‚ç
			if (!CrystalAndHit(m_position + (diff * ADD_LENGTH))) {
				// ‰~Œ`ƒQ[ƒW‚ğ•`‰æ‚·‚é
				m_pressAndHoldGauge->SetCanDrawGauge(true);
				// ©g‚ÌÀ•W‚ğ‹³‚¦‚é
				m_pressAndHoldGauge->Set3DPosition(m_position);
				// ƒNƒŠƒXƒ^ƒ‹‚ğ•Û‘¶
				m_getCrystal = m_game->GetCrystalList()[i];
				m_crystalPosition = crystalPos;
				// Šp“x‚ğ‘‚â‚·
				m_pressAndHoldGauge->SetChangeGaugeAngle(true);
				m_isDig = true;
				break;
			}

			// ‰~Œ`ƒQ[ƒW‚ğ•`‰æ‚·‚é
			m_pressAndHoldGauge->SetCanDrawGauge(false);
		}
	}
	else {
		// ©g‚ÌÀ•W‚©‚çƒNƒŠƒXƒ^ƒ‹‚ÖŒü‚©‚¤ƒxƒNƒgƒ‹‚ğì¬
		diff = m_crystalPosition - m_position;

		// ˆê’èˆÈã—£‚ê‚½‚ç
		if (diff.Length() >= NOT_DRAW_LENGTH) {
			// ÌŒ@‚µ‚È‚¢
			m_isDig = false;
			return;
		}

		// ƒQ[ƒW‚ªÅ‘å‚Å‚È‚¢‚Æ‚«ˆÈ‰º‚Ìˆ—‚ÍÀs‚µ‚È‚¢
		if (m_pressAndHoldGauge->GetNowStatus() != m_pressAndHoldGauge->enGaugeState_Min) {
			return;
		}

		//m_game->GetCrystalList().erase(
		//	std::remove(m_game->GetCrystalList().begin(), m_game->GetCrystalList().end(),m_getCrystal),
		//	m_game->GetCrystalList().end()
		//);

		//while (it != m_game->GetCrystalList().end()) {
		//	if (*it == m_getCrystal) {
		//		it = m_game->GetCrystalList().erase(it);
		//	}
		//	else {
		//		it++;
		//	}
		//}

		// Šl“¾ˆ—
		m_getCrystal->SetDrawFlag(false);
		m_haveCrystals.push_back(m_getCrystal);

		// ‰~Œ`ƒQ[ƒW‚ğƒŠƒZƒbƒg‚·‚é
		m_pressAndHoldGauge->ResetGaugeAngle();

		m_getCrystal = nullptr;
	}
}

void Player::Death()
{
	m_actionState = m_enActionState_Death;
}

void Player::Clear()
{
	m_actionState = m_enActionState_Clear;
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
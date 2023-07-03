#include "stdafx.h"
#include "PhysicsGhost.h"

PhysicsGhost::PhysicsGhost()
{
}

PhysicsGhost::~PhysicsGhost()
{
}

bool PhysicsGhost::Start()
{
	// ÉSÅ[ÉXÉgÇçÏê¨Ç∑ÇÈ
	m_physicsGhostObjct.CreateBox(
		m_position,
		m_rotation,
		m_scale
	);

	return true;
}

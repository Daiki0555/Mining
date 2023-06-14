#include "k2EngineLowPreCompile.h"
#include "SpotLight.h"

namespace nsK2EngineLow {
	SpotLight::SpotLight()
	{

	}

	SpotLight::~SpotLight()
	{

	}

	void SpotLight::Update()
	{
		RenderingEngine::GetInstance()->SetSpotLight(m_spNum, m_spotLig);
	}
}

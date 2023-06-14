#include "k2EngineLowPreCompile.h"
#include "PointLight.h"
namespace nsK2EngineLow {

	PointLight::PointLight()
	{

	}

	PointLight::~PointLight()
	{

	}

	void PointLight::Update()
	{
		RenderingEngine::GetInstance()->SetPointLight(m_ptNum, m_pointLig);
	}

}
#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "graphics/Model.h"
namespace nsk2EngineLow {

	ModelRender::ModelRender()
	{

	}

	ModelRender::~ModelRender()
	{

	}

	void ModelRender::Init(
		const char* filePath

	)
	{
		//�X�P���g���̏�����
		InitSkeleton(filePath);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		
	}
}
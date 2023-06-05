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
		//ƒXƒPƒ‹ƒgƒ“‚Ì‰Šú‰»
		InitSkeleton(filePath);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		
	}
}
#include "k2EngineLowPreCompile.h"
#include "Level2DRender.h"
#include "level2D/CaslFile.h"

namespace nsK2EngineLow {
	void Level2DRender::Init(
		const char* filePath,
		std::function<bool(Level2DObjeData& objData)>hookFunc
	)
	{
		CaslFile casl;
		casl.Load(filePath);
		//構築
		for (int i= 0; i < casl.GetNumCaslData(); i++)
		{
			auto caslData = casl.GetCaslData(i);
			Level2DObjeData objData;
			objData.scale.x = caslData->scale.x;
			objData.scale.y = caslData->scale.y;
			objData.position.x = caslData->position.x;
			objData.position.y = caslData->position.y;
			objData.width = caslData->width;
			objData.height = caslData->height;
			objData.ddsFilePath = caslData->ddsFilePath.get();
			objData.pivot = caslData->pivot;
			auto isHook = false;
			if (hookFunc != nullptr) {
				//hook関数が指定されているのでhook関数を呼び出し
				isHook = hookFunc(objData);
			}
		}
	}
}
#pragma once
#include "geometry/AABB.h"
#include "graphics/Model.h"
#include "k2EngineLowPreCompile.h"
namespace nsk2EngineLow {
	class ModelRender
	{
	public:
		ModelRender();
		~ModelRender();
		/// <summary>
		/// モデルの初期化
		/// </summary>
		/// <param name="filePath"></param>
		void Init(
			const char* filePath
		);

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update();
		


	private:
		/// <summary>
		/// スケルトンの初期化
		/// </summary>
		/// <param name="filePath"></param>
		void InitSkeleton(const char* filePath);

	private:
		
	};
};



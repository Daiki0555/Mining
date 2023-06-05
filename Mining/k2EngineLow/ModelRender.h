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
		/// ���f���̏�����
		/// </summary>
		/// <param name="filePath"></param>
		void Init(
			const char* filePath
		);

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update();
		


	private:
		/// <summary>
		/// �X�P���g���̏�����
		/// </summary>
		/// <param name="filePath"></param>
		void InitSkeleton(const char* filePath);

	private:
		
	};
};



#pragma once
#include "level3D/TklFile.h"
namespace nsK2EngineLow {

	struct LevelObjectData {
		Vector3			position;		//���W
		Quaternion		rotaition;		//��]
		Vector3			scale;			//�傫��
		const wchar_t* name;			//���O
		int				number = 0;		//�ԍ�

		/// <summary>
		/// �I�u�W�F�N�g������������
		/// </summary>
		/// <param name="objName">�I�u�W�F�N�g��</param>
		/// <returns>���S��v�Ȃ�true</returns>
		bool EqualObjectName(const wchar_t* objName)
		{
			return wcscmp(objName, name) == 0;
		}

		bool ForwardMatchName(const wchar_t* objName)
		{
			auto len = wcslen(objName);
			auto namelen = wcslen(name);

			if (len > namelen)
			{
				//���O�������̂ŕs��v
			}
			return wcsncmp(objName, name, len) == 0;
		}


	};
	/// <summary>
	/// �����_���[�N���X
	/// </summary>
	class LevelRender : public Noncopyable
	{
	public:
		LevelRender();
		~LevelRender();
		/// <summary>
		/// ����������
		/// </summary>
		void Init(const char* filePath, std::function<bool(LevelObjectData& objData)>hookFunc);

	private:
		/// <summary>
		/// Tkl�t�@�C���̍s���ϊ�����
		/// </summary>
		void MatrixTklToLever();
	private:
		using BonePtr = std::unique_ptr<Bone>;		//�{�[���̃|�C���^
		std::vector<BonePtr>	m_boneList;			//�{�[���̃��X�g
		TklFile					m_tklFile;			//tkl�t�@�C��


	};

}


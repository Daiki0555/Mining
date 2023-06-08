#pragma once
namespace nsK2EngineLow {

	struct CaslData;
	
	struct Level2DObjeData{
		Vector3		position = Vector3::Zero;				//���W
		Quaternion	rotation = Quaternion::Identity;		//��]
		Vector3		scale = Vector3::One;					//�g�嗦
		int			width = 0;								//����
		int			height = 0;								//�c��
		const char* name;									//���O
		const char* ddsFilePath;							//dds�t�@�C���̃t�@�C���p�X
		Vector2		pivot = Sprite::DEFAULT_PIVOT;			//�s�{�b�g

		/// <summary>
		/// �����œn�����I�u�W�F�N�g���̃I�u�W�F�N�g�𒲂ׂ�
		/// </summary>
		/// <param name="objName"></param>
		/// <returns></returns>
		bool EqualObjectName(const char* objName)const
		{
			return strcmp(objName, name) == 0;
		}
		/// <summary>
		/// ���O���O����v���邩���ׂ�B
		/// </summary>
		/// <param name="n"></param>
		/// <returns></returns>
		bool ForwardMatchName(const char* n)const
		{
			auto len = strlen(n);
			auto namelen = strlen(name);
			if (len > namelen) {
				//���O�������B�s��v
				return false;
			}
			return strncmp(n, name, len) == 0;
		}
	};

	/// <summary>
	/// ���x��2D�����_�[�N���X
	/// </summary>
	class Level2DRender
	{
	public:
		/// <summary>
		/// ���x����������
		/// </summary>
		/// <param name="filePath">casl�t�@�C���̃t�@�C���p�X</param>
		/// <param name="hookFunc">�I�u�W�F�N�g���쐬����Ƃ��̏������t�b�N����</param>
		void Init(const char* filePath, std::function<bool(Level2DObjeData& objData)>hookFunc);
	};
}



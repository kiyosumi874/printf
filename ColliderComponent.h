#pragma once
#include "Collision.h"
#include "Tag.h"
#include "Object.h"

class ColliderComponent
{
public:
	// @param �R���X�g���N�^
	ColliderComponent() {};
	// @param �f�X�g���N�^(�p�����override)
	virtual ~ColliderComponent() {};

	class Object* m_pParent;  // Object�N���X�|�C���^�ϐ�

	// @param �R���C�_�[�̃p�����[�^�[�ݒ��������
	// pos �R���C�_�[�̈ʒu  owner �R���C�_�[�����R���|�[�l���g  tag �R���C�_�[�����I�u�W�F�N�g�̃^�O��  type �R���C�_�[�^�C�v
	virtual void Init(const VECTOR& pos, class Component* owner, class Tag* tag, CollisionInfo::CollisionType type) {};

	// @param �R���C�_�[�����I�u�W�F�N�g�̃^�O����Ԃ�
	class Tag* GetTag() { return m_pTag; }
	// @param �R���C�_�[�����I�u�W�F�N�g�̃^�O���𓾂�
	// tag �R���C�_�[�����I�u�W�F�N�g�̃^�O��
	void SetTag(Tag* tag) { m_pTag = tag; }
	// @param �R���C�_�[�����I�u�W�F�N�g�𐶐������I�u�W�F�N�g�̃^�O����Ԃ�
	class Tag* GetParentTag() { return m_pParentTag; }
	// @param �R���C�_�[�����I�u�W�F�N�g�𐶐������I�u�W�F�N�g�̃^�O���𓾂�
	// tag �R���C�_�[�����I�u�W�F�N�g�𐶐������I�u�W�F�N�g�̃^�O��(�R�s�[�Ƃ���)
	void SetParentTag(Tag* tag) { m_pParentTag = tag; }
	// @param �O��̃��[�v�œ��������I�u�W�F�N�g�̃^�O�������炤(�R�s�[�Ƃ���)
	// tag ���������I�u�W�F�N�g�̃^�O��
	void SetOnCollisionTag(class Tag* tag);
	enum class ObjectTag* GetOnCollisionTag(ObjectTag tag);
	void CleanCollisionTag();
	// @param �R���C�_�[�^�C�v��Ԃ�
	CollisionInfo::CollisionType GetCollisionType() { return m_pInfo->m_collType; }
	// @param �����蔻��t���O��Ԃ�
	bool GetOnCollisionFlag() { return m_onCollisionFlag; }
	// @param �����蔻��t���O�𓾂�
	// flag �����蔻���  true �s��  false �s��Ȃ�
	void SetOnCollisionFlag(bool flag) { m_onCollisionFlag = flag; }

	// @prama �����蔻�����������Ă���
	// info �����蔻����
	void SetInfo(const CollisionInfo& info) { *m_pInfo = info; }
	// @param �����蔻�����������
	void ClearInfo();

	// @param �����蔻�����Ԃ�
	CollisionInfo& GetCollisionInfo() { return *m_pInfo; }

	// @param �R���C�_�[�����R���|�[�l���g��Ԃ�
	class Component* GetOwner() { return m_pOwner; }
	// @param �R���C�_�[�����R���|�[�l���g�𓾂�(Component*�ɕϊ�����)
	// owner �R���C�_�[�����R���|�[�l���g
	template<class T>
	class Component* SetOwner(T* owner) { return dynamic_cast<Component*>(owner); }

	// override����Ȃ��ꍇfalse��Ԃ�

	// @param �����蔻������o
	// other ����̃R���C�_�[
	virtual bool CollisionDetection(ColliderComponent* other);
	
	// @param �����蔻�茋�ʂ�Ԃ�
	// other �����̃R���C�_�[
	virtual bool Check(class BoxCollider* other) { return false; }
	// @param �����蔻�茋�ʂ�Ԃ�
	// other �����̃R���C�_�[
	virtual bool Check(class SphereCollider* other) { return false; }
	// @param �����蔻�茋�ʂ�Ԃ�
	// other �����̃R���C�_�[
	virtual bool Check(class WallCollider* other) { return false; }
	// @param �����蔻�茋�ʂ�Ԃ�
	// other �����̃R���C�_�[
	virtual bool Check(class WorldCollider* other) { return false; }
	// @param �����蔻�茋�ʂ�Ԃ�
	// other �����̃R���C�_�[
	virtual bool Check(class GroundCollider* other) { return false; }

	// @ param Collider�`��(��Ί֐���`override)
	// DxLib�̃J�����֌W�ňʒu�����܂������Ă��Ȃ��̂ŁA�傫�������邽�߂Ɏg���Ă�������
	virtual void DrawCollider() = 0;

protected:
	class Tag* m_pTag = nullptr;               // �R���C�_�[�����I�u�W�F�N�g�̃^�O��
	class Tag* m_pParentTag = nullptr;         // �e�̔��ʂ��K�v�ȃI�u�W�F�N�g�̂ݎg�p(�N�̒e���Ȃ�)
	std::vector<class Tag> m_onCollisionTag;  // ���������I�u�W�F�N�g�̃^�O��

	class Component* m_pOwner = nullptr;       // �R���C�_�[�����R���|�[�l���g
	class CollisionInfo* m_pInfo = nullptr;    // �����蔻����

	bool m_onCollisionFlag = false;            // �����蔻����s�����ǂ���
};


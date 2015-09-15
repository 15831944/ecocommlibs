#include ".\kplane.h"

KPlane::KPlane(void)
: m_BasePosition()
{
}

KPlane::~KPlane(void)
{
}

KPlane::KPlane(KPosition p0, KVector v0)
{
	m_BasePosition  = p0;
	v0.Nomalize(); 	
	m_NormalVector = v0; 
}

/*-----------------------------------------------------------------------
Ŭ������		: KPlane
�Լ���			: KPlane
���			: 3���� ������ ��� ����
�Ű�����		: KPosition position0 => �� 1
				  KPosition position1 => �� 2
				  KPosition position2 => �� 3
����			: ����
�ۼ�����		: 2007-04-27
������ ��������	: 2007-04-27
�ۼ���			: �����
-----------------------------------------------------------------------*/
KPlane::KPlane(KPosition position0, KPosition position1, KPosition position2)
{
	KVector leg1, leg2;
	KVector normal_vec;

	leg1 = position1 - position0;
	leg2 = position2 - position0;

	ComputeCrossProduct(leg1, leg2, &normal_vec);
	m_BasePosition = position0;

	normal_vec.Nomalize();

    m_NormalVector = normal_vec;

}

/*-----------------------------------------------------------------------
Ŭ������		: KPlane
�Լ���			: ComputeCrossProduct
���			: �� ������ �������
�Ű�����		: KVector leg1 => ���� 1
				  KVector leg2 => ���� 2
				  KVector* out_vec => ��� ����
����			: ����
�ۼ�����		: 2007-04-27
������ ��������	: 2007-04-27
�ۼ���			: �����
-----------------------------------------------------------------------*/
void KPlane::ComputeCrossProduct(KVector leg1, KVector leg2, KVector* out_vec)
{
	out_vec->x = leg1.y * leg2.z - leg1.z * leg2.y;
	out_vec->y = leg1.z * leg2.x - leg1.x * leg2.z;
	out_vec->z = leg1.x * leg2.y - leg1.y * leg2.x;
}

/*-----------------------------------------------------------------------
Ŭ������		: KPlane
�Լ���			: SetBasePosition
���			: Base Position �Է�
�Ű�����		: KPosition base_position => �Է� position
����			: ����
�ۼ�����		: 2007-04-28
������ ��������	: 2007-04-28
�ۼ���			: �����
-----------------------------------------------------------------------*/
void KPlane::SetBasePosition(KPosition base_position)
{
	m_BasePosition = base_position;

}

/*-----------------------------------------------------------------------
Ŭ������		: KPlane
�Լ���			: SetNormalVector
���			: Normal Vector �Է�
�Ű�����		: KVector normal_vector => �Էº���
����			: ����
�ۼ�����		: 2007-04-28
������ ��������	: 2007-04-28
�ۼ���			: �����
-----------------------------------------------------------------------*/
void KPlane::SetNormalVector(KVector normal_vector)
{
	KVector temp;

	temp = normal_vector;

	temp.Nomalize();

	m_NormalVector = temp;
}

/*-----------------------------------------------------------------------
Ŭ������		: KPlane
�Լ���			: GetNormalVector
���			: Normal Vector ����
�Ű�����		: ����
����			: ����
�ۼ�����		: 2007-04-28
������ ��������	: 2007-04-28
�ۼ���			: �����
-----------------------------------------------------------------------*/
KVector KPlane::GetNormalVector(void)
{
	return m_NormalVector;
}

/*-----------------------------------------------------------------------
Ŭ������		: KPlane
�Լ���			: GetBasePosition
���			: Base Position ����
�Ű�����		: ����
����			: ����
�ۼ�����		: 2007-04-28
������ ��������	: 2007-04-28
�ۼ���			: �����
-----------------------------------------------------------------------*/
KPosition KPlane::GetBasePosition(void)
{
	return m_BasePosition;
}

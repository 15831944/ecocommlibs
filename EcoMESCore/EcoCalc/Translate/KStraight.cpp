#include ".\kstraight.h"

KStraight::KStraight(void)
: m_BasePosition()
{
}

KStraight::~KStraight(void)
{
}

KStraight::KStraight(KPosition p0, KVector v0)
{
	m_BasePosition  = p0;

	v0.Nomalize();

	m_TangentVector = v0; 
}

/*-----------------------------------------------------------------------
Ŭ������		: KStraight
�Լ���			: SetBasePosition
���			: Base Position �Է�
�Ű�����		: KPosition base_position => �Է� Position
����			: ����
�ۼ�����		: 2007-04-28
������ ��������	: 2007-04-28
�ۼ���			: �����
-----------------------------------------------------------------------*/
void KStraight::SetBasePosition(KPosition base_position)
{
	m_BasePosition = base_position;
}

/*-----------------------------------------------------------------------
Ŭ������		: KStraight
�Լ���			: SetTangentVector
���			: ���� �Է�
�Ű�����		: KVector tangent_vector => �Է� ����
����			: ����
�ۼ�����		: 2007-04-28
������ ��������	: 2007-04-28
�ۼ���			: �����
-----------------------------------------------------------------------*/
void KStraight::SetTangentVector(KVector tangent_vector)
{
	KVector temp;

	temp = tangent_vector;

	temp.Nomalize();

	m_TangentVector = temp;
}

/*-----------------------------------------------------------------------
Ŭ������		: KStraight
�Լ���			: GetBasePosition
���			: Base position ����
�Ű�����		: ����
����			: ����
�ۼ�����		: 2007-04-28
������ ��������	: 2007-04-28
�ۼ���			: �����
-----------------------------------------------------------------------*/
KPosition KStraight::GetBasePosition(void)
{
	return m_BasePosition;
}

/*-----------------------------------------------------------------------
Ŭ������		: KStraight
�Լ���			: GetTangentVector
���			: Tangent Vector ����
�Ű�����		: ����
����			: ����
�ۼ�����		: 2007-04-28
������ ��������	: 2007-04-28
�ۼ���			: �����
-----------------------------------------------------------------------*/
KVector KStraight::GetTangentVector(void)
{
	return m_TangentVector;
}

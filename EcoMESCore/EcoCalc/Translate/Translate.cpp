#include ".\translate.h"

#include "math.h"

#define PI 3.14159265
#define DEG_TO_RAD   ( PI / 180.0 )
#define RAD_TO_DEG   ( 180.0 / PI )
#define SMALL_NUM  0.00000001 

CTranslate::CTranslate(void)
{
}

CTranslate::~CTranslate(void)
{
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: GetMatrixTranslate
���			: �̵���ȯ ��� ���
�Ű�����		: double in_matrix[4][4] => ���� ���
				  tx => x ���� �̵���
				  ty => y ���� �̵���
				  tz => z ���� �̵���
				  double out_matrix[4][4] => ��ȯ ���
����			: ����
�ۼ�����		: 2007-03-29
������ ��������	: 2007-03-29
�ۼ���			: �����
-----------------------------------------------------------------------*/
void CTranslate::GetMatrixTranslate(double in_matrix[4][4], double tx, double ty, double tz, double out_matrix[4][4])
{
	int i;
	int j;

	for ( i = 0; i < 4; i++ )
	{
		for ( j = 0; j < 4; j++ )
		{
			out_matrix[i][j] = in_matrix[i][j];
		}
	}
	out_matrix[0][3] = out_matrix[0][3] + tx;
	out_matrix[1][3] = out_matrix[1][3] + ty;
	out_matrix[2][3] = out_matrix[2][3] + tz;

	return;
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: GetMatrixRotateOffAxis
���			: �־��� �࿡ ���� ȸ����ȯ ��� ���
�Ű�����		: double in_matrix[4][4] => ���� ���
				  vec_x => ȸ���� x ��
				  vec_y => ȸ���� y ��
				  vec_z => ȸ���� z ��
				  angle => ȸ����(Degree)
				  double out_matrix[4][4] => ��ȯ ���
����			: ����
�ۼ�����		: 2007-03-29
������ ��������	: 2007-03-30
�ۼ���			: �����
-----------------------------------------------------------------------*/
void CTranslate::GetMatrixRotateOffAxis(double in_matrix[4][4], double vec_x, double vec_y, double vec_z, double angle, double out_matrix[4][4])
{
	double c[4][4];
	double ca;
	double d[4][4];
	int i;
	int j;
	double sa;
	double theta;

	// normalize rotate KVector
	double length = 0.0;
	length = sqrt(vec_x*vec_x + vec_y*vec_y + vec_z*vec_z);

	if(length == 0)
		return;

	vec_x = vec_x/length;
	vec_y = vec_y/length;
	vec_z = vec_z/length;

	if ( vec_x * vec_x + vec_y * vec_y + vec_z * vec_z == 0.0 )
	{
		return;
	}

	theta = angle * DEG_TO_RAD;

	InitMatrix ( c );

	ca = cos ( theta );
	sa = sin ( theta );

	c[0][0] =                vec_x * vec_x + ca * ( 1.0 - vec_x * vec_x );
	c[0][1] = ( 1.0 - ca ) * vec_x * vec_y - sa * vec_z;
	c[0][2] = ( 1.0 - ca ) * vec_x * vec_z + sa * vec_y;

	c[1][0] = ( 1.0 - ca ) * vec_y * vec_x + sa * vec_z;
	c[1][1] =                vec_y * vec_y + ca * ( 1.0 - vec_y * vec_y );
	c[1][2] = ( 1.0 - ca ) * vec_y * vec_z - sa * vec_x;

	c[2][0] = ( 1.0 - ca ) * vec_z * vec_x - sa * vec_y;
	c[2][1] = ( 1.0 - ca ) * vec_z * vec_y + sa * vec_x;
	c[2][2] =                vec_z * vec_z + ca * ( 1.0 - vec_z * vec_z );

	MatrixMultiply ( c, in_matrix, d );

	for ( i = 0; i < 4; i++ )
	{
		for ( j = 0; j < 4; j++ )
		{
			out_matrix[i][j] = d[i][j];
		}
	}
	return;
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: InitMatrix
���			: ��ȯ��� �ʱ�ȭ
�Ű�����		: double tmatrix[4][4] => ��� ���
����			: ����
�ۼ�����		: 2007-03-29
������ ��������	: 2007-03-29
�ۼ���			: �����
-----------------------------------------------------------------------*/
void CTranslate::InitMatrix(double tmatrix[4][4])
{
	int i;
	int j;

	for ( i = 0; i < 4; i++ )
	{
		for ( j = 0; j < 4; j++ )
		{
			if ( i == j )
			{
				tmatrix[i][j] = 1.0;
			}
			else
			{
				tmatrix[i][j] = 0.0;
			}
		}
	}
	return;

}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: MatrixMultiply
���			: ��� ��
�Ű�����		: double in_matrix1[4][4] => ���� ���
				  double in_matrix2[4][4] => ������ ���
				  double out_matrix[4][4] => ��ȯ���
����			: ����
�ۼ�����		: 2007-03-29
������ ��������	: 2007-03-29
�ۼ���			: �����
-----------------------------------------------------------------------*/
void CTranslate::MatrixMultiply(double in_matrix1[4][4], double in_matrix2[4][4], double out_matrix[4][4])
{
	double d[4][4];
	int i;
	int j;
	int k;

	for ( i = 0; i < 4; i++ )
	{
		for ( k = 0; k < 4; k++ )
		{
			d[i][k] = 0.0;
			for ( j = 0; j < 4; j++ )
			{
				d[i][k] = d[i][k] + in_matrix1[i][j] * in_matrix2[j][k];
			}
		}
	}

	for ( i = 0; i < 4; i++ )
	{
		for ( j = 0; j < 4; j++ )
		{
			out_matrix[i][j] = d[i][j];
		}
	}
	return;

}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: EvaluateVector
���			: �־��� ��Ŀ� ���� ��ȯ�� ���� ���
�Ű�����		: KVector in_pt => �Էº���
				  double tmatrix[4][4] => ��ȯ ����
				  KVector* out_pt => ��º���
����			: ����
�ۼ�����		: 2007-03-29
������ ��������	: 2007-03-29
�ۼ���			: �����
-----------------------------------------------------------------------*/
void CTranslate::EvaluateVector(KVector in_pt, double tmatrix[4][4], KVector* out_pt)
{
	int i;
	int j;
	double in[4], out[4], z[4];

	in[0] = in_pt.x;
	in[1] = in_pt.y;
	in[2] = in_pt.z;
	in[3] = 1.0;

	for ( i = 0; i < 3; i++ )
	{
		z[i] = tmatrix[i][3];
		for ( j = 0; j < 3; j++ )
		{
			z[i] = z[i] + tmatrix[i][j] * in[j];
		}
	}

	for ( i = 0; i < 3; i++ )
	{
		out[i] = z[i];
	}

	out_pt->x = out[0];
	out_pt->y = out[1];
	out_pt->z = out[2];

	return;

}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: ComputeCrossProduct
���			: ���� ���� ���
�Ű�����		: KVector leg1 => �Էº��� 1
				  KVector leg2 => �Էº��� 2
				  KVector* out_vec => ��º���
����			: ����
�ۼ�����		: 2007-03-29
������ ��������	: 2007-03-29
�ۼ���			: �����
-----------------------------------------------------------------------*/
void CTranslate::ComputeCrossProduct(KVector leg1, KVector leg2, KVector* out_vec)
{
	out_vec->x = leg1.y * leg2.z - leg1.z * leg2.y;
	out_vec->y = leg1.z * leg2.x - leg1.x * leg2.z;
	out_vec->z = leg1.x * leg2.y - leg1.y * leg2.x;
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: ComputeDotProduct
���			: ���� ���� ���
�Ű�����		: KVector leg1 => �Էº��� 1
				  KVector leg2 => �Էº��� 2
����			: ������
�ۼ�����		: 2007-03-29
������ ��������	: 2007-03-29
�ۼ���			: �����
-----------------------------------------------------------------------*/
double CTranslate::ComputeDotProduct(KVector leg1, KVector leg2)
{
	return (leg1.x * leg2.x + leg1.y * leg2.y + leg1.z * leg2.z);

}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: ComputeVectorNormalize
���			: ���� ����ȭ
�Ű�����		: KVector in_KVector => �Էº���
				  KVector* out_KVector => ��º���
����			: ������
�ۼ�����		: 2007-03-29
������ ��������	: 2007-03-29
�ۼ���			: �����
-----------------------------------------------------------------------*/
void CTranslate::ComputeVectorNormalize(KVector in_KVector, KVector* out_KVector)
{
	double vec_len = 0.0;

	vec_len = ComputeVectorLength(in_KVector);

	if(vec_len == 0)
		return;

	out_KVector->x = in_KVector.x/vec_len;
	out_KVector->y = in_KVector.y/vec_len;
	out_KVector->z = in_KVector.z/vec_len;

	return;
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: ComputeVectorLength
���			: ���� ���� ���
�Ű�����		: KVector vec => �Էº���
����			: ���� ����
�ۼ�����		: 2007-03-29
������ ��������	: 2007-03-29
�ۼ���			: �����
-----------------------------------------------------------------------*/
double CTranslate::ComputeVectorLength(KVector vec)
{
	return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: ComputeVectorAngle
���			: �� ���� ���̰� ���
�Ű�����		: KVector leg1 => �Էº���1
				  KVector leg2 => �Էº���2
����			: ���̰�(Degree)
�ۼ�����		: 2007-03-29
������ ��������	: 2007-03-29
�ۼ���			: �����
-----------------------------------------------------------------------*/
double CTranslate::ComputeVectorAngle(KVector leg1, KVector leg2)
{
	KVector vec1, vec2;
	double dot = 0.0;

	// normalize KVector
	ComputeVectorNormalize(leg1, &vec1);
	ComputeVectorNormalize(leg2, &vec2);

	// calc dot product
	dot= ComputeDotProduct(vec1, vec2);

	// get angle
	return RAD_TO_DEG*acos(dot);
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: GetTran1Pt1Axis
���			: ����+1�� ��ȯ ��� ���
�Ű�����		: double inmatrix[4][4] => ��������
				  KVector OriginPt => ����
				  KVector OriginAxis => ����
				  KVector TargetPt => ������
				  KVector TargetAxis => ��� ��
				  double tmatrix[4][4] => ��ȯ���
����			: ����
�ۼ�����		: 2007-03-29
������ ��������	: 2007-03-29
�ۼ���			: �����
-----------------------------------------------------------------------*/
void CTranslate::GetTran1Pt1Axis(bool level, double inmatrix[4][4], KVector OriginPt, KVector OriginAxis, KVector TargetPt, KVector TargetAxis, double tmatrix[4][4])
{
	int i, j;
	KVector move;
	double temp_matrix[4][4];

	InitMatrix(temp_matrix);

	// unite origin
	move.x = TargetPt.x - OriginPt.x;
	move.y = TargetPt.y - OriginPt.y;
	move.z = TargetPt.z - OriginPt.z;

	// move
	GetMatrixTranslate(inmatrix,move.x, move.y, move.z, temp_matrix); 

	// update coordinate 
	OriginPt.x += move.x;
	OriginPt.y += move.y;
	OriginPt.z += move.z;

	OriginAxis.x += move.x;
	OriginAxis.y += move.y;
	OriginAxis.z += move.z;

	if(level == true)
	{
		OriginAxis.z = OriginPt.z;
		TargetAxis.z = TargetPt.z;
	}

	// unite leg1 and leg2
	KVector leg1, leg2;
	
	leg1.x = TargetAxis.x - TargetPt.x;
	leg1.y = TargetAxis.y - TargetPt.y;
	leg1.z = TargetAxis.z - TargetPt.z;

	leg2.x = OriginAxis.x - OriginPt.x;
	leg2.y = OriginAxis.y - OriginPt.y;
	leg2.z = OriginAxis.z - OriginPt.z;

	// compute axis of rotation
	KVector rot_axis;
	ComputeCrossProduct(leg1, leg2, &rot_axis);

	// compute rotation angle
	double angle = 0.0;
	angle = ComputeVectorAngle(leg1, leg2);

	// rotate
	GetMatrixTranslate(temp_matrix, -OriginPt.x, -OriginPt.y, -OriginPt.z, temp_matrix);

	if(angle != 0.0)
		GetMatrixRotateOffAxis(temp_matrix,rot_axis.x, rot_axis.y, rot_axis.z, -angle, temp_matrix);

	GetMatrixTranslate(temp_matrix, OriginPt.x, OriginPt.y, OriginPt.z, temp_matrix);

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			tmatrix[i][j] = temp_matrix[i][j];
    
	return;

}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: GetTran1Pt1Axis1Plane
���			: ����+1��+1��� ��ȯ ��� ���
�Ű�����		: double inmatrix[4][4] => ��������
				  KVector OriginPt => ����
				  KVector OriginAxis => ����
				  KVector OriginPlane => �����
				  KVector TargetPt => ������
				  KVector TargetAxis => ��� ��
				  KVector TargetPlane => ��� ���
				  double tmatrix[4][4] => ��ȯ���
����			: ����
�ۼ�����		: 2007-03-30
������ ��������	: 2007-03-30
�ۼ���			: �����
-----------------------------------------------------------------------*/
void CTranslate::GetTran1Pt1Axis1Plane(double in_matrix[4][4], KVector OriginPt, KVector OriginAxis, KVector OriginPlane, KVector TargetPt, KVector TargetAxis, KVector TargetPlane, double out_matrix[4][4])
{
	int i, j;
    double angle;
    double temp_matrix[4][4];
	KVector origin_pt, origin_axis, origin_plane;
	KVector leg1, leg2;
	KVector origin_face_normal, target_face_normal;
	KVector rot_axis;

	InitMatrix(temp_matrix);

	
	//**** tran1
	GetTran1Pt1Axis(false, in_matrix, OriginPt, OriginAxis, TargetPt, TargetAxis, temp_matrix);
	
	//**** tran2
	EvaluateVector(OriginPt, temp_matrix, &origin_pt);
	EvaluateVector(OriginAxis, temp_matrix, &origin_axis);
	EvaluateVector(OriginPlane, temp_matrix, &origin_plane);

	// compute normal KVector of face1
	leg1.x = TargetAxis.x - TargetPt.x;
	leg1.y = TargetAxis.y - TargetPt.y;
	leg1.z = TargetAxis.z - TargetPt.z;

	leg2.x = TargetPlane.x - TargetPt.x;
	leg2.y = TargetPlane.y - TargetPt.y;
	leg2.z = TargetPlane.z - TargetPt.z;

	ComputeCrossProduct(leg1, leg2, &origin_face_normal);

	// compute normal KVector of face2
	leg1.x = origin_axis.x - origin_pt.x;
	leg1.y = origin_axis.y - origin_pt.y;
	leg1.z = origin_axis.z - origin_pt.z;

	leg2.x = origin_plane.x - origin_pt.x;
	leg2.y = origin_plane.y - origin_pt.y;
	leg2.z = origin_plane.z - origin_pt.z;

	ComputeCrossProduct(leg1, leg2, &target_face_normal);

	// get axis of rotation
	angle = ComputeVectorAngle(target_face_normal, origin_face_normal);
	ComputeCrossProduct(target_face_normal, origin_face_normal, &rot_axis);

	// rotate
	GetMatrixTranslate(temp_matrix, -origin_pt.x, -origin_pt.y, -origin_pt.z, temp_matrix);

	if(angle != 0.0)
		GetMatrixRotateOffAxis(temp_matrix,rot_axis.x, rot_axis.y, rot_axis.z, angle, temp_matrix);

	GetMatrixTranslate(temp_matrix, origin_pt.x, origin_pt.y, origin_pt.z, temp_matrix);

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			out_matrix[i][j] = temp_matrix[i][j];
    
	return;
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: Compute2PtTarget
���			: 2�� Ÿ�� ������ǥ ���
�Ű�����		: KVector pt1 => ������ 1
				  KVector pt2 => ������ 2
				  double length_pt2_end => ������ 2���� Ÿ�ٳ��ܺα����� �Ÿ�
				  double* error => ������ 1-2�� ���� ������
				  KVector* target_pt => 2�� Ÿ�ٿ� ���� ���� ������
����			: ����
�ۼ�����		: 2007-03-30
������ ��������	: 2007-03-30
�ۼ���			: �����
-----------------------------------------------------------------------*/
void CTranslate::Compute2PtTarget(KVector pt1, KVector pt2, double length_pt1_pt2, double length_pt2_end, double* error, KVector* target_pt)
{
	// compute real length between pt1 and pt2
	KVector diff;

	diff.x = pt2.x - pt1.x;
	diff.y = pt2.y - pt1.y;
	diff.z = pt2.z - pt1.z;

	*error = ComputeVectorLength(diff) - length_pt1_pt2;

	// compute the position of target pt
	double t;

	if(length_pt1_pt2 <= 0)
		return;

	t = (length_pt1_pt2 + *error + length_pt2_end)/(length_pt1_pt2 + *error);

	target_pt->x = pt1.x + t*diff.x;
	target_pt->y = pt1.y + t*diff.y;
	target_pt->z = pt1.z + t*diff.z;

	return;
}

int CTranslate::InvMatrix(int n, const double *A, double *b)
{
   double m;
    register int i, j, k;
    double* a = new double[n*n];
    if(a == 0 )  return 0;
    for(i=0; i<n*n; i++)  a[i]=A[i];

    for(i=0; i<n; i++)  {
        for(j=0; j<n; j++)  {
            b[i*n+j]=(i==j)?1.:0.;
            }
        }
    for(i=0; i<n; i++)  {
        if(a[i*n+i]==0.)  {
            if(i==n-1)  {
                delete[] a;  return 0;
                }
            for(k=1; i+k<n; k++)  {
                if(a[i*n+i+k]!=0.)  break;
                }
            if(i+k>=n)  {
                delete[] a;  return 0;
                }
            for(j=0; j<n; j++)  {
                m = a[i*n+j];
                a[i*n+j] = a[(i+k)*n+j];
                a[(i+k)*n+j] = m;
                m = b[i*n+j];
                b[i*n+j] = b[(i+k)*n+j];
                b[(i+k)*n+j] = m;

                }
            }
        m = a[i*n+i];
        for(j=0; j<n; j++)  {
            a[i*n+j]/=m;
            b[i*n+j]/=m;
            }
        for(j=0; j<n; j++)  {
            if(i==j)  continue;
            m = a[j*n+i];
            for(k=0; k<n; k++)  {
                a[j*n+k] -= a[i*n+k]*m;
                b[j*n+k] -= b[i*n+k]*m;
                }
            }
        }
    delete[] a;
    return 1;
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: Intersect2Planes
���			: �� ����� ���� ���
�Ű�����		: const KPlane plane1 => ��� 1
				  const KPlane plane2 => ��� 2
				  KStraight* result_straight => ������
����			: ������� ���: 0=>������, 1=>�������� ����(����), 2=>������� ��ġ
�ۼ�����		: 2007-04-27
������ ��������	: 2007-04-27
�ۼ���			: �����
-----------------------------------------------------------------------*/
int CTranslate::Intersect2Planes(KPlane plane1, KPlane plane2, KStraight* result_straight)
{
	KVector u;

	ComputeCrossProduct(plane1.GetNormalVector(), plane2.GetNormalVector(), &u); 
		
    double    ax, ay, az;
	
	ax = (u.x >= 0 ? u.x : -u.x);
    ay = (u.y >= 0 ? u.y : -u.y);
    az = (u.z >= 0 ? u.z : -u.z);

    // �� ����� �������� �׽�Ʈ
    if ((ax+ay+az) < SMALL_NUM)
	{       
		KVector v;
		
		v = plane2.GetBasePosition() - plane1.GetBasePosition();

		if (ComputeDotProduct(plane1.GetNormalVector(), v) == 0)         
            return 2;                   // �� ����� ��ġ
        else 
            return 1;                   // �� ����� ����
    }

	// ���� �ִ밪 ���
    int      maxc;                     
    if (ax > ay)
	{
        if (ax > az)
             maxc = 1;
        else maxc = 3;
    }
    else
	{
        if (ay > az)
             maxc = 2;
        else maxc = 3;
    }
   
	// ������ ���
    KPosition    iP;               
    double    d1, d2;           

    d1 = -ComputeDotProduct(plane1.GetNormalVector(), plane1.GetBasePosition()); 
    d2 = -ComputeDotProduct(plane2.GetNormalVector(), plane2.GetBasePosition());  
	
    switch (maxc) {           
    case 1:                  
        iP.x = 0;
        iP.y = (d2*plane1.GetNormalVector().z - d1*plane2.GetNormalVector().z) / u.x;
        iP.z = (d1*plane2.GetNormalVector().y - d2*plane1.GetNormalVector().y) / u.x;
        break;
    case 2:                   
      iP.x = (d1*plane2.GetNormalVector().z - d2*plane1.GetNormalVector().z) / u.y;
        iP.y = 0;
        iP.z = (d2*plane1.GetNormalVector().x - d1*plane2.GetNormalVector().x) / u.y;
       break;
    case 3:                    
        iP.x = (d2*plane1.GetNormalVector().y - d1*plane2.GetNormalVector().y) / u.z;
        iP.y = (d1*plane2.GetNormalVector().x - d2*plane1.GetNormalVector().x) / u.z;
        iP.z = 0;
    }

	result_straight->SetBasePosition(iP);
	result_straight->SetTangentVector(u);
    return 0;
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: ComputeDotProduct
���			: ���� ���� ���
�Ű�����		: KVector leg1 => �Էº��� 1
				  KPosition leg2 => �Էº��� 2
����			: ������
�ۼ�����		: 2007-04-27
������ ��������	: 2007-03-27
�ۼ���			: �����
-----------------------------------------------------------------------*/
double CTranslate::ComputeDotProduct(KVector leg1, KPosition leg2)
{
	return (leg1.x * leg2.x + leg1.y * leg2.y + leg1.z * leg2.z);
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: IntersectStraightSphere
���			: ����, �� �������
�Ű�����		: KStraight straight => ����
				  KSphere sphere => ��
				  KPosition result_positions[2] => ������
����			: ������ ����
�ۼ�����		: 2007-04-27
������ ��������	: 2007-04-27
�ۼ���			: �����
-----------------------------------------------------------------------*/
int CTranslate::IntersectStraightSphere(KStraight straight, KSphere sphere, KPosition result_positions[2])
{
	// Straight ���� ���� 2�� ���
	double param = 1;
	KPosition p1, p2, p3;

	// vector normalize
	ComputeVectorNormalize(straight.GetTangentVector(), &straight.GetTangentVector());

	p1.x = straight.GetBasePosition().x;
	p1.y = straight.GetBasePosition().y;
	p1.z = straight.GetBasePosition().z;

	p2.x = straight.GetBasePosition().x + param*straight.GetTangentVector().x;
	p2.y = straight.GetBasePosition().y + param*straight.GetTangentVector().y;
	p2.z = straight.GetBasePosition().z + param*straight.GetTangentVector().z;

	p3 = sphere.m_Center;

	double a, b, c, mu, i ;

	a =  ComputeSquare(p2.x - p1.x) + ComputeSquare(p2.y - p1.y) + ComputeSquare(p2.z - p1.z);

	b =  2* ( (p2.x - p1.x)*(p1.x - p3.x)
		+ (p2.y - p1.y)*(p1.y - p3.y)
		+ (p2.z - p1.z)*(p1.z - p3.z) ) ;

	c =  ComputeSquare(p3.x) + ComputeSquare(p3.y) +
		ComputeSquare(p3.z) + ComputeSquare(p1.x) +
		ComputeSquare(p1.y) + ComputeSquare(p1.z) -
		2* ( p3.x*p1.x + p3.y*p1.y + p3.z*p1.z ) - ComputeSquare(sphere.m_Radius) ;

	i =   b * b - 4 * a * c ;

	if ( i < 0.0 )
	{
		return 0;
	}
	if ( i == 0.0 )
	{
		// one intersection
		mu = -b/(2*a) ;

		result_positions[0].x = p1.x + mu*(p2.x-p1.x);
		result_positions[0].y = p1.y + mu*(p2.y-p1.y);
		result_positions[0].z = p1.z + mu*(p2.z-p1.z);

		return 1;
	}
	if ( i > 0.0 )
	{
		// first intersection
		mu = (-b + sqrt( ComputeSquare(b) - 4*a*c )) / (2*a);
		result_positions[0].x = p1.x + mu*(p2.x-p1.x);
		result_positions[0].y = p1.y + mu*(p2.y-p1.y);
		result_positions[0].z = p1.z + mu*(p2.z-p1.z);

		// second intersection
		mu = (-b - sqrt(ComputeSquare(b) - 4*a*c )) / (2*a);
		result_positions[1].x = p1.x + mu*(p2.x-p1.x);
		result_positions[1].y = p1.y + mu*(p2.y-p1.y);
		result_positions[1].z = p1.z + mu*(p2.z-p1.z);

		return 2;
	}

	return 0;
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: ComputeSquare
���			: ������ ���
�Ű�����		: double value => �Է°�
����			: ������
�ۼ�����		: 2007-04-27
������ ��������	: 2007-04-27
�ۼ���			: �����
-----------------------------------------------------------------------*/
double CTranslate::ComputeSquare(double value)
{
	return value*value;
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: ComputePerPosition
���			: ������ ������ ������ �������� ���� �������� ����ǥ ���
�Ű�����		: KStraight straight => ����
				  KPosition position => ��
				  KPosition* result_position => �������� ���� ��
����			: �Ÿ�
�ۼ�����		: 2007-04-27
������ ��������	: 2007-04-27
�ۼ���			: �����
-----------------------------------------------------------------------*/
double CTranslate::ComputePerPosition(KStraight straight, KPosition position, KPosition* result_position)
{
	KVector w;
	double c1;
	double c2;
	double b;

	w = position - straight.GetBasePosition();

	c1 = ComputeDotProduct(w, straight.GetTangentVector());
	c2 = ComputeDotProduct(straight.GetTangentVector(), straight.GetTangentVector());

	/*  if ( c1 <= 0 )
	{
		return ComputeDistance(position, straight.GetBasePosition());
	}

   
	if ( c2 <= c1 )
	{
		KPosition p1;

		p1.x = straight.GetBasePosition().x + straight.GetTangentVector().x;
		p1.y = straight.GetBasePosition().y + straight.GetTangentVector().y;
		p1.z = straight.GetBasePosition().z + straight.GetTangentVector().z;

		return ComputeDistance(position, p1);
	}
*/
    b = c1 / c2;

	result_position->x = straight.GetBasePosition().x + b * straight.GetTangentVector().x;
	result_position->y = straight.GetBasePosition().y + b * straight.GetTangentVector().y;
	result_position->z = straight.GetBasePosition().z + b * straight.GetTangentVector().z;

    return ComputeDistance(position, *result_position);

}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: ComputeDotProduct
���			: ���� ���� ���
�Ű�����		: KPosition leg1 => �Էº��� 1
				  KPosition leg2 => �Էº��� 2
����			: ������
�ۼ�����		: 2007-04-27
������ ��������	: 2007-04-27
�ۼ���			: �����
-----------------------------------------------------------------------*/
double CTranslate::ComputeDotProduct(KPosition leg1, KPosition leg2)
{
	return (leg1.x * leg2.x + leg1.y * leg2.y + leg1.z * leg2.z);
}



/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: ComputeStraightLength
���			: ���� ���̰��
�Ű�����		: KStraight straight => �Է�����
����			: ���� ����
�ۼ�����		: 2007-04-27
������ ��������	: 2007-04-27
�ۼ���			: �����
-----------------------------------------------------------------------*/
double CTranslate::ComputeDistance(KPosition position1, KPosition position2)
{
	KVector diff;

	diff = position2 - position1;

	return ComputeVectorLength(diff);
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: GetTran2PtRotate
���			: 2����ȸ��
�Ű�����		: double inmatrix[4][4] => ��������
				  KVector AxisPt1 => ����
				  KVector AxisPt2 => ����
				  KVector RotatePt => ȸ����
				  int Direction => ȸ������: 0 => x��, 1 => y��, 2 => z��
				  double tmatrix[4][4] => ��ȯ���
����			: ���� ����
�ۼ�����		: 2007-04-27
������ ��������	: 2007-04-27
�ۼ���			: �����
-----------------------------------------------------------------------*/
bool CTranslate::GetTran2PtRotate(KPosition AxisPt1, KPosition AxisPt2, KPosition RotatePt, int Direction, double Distance, double tmatrix[4][4])
{

	if(AxisPt1.x == AxisPt2.x && AxisPt1.y == AxisPt2.y && AxisPt1.z == AxisPt2.z)
		return false;

	// �̵��� ���ϱ�
	KPosition new_rotate_pt;

	new_rotate_pt = RotatePt;
    
	if(Direction == 0)
		new_rotate_pt.x = RotatePt.x + Distance;
	else if(Direction == 1)
		new_rotate_pt.y = RotatePt.y + Distance;
	else if(Direction == 2)
		new_rotate_pt.z = RotatePt.z + Distance;

	// ȸ������ ���ϱ�
	KPosition rotation_center;
	KStraight rotation_axis;
	KVector diff;

	rotation_axis.SetBasePosition(AxisPt1);
	rotation_axis.SetTangentVector(AxisPt2 - AxisPt1);

	ComputePerPosition(rotation_axis, RotatePt, &rotation_center);

	// �������ϱ�
	KVector dir;

	dir = new_rotate_pt- RotatePt;

	KPlane plane2(new_rotate_pt, dir);
	KPlane plane1(rotation_center,rotation_axis.GetTangentVector());

	// �� ����� �������
	KStraight int_straight;

	if(Intersect2Planes(plane1, plane2, &int_straight) != 0)
		return false;

	// ���� ������ �������
	int count = 0;
	double radius = 0.0;
	KPosition int_pt[2];

	radius = ComputeDistance(RotatePt, rotation_center); 
	KSphere sphere(rotation_center, radius);

	count = IntersectStraightSphere(int_straight, sphere, int_pt);

	// ������ ���
	KPosition nearest_pt;

	if(count == 0)
		return false;
	else if(count == 1)
	{
		nearest_pt = int_pt[0];
	}
	else if(count == 2)
	{
		double dist0=0.0, dist1=0.0;

		dist0 = ComputeDistance(RotatePt, int_pt[0]);
		dist1 = ComputeDistance(RotatePt, int_pt[1]);

		if(dist0 <= dist1)
		{
			nearest_pt = int_pt[0];
		}
		else
		{
			nearest_pt = int_pt[1];
		}

	}

	// ȸ���� ���
	KVector leg1, leg2, rot_vec;
	double angle;

	leg1 = RotatePt - rotation_center;
	leg2 = nearest_pt - rotation_center;

	ComputeCrossProduct(leg1, leg2, &rot_vec);
	ComputeVectorNormalize(rot_vec, &rot_vec);

	angle = ComputeVectorAngle(leg2, leg1); 

	// matrix ���
	int i, j;
	double temp_matrix[4][4];
	InitMatrix(temp_matrix);

	GetMatrixTranslate(temp_matrix, -rotation_center.x, -rotation_center.y, -rotation_center.z, temp_matrix);

	if(angle != 0.0)
		GetMatrixRotateOffAxis(temp_matrix,rot_vec.x, rot_vec.y, rot_vec.z, angle, temp_matrix);

	GetMatrixTranslate(temp_matrix, rotation_center.x, rotation_center.y, rotation_center.z, temp_matrix);

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			tmatrix[i][j] = temp_matrix[i][j];
	
	return true;

}


bool CTranslate::GetTran2PtRotateAngle(KPosition AxisPt1, KPosition AxisPt2, KPosition RotatePt, double Angle, double tmatrix[4][4])
{

	if(AxisPt1.x == AxisPt2.x && AxisPt1.y == AxisPt2.y && AxisPt1.z == AxisPt2.z)
		return false;

	// ȸ���� ���
	KVector leg1, leg2, rot_vec;

	rot_vec.x = AxisPt2.x - AxisPt1.x;
	rot_vec.y = AxisPt2.y - AxisPt1.y;
	rot_vec.z = AxisPt2.z - AxisPt1.z;

	// matrix ���
	int i, j;
	double temp_matrix[4][4];
	InitMatrix(temp_matrix);

	GetMatrixTranslate(temp_matrix, -AxisPt1.x, -AxisPt1.y, -AxisPt1.z, temp_matrix);

	if(Angle != 0.0)
		GetMatrixRotateOffAxis(temp_matrix,rot_vec.x, rot_vec.y, rot_vec.z, Angle, temp_matrix);

	GetMatrixTranslate(temp_matrix, AxisPt1.x, AxisPt1.y, AxisPt1.z, temp_matrix);

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			tmatrix[i][j] = temp_matrix[i][j];
	
	return true;

}


/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: EvaluatePosition
���			: �־��� ��Ŀ� ���� ��ȯ�� �� ���
�Ű�����		: KPostion in_pt => �Է���
				  double tmatrix[4][4] => ��ȯ ����
				  KPosition* out_pt => �����
����			: ����
�ۼ�����		: 2007-04-28
������ ��������	: 2007-04-28
�ۼ���			: �����
-----------------------------------------------------------------------*/
void CTranslate::EvaluatePosition(KPosition in_pt, double tmatrix[4][4], KPosition* out_pt)
{
	int i;
	int j;
	double in[4], out[4], z[4];

	in[0] = in_pt.x;
	in[1] = in_pt.y;
	in[2] = in_pt.z;
	in[3] = 1.0;

	for ( i = 0; i < 3; i++ )
	{
		z[i] = tmatrix[i][3];
		for ( j = 0; j < 3; j++ )
		{
			z[i] = z[i] + tmatrix[i][j] * in[j];
		}
	}

	for ( i = 0; i < 3; i++ )
	{
		out[i] = z[i];
	}

	out_pt->x = out[0];
	out_pt->y = out[1];
	out_pt->z = out[2];

	return;
}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: Compute2PlanesAngle
���			: �� ����� ���� ���
�Ű�����		: KPosition axis_pt1 => ������� �������� 1
				  KPosition axis_pt2 => �� ����� �������� 2
				  KPosition plane_pt1 => ù��° ������ ��
				  KPosition plane_pt2 => �ι�° ������ ��
����			: ����
�ۼ�����		: 2007-07-02
������ ��������	: 2007-07-02
�ۼ���			: �����
-----------------------------------------------------------------------*/
double CTranslate::Compute2PlanesAngle(KPosition axis_pt1, KPosition axis_pt2, KPosition plane_pt1, KPosition plane_pt2)
{
	double angle = 0.0;

	// �� ��� ����
	KPlane plane1(axis_pt1, axis_pt2, plane_pt1);
	KPlane plane2(axis_pt1, axis_pt2, plane_pt2);

	angle = Compute2PlanesAngle(plane1, plane2);

	return angle;

}

/*-----------------------------------------------------------------------
Ŭ������		: CTranslate
�Լ���			: Compute2PlanesAngle
���			: �� ����� ���� ���
�Ű�����		: const KPlane plane1 => ��� 1
				  const KPlane plane2 => ��� 2
����			: ����
�ۼ�����		: 2007-07-02
������ ��������	: 2007-07-02
�ۼ���			: �����
-----------------------------------------------------------------------*/
double CTranslate::Compute2PlanesAngle(KPlane plane1 , KPlane plane2)
{
	double angle=0.0;

	KVector normal_vector1, normal_vector2;

	normal_vector1 = plane1.GetNormalVector();
	normal_vector2 = plane2.GetNormalVector();

	angle = ComputeVectorAngle(normal_vector1, normal_vector2);

	return angle;
}

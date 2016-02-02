#include "Matrix3.h"


Matrix3::Matrix3(void)	{
	ToIdentity();
}

Matrix3::Matrix3(float elements[16]) {
	values[0] = elements[0];
	values[1] = elements[1];
	values[2] = elements[2];

	values[3] = elements[4];
	values[4] = elements[5];
	values[5] = elements[6];

	values[6] = elements[8];
	values[7] = elements[9];
	values[8] = elements[10];
}

Matrix3::Matrix3(const Matrix4 &m4) {
	values[0] = m4.values[0];
	values[1] = m4.values[1];
	values[2] = m4.values[2];

	values[3] = m4.values[4];
	values[4] = m4.values[5];
	values[5] = m4.values[6];

	values[6] = m4.values[8];
	values[7] = m4.values[9];
	values[8] = m4.values[10];
}


Matrix3::~Matrix3(void)	{

}

Matrix3 Matrix3::Rotation(float degrees, const Vector3 &inaxis)	 {
	Matrix3 m;

	Vector3 axis = inaxis;

	axis.Normalise();

	float c = cos((float)DegToRad(degrees));
	float s = sin((float)DegToRad(degrees));

	m.values[0]  = (axis.x * axis.x) * (1.0f - c) + c;
	m.values[1]  = (axis.y * axis.x) * (1.0f - c) + (axis.z * s);
	m.values[2]  = (axis.z * axis.x) * (1.0f - c) - (axis.y * s);

	m.values[3]  = (axis.x * axis.y) * (1.0f - c) - (axis.z * s);
	m.values[4]  = (axis.y * axis.y) * (1.0f - c) + c;
	m.values[5]  = (axis.z * axis.y) * (1.0f - c) + (axis.x * s);

	m.values[6]  = (axis.x * axis.z) * (1.0f - c) + (axis.y * s);
	m.values[7]  = (axis.y * axis.z) * (1.0f - c) - (axis.x * s);
	m.values[8]  = (axis.z * axis.z) * (1.0f - c) + c;

	return m;
}

Matrix3 Matrix3::Scale( const Vector3 &scale )	{
	Matrix3 m;

	m.values[0]  = scale.x;
	m.values[4]  = scale.y;
	m.values[8]  = scale.z;	

	return m;
}


void	Matrix3::ToZero()	{
	for(int i = 0; i < 9; ++i) {
		values[0] = 0.0f;
	}
}

void	Matrix3::ToIdentity() {
	for(int i = 0; i < 9; ++i) {
		values[0] = 0.0f;
	}
	values[0]  = 1.0f;
	values[4]  = 1.0f;
	values[8]  = 1.0f;	
}
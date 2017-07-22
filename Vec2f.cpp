#include "StdAfx.h"
#include "Vec2f.h"

Vec2f::Vec2f(void)
: m_x(0)
, m_y(0)
{
}

Vec2f::Vec2f(float x, float y)
: m_x(x)
, m_y(y)
{

}

Vec2f::~Vec2f(void)
{
}

Vec2f operator+(const Vec2f& v1, const Vec2f& v2)
{
	Vec2f v;
	v=v1;
	v+=v2;
	return v;
}

Vec2f operator-(const Vec2f& v1, const Vec2f& v2)
{
	Vec2f v;
	v=v1;
	v-=v2;
	return v;
}

Vec2f operator*(const Vec2f& v1, const float& value)
{
	Vec2f v=v1;
	v*=value;
	return v;
}

Vec2f operator*(const float& value, const Vec2f& v2)
{
	Vec2f v=v2;
	v*=value;
	return v;
}

Vec2f operator*(const Vec2f& v1, const int& value)
{
	Vec2f v=v1;
	v*=value;
	return v;
}

Vec2f operator*(const int& value, const Vec2f& v2)
{
	Vec2f v=v2;
	v*=value;
	return v;
}

float Vec2f::GetRadian(int iAngleRange) const
{
	static const float PI=3.14159265F;

	float rad=atan2(m_y, m_x);
	if(rad < 0 && iAngleRange==ANGLERANGE_FROM_0_TO_360)
	{
		rad += PI * 2;
	}

	return rad;
}

float Vec2f::GetAngle(int iAngleRange) const
{
	static const float PI=3.14159265f;

	float rad=GetRadian(iAngleRange);

	return rad * 180 / PI;
}

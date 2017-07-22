#pragma once
#include "afx.h"
#include <cmath>

class Vec2f :
	public CObject
{
public:
	Vec2f(void);
	Vec2f(float x, float y);
	Vec2f(int x, int y);
	~Vec2f(void);

public:
	static const int ANGLERANGE_FROM_0_TO_360=1;
	static const int ANGLERANGE_FROM_M180_TO_P180=2;

public:
	Vec2f& operator=(const Vec2f& rhs)
	{
		m_x=rhs.m_x;
		m_y=rhs.m_y;
		return *this;
	}
	Vec2f(const Vec2f& rhs)
	{
		m_x=rhs.m_x;
		m_y=rhs.m_y;
	}
	Vec2f& operator+=(const Vec2f& rhs)
	{
		m_x+=rhs.m_x;
		m_y+=rhs.m_y;
		return *this;
	}
	Vec2f& operator-=(const Vec2f& rhs)
	{
		m_x-=rhs.m_x;
		m_y-=rhs.m_y;
		return *this;
	}
	bool operator==(const Vec2f& rhs) const
	{
		if(m_x != rhs.m_x)
		{
			return false;
		}
		if(m_y != rhs.m_y)
		{
			return false;
		}
		return true;
	}
	float Length() const
	{
		return sqrt(m_x * m_x + m_y * m_y);
	}

	Vec2f Normalize() const
	{
		Vec2f v;

		float l=Length();

		if(l != 0)
		{
			v.SetX(m_x / l);
			v.SetY(m_y / l);
		}

		return v;
	}

	Vec2f operator*=(const float& value)
	{
		m_x *= value;
		m_y *= value;

		return *this;
	}

	Vec2f operator*=(const int& value)
	{
		m_x *= value;
		m_y *= value;
		return *this;
	}

public:
	float GetX() const 
	{
		return m_x;
	}
	float GetY() const
	{
		return m_y;
	}
	void SetX(float x) 
	{
		m_x=x;
	}
	void SetY(float y)
	{
		m_y=y;
	}
private:
	float m_x;
	float m_y;

public:
	friend Vec2f operator+(const Vec2f& v1, const Vec2f& v2);
	friend Vec2f operator-(const Vec2f& v1, const Vec2f& v2);
	friend Vec2f operator*(const Vec2f& v1, const float& value);
	friend Vec2f operator*(const Vec2f& v1, const int& value);
	friend Vec2f operator*(const float& value, const Vec2f& v2);
	friend Vec2f operator*(const int& value, const Vec2f& v2);
	float GetRadian(int iAngleRange = ANGLERANGE_FROM_0_TO_360) const;
	float GetAngle(int iAngleRange = ANGLERANGE_FROM_0_TO_360) const;
};


#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(int x, int y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::add(const Vector2D& vector)
{
	x += vector.x;
	y += vector.y;

	return *this;
}

Vector2D& Vector2D::substract(const Vector2D& vector)
{
	x -= vector.x;
	y -= vector.y;

	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& vector)
{
	return add(vector);
}

Vector2D& Vector2D::operator-=(const Vector2D& vector)
{
	return substract(vector);
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.substract(v2);
}

void  Vector2D::zero()
{
	x = 0;
	y = 0;
}
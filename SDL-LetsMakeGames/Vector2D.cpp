#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D & Vector2D::add(const Vector2D & rightVector)
{
	this->x += rightVector.x;
	this->y += rightVector.y;

	return *this;
}

Vector2D & Vector2D::subtract(const Vector2D & rightVector)
{
	this->x -= rightVector.x;
	this->y -= rightVector.y;

	return *this;
}

Vector2D & Vector2D::multiply(const Vector2D & rightVector)
{
	this->x *= rightVector.x;
	this->y *= rightVector.y;

	return *this;
}

Vector2D & Vector2D::divide(const Vector2D & rightVector)
{
	this->x /= rightVector.x;
	this->y /= rightVector.y;

	return *this;
}

Vector2D & Vector2D::operator+=(const Vector2D & rightVector)
{
	return this->add(rightVector);
}

Vector2D & Vector2D::operator-=(const Vector2D & rightVector)
{
	return this->subtract(rightVector);
}

Vector2D & Vector2D::operator*=(const Vector2D & rightVector)
{
	return this->multiply(rightVector);
}

Vector2D & Vector2D::operator/=(const Vector2D & rightVector)
{
	return this->divide(rightVector);
}

Vector2D & Vector2D::operator*(const int & i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D & Vector2D::zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}

Vector2D & operator+(Vector2D & leftVector, const Vector2D & rightVector)
{
	return leftVector.add(rightVector);
}

Vector2D & operator-(Vector2D & leftVector, const Vector2D & rightVector)
{
	return leftVector.subtract(rightVector);
}

Vector2D & operator*(Vector2D & leftVector, const Vector2D & rightVector)
{
	return leftVector.multiply(rightVector);
}

Vector2D & operator/(Vector2D & leftVector, const Vector2D & rightVector)
{
	return leftVector.divide(rightVector);
}

std::ostream & operator<<(std::ostream & stream, const Vector2D & inVector)
{
	stream << "(" << inVector.x << "," << inVector.y << ")";
	return stream;
}

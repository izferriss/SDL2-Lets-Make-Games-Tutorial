#pragma once
#include <iostream>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& add(const Vector2D& rightVector);
	Vector2D& subtract(const Vector2D& rightVector);
	Vector2D& multiply(const Vector2D& rightVector);
	Vector2D& divide(const Vector2D& rightVector);

	friend Vector2D& operator+(Vector2D& leftVector, const Vector2D& rightVector);
	friend Vector2D& operator-(Vector2D& leftVector, const Vector2D& rightVector);
	friend Vector2D& operator*(Vector2D& leftVector, const Vector2D& rightVector);
	friend Vector2D& operator/(Vector2D& leftVector, const Vector2D& rightVector);

	Vector2D& operator+=(const Vector2D& rightVector);
	Vector2D& operator-=(const Vector2D& rightVector);
	Vector2D& operator*=(const Vector2D& rightVector);
	Vector2D& operator/=(const Vector2D& rightVector);

	Vector2D& operator*(const int& i);
	Vector2D& zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& inVector);

};
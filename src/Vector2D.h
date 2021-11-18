#pragma once

class Vector2D
{
public:
	Vector2D();
	Vector2D(int x, int y);
	Vector2D& add(const Vector2D& vector);
	Vector2D& substract(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	bool operator!=(const Vector2D& vec);
	bool operator==(const Vector2D& vector);

	void zero();
	int x;
	int y;

};
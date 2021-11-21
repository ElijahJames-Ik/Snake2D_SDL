#pragma once

class Vector2D
{
public:
	Vector2D();	// default constructor
	Vector2D(int x, int y);
	Vector2D(const Vector2D& vector); // copy constructor
	Vector2D(Vector2D&& vector) noexcept; // move constructor
	Vector2D& operator=(const Vector2D& vector); // copy assignment
	Vector2D& operator=(Vector2D&& vector) noexcept; // move assignment
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
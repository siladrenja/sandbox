#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>
#include <mymath.hpp>

namespace myGL {

	template <typename T>
	struct Point {
		T x, y, z;
	};

	template <typename T>
	struct Rect {
		Point<T> TopLeft, BottomLeft, BottomRight, TopRight;
	};

	class Texture {

	};

	class Shader {

	};

	class GlSession {

	};
}

#pragma region point operators



template <typename T>
myGL::Point<T> operator+(const myGL::Point<T>& pointA, const myGL::Point<T>& pointB) {
	return {pointA.x + pointB.x, pointA.y + pointB.y, pointA.z + pointB.z };
}

template <typename T>
myGL::Point<T>& operator+=(myGL::Point<T>& pointA, const myGL::Point<T>& pointB) {
	return (pointA = { pointA.x + pointB.x, pointA.y + pointB.y, pointA.z + pointB.z });
}
template <typename T>
myGL::Point<T> operator-(const myGL::Point<T>& pointA, const myGL::Point<T>& pointB) {
	return { pointA.x - pointB.x, pointA.y - pointB.y, pointA.z - pointB.z };
}

template <typename T>
myGL::Point<T>& operator-=(myGL::Point<T>& pointA, const myGL::Point<T>& pointB) {
	return (pointA = { pointA.x - pointB.x, pointA.y - pointB.y, pointA.z - pointB.z });
}

template <typename T>
myGL::Point<T> operator*(const T& pointA, const myGL::Point<T>& pointB) {
	return { pointA * pointB.x, pointA * pointB.y, pointA * pointB.z };
}

template <typename T>
myGL::Point<T> operator*( const myGL::Point<T>& pointB, const T& pointA) {
	return { pointA * pointB.x, pointA * pointB.y, pointA * pointB.z };
}

template <typename T>
myGL::Point<T>& operator*=(myGL::Point<T>& pointB, const T& pointA) {
	return (pointB = { pointA * pointB.x, pointA * pointB.y, pointA * pointB.z });
}

#pragma endregion

#pragma region rect operators
template <typename T>
myGL::Rect<T> operator+(const myGL::Rect<T>& _1_rect, const myGL::Point<T>& _1_point) {
	return {_1_rect.TopLeft + _1_point, _1_rect.BottomLeft + _1_point, _1_rect.BottomRight + _1_point, _1_rect.TopRight + _1_point };
}
#pragma endregion
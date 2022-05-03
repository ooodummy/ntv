#ifndef _UTIL_UTIL_HPP_
#define _UTIL_UTIL_HPP_

#include <raylib.h>
#include <cmath>

namespace util {
	Vector2 rotate(Vector2 src, float angle, float radius);
	Vector2 rotate(Vector2 src, float angle);
}

#endif
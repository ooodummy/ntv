#include "util/util.hpp"

Vector2 util::rotate(Vector2 src, float angle, float radius) {
	return {
		src.x + std::cosf(angle) * radius,
		src.y + std::sinf(angle) * radius,
	};
}
Vector2 util::rotate(Vector2 src, float angle) {
	return {
		src.x * std::cosf(angle) - src.y * std::sinf(angle),
		src.x * std::sinf(angle) + src.y * std::cosf(angle),
	};
}

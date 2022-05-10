#include "util/util.hpp"

ImVec2 util::rotate(ImVec2 src, float angle, float radius) {
	return {
		src.x + std::cosf(angle) * radius,
		src.y + std::sinf(angle) * radius,
	};
}
ImVec2 util::rotate(ImVec2 src, float angle) {
	return {
		src.x * std::cosf(angle) - src.y * std::sinf(angle),
		src.x * std::sinf(angle) + src.y * std::cosf(angle),
	};
}

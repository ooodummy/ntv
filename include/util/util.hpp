#ifndef _UTIL_UTIL_HPP_
#define _UTIL_UTIL_HPP_

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#define IM_VEC2_CLASS_EXTRA                                                 \
        ImVec2(const glm::vec2& f) { x = f.x; y = f.y; }                       \
        operator glm::vec2() const { return glm::vec2(x,y); }

#define IM_VEC4_CLASS_EXTRA                                                 \
        ImVec4(const glm::vec4& f) { x = f.x; y = f.y; z = f.z; w = f.w; }     \
        operator glm::vec4() const { return glm::vec4(x,y,z,w); }

#include <hello_imgui/hello_imgui.h>

#include <cmath>
#include <optional>

namespace util {
	// https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
	[[nodiscard]] std::optional<std::vector<glm::vec2>> get_convex_hull(const std::vector<glm::vec2>& points);
}

#endif
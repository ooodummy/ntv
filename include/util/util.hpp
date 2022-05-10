#ifndef _UTIL_UTIL_HPP_
#define _UTIL_UTIL_HPP_

#include <hello_imgui/hello_imgui.h>
#include <cmath>

namespace util {
	ImVec2 rotate(ImVec2 src, float angle, float radius);
	ImVec2 rotate(ImVec2 src, float angle);
}

#endif
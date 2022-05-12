#include "util/util.hpp"

#include <algorithm>
#include <cstdlib>
#include <stack>

enum e_orientation {
	collinear,
	clockwise,
	counterclockwise
};

e_orientation get_orientation(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3) {
	// TODO: Forgot the name of the math function probably dot or something
	//  change this to the proper one
	auto v = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);

	if (v == 0.0f)
		return collinear;
	else if (v > 0.0f)
		return clockwise;
	else
		return counterclockwise;
}

// Global!!! :(
glm::vec2 p0;

int sort_compare(const void* v1, const void* v2) {
	auto* p1 = (glm::vec2*)v1;
	auto* p2 = (glm::vec2*)v2;

	const auto orientation = get_orientation(p0, *p1, *p2);

	if (orientation == collinear)
		return glm::distance(p0, *p2) >= glm::distance(p0, *p1) ? -1 : 1;
	else if (orientation == clockwise)
		return 1;
	else
		return -1;
}

template <class T>
T next_top(std::stack<T>& s) {
	T p = s.top();
	s.pop();
	T res = s.top();
	s.push(p);
	return res;
}

// Some very stupid things are done in this function, I'm in a rush...
std::optional<std::vector<glm::vec2>> util::get_convex_hull(const std::vector<glm::vec2>& points) {
	// Get the smallest y and if they match then smallest x too
	size_t min_y_id = 0;

	for (size_t i = 0; i < points.size(); i++) {
		const auto current = points[i];
		const auto min = points[min_y_id];

		// Compare if point is lower  or choose furthest
		// to the left in case of a tie
		if (current.y < min.y || (current.y == min.y && current.x <min.x)) {
			min_y_id = i;
		}
	}

	std::vector<glm::vec2> copy = points;

	std::swap(copy[0], copy[min_y_id]);

	p0 = copy[0];

	qsort(&copy[1], copy.size() - 1, sizeof(glm::vec2), sort_compare);

	size_t modified = 1;

	for (size_t i = 0; i < copy.size() - 1; i++) {
		while (i < copy.size() - 1 && get_orientation(p0, copy[i], copy[i + 1]) == collinear)
			i++;

		copy[modified] = copy[i];
		modified++;
	}

	// Check if convex hull is possible
	if (modified < 3)
		return {};

	std::stack<glm::vec2> s;

	for (size_t i = 0; i < 3; i++)
		s.push(copy[i]);

	for (size_t i = 3; i < modified; i++) {
		while (s.size() > 1 && get_orientation(next_top(s), s.top(), copy[i]) != counterclockwise)
			s.pop();

		s.push(copy[i]);
	}

	// So many vectors!
	std::vector<glm::vec2> hull;
	hull.reserve(s.size());

	while (!s.empty()) {
		hull.push_back(s.top());
		s.pop();
	}

	return hull;
}

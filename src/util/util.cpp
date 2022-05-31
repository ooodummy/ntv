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

template <class T>
T next_top(std::stack<T>& s) {
	T p = s.top();
	s.pop();
	T res = s.top();
	s.push(p);
	return res;
}

// Some very stupid things are done in this function, I'm in a rush...
std::vector<glm::vec2> util::get_convex_hull(std::vector<glm::vec2> points) {
	if (points.size() < 3)
		return {};

	// Get the smallest y and if they match then smallest x too
	float min_y = FLT_MAX;
	size_t min_y_id = 0;

	for (size_t i = 0; i < points.size(); i++) {
		const auto current = points[i];

		// Compare if point is lower  or choose furthest
		// to the left in case of a tie
		if (current.y < min_y || (current.y == min_y && current.x < min_y)) {
			min_y_id = i;
			min_y = current.y;
		}
	}

	std::swap(points[0], points[min_y_id]);

	auto p0 = points[0];

	sort(points.begin(), points.end(), [&p0](glm::vec2 a, glm::vec2 b){
		const auto orientation = get_orientation(p0, a, b);

		if (orientation == collinear)
			return glm::distance(p0, b) >= glm::distance(p0, a);
		else if (orientation == clockwise)
			return false;
		else
			return true;
	});

	size_t modified = 1;

	for (size_t i = 0; i < points.size(); i++) {
		while (i < points.size() - 1 && get_orientation(p0, points[i], points[i + 1]) == collinear)
			i++;

		points[modified] = points[i];
		modified++;
	}

	// Check if convex hull is possible
	if (modified < 3)
		return {};

	std::stack<glm::vec2> s;

	for (size_t i = 0; i < 3; i++)
		s.push(points[i]);

	for (size_t i = 3; i < modified; i++) {
		while (s.size() > 1 && get_orientation(next_top(s), s.top(), points[i]) != counterclockwise)
			s.pop();

		s.push(points[i]);
	}

	std::vector<glm::vec2> hull;
	hull.reserve(s.size());

	while (!s.empty()) {
		hull.push_back(s.top());
		s.pop();
	}

	return hull;
}

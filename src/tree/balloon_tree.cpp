#include "tree/balloon_tree.hpp"

void ntl::balloon_tree::compute_branch(ntl::node* item, const Vector2& pos, float radius, float branch_angle) const { // NOLINT(misc-no-recursion)
	item->limit_branches(max_branches_);

	const auto step = static_cast<float>(M_PI) * 2.0f / static_cast<float>(item->get_children().size() + 1.0f);

	float angle = /*((static_cast<float>(M_PI) * 2.0f) / static_cast<float>(item->get_children().size())) +*/ branch_angle + step - M_PI;
	for (auto& child : item->get_children()) {
		child->set_pos(util::rotate(pos, angle, radius));

		compute_branch(child.get(), child->get_pos(), radius / 2.0f, angle);

		angle += step;
	}
}

void ntl::balloon_tree::compute() {
	compute_branch(this, pos_, radius_, 0.0f);
}

void ntl::balloon_tree::set_radius(float radius) {
	radius_ = radius;
}

void ntl::balloon_tree::set_max_branches(size_t max_branches) {
	max_branches_ = max_branches;
}

#include "tree/balloon_tree.hpp"

// TODO: Actual good aspect ratio and angular resolution
void ntv::balloon_tree::compute_branch(ntv::node* item, const glm::vec2& pos, float radius, float branch_angle) const { // NOLINT(misc-no-recursion)
	item->limit_branches(max_branches_);

	auto segments = item->get_children().size();

	if (item->get_parent())
		segments += 1.0f;

	const auto step = static_cast<float>(M_PI) * 2.0f / static_cast<float>(segments);
	float angle = static_cast<float>(branch_angle) + step - static_cast<float>(M_PI);

	for (auto& child : item->get_children()) {
		child->set_pos(glm::rotate(glm::vec2(radius, 0.0f), angle) + pos);

		compute_branch(child.get(), child->get_pos(), radius / 2.0f, angle);

		angle += step;
	}
}

void ntv::balloon_tree::compute_impl() {
	compute_branch(this, pos_, radius_, 0.0f);
}

void ntv::balloon_tree::set_radius(float radius) {
	radius_ = radius;
}

void ntv::balloon_tree::set_max_branches(size_t max_branches) {
	max_branches_ = max_branches;
}

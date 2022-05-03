#include "tree/radial_tree.hpp"

void qtv::radial_tree::compute_branch(qtv::node* item, Vector2 pos, float angle_range, float angle, size_t depth) const {
	const auto size = item->get_children().size();

	auto child_angle_range = angle_range / static_cast<float>(size);

	size_t i = 0;
	for (auto& child : item->get_children()) {
		auto child_angle = angle + angle_range * static_cast<float>(i);

		auto child_pos = util::rotate({step_size_ * (static_cast<float>(depth) + 1.0f), 0.0f}, child_angle);
		child_pos.x += pos.x;
		child_pos.y += pos.y;

		compute_branch(child.get(), pos, child_angle_range, child_angle, depth + 1);

		i++;
	}
}

void qtv::radial_tree::compute() {
	compute_branch(this, get_pos(), M_PI * 2.0f, 0.0f, 0);
}
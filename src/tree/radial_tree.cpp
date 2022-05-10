#include "tree/radial_tree.hpp"

void ntv::radial_tree::compute_branch(ntv::node* item, ImVec2 pos, float angle_range, float angle, size_t depth) const { // NOLINT(misc-no-recursion)
	const auto child_angle_range = angle_range / static_cast<float>(item->get_children().size());
	float child_angle = item->get_parent() ? angle + (-angle_range + child_angle_range) / 2.0f : angle;

	for (auto& child : item->get_children()) {
		auto child_pos = util::rotate({step_size_ * (static_cast<float>(depth) + 1.0f), 0.0f}, child_angle);
		child_pos.x += pos.x;
		child_pos.y += pos.y;

		child->set_pos(child_pos);

		compute_branch(child.get(), pos, child_angle_range, child_angle, depth + 1);

		child_angle += child_angle_range;
	}
}

void ntv::radial_tree::compute() {
	compute_branch(this, get_pos(), M_PI * 2.0f, 0.0f, 0);
}

void ntv::radial_tree::set_step(float step) {
	step_size_ = step;
}

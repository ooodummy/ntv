#include "tree/balloon_tree.hpp"

void qtv::balloon_tree::compute_branch(qtv::node* item, const Vector2& pos, float radius) const { // NOLINT(misc-no-recursion)
	auto branch_nodes = static_cast<float>(item->get_children().size()) / static_cast<float>(max_branches_);

	if (branch_nodes > 1.0f) {
		auto children = std::move(item->get_children());

		auto branches = static_cast<int>(std::ceil(branch_nodes));

		size_t size = children.size();
		size_t copied = 0;

		for (size_t i = 0; i < branches; i++) {
			auto branch = item->add_child(std::make_unique<node>());
			branch->set_link(true);

			for (size_t j = 0; j < max_branches_; j++) {
				if (copied >= size)
					break;

				branch->add_child(std::move(children.back()));
				children.pop_back();

				copied++;
			}
		}
	}

	const auto step = static_cast<float>(M_PI) * 2.0f / static_cast<float>(item->get_children().size());

	float angle = 0.0f;
	for (auto& child : item->get_children()) {
		child->set_pos(util::rotate(pos, angle, radius));

		compute_branch(child.get(), child->get_pos(), radius / 2.0f);

		angle += step;
	}
}

void qtv::balloon_tree::compute() {
	compute_branch(this, pos_, radius_);
}

void qtv::balloon_tree::set_radius(float radius) {
	radius_ = radius;
}

void qtv::balloon_tree::set_max_branches(size_t max_branches) {
	max_branches_ = max_branches;
}

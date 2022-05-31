#include "tree/quad_tree.hpp"

void ntv::quad_tree::compute_branch(ntv::node* item, glm::vec2 pos, glm::vec2 size) { // NOLINT(misc-no-recursion)
	item->limit_branches(4);

	glm::vec2 radius = size / 2.0f;

	const glm::vec2 quads[4] = {
		{pos.x - radius.x, pos.y - radius.y},
		{pos.x + radius.x, pos.y - radius.y},
		{pos.x + radius.x, pos.y + radius.y},
		{pos.x - radius.x, pos.y + radius.y}
	};

	for (size_t i = 0; i < item->get_children().size(); i++) {
		auto& child = item->get_children()[i];

		child->set_pos(quads[i]);

		compute_branch(child.get(), child->get_pos(), radius);
	}
}

void ntv::quad_tree::compute_impl() {
	compute_branch(this, pos_, size_);
}

void ntv::quad_tree::set_size(glm::vec2 size) {
	size_ = size;
}

#include "tree/quad_tree.hpp"

void ntl::quad_tree::compute_branch(ntl::node* item, Vector2 pos, Vector2 size) { // NOLINT(misc-no-recursion)
	item->limit_branches(4);

	const Vector2 radius = { size.x / 2.0f, size.y / 2.0f };

	const Vector2 quads[4] = {
		{pos.x - radius.x, pos.y - radius.y},
		{pos.x + radius.x, pos.y - radius.y},
		{pos.x + radius.x, pos.y + radius.y},
		{pos.x - radius.x, pos.y + radius.y}
	};

	size_t i = 0;
	for (auto& child : item->get_children()) {
		child->set_pos(quads[i]);

		compute_branch(child.get(), child->get_pos(), radius);

		i++;
	}
}

void ntl::quad_tree::compute() {
	compute_branch(this, pos_, size_);
}

void ntl::quad_tree::set_size(Vector2 size) {
	size_ = size;
}

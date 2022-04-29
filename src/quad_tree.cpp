#include "quad_tree.hpp"

void qtv::quad_item::draw() {
	DrawRectangleRec(bounds, RED);
}

void qtv::quad_item::draw_contents() {
	draw();
}

void qtv::quad_item::set_parent(qtv::quad_node* parent) {
	parent_ = parent;
}

qtv::quad_node* qtv::quad_item::get_parent() const {
	return parent_;
}

qtv::quad_node* qtv::quad_item::get_top_parent() const {
	if (!parent_)
		return nullptr;

	for (auto parent = parent_;; parent = parent->get_parent()) {
		if (!parent->get_parent())
			return parent;
	}
}

void qtv::quad_node::draw_contents() { // NOLINT(misc-no-recursion)
	draw();

	for (auto& leaf : leafs_) {
		draw_contents();
	}
}

void qtv::quad_node::add_item(std::unique_ptr<quad_item> item) {
	item->set_parent(this);
	items_.push_back(std::move(item));
}

void qtv::quad_node::create_leafs() {
	const Vector2 half = { bounds.width / 2.0f, bounds.height / 2.0f };
	const Vector2 center = { bounds.x + half.x, bounds.y + half.y };

	const Vector2 segments[4] = {
		{ bounds.x, bounds.y },
		{ bounds.x + half.x, bounds.y },
		{ bounds.x, bounds.y + half.y },
		{ bounds.x + half.x, bounds.y + half.y }
	};

	for (size_t i = 0; i < leafs_.size(); i++) {
		auto& quad = leafs_[i];

		// How much time would be lost by iterating through parents to find the root?
		quad = std::make_unique<quad_node>();
		quad->set_parent(this);

		const auto& pos = segments[i];
		quad->bounds = { pos.x, pos.y, half.x, half.y };
	}
}
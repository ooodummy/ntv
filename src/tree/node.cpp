#include "tree/node.hpp"

/*std::string qtv::item::get_title() {
	return "";
}

std::vector<std::string> qtv::item::get_descriptors() {
	return {};
}*/

void qtv::node::set_parent(qtv::node* parent) {
	parent_ = parent;
}

qtv::node* qtv::node::get_parent() const {
	return parent_;
}

qtv::node* qtv::node::get_top_parent() const {
	if (!parent_)
		return nullptr;

	for (auto parent = parent_;; parent = parent->get_parent()) {
		if (!parent->get_parent())
			return parent;
	}
}

qtv::node* qtv::node::add_child(std::unique_ptr<node> item) {
	item->set_parent(this);
	children_.push_back(std::move(item));
	return children_.back().get();
}

std::vector<std::unique_ptr<qtv::node>>& qtv::node::get_children() {
	return children_;
}

void qtv::node::set_link(bool link) {
	is_link_ = link;
}

bool qtv::node::get_link() const {
	return is_link_;
}

void qtv::node::set_pos(Vector2 pos) {
	pos_ = pos;
}

Vector2 qtv::node::get_pos() const {
	return pos_;
}

void draw_node(qtv::node* item) { // NOLINT(misc-no-recursion)
	for (auto& child : item->get_children()) {
		draw_node(child.get());
	}

	auto parent = item->get_parent();
	if (parent != nullptr)
		DrawLineV(parent->get_pos(), item->get_pos(), YELLOW);

	DrawCircleV(item->get_pos(), 5, item->get_link() ? BLUE : RED);
}

void qtv::tree::draw() {
	draw_node(this);
}

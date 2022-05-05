#include "tree/node.hpp"

/*std::string ntl::item::get_title() {
	return "";
}

std::vector<std::string> ntl::item::get_descriptors() {
	return {};
}*/

void ntl::node::set_parent(ntl::node* parent) {
	parent_ = parent;
}

ntl::node* ntl::node::get_parent() const {
	return parent_;
}

ntl::node* ntl::node::get_top_parent() const {
	if (!parent_)
		return nullptr;

	for (auto parent = parent_;; parent = parent->get_parent()) {
		if (!parent->get_parent())
			return parent;
	}
}

ntl::node* ntl::node::add_child(std::unique_ptr<node> item) {
	item->set_parent(this);
	children_.push_back(std::move(item));
	return children_.back().get();
}

std::vector<std::unique_ptr<ntl::node>>& ntl::node::get_children() {
	return children_;
}

void ntl::node::set_link(bool link) {
	is_link_ = link;
}

bool ntl::node::get_link() const {
	return is_link_;
}

void ntl::node::set_pos(Vector2 pos) {
	pos_ = pos;
}

Vector2 ntl::node::get_pos() const {
	return pos_;
}

// I think this needs some improvements
void ntl::node::limit_branches(size_t max) {
	if (max <= 0)
		return;

	auto aspect = static_cast<float>(get_children().size()) / static_cast<float>(max);

	if (aspect > 1.0f) {
		auto children = std::move(get_children());
		auto floor = static_cast<int>(std::floorf(aspect));

		size_t size = children.size();
		size_t copied = 0;

		for (size_t i = 0; i < max; i++) {
			auto branch = add_child(std::make_unique<node>());
			branch->set_link(true);

			for (size_t j = 0; j < floor || i == max - 1; j++) {
				if (copied >= size)
					break;

				branch->add_child(std::move(children.back()));
				children.pop_back();

				copied++;
			}
		}
	}
}

void draw_node(ntl::node* item) { // NOLINT(misc-no-recursion)
	for (auto& child : item->get_children()) {
		draw_node(child.get());
	}

	auto parent = item->get_parent();
	if (parent != nullptr)
		DrawLineV(parent->get_pos(), item->get_pos(), YELLOW);

	DrawCircleV(item->get_pos(), 5, item->get_link() ? BLUE : RED);
}

void ntl::tree::draw() {
	draw_node(this);
}

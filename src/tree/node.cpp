#include "tree/node.hpp"

void ntv::item::set_label(const std::string& label) {
	label_ = label;
}

const std::string& ntv::item::get_label() const {
	return label_;
}

void ntv::node::set_parent(ntv::node* parent) {
	parent_ = parent;
}

ntv::node* ntv::node::get_parent() const {
	return parent_;
}

ntv::node* ntv::node::get_top_parent() const {
	if (!parent_)
		return nullptr;

	for (auto parent = parent_;; parent = parent->get_parent()) {
		if (!parent->get_parent())
			return parent;
	}
}

ntv::node* ntv::node::add_node(std::unique_ptr<node> item) {
	item->set_parent(this);
	children_.push_back(std::move(item));
	return children_.back().get();
}

ntv::node* ntv::node::make_node() {
	return add_node(std::make_unique<ntv::node>());
}

void ntv::node::remove_node(size_t index) {
	children_.erase(children_.begin() + static_cast<int>(index));
}

std::vector<std::unique_ptr<ntv::node>>& ntv::node::get_children() {
	return children_;
}

void ntv::node::set_link(bool link) {
	is_link_ = link;
}

bool ntv::node::get_link() const {
	return is_link_;
}

void ntv::node::set_pos(ImVec2 pos) {
	pos_ = pos;
}

ImVec2 ntv::node::get_pos() const {
	return pos_;
}

// I think this needs some improvements
void ntv::node::limit_branches(size_t max) {
	if (max <= 0)
		return;

	auto aspect = static_cast<float>(get_children().size()) / static_cast<float>(max);

	if (aspect > 1.0f) {
		auto children = std::move(get_children());
		auto floor = static_cast<int>(std::floorf(aspect));

		size_t size = children.size();
		size_t copied = 0;

		for (size_t i = 0; i < max; i++) {
			auto branch = add_node(std::make_unique<node>());
			branch->set_link(true);

			for (size_t j = 0; j < floor || i == max - 1; j++) {
				if (copied >= size)
					break;

				branch->add_node(std::move(children.back()));
				children.pop_back();

				copied++;
			}
		}
	}
}

void ntv::node::compute() {
	tree* root;

	// TODO: Could maybe not be tree type
	if (get_parent() == nullptr) {
		root = static_cast<ntv::tree*>(this);
	}
	else {
		root = static_cast<ntv::tree*>(this->get_top_parent());
	}

	root->compute();
}

void draw_node(ntv::node* item) { // NOLINT(misc-no-recursion)
	for (auto& child : item->get_children()) {
		draw_node(child.get());
	}

	auto draw_list = ImGui::GetWindowDrawList();

	auto parent = item->get_parent();
	if (parent != nullptr)
		draw_list->AddLine(parent->get_pos(), item->get_pos(), ImColor(255, 0, 255));

	draw_list->AddCircleFilled(item->get_pos(), 5.0f, item->get_link() ? ImColor(0, 0, 255) : ImColor(255, 0, 0));
}

void ntv::tree::draw() {
	draw_node(this);
}

// https://cs.brown.edu/people/rtamassi/gdhandbook/chapters/trees.pdf
// 5.1.12
ntv::tree::aesthetic_properties_t ntv::tree::get_aesthetic_properties() {
	aesthetic_properties_t ret{};

	float total_nodes;
	ImVec2 min_pos = {FLT_MAX, FLT_MAX};
	ImVec2 max_pos = {FLT_MIN, FLT_MIN};

	auto gather_info = [&](ntv::node* item) -> void {
		auto impl_gather_info = [&](ntv::node* item, auto self_ref, const std::string& id = "", ntv::node* parent = nullptr, size_t index = 0) mutable -> void {// NOLINT(misc-no-recursion)
			for (auto& child : item->get_children()) {
				total_nodes++;
				auto pos = child->get_pos();
				min_pos.x = std::min(min_pos.x, pos.x);
				min_pos.y = std::min(min_pos.y, pos.y);
				max_pos.x = std::max(max_pos.x, pos.x);
				max_pos.y = std::max(max_pos.y, pos.y);

				self_ref(child.get(), self_ref);
			}
		};

		impl_gather_info(item, impl_gather_info);
	};

	gather_info(this);

	gather_info_impl(this, gather_info_impl);

	return ntv::tree::aesthetic_properties_t();
}

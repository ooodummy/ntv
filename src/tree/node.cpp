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

void ntv::node::set_pos(glm::vec2 pos) {
	pos_ = pos;
}

glm::vec2 ntv::node::get_pos() const {
	return pos_;
}

// I think this needs some improvements
void ntv::node::limit_branches(size_t max) {
	if (max <= 0)
		return;

	auto aspect = static_cast<float>(get_children().size()) / static_cast<float>(max);

	if (aspect > 1.0f) {
		auto children = std::move(get_children());
		auto floor = static_cast<int>(floorf(aspect));

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

void ntv::node::compute_impl() { // NOLINT(misc-no-recursion)
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

void ntv::node::compute() { // NOLINT(misc-no-recursion)
	compute_impl();
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

glm::vec4 ntv::tree::get_bounds(const std::vector<glm::vec2>& points) {
	glm::vec2 min_pos = {FLT_MAX, FLT_MAX};
	glm::vec2 max_pos = {FLT_MIN, FLT_MIN};

	for (const auto& point : points) {
		min_pos.x = std::min(min_pos.x, point.x);
		min_pos.y = std::min(min_pos.y, point.y);
		max_pos.x = std::max(max_pos.x, point.x);
		max_pos.y = std::max(max_pos.y, point.y);
	}

	return {
		min_pos.x,
		min_pos.y,
		max_pos.x - min_pos.x,
		max_pos.y - min_pos.y
	};
}

const ntv::tree::aesthetic_properties_t& ntv::tree::get_aesthetic_properties() const {
	return aesthetic_properties;
}

// https://cs.brown.edu/people/rtamassi/gdhandbook/chapters/trees.pdf 5.1.12
void ntv::tree::compute_aesthetic_properties() {
	size_t total_nodes = 0;
	std::vector<glm::vec2> points;

	glm::vec2 min_pos = {FLT_MAX, FLT_MAX};
	glm::vec2 max_pos = {FLT_MIN, FLT_MIN};

	const auto root_pos = get_pos();

	aesthetic_properties.closest_leaf = FLT_MAX;
	aesthetic_properties.furthest_leaf = FLT_MIN;
	aesthetic_properties.total_edge_length = 0.0f;
	aesthetic_properties.maximum_edge_length = FLT_MIN;

	auto gather_info = [&](ntv::node* item) -> void {
		auto impl_gather_info = [&](ntv::node* item, auto self_ref, const std::string& id = "", ntv::node* parent = nullptr, size_t index = 0) mutable -> void {// NOLINT(misc-no-recursion)
			const auto parent_pos = item->get_pos();

			for (auto& child : item->get_children()) {
				const auto pos = child->get_pos();

				const auto leaf_distance = glm::distance(root_pos, pos);
				aesthetic_properties.closest_leaf = std::min(aesthetic_properties.closest_leaf, leaf_distance);
				aesthetic_properties.furthest_leaf = std::max(aesthetic_properties.furthest_leaf, leaf_distance);

				const auto edge_length = glm::distance(parent_pos, pos);
				aesthetic_properties.total_edge_length += edge_length;
				aesthetic_properties.maximum_edge_length = std::max(aesthetic_properties.maximum_edge_length, edge_length);

				points.push_back(pos);
				self_ref(child.get(), self_ref);

				total_nodes++;
			}
		};

		impl_gather_info(item, impl_gather_info);
	};

	gather_info(this);

	aesthetic_properties.average_edge_length = aesthetic_properties.total_edge_length / total_nodes;

	// This feels like a huge waste of CPU time since we are already iterating the nodes
	aesthetic_properties.bounds = get_bounds(points);

	aesthetic_properties.hull = util::get_convex_hull(points);

	// Calculate area
	aesthetic_properties.area = 0.0f;

	if (!aesthetic_properties.hull.empty()) {
		const auto hull_bounds = get_bounds(aesthetic_properties.hull);
		const glm::vec2 hull_center = { hull_bounds.x + hull_bounds.w / 2.0f, hull_bounds.y + hull_bounds.z / 2.0f };

		// Create a triangle fan and calculate the size of each fan then use the sum for the hulls area
		auto it = aesthetic_properties.hull.begin();

		while (it != aesthetic_properties.hull.end()) {
			auto nx = std::next(it, 1);

			if (nx == aesthetic_properties.hull.end())
				break;

			auto fan_area = std::abs(hull_center.x * (it->y - nx->y) + it->x * (nx->y - hull_center.y) + nx->x * (hull_center.y - it->y)) / 2.0f;
			aesthetic_properties.area += fan_area;

			it = std::next(nx, 1);
		}
	}

	// Calculate Symmetry

}
void ntv::tree::compute() { // NOLINT(misc-no-recursion)
	compute_impl();
	compute_aesthetic_properties();
}
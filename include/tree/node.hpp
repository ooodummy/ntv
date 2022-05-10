#ifndef _TREE_NODE_HPP_
#define _TREE_NODE_HPP_

#include "../util/util.hpp"

#define M_PI 3.14159265358979323846
#include <vector>
#include <memory>
#include <string>

// https://cs.brown.edu/people/rtamassi/gdhandbook/chapters/trees.pdf

namespace ntv {
	class item {
	public:
		void set_label(const std::string& label);
		const std::string& get_label() const;

		//const std::vector<std::string>& get_descriptors();

	protected:
		std::string label_ = "Undefined";
	};

	class node : public item {
	public:
		void set_parent(node* parent);
		[[nodiscard]] node* get_parent() const;
		[[nodiscard]] node* get_top_parent() const;

		node* add_node(std::unique_ptr<node> item);
		node* make_node();

		void remove_node(size_t index);

		std::vector<std::unique_ptr<node>>& get_children();

		void limit_branches(size_t max);

		virtual void compute();

		void set_link(bool link);
		[[nodiscard]] bool get_link() const;

		void set_pos(ImVec2 pos);
		[[nodiscard]] ImVec2 get_pos() const;

	protected:
		node* parent_;
		std::vector<std::unique_ptr<node>> children_;

		// Used for positioning some tree layout types
		bool is_link_ = false;

		// !!!
	public:
		ImVec2 pos_;
		ImVec2 velocity_;
	};

	class tree : public node {
	public:
		virtual void draw();

		struct aesthetic_properties_t {
			float area;
			float aspect_ratio;
			float subtree_separation;
			float closest_leaf;
			float furthest_leaf;
			float size;
			float total_edge_length;
			float average_edge_length;
			float maximum_edge_length;
			float uniform_edge_length;
			float angular_resolution;
			float symmetry;
		};

		aesthetic_properties_t get_aesthetic_properties();
	};
}

#endif
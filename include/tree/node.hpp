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
		[[nodiscard]] const std::string& get_label() const;

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

		virtual void compute_impl();
		virtual void compute();

		void set_link(bool link);
		[[nodiscard]] bool get_link() const;

		void set_pos(glm::vec2 pos);
		[[nodiscard]] glm::vec2 get_pos() const;

	protected:
		node* parent_;
		std::vector<std::unique_ptr<node>> children_;

		// Used for positioning some tree layout types
		bool is_link_ = false;

		// !!!
	public:
		glm::vec2 pos_;
		glm::vec2 velocity_;
	};

	class tree : public node {
	public:
		void compute() override;

		virtual void draw();

		struct aesthetic_properties_t {
			std::vector<glm::vec2> hull;
			glm::vec4 bounds;

			// Convex hull area of all the points
			// Or it will just be the size
			float area;
			float aspect_ratio;
			float subtree_separation;
			float closest_leaf;
			float furthest_leaf;
			float length;
			float total_edge_length;
			float average_edge_length;
			float maximum_edge_length;
			float uniform_edge_length;
			float angular_resolution;
			float symmetry;
		};

		const aesthetic_properties_t& get_aesthetic_properties() const;

	private:
		static glm::vec4 get_bounds(const std::vector<glm::vec2>& points);
		void compute_aesthetic_properties();

		aesthetic_properties_t aesthetic_properties;
	};
}

#endif
#ifndef _TREE_NODE_HPP_
#define _TREE_NODE_HPP_

#include "../util/util.hpp"

#define M_PI 3.14159265358979323846
#include <vector>
#include <memory>
#include <string>

namespace qtv {
	class item {
	public:
		//std::string get_title();
		//std::vector<std::string> get_descriptors();
	};

	class node : public item {
	public:
		void set_parent(node* parent);
		[[nodiscard]] node* get_parent() const;
		[[nodiscard]] node* get_top_parent() const;

		node* add_child(std::unique_ptr<node> item);
		std::vector<std::unique_ptr<node>>& get_children();

		void set_link(bool link);
		[[nodiscard]] bool get_link() const;

		void set_pos(Vector2 pos);
		[[nodiscard]] Vector2 get_pos() const;

	protected:
		node* parent_;
		std::vector<std::unique_ptr<node>> children_;

		// Used for positioning some tree layout types
		bool is_link_ = false;

		Vector2 pos_;
	};

	class tree : public node {
	public:
		virtual void compute() = 0;
		virtual void draw();
	};
}

#endif
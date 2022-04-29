#ifndef _QUAD_TREE_HPP_
#define _QUAD_TREE_HPP_

#include <vector>
#include <memory>
#include <array>

#include <raylib.h>

namespace qtv {
	class quad_node;

	class quad_item {
	public:
		virtual void draw();
		virtual void draw_contents();

		void set_parent(quad_node* parent);
		[[nodiscard]] quad_node* get_parent() const;
		[[nodiscard]] quad_node* get_top_parent() const;

		Rectangle bounds{};
		size_t connections{};

	protected:
		quad_node* parent_{};
	};

	class quad_node : public quad_item {
	public:
		void draw_contents() override;

		void add_item(std::unique_ptr<quad_item> item);

	private:
		void create_leafs();

		std::array<std::unique_ptr<quad_node>, 4> leafs_;
		std::vector<std::unique_ptr<quad_item>> items_;
	};
}

#endif
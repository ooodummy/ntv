#ifndef _TREE_QUAD_TREE_HPP_
#define _TREE_QUAD_TREE_HPP_

#include "node.hpp"

namespace ntl {
	class quad_tree : public tree {
	public:
		void compute() override;

		void set_size(Vector2 size);

	private:
		void compute_branch(node* item, Vector2 pos, Vector2 size);

		Vector2 size_{};
	};
}

#endif
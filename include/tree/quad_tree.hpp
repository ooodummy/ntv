#ifndef _TREE_QUAD_TREE_HPP_
#define _TREE_QUAD_TREE_HPP_

#include "node.hpp"

namespace ntv {
	class quad_tree : public tree {
	public:
		void compute() override;

		void set_size(ImVec2 size);

	private:
		void compute_branch(node* item, ImVec2 pos, ImVec2 size);

		ImVec2 size_{};
	};
}

#endif
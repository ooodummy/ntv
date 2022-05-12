#ifndef _TREE_QUAD_TREE_HPP_
#define _TREE_QUAD_TREE_HPP_

#include "node.hpp"

namespace ntv {
	class quad_tree : public tree {
	public:
		void compute() override;

		void set_size(glm::vec2 size);

	private:
		void compute_branch(node* item, glm::vec2 pos, glm::vec2 size);

		glm::vec2 size_{};
	};
}

#endif
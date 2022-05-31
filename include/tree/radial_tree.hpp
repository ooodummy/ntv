#ifndef _TREE_RADIAL_TREE_HPP_
#define _TREE_RADIAL_TREE_HPP_

#include "node.hpp"

namespace ntv {
	// https://stackoverflow.com/questions/33328245/radial-tree-layout-algorithm
	class radial_tree : public tree {
	public:
		void compute_impl() override;

		void set_step(float step);

	private:
		void compute_branch(node* item, glm::vec2 pos, float angle_range, float angle, size_t depth) const;

		float step_size_{};
	};
}

#endif
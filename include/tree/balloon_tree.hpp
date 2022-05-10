#ifndef _TREE_BALLOON_TREE_HPP_
#define _TREE_BALLOON_TREE_HPP_

#include "node.hpp"

namespace ntv {
	// https://jgaa.info/accepted/2007/LinYen2007.11.2.pdf
	class balloon_tree : public tree {
	public:
		void compute() override;

		void set_radius(float radius);
		void set_max_branches(size_t max_branches);

	private:
		void compute_branch(node* item, const ImVec2& pos, float radius, float branch_angle) const;

		float radius_{};
		size_t max_branches_ = 0;
	};
}

#endif
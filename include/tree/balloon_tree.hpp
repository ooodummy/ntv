#ifndef _TREE_BALLOON_TREE_HPP_
#define _TREE_BALLOON_TREE_HPP_

#include "node.hpp"

namespace qtv {
	// Example https://imgur.com/sVSLopo

	// TODO:
	//  Set child balloon radius to be proper instead of just half
	//  Also change the angle to not just be using step for when some children have another radius
	class balloon_tree : public tree {
	public:
		void compute() override;

		void set_radius(float radius);
		void set_max_branches(size_t max_branches);

	private:
		void compute_branch(node* item, const Vector2& pos, float radius) const;

		float radius_{};
		size_t max_branches_ = 0;
	};
}

#endif
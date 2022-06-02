#ifndef _TREE_ADVANCED_HPP_
#define _TREE_ADVANCED_HPP_

#include "node.hpp"

namespace ntv {
	// https://jgaa.info/accepted/2007/LinYen2007.11.2.pdf
	class advanced_tree : public tree {
	public:
		void compute_impl() override;

		void set_radius(float radius);

	private:
		void compute_branch(node* item, const glm::vec2& pos, float radius, float branch_angle) const;

		float radius_{};
	};
}

#endif
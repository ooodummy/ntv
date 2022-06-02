#include "tree/advanced.hpp"

void ntv::advanced_tree::compute_branch(ntv::node* item, const glm::vec2& pos, float radius, float branch_angle) const {

}

void ntv::advanced_tree::compute_impl() {
	compute_branch(this, pos_, radius_, 0.0f);
}

void ntv::advanced_tree::set_radius(float radius) {
	radius_ = radius;
}

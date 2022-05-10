#ifndef _TEST_HPP_
#define _TEST_HPP_

#include <memory>

#include "tree/balloon_tree.hpp"
#include "tree/quad_tree.hpp"
#include "tree/radial_tree.hpp"

namespace ntv {
	template <class TreeType>
	std::unique_ptr<TreeType> make_test_tree() {
		auto root = std::make_unique<TreeType>();

		auto node1 = root->make_node();
		node1->make_node();
		node1->make_node();
		auto node13 = node1->make_node();
		auto node131 = node13->make_node();
		node131->make_node();
		node131->make_node();
		node13->make_node();
		node13->make_node();
		root->make_node();
		auto node3 = root->make_node();
		node3->make_node();
		node3->make_node();
		auto node4 = root->make_node();
		node4->make_node();
		node4->make_node();
		node4->make_node();
		node4->make_node();
		auto node5 = root->make_node();
		auto node51 = node5->make_node();
		node51->make_node();
		root->make_node();
		auto node7 = root->make_node();
		node7->make_node();
		auto node8 = root->make_node();
		auto node81 = node8->make_node();
		auto node811 = node81->make_node();
		node811->make_node();
		node811->make_node();
		node811->make_node();
		node811->make_node();
		node811->make_node();
		node81->make_node();
		root->make_node();

		return root;
	}
}

#endif
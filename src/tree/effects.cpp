#include "tree/effects.hpp"

#include "tree/node.hpp"

void ntv::apply_effects(ntv::node* item) { // NOLINT(misc-no-recursion)
	// TODO: Move them around randomly
	//const auto dt = GetFrameTime();

	for (auto& child : item->get_children()) {
		apply_effects(child.get());
	}
}

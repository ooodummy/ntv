#include "tree/effects.hpp"

void ntl::apply_effects(ntl::node* item) { // NOLINT(misc-no-recursion)
	// TODO: Move them around randomly
	const auto dt = GetFrameTime();

	for (auto& child : item->get_children()) {
		apply_effects(child.get());
	}
}

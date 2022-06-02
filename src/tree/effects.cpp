#include "tree/effects.hpp"

#include "tree/node.hpp"

constexpr float time_scale = 1.0f;

void ntv::apply_effects(ntv::node* item) { // NOLINT(misc-no-recursion)
	// TODO: Move them around randomly
	auto dt = ImGui::GetIO().DeltaTime;
	dt *= time_scale;

	for (auto& child : item->get_children()) {
		apply_effects(child.get());
	}
}

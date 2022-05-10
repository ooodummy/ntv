#include "tree/balloon_tree.hpp"
#include "tree/quad_tree.hpp"
#include "tree/radial_tree.hpp"

#include "test.hpp"

#include <fmt/format.h>

#undef main
int main() {
	auto tree = ntv::make_test_tree<ntv::radial_tree>();
	tree->set_label("Primary");
	tree->set_pos({300, 200});
	//tree->set_size({500, 500});
	tree->set_step(40.0f);
	//tree->set_radius(150.0f);
	//tree->set_max_branches(6);

	tree->compute();

	HelloImGui::Run([&]{
		tree->draw();

		if (ImGui::Begin("Settings")) {
			if (ImGui::CollapsingHeader("Node list")) {
				auto add_node_settings = [](ntv::node* item) -> void {
					auto impl_add_node_settings = [](ntv::node* item, auto self_ref, const std::string& id = "", ntv::node* parent = nullptr, size_t index = 0) mutable -> void {// NOLINT(misc-no-recursion)
						if (ImGui::CollapsingHeader(fmt::format("{} - {}##main_header{}", item->get_label(), item->get_children().size(), id).c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
							if (!parent) {
								if (ImGui::Button(fmt::format("Compute##compute_button{}", id).c_str())) {
									item->compute();
								}
								ImGui::Text("Position");
								ImGui::SameLine();
								ImGui::PushItemWidth(100.0f);
								if (ImGui::InputFloat(fmt::format("##input_x_pos{}", id).c_str(), &item->pos_.x)) {
									item->compute();
								}
								ImGui::SameLine();
								if (ImGui::InputFloat(fmt::format("##input_y_pos{}", id).c_str(), &item->pos_.y)) {
									item->compute();
								}
								ImGui::PopItemWidth();
							}
							if (ImGui::Button(fmt::format("Add##add_button{}", id).c_str())) {
								item->make_node();
								item->compute();
							}
							if (parent) {
								ImGui::SameLine();
								if (ImGui::Button(fmt::format("Delete##delete_button{}", id).c_str())) {
									parent->remove_node(index);
									parent->compute();
								}
							}
							ImGui::Indent(12.0f);
							for (size_t i = 0; i < item->get_children().size(); i++) {
								auto& child = item->get_children()[i];

								self_ref(child.get(), self_ref, id + std::to_string(i), item, i);
							}
							ImGui::Unindent(12.0f);
						}
					};

					impl_add_node_settings(item, impl_add_node_settings);
				};

				add_node_settings(tree.get());
			}
			ImGui::End();
		}

		ImGui::ShowDemoWindow();
	}, {720.0f, 480.0f}, "Node tree view");

	return 0;
}
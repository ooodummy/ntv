#include "format.hpp"
#include "quad_tree.hpp"

#include <raylib.h>

int main() {
	InitWindow(720, 480, "Quad tree view");

	auto root = std::make_unique<qtv::quad_node>();
	root->add_item(std::make_unique<qtv::quad_item>());

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawFPS(0.0f, 0.0f);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
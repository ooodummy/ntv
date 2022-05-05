#include "tree/balloon_tree.hpp"
#include "tree/radial_tree.hpp"

#include <raylib.h>

void process_movement(Camera2D& camera) {
	if (IsKeyDown(KEY_RIGHT)) camera.target.x += 2;
	if (IsKeyDown(KEY_LEFT)) camera.target.x -= 2;
	if (IsKeyDown(KEY_DOWN)) camera.target.y += 2;
	if (IsKeyDown(KEY_UP)) camera.target.y -= 2;

	if (IsKeyDown(KEY_A)) camera.rotation--;
	if (IsKeyDown(KEY_S)) camera.rotation++;

	camera.zoom += ((float)GetMouseWheelMove()*0.05f);

	if (camera.zoom > 3.0f) camera.zoom = 3.0f;
	else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

	if (IsKeyPressed(KEY_R)) {
		camera.zoom = 1.0f;
		camera.rotation = 0.0f;
	}
}

int main() {
	auto root = std::make_unique<qtv::radial_tree>();
	root->set_pos({300, 200});
	root->set_step(40.0f);
	/*root->set_radius(150.0f);
	root->set_max_branches(5);*/

	auto node1 = root->add_child(std::make_unique<qtv::node>());
	node1->add_child(std::make_unique<qtv::node>());
	node1->add_child(std::make_unique<qtv::node>());
	auto node13 = node1->add_child(std::make_unique<qtv::node>());
	auto node131 = node13->add_child(std::make_unique<qtv::node>());
	node131->add_child(std::make_unique<qtv::node>());
	node131->add_child(std::make_unique<qtv::node>());
	node13->add_child(std::make_unique<qtv::node>());
	node13->add_child(std::make_unique<qtv::node>());
	root->add_child(std::make_unique<qtv::node>());
	root->add_child(std::make_unique<qtv::node>());
	auto node4 = root->add_child(std::make_unique<qtv::node>());
	node4->add_child(std::make_unique<qtv::node>());
	node4->add_child(std::make_unique<qtv::node>());
	node4->add_child(std::make_unique<qtv::node>());
	node4->add_child(std::make_unique<qtv::node>());
	auto node5 = root->add_child(std::make_unique<qtv::node>());
	auto node51 = node5->add_child(std::make_unique<qtv::node>());
	node51->add_child(std::make_unique<qtv::node>());
	root->add_child(std::make_unique<qtv::node>());
	auto node7 = root->add_child(std::make_unique<qtv::node>());
	node7->add_child(std::make_unique<qtv::node>());
	root->add_child(std::make_unique<qtv::node>());
	root->add_child(std::make_unique<qtv::node>());

	root->compute();

	InitWindow(720, 480, "Node tree layout");

	Camera2D camera = {
		{0.0f, 0.0f},
		{0.0f, 0.0f},
		0.0f,
		1.0f
	};

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		process_movement(camera);

		BeginDrawing();

		ClearBackground(BLACK);

		BeginMode2D(camera);

		root->draw();

		EndMode2D();

		DrawFPS(0.0f, 0.0f);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
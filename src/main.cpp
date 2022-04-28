#include "tree.hpp"

#include <raylib.h>

int main() {
	InitWindow(720, 480, "Quad tree view");

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(RAYWHITE);


		EndDrawing();
	}

	CloseWindow();

	return 0;
}
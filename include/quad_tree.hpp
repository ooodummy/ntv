#ifndef _QUAD_TREE_HPP_
#define _QUAD_TREE_HPP_

#include <vector>
#include <memory>

#include <raylib.h>

namespace net {
	class item {
		Vector4 bounds;

		virtual void draw() = 0;
	};

	class node {
		

	private:
		std::vector<std::unique_ptr<item>> children_;
	};
}

#endif